#include "Components/SceneComponent.h"

void SceneComponent::UpdateWorldMatrix()
{
	mRelativeMatrix =
		XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z)
		* 
		XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z)
		* 
		XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}

void SceneComponent::UpdateParent(SceneComponent* parent)
{
	this->parent = parent;
	UpdateWorldMatrix();
}

void SceneComponent::Tick(float dt)
{
}

DirectX::XMMATRIX SceneComponent::GetWorldMaterix()
{
	if (parent == nullptr)
	{
		return mRelativeMatrix;
	}
	else
	{
		return GetWorldMaterix() * mRelativeMatrix;
	}
}

SceneComponent::SceneComponent()
{
	this->SetPosition(0.0, 0.0, 0.0);
	this->SetRotation(0.0, 0.0, 0.0);
	this->SetScale(1.0, 1.0, 1.0);
}

SceneComponent::~SceneComponent()
{
}

const XMVECTOR & SceneComponent::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3 & SceneComponent::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR & SceneComponent::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3 & SceneComponent::GetRotationFloat3() const
{
	return this->rot;
}

const XMVECTOR & SceneComponent::GetScaleVector() const
{
	return this->scaleVector;
}

const XMFLOAT3 & SceneComponent::GetScaleFloat3() const
{
	return this->scale;
}

void SceneComponent::SetPosition(const XMVECTOR & pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateWorldMatrix();
}

void SceneComponent::SetPosition(const XMFLOAT3 & pos)
{
	this->pos = pos;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustPosition(const XMVECTOR & pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustPosition(const XMFLOAT3 & pos)
{
	this->pos.x += pos.y;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetRotation(const XMVECTOR & rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetRotation(const XMFLOAT3 & rot)
{
	this->rot = rot;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustRotation(const XMVECTOR & rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustRotation(const XMFLOAT3 & rot)
{
	this->rot.x += rot.x;
	this->rot.y += rot.y;
	this->rot.z += rot.z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetScale(const XMVECTOR & scale)
{
	this->scaleVector = scale;
	XMStoreFloat3(&this->scale, scale);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetScale(const XMFLOAT3 & scale)
{
	this->scale = scale;
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetScale(float x, float y, float z)
{
	this->scale = XMFLOAT3(x, y, z);
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustScale(const XMVECTOR & scale)
{
	this->scaleVector += scale;
	XMStoreFloat3(&this->scale, this->scaleVector);
	this->UpdateWorldMatrix();
}

void SceneComponent::AdjustScale(const XMFLOAT3 & scale)
{
	this->scale.x += scale.x;
	this->scale.y += scale.y;
	this->scale.z += scale.z;
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateWorldMatrix();
}
void SceneComponent::AdjustScale(float x, float y, float z)
{
	this->scale.x += x;
	this->scale.y += y;
	this->scale.z += z;
	this->scaleVector = XMLoadFloat3(&this->scale);
	this->UpdateWorldMatrix();
}

void SceneComponent::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	//Verify that look at pos is not the same as cam pos. They cannot be the same as that wouldn't make sense and would result in undefined behavior.
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR & SceneComponent::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR & SceneComponent::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR & SceneComponent::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR & SceneComponent::GetLeftVector()
{
	return this->vec_left;
}