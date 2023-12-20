//------------ INCLUDES -----------
#include "Weapon.h"
#include "../../Component/StaticMeshComponent/StaticMeshComponent.h"
#include "../../Component/StaticMeshComponent/StaticMesh.h"
#include "../../Component/CollisionComponent/CapsuleCollisionComponent.h"
#include "../../../System/RendererSystem/Shader/VertexShader/OutlineLightVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/OutlinePixelShader.h"
#include "../../Resource/SkeletalMesh.h"
#include "../../Resource/Bone.h"
#include "../../../System/InputSystem/Input.h"
#include "../../../Utility/Debug.h"
#include "../../../Utility/MathLibrary.h"


//------------ NAMESPACEAILIAS ---------------
namespace DXSimpleMath = DirectX::SimpleMath;

Weapon::Weapon()
{
	// 処理なし
}

Weapon::~Weapon()
{
	// 処理なし
}

void Weapon::Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh)
{
	// メッシュの読み込み
	std::shared_ptr<StaticMeshComponent> staticMeshComp = AddComponent<StaticMeshComponent>();
	staticMeshComp->Load(_filePath);
	
	// アウトライン用のシェーダーを追加
	std::shared_ptr<StaticMesh> staticMesh = staticMeshComp->GetStaticMesh();
	staticMesh->AddVertexShader<OutlineLightVertexShader>()->SetOutlineThickness(0.7f);
	staticMesh->AddPixelShader<OutlinePixelShader>();
	staticMesh->SwapShader();
	staticMesh->SetDrawType(DrawType::Draw_SolidFront,0);
	staticMesh->SetDrawType(DrawType::Draw_SolidBack, 1);

	// 親オブジェクトの影響を受けない
	mTransform.lock()->SetParentTransformInfluence(false);
	mAttachBone = _attachBone;
}

void Weapon::Update(const double _deltaTime)
{
	DXSimpleMath::Matrix boneMat = mAttachBone.lock()->GetBoneWorldMatrix();
	Transform boneTrans;
	MathLibrary::DecomposeMatrix(boneMat, boneTrans);
	mTransform.lock()->SetWorldMatrix(boneMat);
	mTransform.lock()->SetTransform(boneTrans);
	GetComponent<StaticMeshComponent>()->GetStaticMesh()->SetWorldMatrix(boneMat);	
}

