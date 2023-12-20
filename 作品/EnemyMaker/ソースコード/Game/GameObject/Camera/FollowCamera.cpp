//--------- INCLUDES ----------
#include "FollowCamera.h"
#include "../../Component/TransformComponent/TransformComponent.h"
#include "../../../Utility/MathLibrary.h"

using namespace DirectX::SimpleMath;

FollowCamera::~FollowCamera()
{
	Cout<std::string>("FollowCameraが解放されました");
}

void FollowCamera::Update(const double _deltaTime)
{
	std::shared_ptr<TransformComponent> trans = mFollowObject->GetComponent<TransformComponent>();
	Vector3 newPos = trans->GetPosition();
	Vector3 offset = MathLibrary::RotateVector(mOffSet, trans->GetRotation());
	newPos += offset * mDistance;
	mTransform.lock()->SetPosition(newPos);
	mFocusPosition = trans->GetPosition() + trans->GetForwardVector() * 100; // 注視点をターゲットから視線の長さ分先の位置を見る
	mFocusPosition.y += mFixTargetHeight;
}