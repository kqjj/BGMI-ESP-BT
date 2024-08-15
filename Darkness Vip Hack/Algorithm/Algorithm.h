#pragma once

#include "Includes.h"
#include "Utility\Utility.h"
#include "Dx11\\DX11Window.h"

#define M_PI 3.14159265358979323846f
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / IM_PI) )
#define DEG2RAD( x ) ( (float)(x) * (float)(IM_PI / 180.f) )

typedef struct D3DMATRIX1 {
	float m[4][4];
}
D3DMATRIX1, * LPD3DMATRIX;

struct VECTOR2
{
	FLOAT X = 0;
	FLOAT Y = 0;
};

struct VECTOR3
{


	float X;
	float Y;
	float Z;

	float  Size()
	{
		return sqrt((this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z));
	}


	VECTOR3 FVector(float _X, float _Y, float _Z)
	{
		VECTOR3 emmm;
		emmm.X = _X;
		emmm.Y = _Y;
		emmm.Z = _Z;
		return emmm;
	}

	VECTOR3  operator+ (const VECTOR3& A)
	{
		return FVector(this->X + A.X, this->Y + A.Y, this->Z + A.Z);
	}

	VECTOR3 operator+ (const float A)
	{
		return FVector(this->X + A, this->Y + A, this->Z + A);
	}

	VECTOR3  operator+= (const VECTOR3& A)
	{
		this->X += A.X;
		this->Y += A.Y;
		this->Z += A.Z;
		return *this;
	}

	VECTOR3  operator+= (const float A)
	{
		this->X += A;
		this->Y += A;
		this->Z += A;
		return *this;
	}

	VECTOR3  operator- (const VECTOR3& A)
	{
		return FVector(this->X - A.X, this->Y - A.Y, this->Z - A.Z);
	}

	VECTOR3  operator- (const float A)
	{
		return FVector(this->X - A, this->Y - A, this->Z - A);
	}

	VECTOR3 operator-= (const VECTOR3& A)
	{
		this->X -= A.X;
		this->Y -= A.Y;
		this->Z -= A.Z;
		return *this;
	}

	VECTOR3 operator-= (const float A)
	{
		this->X -= A;
		this->Y -= A;
		this->Z -= A;
		return *this;
	}

	VECTOR3  operator* (const VECTOR3& A)
	{
		return FVector(this->X * A.X, this->Y * A.Y, this->Z * A.Z);
	}

	VECTOR3  operator* (const float A)
	{
		return FVector(this->X * A, this->Y * A, this->Z * A);
	}

	VECTOR3  operator*= (const VECTOR3& A)
	{
		this->X *= A.X;
		this->Y *= A.Y;
		this->Z *= A.Z;
		return *this;
	}

	VECTOR3 operator*= (const float A)
	{
		this->X *= A;
		this->Y *= A;
		this->Z *= A;
		return *this;
	}

	VECTOR3  operator/ (const VECTOR3& A)
	{
		return FVector(this->X / A.X, this->Y / A.Y, this->Z / A.Z);
	}

	VECTOR3 operator/ (const float A)
	{
		return FVector(this->X / A, this->Y / A, this->Z / A);
	}

	VECTOR3  operator/= (const VECTOR3& A)
	{
		this->X /= A.X;
		this->Y /= A.Y;
		this->Z /= A.Z;
		return *this;
	}

	VECTOR3 operator/= (const float A)
	{
		this->X /= A;
		this->Y /= A;
		this->Z /= A;
		return *this;
	}

	bool  operator== (const VECTOR3& A)
	{
		if (this->X == A.X
			&& this->Y == A.Y
			&& this->Z == A.Z)
			return true;

		return false;
	}

	bool operator!= (const VECTOR3& A)
	{
		if (this->X != A.X
			|| this->Y != A.Y
			|| this->Z != A.Z)
			return true;

		return false;
	}
	inline float Distance(VECTOR3 v)
	{
		return float(sqrtf(powf(v.X - X, 2.0) + powf(v.Y - Y, 2.0) + powf(v.Z - Z, 2.0)));
	}
};

struct VECTOR4
{
	FLOAT X = 0;
	FLOAT Y = 0;
	FLOAT Z = 0;
	FLOAT W = 0;
};

struct D3DMATRIX
{
	FLOAT _11, _12, _13, _14;
	FLOAT _21, _22, _23, _24;
	FLOAT _31, _32, _33, _34;
	FLOAT _41, _42, _43, _44;
};

struct FTTransform
{
	VECTOR4 Rotation;
	VECTOR3 Translation;
	FLOAT _Padding;
	VECTOR3 Scale3D;
};

struct FRotator {
	float Pitch;
	float Yaw;
	float Roll;
};

struct MinimalViewInfo {
	VECTOR3 Location;
	VECTOR3 LocationLocalSpace;
	FRotator Rotation;
	float FOV;
};

struct CameraCacheEntry {
	float TimeStamp;
	char chunks[0xC];
	MinimalViewInfo POV;
};


namespace Algorithm
{
	VECTOR3 RotatePoint(VECTOR3 EntityPos, VECTOR3 LocalPlayerPos, int posX, int posY, int sizeX, int sizeY, float angle, float zoom, bool* viewCheck);
	BOOL WorldToScreen(VECTOR3 Position, VECTOR3& Screen, INT* Distance, D3DMATRIX ViewMatrix);
	VECTOR3 WorldToRadarM(float Yaw, VECTOR3 Origin, VECTOR3 LocalOrigin, float PosX, float PosY, VECTOR3 Size, bool& outbuff);
	VECTOR3 WorldToRadar(float Yaw, VECTOR3 Origin, VECTOR3 LocalOrigin, float PosX, float PosY, VECTOR3 Size, bool& outbuff);
	BOOL WorldToScreenPlayer(VECTOR3 Position, VECTOR3& Screen, INT* Distance, D3DMATRIX ViewMatrix);
	BOOL WorldToScreenBone(D3DMATRIX ViewMatrix, VECTOR3 Position, VECTOR2& Screen, INT* Distance);
	D3DMATRIX ToMatrixWithScale(VECTOR3 Translation, VECTOR3 Scale, VECTOR4 Rot);
	D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2);
	VECTOR3 GetBoneWorldPosition(DWORD ActorAddv, DWORD BoneAddv);
	float Distance(VECTOR3 myPos, VECTOR3 enPos);
	VECTOR3 ToVECTOR3(float x, float y, float z);
	void VectorAnglesRadar(VECTOR3& forward, VECTOR3& angles);
}
