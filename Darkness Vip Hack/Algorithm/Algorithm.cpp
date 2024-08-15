#include "Algorithm.h"

VECTOR3 Algorithm::RotatePoint(VECTOR3 EntityPos, VECTOR3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck) {
	float r_1, r_2;
	float x_1, y_1;

	r_1 = -(EntityPos.Y - LocalPlayerPos.Y);
	r_2 = EntityPos.X - LocalPlayerPos.X;
	float Yaw = angle - 90.0f;

	float yawToRadian = Yaw * (float)(M_PI / 180.0F);
	x_1 = (float)(r_2 * (float)cos((double)(yawToRadian)) - r_1 * sin((double)(yawToRadian))) / 20;
	y_1 = (float)(r_2 * (float)sin((double)(yawToRadian)) + r_1 * cos((double)(yawToRadian))) / 20;

	*viewCheck = y_1 < 0;

	x_1 *= zoom;
	y_1 *= zoom;

	int sizX = sizeX / 2;
	int sizY = sizeY / 2;

	x_1 += sizX;
	y_1 += sizY;

	if (x_1 < 5)
		x_1 = 5;

	if (x_1 > sizeX - 5)
		x_1 = sizeX - 5;

	if (y_1 < 5)
		y_1 = 5;

	if (y_1 > sizeY - 5)
		y_1 = sizeY - 5;

	x_1 += posX;
	y_1 += posY;

	return VECTOR3{ x_1, y_1, 0 };
}

BOOL Algorithm::WorldToScreen(VECTOR3 Position, VECTOR3& Screen, INT* Distance, D3DMATRIX ViewMatrix)
{
	FLOAT ScreenW = (ViewMatrix._14 * Position.X) + (ViewMatrix._24 * Position.Y) + (ViewMatrix._34 * Position.Z + ViewMatrix._44);
	*Distance = (ScreenW / 100);
	if (ScreenW < 0.0001f) return FALSE;

	ScreenW = 1 / ScreenW;
	FLOAT SightX = (DX11Window::Width / 2);
	FLOAT SightY = (DX11Window::Height / 2);

	Screen.X = SightX + (ViewMatrix._11 * Position.X + ViewMatrix._21 * Position.Y + ViewMatrix._31 * Position.Z + ViewMatrix._41) * ScreenW * SightX;
	Screen.Y = SightY - (ViewMatrix._12 * Position.X + ViewMatrix._22 * Position.Y + ViewMatrix._32 * Position.Z + ViewMatrix._42) * ScreenW * SightY;

	return TRUE;
}

VECTOR3 Algorithm::WorldToRadar(float Yaw, VECTOR3 Origin, VECTOR3 LocalOrigin, float PosX, float PosY, VECTOR3 Size, bool& outbuff)
{
	bool flag = false;
	double num = (double)Yaw;
	double num2 = num * 0.017453292519943295;
	float num3 = (float)std::cos(num2);
	float num4 = (float)std::sin(num2);
	float num5 = Origin.X - LocalOrigin.X;
	float num6 = Origin.Y - LocalOrigin.Y;
	VECTOR3 vector;
	vector.X = (num6 * num3 - num5 * num4) / 150.f;
	vector.Y = (num5 * num3 + num6 * num4) / 150.f;
	VECTOR3 vector2;
	vector2.X = vector.X + PosX + Size.X / 2.f;
	vector2.Y = -vector.Y + PosY + Size.Y / 2.f;
	bool flag2 = vector2.X > PosX + Size.X;
	if (flag2)
	{
		vector2.X = PosX + Size.X;
	}
	else
	{
		bool flag3 = vector2.X < PosX;
		if (flag3)
		{
			vector2.X = PosX;
		}
	}
	bool flag4 = vector2.Y > PosY + Size.Y;
	if (flag4)
	{
		vector2.Y = PosY + Size.Y;
	}
	else
	{
		bool flag5 = vector2.Y < PosY;
		if (flag5)
		{
			vector2.Y = PosY;
		}
	}
	bool flag6 = vector2.Y == PosY || vector2.X == PosX;
	if (flag6)
	{
		flag = true;
	}
	outbuff = flag;
	return vector2;
}

VECTOR3 Algorithm::WorldToRadarM(float Yaw, VECTOR3 Origin, VECTOR3 LocalOrigin, float PosX, float PosY, VECTOR3 Size, bool& outbuff)
{
	bool flag = false;
	float num5 = Origin.X - LocalOrigin.X;
	float num6 = Origin.Y - LocalOrigin.Y;
	VECTOR3 vector;
	vector.X = num5 / 150.f;
	vector.Y = num6 / 150.f;
	VECTOR3 vector2;
	vector2.X = vector.X + PosX + Size.X / 2.f;
	vector2.Y = vector.Y + PosY + Size.Y / 2.f;

	// Clamping the positions to stay within radar bounds
	if (vector2.X > PosX + Size.X)
	{
		vector2.X = PosX + Size.X;
	}
	else if (vector2.X < PosX)
	{
		vector2.X = PosX;
	}
	if (vector2.Y > PosY + Size.Y)
	{
		vector2.Y = PosY + Size.Y;
	}
	else if (vector2.Y < PosY)
	{
		vector2.Y = PosY;
	}

	// Check if the position is out of bounds
	if (vector2.Y == PosY || vector2.X == PosX)
	{
		flag = true;
	}
	outbuff = flag;
	return vector2;
}



BOOL Algorithm::WorldToScreenPlayer(VECTOR3 Position, VECTOR3& Screen, INT* Distance, D3DMATRIX ViewMatrix)
{
	FLOAT ScreenW = (ViewMatrix._14 * Position.X) + (ViewMatrix._24 * Position.Y) + (ViewMatrix._34 * Position.Z + ViewMatrix._44);
	*Distance = (ScreenW / 100);
	if (ScreenW < 0.0001f) return FALSE;

	FLOAT ScreenX = (ViewMatrix._11 * Position.X) + (ViewMatrix._21 * Position.Y) + (ViewMatrix._31 * Position.Z + ViewMatrix._41);
	FLOAT ScreenY = (ViewMatrix._12 * Position.X) + (ViewMatrix._22 * Position.Y) + (ViewMatrix._32 * (Position.Z + 85) + ViewMatrix._42);

	Screen.X = (DX11Window::Width / 2) + (DX11Window::Width / 2) * ScreenX / ScreenW;
	Screen.Y = (DX11Window::Height / 2) - (DX11Window::Height / 2) * ScreenY / ScreenW;
	FLOAT Y1 = (DX11Window::Height / 2) - (ViewMatrix._12 * Position.X + ViewMatrix._22 * Position.Y + ViewMatrix._32 * (Position.Z - 95) + ViewMatrix._42) * (DX11Window::Height / 2) / ScreenW;
	Screen.Z = Y1 - Screen.Y;

	return TRUE;
}

BOOL Algorithm::WorldToScreenBone(D3DMATRIX ViewMatrix, VECTOR3 Position, VECTOR2& Screen, INT* Distance)
{
	FLOAT ScreenW = (ViewMatrix._14 * Position.X) + (ViewMatrix._24 * Position.Y) + (ViewMatrix._34 * Position.Z + ViewMatrix._44);
	*Distance = (ScreenW / 100);
	if (ScreenW < 0.0001f) return FALSE;

	ScreenW = 1 / ScreenW;
	FLOAT SightX = (DX11Window::Width / 2);
	FLOAT SightY = (DX11Window::Height / 2);

	Screen.X = SightX + (ViewMatrix._11 * Position.X + ViewMatrix._21 * Position.Y + ViewMatrix._31 * Position.Z + ViewMatrix._41) * ScreenW * SightX;
	Screen.Y = SightY - (ViewMatrix._12 * Position.X + ViewMatrix._22 * Position.Y + ViewMatrix._32 * Position.Z + ViewMatrix._42) * ScreenW * SightY;

	return TRUE;
}

D3DMATRIX Algorithm::ToMatrixWithScale(VECTOR3 Translation, VECTOR3 Scale, VECTOR4 Rot)
{
	D3DMATRIX m;
	m._41 = Translation.X;
	m._42 = Translation.Y;
	m._43 = Translation.Z;

	FLOAT x2 = Rot.X + Rot.X;
	FLOAT y2 = Rot.Y + Rot.Y;
	FLOAT z2 = Rot.Z + Rot.Z;

	FLOAT xx2 = Rot.X * x2;
	FLOAT yy2 = Rot.Y * y2;
	FLOAT zz2 = Rot.Z * z2;
	m._11 = (1.0f - (yy2 + zz2)) * Scale.X;
	m._22 = (1.0f - (xx2 + zz2)) * Scale.Y;
	m._33 = (1.0f - (xx2 + yy2)) * Scale.Z;

	FLOAT yz2 = Rot.Y * z2;
	FLOAT wx2 = Rot.W * x2;
	m._32 = (yz2 - wx2) * Scale.Z;
	m._23 = (yz2 + wx2) * Scale.Y;

	FLOAT xy2 = Rot.X * y2;
	FLOAT wz2 = Rot.W * z2;
	m._21 = (xy2 - wz2) * Scale.Y;
	m._12 = (xy2 + wz2) * Scale.X;

	FLOAT xz2 = Rot.X * z2;
	FLOAT wy2 = Rot.W * y2;
	m._31 = (xz2 + wy2) * Scale.Z;
	m._13 = (xz2 - wy2) * Scale.X;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;

	return m;
}

D3DMATRIX Algorithm::MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut =
	{
		pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41,
		pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42,
		pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43,
		pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44,
		pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41,
		pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42,
		pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43,
		pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44,
		pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41,
		pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42,
		pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43,
		pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44,
		pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41,
		pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42,
		pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43,
		pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44
	};

	return pOut;
}

VECTOR3 Algorithm::GetBoneWorldPosition(DWORD ActorAddv, DWORD BoneAddv)
{
	FTTransform Bone = Utility::ReadMemoryEx<FTTransform>(BoneAddv);
	FTTransform Actor = Utility::ReadMemoryEx<FTTransform>(ActorAddv);
	D3DMATRIX BoneMatrix = ToMatrixWithScale(Bone.Translation, Bone.Scale3D, Bone.Rotation);
	D3DMATRIX ComponentToWorldMatrix = ToMatrixWithScale(Actor.Translation, Actor.Scale3D, Actor.Rotation);
	D3DMATRIX NewMatrix = MatrixMultiplication(BoneMatrix, ComponentToWorldMatrix);

	VECTOR3 BonePos;
	BonePos.X = NewMatrix._41;
	BonePos.Y = NewMatrix._42;
	BonePos.Z = NewMatrix._43;

	return BonePos;
}

float Algorithm::Distance(VECTOR3 myPos, VECTOR3 enPos)
{
	return sqrt((myPos.X - enPos.X) * (myPos.X - enPos.X) + (myPos.Y - enPos.Y) * (myPos.Y - enPos.Y) + (myPos.Z - enPos.Z) * (myPos.Z - enPos.Z));
}

VECTOR3 Algorithm::ToVECTOR3(float x, float y, float z)
{
	VECTOR3 tem;
	tem.X = x;
	tem.Y = y;
	tem.Z = z;
	return tem;
}

void Algorithm::VectorAnglesRadar(VECTOR3& forward, VECTOR3& angles)
{
	if (forward.X == 0.f && forward.Y == 0.f)
	{
		angles.X = forward.Z > 0.f ? -90.f : 90.f;
		angles.Y = 0.f;
	}
	else
	{
		angles.X = RAD2DEG(atan2(-forward.Z, forward.Size()));
		angles.Y = RAD2DEG(atan2(forward.Y, forward.X));
	}
	angles.Z = 0.f;
}

