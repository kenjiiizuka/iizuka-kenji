#pragma once

//----------- INCLUDES ---------- 
#include <SimpleMath.h>


/**
* @struct Transform
* @brief トランスフォーム
*/
struct Transform
{
	DirectX::SimpleMath::Vector3 mPosition{};
	DirectX::SimpleMath::Vector3 mScale = { 1,1,1 };
	DirectX::SimpleMath::Vector3 mRotation{};

	Transform();
	Transform(DirectX::SimpleMath::Vector3 _position, DirectX::SimpleMath::Vector3 _scale, DirectX::SimpleMath::Vector3 _rotation);
};