namespace TU7
{
	void FixMovement(Usercmd_t* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove) {
		const auto deltaView = CurAngle - OldAngle;
		auto forward = static_cast<int>(cos(deltaView * (3.14159265358979323846264338327950288f / 180.0f)) * fOldForward + cos(
			(deltaView + 90.f) * (3.14159265358979323846264338327950288f / 180.0f)) * fOldSidemove);
		auto right = static_cast<int>(sin(deltaView * (3.14159265358979323846264338327950288f / 180.0f)) * fOldForward + sin(
			(deltaView + 90.f) * (3.14159265358979323846264338327950288f / 180.0f)) * fOldSidemove);

		if (forward < -128) forward = -128;
		else if (forward > 127) forward = 127;
		if (right < -128) right = -128;
		else if (right > 127) right = 127;

		pCmd->fDir = static_cast<char>(forward);
		pCmd->rDir = static_cast<char>(right);
	}

	void AimSilent(Usercmd_t* oldCommand, Vector3 toAngle) {
		const auto oldAngle = SHORT2ANGLE(oldCommand->viewAngles[1]);
		oldCommand->viewAngles[0] = ANGLE2SHORT(toAngle.x);
		oldCommand->viewAngles[1] = ANGLE2SHORT(toAngle.y);
		FixMovement(oldCommand, SHORT2ANGLE(oldCommand->viewAngles[1]), oldAngle, oldCommand->fDir, oldCommand->rDir);
	}

	bool playerVisible(int unknown, char* Tag) {
		trace_t trace;
		auto headPos = GetTagPos(unknown, Tag);
		auto eyePos = GetPlayerViewOrigin();
		CG_LocationalTrace(&trace, &eyePos, &headPos, cg->clientNum, 0x803003);
		return trace.fraction >= 0.95f;
	}

	void setupBulletTrace(BulletFireParams* bp, Vector3 start, Vector3 end) {
		bp->weaponEntIndex = 0x7FE;
		bp->ignoreEntIndex = cg->clientNum;
		bp->damageMultiplier = 1;
		bp->methodOfDeath = 2;
		bp->origStart = GetPlayerViewOrigin();
		bp->start = start;
		bp->end = end;

		auto delta = end - start;

		Vector3 angles;
		VectorAngles(delta, angles);
		bp->dir = delta;
	}

	bool CanKillPlayer(int Target, char* Tag)
	{
		getStructs();
		BulletFireParams bp;
		const auto eyePos = GetPlayerViewOrigin();
		setupBulletTrace(&bp, eyePos, GetTagPos(Target, Tag));
		*reinterpret_cast<long long*>(0x8219F640) = 0x386000014E800020; //BulletHitEvent
		*reinterpret_cast<long long*>(0x821EDEF0) = 0x386000014E800020; //DynEntCl_DynEntImpactEvent
		*reinterpret_cast<long long*>(0x8219BB90) = 0x386000014E800020; //CG_BulletEndpos
		FireBulletPenetrate(0, &bp, cg->Weapon, &Centity_s[cg->clientNum], reinterpret_cast<float*>(&cg->refdef.viewOrigin), false);
		*reinterpret_cast<long long*>(0x8219F640) = 0x386000014E800020; //BulletHitEvent
		*reinterpret_cast<long long*>(0x821EDEF0) = 0x386000014E800020; //DynEntCl_DynEntImpactEvent
		*reinterpret_cast<long long*>(0x8219BB90) = 0x7D8802A6482A2A99; //CG_BulletEndpos
		return (bp.ignoreEntIndex == Target && bp.damageMultiplier > 0.0f);
	}

	int getClosestClient(int clientNum) {
		auto closest = -1;
		auto maxDistance = 1000000.0f;

		for (auto i = 0; i < 18; i++) {
			if (i == clientNum) continue;
			if (!Centity_s[i].valid) continue;
			if (!Centity_s[i].State & 1) continue;
			if (!notTeam(i)) continue;
			if (!aimbot) continue;
			const auto d = GetDistance(cg->refdef.viewOrigin, Centity_s[i].origin);
			if (aimbot && !autowall) {
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

	void _SmoothAngle(Vector3 End, Vector3 Start, float Speed)
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
		vPoint[1].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - 5, vPoint[0].y + (vPoint[3].y - vPoint[0].y) + 5);

		flNormalize(&vPoint[1].x);
		flNormalize(&vPoint[1].y);

		vPoint[2].x = RandomFloat(vPoint[1].x, vPoint[3].x);
		vPoint[2].y = RandomFloat(vPoint[0].y + (vPoint[3].y - vPoint[0].y) - 5, vPoint[0].y + (vPoint[3].y - vPoint[0].y) + 5);

		flNormalize(&vPoint[2].x);
		flNormalize(&vPoint[2].y);

		auto vCur = CubicBezier(vPoint[0], vPoint[1], vPoint[2], vPoint[3], flBezierTime);

		flNormalize(&vCur.x);
		flNormalize(&vCur.y);

		clientActive* ca;
		ca = static_cast<clientActive*>(getCA());
		ca->viewAngle.x = vCur.y;
		ca->viewAngle.y = vCur.x;
	}

	XINPUT_STATE controllerState;
	void noSpread(Usercmd_t* old)
	{
		if (!((controllerState.Gamepad.bLeftTrigger / 30) > 0))
		{
			const auto def = BG_GetWeaponDef(cg->Weapon);
			float min, max, rndX, rndY;
			BG_GetSpreadForWeapon(cg, def, &min, &max);
			auto spread = (cg->SpreadMultiplier * spreadMultiplier);
			const auto mSeed = transformSeed(&old->time);

			spread = min + ((max - min) * spread);

			RandomBulletDir(mSeed, &rndX, &rndY);
			rndX *= spread; rndY *= spread;

			old->viewAngles[0] -= ANGLE2SHORT(-rndY);
			old->viewAngles[1] -= ANGLE2SHORT(-rndX);
		}
	}
}