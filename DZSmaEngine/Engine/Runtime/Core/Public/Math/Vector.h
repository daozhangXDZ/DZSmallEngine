#pragma once
#include "CoreMinimal.h"
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class DFVector
{
private:
	XMVECTOR mCtorData;
	float X;
	float Y;
	float Z;

public:
	DFVector()
	{
		
	}

	DFVector(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

	DFVector(const DFVector& other)
	{
		
		this->X = other.X;
		this->Y = other.Y;
		this->Z = other.Z;
	}

	DFVector(const XMVECTOR& mCtorData)
	{
		XMFLOAT3 vT;
		XMStoreFloat3(&vT, mCtorData);
		this->X = vT.x;
		this->Y = vT.y;
		this->Z = vT.z;
		Refresh();
	}

	float getX()
	{
		return X;
	}

	float getY()
	{
		return Y;
	}

	float getZ()
	{
		return Z;
	}

	float setX(float x)
	{
		this->X = x;
		this->Refresh();
	}

	float setY(float y)
	{
		this->Y = y;
		this->Refresh();
	}

	float setZ(float z)
	{
		this->Z = z;
		this->Refresh();
	}


	void Refresh()
	{
		XMFLOAT3 vFloat3Data = XMFLOAT3(X, Y, Z);
		this->mCtorData = XMLoadFloat3(&vFloat3Data);
	}

	DFVector operator +(DFVector& other)
	{
		DFVector* vs = new DFVector();
		vs->setX(this->X + other.X);
		vs->setY(this->Y + other.Y);
		vs->setZ(this->Z + other.Z);
		return *vs;
	}

	FORCEINLINE DFVector operator-(DFVector& other) const
	{
		DFVector* vs = new DFVector();
		vs->setX(this->X - other.X);
		vs->setY(this->Y - other.Y);
		vs->setZ(this->Z - other.Z);
		return *vs;
	}


	FORCEINLINE DFVector operator+=(const DFVector& V)
	{
		X += V.X; Y += V.Y; Z += V.Z;
		Refresh();
		return *this;
	}

	FORCEINLINE DFVector operator-=(const DFVector& V)
	{
		X -= V.X; Y -= V.Y; Z -= V.Z;
		Refresh();
		return *this;
	}

	FORCEINLINE DFVector operator =(DFVector& other)
	{
		this->X = other.X;
		this->Y = other.Y;
		this->Z = other.Z;
		this->Refresh();
		return *this;
	}

	//FORCEINLINE DFVector& operator =(const DFVector& other)
	//{
	//	this->X = other.X;
	//	this->Y = other.Y;
	//	this->Z = other.Z;
	//	this->Refresh();
	//	return *this;
	//}
};