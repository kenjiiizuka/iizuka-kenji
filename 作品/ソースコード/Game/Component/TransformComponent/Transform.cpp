#include "Transform.h"

using namespace DirectX::SimpleMath;

Transform::Transform()
{
	mPosition = Vector3::Zero;
	mScale = Vector3::One;
	mRotation = Vector3::Zero;
}

Transform::Transform(DirectX::SimpleMath::Vector3 _position, DirectX::SimpleMath::Vector3 _scale, DirectX::SimpleMath::Vector3 _rotation)
{
	mPosition = _position;
	mScale = _scale;
	mRotation = _rotation;
}
