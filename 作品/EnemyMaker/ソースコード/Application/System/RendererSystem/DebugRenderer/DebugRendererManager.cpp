#ifdef _DEBUG
//-------------- includes -------------------
#include "DebugRendererManager.h"
#include "../../../Game/Component/StaticMeshComponent/StaticMeshComponent.h"
#include "../RendererManager.h"
#include "../Shader/VertexShader/Object3DVertexShader.h"
#include "../Shader/PixelShader/LightPixelShader.h"
#include "../../../Utility/MathLibrary.h"
#include "../../RendererSystem/VisualEntity/VisualEntity.h"
#include "../../../Game/Component/StaticMeshComponent/StaticMesh.h"
#include "../../AssetSystem/StaticMesh/StaticMeshProvider.h"
#include "../../AssetSystem/AssetManager.h"

DebugRendererManager::DebugRendererManager()
{
	// 処理なし
}

DebugRendererManager::~DebugRendererManager()
{
	// 処理なし
}

void DebugRendererManager::Init()
{
	// 半球メッシュの読み込み
	mHalfCircleMesh = std::make_shared<StaticMesh>();
	// 半球メッシュロード
	AssetManager::GetInstance().Load<StaticMeshProvider>("assets/Debug/HalfSphere.fbx");

	// 板メッシュの読み込み
	mPlaneMesh = std::make_shared<StaticMesh>();
	// 板メッシュロード
	AssetManager::GetInstance().Load<StaticMeshProvider>("assets/Debug/Plane.fbx");

	// 球メッシュ読み込み
	mSphereMesh = std::make_shared<StaticMesh>();
	AssetManager::GetInstance().Load<StaticMeshProvider>("assets/Debug/Sphere.fbx");
}

void DebugRendererManager::Update()
{
	// 配列にあるデバッグ描画オブジェクトの描画したフレーム数カウントを進める

	// 半球
	for (auto halfCircle_it = mDrawHalfCircles.begin(); halfCircle_it != mDrawHalfCircles.end();)
	{
		// 描画したフレーム数が、指定されたフレーム数を描画されたか判断する
		if (halfCircle_it->mCurrentDrewFrameCount >= halfCircle_it->mDrawFrame)
		{
			// メッシュを解放して配列からも除外
			halfCircle_it->mMesh.reset();
			halfCircle_it = mDrawHalfCircles.erase(halfCircle_it);
		}
		else
		{
			halfCircle_it++;
		}
	}

	// ライン
	for (auto lines_it = mDrawLines.begin(); lines_it != mDrawLines.end();)
	{
		// 描画したフレーム数が、指定されたフレーム数を描画されたか判断する
		if (lines_it->mCurrentDrewFrameCount >= lines_it->mDrawFrame)
		{
			// メッシュを解放して配列からも除外
			lines_it->mMesh.reset();
			lines_it = mDrawLines.erase(lines_it);
		}
		else
		{
			lines_it++;
		}
	}

	// プレーン
	for (auto plane_it = mDrawPlanes.begin(); plane_it != mDrawPlanes.end();)
	{
		// 描画したフレーム数が、指定されたフレーム数を描画されたか判断する
		if (plane_it->mCurrentDrewFrameCount >= plane_it->mDrawFrame)
		{
			// メッシュを解放して配列からも除外
			plane_it->mMesh.reset();
			plane_it = mDrawPlanes.erase(plane_it);
		}
		else
		{
			plane_it++;
		}
	}

	for (auto sphere_it = mDrawSpheres.begin(); sphere_it != mDrawSpheres.end();)
	{
		if (sphere_it->mCurrentDrawFrameCount >= sphere_it->mDrawFrame)
		{
			sphere_it->mMesh.reset();
			sphere_it = mDrawSpheres.erase(sphere_it);
		}
		else
		{
			sphere_it++;
		}
	}
}

void DebugRendererManager::Draw()
{
	// 配列にあるデバッグ描画オブジェクトの描画したフレーム数カウントを進める
	for (DebugDrawHalfCircle& halfCircle : mDrawHalfCircles)
	{
		halfCircle.mCurrentDrewFrameCount++;
	}

	for(DebugDrawPlane& plane : mDrawPlanes)
	{ 
		plane.mCurrentDrewFrameCount++;
	}

	for (DebugDrawLine& line : mDrawLines)
	{
		line.mCurrentDrewFrameCount++;
	}

	for (DebugDrawSphere& sphere : mDrawSpheres)
	{
		sphere.mCurrentDrawFrameCount++;
	}
}

void DebugRendererManager::DrawSetup(const Transform& _trans, std::shared_ptr<VisualEntity> _visualEntity, const DirectX::SimpleMath::Vector4& _diffuse)
{
	// 行列作成
	DirectX::SimpleMath::Matrix worldMatrix = MathLibrary::MakeWorldMatrix(_trans);

	// 行列のセット
	_visualEntity->SetWorldMatrix(worldMatrix);

	// 網目状に表示
	_visualEntity->SetCullType(CullType::Draw_WireFrame);

	// マテリアル色のセット
	_visualEntity->GetVisualEntityData(0)->SetMaterialDiffuse(_diffuse);
}

void DebugRendererManager::DrawHalfCircle(const float _radius, const DirectX::SimpleMath::Vector3 _position, const uint16_t _drawFrame, DirectX::SimpleMath::Vector4 _color)
{
	// 半球の生成
	DebugDrawHalfCircle halfCircle(_drawFrame, _radius);

	halfCircle.mMesh->Initialize("assets/Debug/HalfSphere.fbx");
	
	// 描画位置を設定するためのワールド行列を設定する
	// スケールは半径と一致するようにする
	// 行列を作成するためのトランスフォームの設定
	Transform transform;
	transform.mPosition = _position;
	transform.mScale = { _radius,_radius,_radius };
	
	// 描画情報を取得
	std::weak_ptr<VisualEntity> visualEntity = halfCircle.mMesh->GetVisualEntity();

	// NULLチェック
	if (!visualEntity.lock())
	{
		return;
	}

	// 描画周りのセットアップ
	DrawSetup(transform, visualEntity.lock(), _color);

	// デバッグ描画配列に追加
	mDrawHalfCircles.emplace_back(halfCircle);
}

void DebugRendererManager::DrawPlane(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _scale, const DirectX::SimpleMath::Vector3 _rotation, const uint16_t _drawFrame, const DirectX::SimpleMath::Vector4 _color)
{
	// 描画用の板メッシュの生成
	DebugDrawPlane plane(_drawFrame);

	// キャッシュから読み込み
	plane.mMesh->Initialize("assets/Debug/Plane.fbx");

	// 描画位置の設定
	Transform trans(_position, _scale, _rotation);
		
	// 描画用オブジェクトを取得
	std::weak_ptr<VisualEntity> visualEntity = plane.mMesh->GetVisualEntity();

	// NULLチェック
	if (!visualEntity.lock())
	{
		return;
	}

	// 描画周りのセットアップ
	DrawSetup(trans,visualEntity.lock(), _color);

	// 配列への追加
	mDrawPlanes.emplace_back(plane);
}

void DebugRendererManager::DrawSegment(const DirectX::SimpleMath::Vector3 _startPosition, const DirectX::SimpleMath::Vector3 _endPosition, const uint16_t _drawFrame, const DirectX::SimpleMath::Vector4 _color)
{
	DebugDrawLine line(_drawFrame);

	// 頂点の位置を設定
	Vertex* vertex = new Vertex[2];
	vertex[0].mPosition = _startPosition;
	vertex[0].mNormal = { 0.0, 1.0f, 0.0f };
	vertex[0].mTexCoord = { 0.0f,0.0f };
	vertex[0].mDiffuse = _color;

	vertex[1].mPosition = _endPosition;
	vertex[1].mNormal = { 0.0, 1.0f, 0.0f };
	vertex[1].mTexCoord = { 0.0f,0.0f };
	vertex[1].mDiffuse = _color;

	std::shared_ptr<void> vertexData(
		vertex,
		[](void* data) {delete[] static_cast<Vertex*>(data); }
	);

	VisualEntityData::Description desc{};
	desc.mbAbleMap = false;
	desc.mbUseIndex = false;
	desc.mIndexCount = 0;
	desc.mIndexTypeByteSize = 0;
	desc.mpIndex = nullptr;
	desc.mpVertex = vertexData;
	desc.mVertexCount = 4;
	desc.mVertexTypeByteSize = sizeof(Vertex);
	desc.mTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

	std::shared_ptr<VisualEntityData> visualData = std::make_shared<VisualEntityData>(desc);
	VisualEntityData::Material material;
	material.mDiffuse = _color;
	visualData->SetMaterial(material);

	line.mMesh = std::make_shared<VisualEntity>(visualData);

	line.mMesh->MakePixelShader<LightPixelShader>();
	line.mMesh->MakeVertexShader<Object3DVertexShader>();

	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::Identity;			// 単位行列にする
	line.mMesh->SetWorldMatrix(world);

	RendererManager::GetInstance().RegisterEntity(line.mMesh, RendererInf::Layer_Object);

	// デバッグ描画配列に追加
	mDrawLines.emplace_back(line);
}

void DebugRendererManager::DrawSphere(const DirectX::SimpleMath::Vector3 _centerPosition, const float _radius, const uint16_t _drawFrame, const DirectX::SimpleMath::Vector4 _color)
{
	// 描画用の球の作成
	DebugDrawSphere sphere(_drawFrame, _radius);
	sphere.mMesh->Initialize("assets/Debug/Sphere.fbx");

	Transform transform(_centerPosition, { _radius, _radius, _radius }, { 0,0,0 });

	// 描画用オブジェクトを取得
	std::weak_ptr<VisualEntity> visualEntity = sphere.mMesh->GetVisualEntity();

	// NULLチェック
	if (!visualEntity.lock())
	{
		return;
	}

	// 描画周りのセットアップ
	DrawSetup(transform, visualEntity.lock(), _color);

	// 配列に追加
	mDrawSpheres.emplace_back(sphere);
}

DebugRendererManager::DebugDrawHalfCircle::DebugDrawHalfCircle(const uint16_t _drawFrame, const float _radius)
	: mDrawFrame(_drawFrame)
	, mCurrentDrewFrameCount(0)
	, mRadius(_radius)
{
	mMesh = std::make_shared<StaticMesh>();
}

DebugRendererManager::DebugDrawPlane::DebugDrawPlane(const uint16_t _drawFrame)
	: mDrawFrame(_drawFrame)
	, mCurrentDrewFrameCount(0)
{
	mMesh = std::make_shared<StaticMesh>();
}

DebugRendererManager::DebugDrawLine::DebugDrawLine(const uint16_t _drawFrame)
	: mDrawFrame(_drawFrame)
	, mCurrentDrewFrameCount(0)
{		
}

DebugRendererManager::DebugDrawSphere::DebugDrawSphere(const uint16_t _drawFrame, const float _radius)
	: mDrawFrame(_drawFrame)
	, mCurrentDrawFrameCount(0)
	, mRadius(_radius)
{
	mMesh = std::make_shared<StaticMesh>();
}

#endif _DEBUG

