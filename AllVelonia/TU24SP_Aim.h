#ifndef TU24SP_AIM_H
#define TU24SP_AIM_H

namespace TU24SP
{
	inline void FixMovement(usercmd_s pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove)
	{
		const auto deltaView = CurAngle - OldAngle;
		auto forward = static_cast<int>(cos(deltaView * (3.14159265358979323846264338327950288f / 180.0f)) * fOldForward
			+ cos(
				(deltaView + 90.f) * (3.14159265358979323846264338327950288f / 180.0f)) * fOldSidemove);
		auto right = static_cast<int>(sin(deltaView * (3.14159265358979323846264338327950288f / 180.0f)) * fOldForward +
			sin(
				(deltaView + 90.f) * (3.14159265358979323846264338327950288f / 180.0f)) * fOldSidemove);

		if (forward < -128) forward = -128;
		else if (forward > 127) forward = 127;
		if (right < -128) right = -128;
		else if (right > 127) right = 127;

		pCmd.forwardmove = static_cast<char>(forward);
		pCmd.rightmove = static_cast<char>(right);
	}

	inline void AimSilent(usercmd_s oldCommand, Vector3 toAngle)
	{
		const auto oldAngle = SHORT2ANGLE(oldCommand.angles[1]);
		oldCommand.angles[0] = ANGLE2SHORT(toAngle.x);
		oldCommand.angles[1] = ANGLE2SHORT(toAngle.y);
		FixMovement(oldCommand, SHORT2ANGLE(oldCommand.angles[1]), oldAngle, oldCommand.forwardmove, oldCommand.rightmove);
	}

	inline bool playerVisible(int unknown, char* Tag)
	{
		trace_t trace;
		auto headPos = GetTagPos(unknown, Tag);
		auto eyePos = cg.refdef.Origin;
		CG_LocationalTrace(&trace, &eyePos, &headPos, cg.clientNum, 0x803003);
		return trace.fraction >= 0.95f;
	}

	inline void setupBulletTrace(BulletFireParams* bp, Vector3 start, Vector3 end)
	{
		bp->weaponEntIndex = 0x7FE;
		bp->ignoreEntIndex = cg.clientNum;
		bp->damageMultiplier = 1;
		bp->methodOfDeath = MOD_RIFLE_BULLET;
		bp->origStart = cg.refdef.Origin;
		bp->start = start;
		bp->end = end;

		auto delta = end - start;

		Vector3 angles;
		VectorAngles(delta, angles);
		bp->dir = delta;
	}

	inline bool CanKillPlayer(int Target, char* Tag)
	{
		getStructs();
		BulletFireParams bp;
		const auto eyePos = cg.refdef.Origin;
		setupBulletTrace(&bp, eyePos, GetTagPos(Target, Tag));
		*reinterpret_cast<long long*>(0x82115400) = 0x386000014E800020; //BulletHitEvent
		*reinterpret_cast<long long*>(0x8218E180) = 0x386000014E800020; //DynEntCl_DynEntImpactEvent
		*reinterpret_cast<long long*>(0x821EEF58) = 0x386000014E800020; //CG_BulletEndpos
		FireBulletPenetrate(0, &bp, Centity_s[cg.clientNum].nextState.weapon, 0, &Centity_s[cg.clientNum], 0xFFFFFFFF, reinterpret_cast<float*>(&cg.refdef.Origin), false);
		*reinterpret_cast<long long*>(0x82115400) = 0x386000014E800020; //BulletHitEvent
		*reinterpret_cast<long long*>(0x8218E180) = 0x386000014E800020; //DynEntCl_DynEntImpactEvent
		*reinterpret_cast<long long*>(0x821EEF58) = 0x7D8802A6482DAE0D; //CG_BulletEndpos
		return (bp.ignoreEntIndex == Target && bp.damageMultiplier > 0.0f);
	}

	inline int getClosestClient(int clientNum)
	{
		auto closest = -1;
		auto maxDistance = 1000000.0f;

		for (auto i = 0; i < 18; i++)
		{
			if (i == clientNum) continue;
			if (!Centity_s[i].pose.eType) continue;
			if (!aimbot) continue;
			const auto d = GetDistance(cg.refdef.Origin, Centity_s[i].pose.origin);
			if (aimbot && !autowall)
			{
				if (!playerVisible(i, Bones[targetBone]))
					continue;
			}
			else if (aimbot && autowall)
			{
				if (!CanKillPlayer(i, Bones[targetBone]))
					continue;
			}
			if (d < maxDistance)
			{
				maxDistance = d;
				closest = i;
			}
		}
		wallClient = closest;
		return closest;
	}

	inline void _SmoothAngle(Vector3 End, Vector3 Start, float Speed)
	{
		if (!bFirstBezierSet)
		{
			flBezierTime = 0.0f;

			if (!bFirstBezierSet)
				bFirstBezierSet = true;
		}

		if (flBezierTime <= 1.0f)
			flBezierTime += ((30 * 2) * 0.001);

		vPoint[0].x = Start.y;
		vPoint[0].y = Start.x;

		flNormalize(&vPoint[0].x);
		flNormalize(&vPoint[0].y);

		vPoint[3].x = End.y;
		vPoint[3].y = End.x;

		flNormalize(&vPoint[3].x);
		flNormalize(&vPoint[3].y);

		vPoint[1].x = RandomFloat(vPoint[0].x, vPoint[3].x);
		vPoint[1].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - 5,
			vPoint[0].y + (vPoint[3].y - vPoint[0].y) + 5);

		flNormalize(&vPoint[1].x);
		flNormalize(&vPoint[1].y);

		vPoint[2].x = RandomFloat(vPoint[1].x, vPoint[3].x);
		vPoint[2].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - 5,
			vPoint[0].y + (vPoint[3].y - vPoint[0].y) + 5);

		flNormalize(&vPoint[2].x);
		flNormalize(&vPoint[2].y);

		auto vCur = CubicBezier(vPoint[0], vPoint[1], vPoint[2], vPoint[3], flBezierTime);

		flNormalize(&vCur.x);
		flNormalize(&vCur.y);

		auto ca = getCA();
		ca.viewangles.x = vCur.y;
		ca.viewangles.y = vCur.x;
	}

	XINPUT_STATE controllerState;

	inline void noSpread(usercmd_s old)
	{
		if (!((controllerState.Gamepad.bLeftTrigger / 30) > 0))
		{
			const auto def = BG_GetWeaponDef(Centity_s[cg.clientNum].nextState.weapon);
			float min, max, rndX, rndY;
			BG_GetSpreadForWeapon(cg.ps, def, &min, &max);
			auto spread = (cg.ps->viewKickScale * spreadMultiplier);
			const auto mSeed = transformSeed(&old.serverTime);

			spread = min + ((max - min) * spread);

			RandomBulletDir(mSeed, &rndX, &rndY);
			rndX *= spread;
			rndY *= spread;

			old.angles[0] -= ANGLE2SHORT(-rndY);
			old.angles[1] -= ANGLE2SHORT(-rndX);
		}
	}
}
#endif // TU24SP_AIM_H
