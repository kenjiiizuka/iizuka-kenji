//----------- INCLUDES -----------
#include "BillboardObject.h"
#include "../Camera/CameraIncludes.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"
#include "../../../Utility/MathLibrary.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../System/RendererSystem/VisualEntity/VisualEntityData.h"

BillboardObject::BillboardObject()
{
	// 処理なし
}

BillboardObject::~BillboardObject()
{
	// 処理なし
}

void BillboardObject::Init(const DirectX::SimpleMath::Vector2 _size)
{
	// メインカメラの取得
	mMainCamera = SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->GetMainCamera();

	// ビルボード用オブジェクト追加
	mPlane = AddComponent<PlaneComponent>();
	mPlane.lock()->Init({_size.x, _size.y, 0.0f }, { 0.0f,0.0f,0.0f }, "assets/shader/White.png", RendererInf::Layer_Object, false);
}

void BillboardObject::Draw()
{
	LookAtCamera();
}

void BillboardObject::LookAtCamera()
{	
	std::shared_ptr<Camera> camera = mMainCamera.lock();
	if (!camera)
	{
		return;
	}

	// View行列の取得
	DirectX::SimpleMath::Matrix view = mMainCamera.lock()->GetViewMatrix();

	// 移動要素をなくす
	view._41 = 0.0f;
	view._42 = 0.0f;
	view._43 = 0.0f;

	// カメラの方を向かせる
	DirectX::SimpleMath::Matrix matrix = view.Invert() * mTransform.lock()->GetWorldMatrix();
	mPlane.lock()->SetWorldMatrix(matrix);
}

void BillboardObject::SetPosition(DirectX::SimpleMath::Vector3 _position)
{
	mTransform.lock()->SetPosition(_position);	
}

void BillboardObject::SetTexture(const Texture _texture)
{
	mPlane.lock()->SetTexture(_texture);
}

void BillboardObject::SetMaterialDiffuse(const DirectX::SimpleMath::Color _diffuse)
{
	mPlane.lock()->GetVisualEntity()->GetVisualEntityData(0)->SetMaterialDiffuse(_diffuse);
}

void BillboardObject::CalcuWorldMatrix(const DirectX::SimpleMath::Matrix& _matrix)
{
	mTransform.lock()->CalucWorldMatrix(_matrix);
}
