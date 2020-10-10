namespace TU17
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
		CG_LocationalTrace(&trace, &eyePos, &headPos, cg->ClientNumber, 0x803003);
		return trace.fraction >= 0.95f;
	}

	void setupBulletTrace(BulletFireParams* bp, Vector3 start, Vector3 end) {
		bp->MaxEntNum = 0x7FE;
		bp->ignoreEntIndex = cg->ClientNumber;
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
		*reinterpret_cast<int*>(0x822C73C0) = 0x4E800020;
		*reinterpret_cast<int*>(0x82385B38) = 0x4E800020;
		*reinterpret_cast<int*>(0x822C7500) = 0x60000000;
		FireBulletPenetrate(0, &bp, Centity_s[cg->ClientNumber].WeaponID, 0, &Centity_s[cg->ClientNumber], 0xFFFFFFFF, reinterpret_cast<float*>(&cg->RefDef.viewOrigin), false);
		return (bp.ignoreEntIndex == Target && bp.damageMultiplier > 0.0f);
	}

	int getClosestClient(int clientNum) {
		auto closest = -1;
		auto maxDistance = 1000000.0f;

		for (auto i = 0; i < 18; i++) {
			if (i == clientNum) continue;
			if (!Centity_s[i].Alive) continue;
			if (Centity_s[i].Type != ET_PLAYER) continue;
			if (!notTeam(i)) continue;
			if (!aimbot) continue;
			const auto d = GetDistance(cg->RefDef.viewOrigin, Centity_s[i].Origin);
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

		ClientActive_t* ca;
		ca = static_cast<ClientActive_t*>(getCA());
		ca->viewAngle.x = vCur.y;
		ca->viewAngle.y = vCur.x;
	}

	XINPUT_STATE controllerState;
	void noSpread(Usercmd_t* old)
	{
		if (!((controllerState.Gamepad.bLeftTrigger / 30) > 0))
		{
			auto def = Centity_s[cg->ClientNumber].WeaponID;
			float min, max, rndX, rndY;
			BG_GetSpreadForWeapon(cg, def, &min, &max);
			auto mSeed = transformSeed(&old->time);
			auto spread = (max - min) * (cg->SpreadMultiplier * 0.00392156862f) + min;
			RandomBulletDir(mSeed, &rndX, &rndY);
			rndX *= spread; rndY *= spread;
			old->viewAngles[0] -= ANGLE2SHORT(-rndY);
			old->viewAngles[1] -= ANGLE2SHORT(-rndX);
		}
	}
}
