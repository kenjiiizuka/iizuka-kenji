//----------- INCLUDES ----------
#include "CapsuleMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/Object3DVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "../../../System/RendererSystem/RendererManager.h"
#include "../.././../Utility/MathLibrary.h"

CapsuleMesh::CapsuleMesh()
	: mRadius(0.0f)
	, mHeight(0.0f)
	, mDivisionHorizontal(0)
	, mDivisionVertical(0)
{
	// 処理なし
}

CapsuleMesh::~CapsuleMesh()
{
	// 処理なし
}

void CapsuleMesh::Initialize(const float _radius, const float _height, const uint16_t _divisionHorizontal, const uint16_t _divisionVertical)
{
	mRadius = _radius;
	mHeight = _height;
	mDivisionHorizontal = _divisionHorizontal;
	mDivisionVertical = _divisionVertical;
	CreateVisualEntity();
}

void CapsuleMesh::Draw()
{
	mTransform.mScale = { 1, 1, 1 };
	mWorldMatrix = MathLibrary::MakeWorldMatrix(mTransform);
	StaticMesh::Draw();
}

void CapsuleMesh::CreateVisualEntity()
{
	VisualEntityData::Description desc;
	desc.mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	desc.mbAbleMap = true;

	// 頂点データ作成
	MakeVertexData(desc);

	// インデックスデータ作成
	MakeIndexData(desc);

	// 描画オブジェクトデータの作成
	std::shared_ptr<VisualEntityData> entityData = std::make_shared<VisualEntityData>(desc);

	// 描画オブジェクトを作成
	mVisualEntity = std::make_shared<VisualEntity>(entityData);

	// シェーダーのセット
	mVisualEntity->MakeVertexShader<Object3DVertexShader>();
	mVisualEntity->MakePixelShader<LightPixelShader>();

	// レンダラーマネージャーに登録
	RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);

	mVisualEntity->SetDrawType(DrawType::Draw_WireFrame, 0);
}

void CapsuleMesh::MakeVertexData(VisualEntityData::Description& _desc)
{
	std::vector<Vertex> vertices = CalucCapsuleVertexPosition();

	// 頂点データを描画データにセットする
	size_t vertexDataSize = vertices.size();
	Vertex* verticesData = new Vertex[vertexDataSize];

	// 頂点データを代入する
	for (size_t vertices_i = 0; vertices_i < vertexDataSize; vertices_i++)
	{
		verticesData[vertices_i] = vertices[vertices_i];
	}
	// 頂点データをstd::shared<void>型に代入
	std::shared_ptr<void> vertexData(
		verticesData,
		[](void* data) {delete[] static_cast<Vertex*>(data); }
	);

	_desc.mpVertex = vertexData;
	_desc.mVertexCount = static_cast<uint32_t>(vertices.size());
	_desc.mVertexTypeByteSize = sizeof(Vertex);
}

void CapsuleMesh::MakeIndexData(VisualEntityData::Description& _desc)
{
	std::vector<uint32_t> indices;

	// インデックス生成
	for (size_t y_i = 0; y_i < mDivisionVertical; y_i++)
	{
		for (unsigned int x_i = 0; x_i < mDivisionHorizontal; x_i++)
		{
			uint32_t count = static_cast<uint32_t>((mDivisionHorizontal + 1) * y_i + x_i);			// 左上座標のインデックス

			// 上半分
			uint32_t index[3] =
			{
				count,
				count + 1,
				count + 1 + (mDivisionHorizontal + 1)
			};

			indices.emplace_back(index[0]);
			indices.emplace_back(index[1]);
			indices.emplace_back(index[2]);

			// 下半分
			index[0] = count;
			index[1] = count + (mDivisionHorizontal + 1) + 1;
			index[2] = count + (mDivisionHorizontal + 1);

			indices.emplace_back(index[0]);
			indices.emplace_back(index[1]);
			indices.emplace_back(index[2]);
		}
	}

	size_t indexDataSize = indices.size();
	uint32_t* indicesData = new uint32_t[indexDataSize];

	// インデックスデータを代入する
	for (size_t indices_i = 0; indices_i < indexDataSize; indices_i++)
	{
		indicesData[indices_i] = indices[indices_i];
	}

	std::shared_ptr<void> indexData(
		indicesData,
		[](void* data) {delete[] static_cast<uint32_t*>(data); }
	);

	// データを描画データにセットする
	_desc.mbUseIndex = true;
	_desc.mpIndex = indexData;
	_desc.mIndexCount = static_cast<uint32_t>(indices.size());
	_desc.mIndexTypeByteSize = sizeof(uint32_t);
}

std::vector<Vertex> CapsuleMesh::CalucCapsuleVertexPosition()
{
	std::vector<Vertex> vertices;
	float divisionX = static_cast<float>(mDivisionHorizontal);
	float divisionY = static_cast<float>(mDivisionVertical);

	// カプセル 上半球
	for (size_t y_i = 0; y_i <= mDivisionVertical / 2; y_i++)
	{
		float elevation = PIFloat * static_cast<float>(y_i) / mDivisionVertical; // 仰角を計算
		float r = mRadius * sinf(elevation);						        // 仰角に応じた半径を計算

		for (size_t x_i = 0; x_i <= mDivisionHorizontal; x_i++)
		{
			float azimuth = (2 * DirectX::XM_PI * static_cast<float>(x_i)) / divisionX;	// 方位角をセット

			// 頂点位置を求める
			Vertex vertex;
			vertex.mPosition.x = r * cosf(azimuth);
			vertex.mPosition.y = mRadius * cosf(elevation) + mHeight;
			vertex.mPosition.z = r * sinf(azimuth);

			// 法線を求める
			vertex.mNormal = vertex.mPosition;
			vertex.mNormal.Normalize();

			// 頂点カラー
			vertex.mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

			vertices.emplace_back(vertex);
		}
	}

	// カプセル 下半球
	for (size_t y_i = mDivisionVertical / 2; y_i <= mDivisionVertical; y_i++)
	{
		float elevation = PIFloat * static_cast<float>(y_i) / mDivisionVertical; // 仰角を計算
		float r = mRadius * sinf(elevation);						        // 仰角に応じた半径を計算

		for (size_t x_i = 0; x_i <= mDivisionHorizontal; x_i++)
		{
			float azimuth = (2 * DirectX::XM_PI * static_cast<float>(x_i)) / divisionX;	// 方位角をセット

			// 頂点位置を求める
			Vertex vertex;
			vertex.mPosition.x = r * cosf(azimuth);
			vertex.mPosition.y = mRadius * cosf(elevation) - mHeight;
			vertex.mPosition.z = r * sinf(azimuth);

			// 法線を求める
			vertex.mNormal = vertex.mPosition;
			vertex.mNormal.Normalize();

			// 頂点カラー
			vertex.mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

			vertices.emplace_back(vertex);
		}
	}
	return vertices;
}

void CapsuleMesh::SetRadius(const float _radius)
{
	mRadius = _radius;
	mVisualEntity->GetVisualEntityData(0)->MapVertexBuffer(CalucCapsuleVertexPosition().data());
}

void CapsuleMesh::SetHeight(const float _height)
{
	mHeight = _height;
	mVisualEntity->GetVisualEntityData(0)->MapVertexBuffer(CalucCapsuleVertexPosition().data());
}
