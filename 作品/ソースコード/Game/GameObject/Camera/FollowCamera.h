#pragma once
#include "Camera.h"
class FollowCamera : public Camera
{
private:
	GameObject* mFollowObject = nullptr;
	DirectX::SimpleMath::Vector3 mOffSet;
	float mFixTargetHeight = 0; // 注視点をみる位置の修正 (モデルの中心を見るようにしたい)
	float mDistance = 0;;
public:
	~FollowCamera();

	void Update(const double _deltaTime) override;
	
	void SetFollowObject(GameObject* _followObject) { mFollowObject = _followObject; }

	void SetFixTargetHeight(float _fixHeight) {
		mFixTargetHeight = _fixHeight;
	}

	void SetOffSet(DirectX::SimpleMath::Vector3 _offset) { 
		mDistance = _offset.Length();
		mOffSet = _offset;
		mOffSet.Normalize();
	}
};

