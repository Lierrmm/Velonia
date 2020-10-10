typedef struct Vector2 {
	FLOAT x, y;
	Vector2() {
		x = y = 0;
	}
	Vector2(FLOAT x, FLOAT y) {
		this->x = x;
		this->y = y;
	}

} Vector2, * PVector2;
typedef struct Vector3 {
	FLOAT x, y, z;
	Vector3() {
		x = y = z = 0;
	}
	Vector3(FLOAT x, FLOAT y, FLOAT z) {
		this->x = x; this->y = y; this->z = z;
	}
	BOOL operator== (Vector3& Vector) {
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	Vector3& operator+ (Vector3& Vector) {
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	Vector3& operator- (Vector3& Vector) {
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	Vector3& operator*(float fact)
	{
		return Vector3(this->x * fact, this->y * fact, this->z * fact);
	}
	FLOAT Distance(Vector3& Vector) {
		return sqrt(DistanceEx(Vector));
	}
	FLOAT DistanceEx(Vector3& Vector) {
		FLOAT _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	FLOAT DotProduct(Vector3& Vector) {
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	Vector3& RoundHalfUp() {
		return Vector3(floor(this->x + 0.7), floor(this->y + 0.7), floor(this->z + 0.7));
	}
	Vector3& RoundHalfDown() {
		return Vector3(floor(this->x + 0.7), floor(this->y + 0.7), floor(this->z + 0.7));
	}
} Vector3, * PVector3;
typedef struct Vector4 {
	FLOAT x, y, z, a;
	Vector4() {
		x = y = z = a = 0;
	}
	Vector4(FLOAT x, FLOAT y, FLOAT z, FLOAT a) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->a = a;
	}
} Vector4, * PVector4;
float GetDistance(Vector3 Self, Vector3 Player) {
	float dx = Self.x - Player.x;
	float dy = Self.y - Player.y;
	float dz = Self.z - Player.z;
	return (float)sqrt((dx * dx) + (dy * dy) + (dz * dz)) * 0.03048f;
}
Vector3 angles;
Vector3 vectoangles(Vector3 Angles) {
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0) {
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else {
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;
		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
	return angles;
}
Vector3 VectorToAngles(Vector3& Delta) {
	float Forward, Yaw, Pitch;
	if (Delta.x == 0 && Delta.y == 0) {
		Yaw = 0;
		if (Delta.z > 0) Pitch = 90;
		else Pitch = 270;
	}
	else {
		if (Delta.x) Yaw = (atan2(Delta.y, Delta.x) * 180 / 3.14159265358979323846);
		else if (Delta.y > 0) Yaw = 90;
		else Yaw = 270;
		if (Yaw < 0) Yaw += 360;
		Forward = sqrt((Delta.x * Delta.x) + (Delta.y * Delta.y));
		Pitch = (atan2(Delta.z, Forward) * 180 / 3.14159265358979323846);
		if (Pitch < 0) Pitch += 360;
	}
	return Vector3(-Pitch, Yaw, 0);
}
void angleVectors(Vector3 angles, Vector3* forward, Vector3* right, Vector3* up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;
	angle = angles.y * ((3.14159265358979323846 * 2) / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles.x * ((3.14159265358979323846 * 2) / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles.z * ((3.14159265358979323846 * 2) / 360);
	sr = sin(angle);
	cr = cos(angle);
	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}
	if (right) {
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}
	if (up) {
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}
void VectorScale(Vector3& vec, float scale, Vector3 out) {
	out.x = vec.x * scale;
	out.y = vec.y * scale;
	out.z = vec.z * scale;
}
Vector3 SubstractVector(Vector3 v1, Vector3 v2) {
	Vector3 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	return r;
}
float DotProduct(Vector3& a, Vector3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
void VectorAngles(Vector3& forward, Vector3& angles) {
	float tmp, yaw, pitch;
	if (forward.z == 0 && forward.x == 0) {
		yaw = 0;
		if (forward.z > 0) pitch = 90;
		else pitch = 270;
	}
	else {
		yaw = (atan2(forward.z, -forward.x) * 180 / XM_PI) - 90;
		if (yaw < 0) yaw += 360;
		tmp = sqrt(forward.x * forward.x + forward.z * forward.z);
		pitch = (atan2(forward.y, tmp) * 180 / XM_PI);
		if (pitch < 0) pitch += 360;
	}
	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
}