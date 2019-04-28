#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include <DirectXMath.h>
using namespace DirectX;

class SceneComponent
{
public:
	SceneComponent();
	~SceneComponent();
public:
	const XMVECTOR & GetPositionVector() const;
	const XMFLOAT3 & GetPositionFloat3() const;
	const XMVECTOR & GetRotationVector() const;
	const XMFLOAT3 & GetRotationFloat3() const;
	const XMVECTOR & GetScaleVector() const;
	const XMFLOAT3 & GetScaleFloat3() const;

	void SetPosition(const XMVECTOR & pos);
	void SetPosition(const XMFLOAT3 & pos);
	void SetPosition(float x, float y, float z);
	void AdjustPosition(const XMVECTOR & pos);
	void AdjustPosition(const XMFLOAT3 & pos);
	void AdjustPosition(float x, float y, float z);
	void SetRotation(const XMVECTOR & rot);
	void SetRotation(const XMFLOAT3 & rot);
	void SetRotation(float x, float y, float z);
	void AdjustRotation(const XMVECTOR & rot);
	void AdjustRotation(const XMFLOAT3 & rot);
	void AdjustRotation(float x, float y, float z);
	void SetScale(const XMVECTOR & scale);
	void SetScale(const XMFLOAT3 & scale);
	void SetScale(float x, float y, float z);
	void AdjustScale(const XMVECTOR & scale);
	void AdjustScale(const XMFLOAT3 & scale);
	void AdjustScale(float x, float y, float z);

	void SetLookAtPos(XMFLOAT3 lookAtPos);


	const XMVECTOR & GetForwardVector();

	const XMVECTOR & GetRightVector();

	const XMVECTOR & GetBackwardVector();

	const XMVECTOR & GetLeftVector();

	void UpdateWorldMatrix();

	void UpdateParent(SceneComponent* parent);

	virtual void Tick(float dt);

protected:
	DirectX::XMMATRIX mRelativeMatrix;
public:
	DirectX::XMMATRIX GetWorldMaterix();
protected:
	XMVECTOR scaleVector;
	XMVECTOR posVector;
	XMVECTOR rotVector;
	XMFLOAT3 scale;
	XMFLOAT3 pos;
	XMFLOAT3 rot;


	const XMVECTOR DEFAULT_FORWARD_VECTOR = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const XMVECTOR DEFAULT_UP_VECTOR = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_BACKWARD_VECTOR = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const XMVECTOR DEFAULT_LEFT_VECTOR = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const XMVECTOR DEFAULT_RIGHT_VECTOR = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMVECTOR vec_forward;
	XMVECTOR vec_left;
	XMVECTOR vec_right;
	XMVECTOR vec_backward;

private:
	SceneComponent* parent = nullptr;
};