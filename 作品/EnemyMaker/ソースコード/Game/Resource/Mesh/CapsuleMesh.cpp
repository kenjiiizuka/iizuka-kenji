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
	// �����Ȃ�
}

CapsuleMesh::~CapsuleMesh()
{
	// �����Ȃ�
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

	// ���_�f�[�^�쐬
	MakeVertexData(desc);

	// �C���f�b�N�X�f�[�^�쐬
	MakeIndexData(desc);

	// �`��I�u�W�F�N�g�f�[�^�̍쐬
	std::shared_ptr<VisualEntityData> entityData = std::make_shared<VisualEntityData>(desc);

	// �`��I�u�W�F�N�g���쐬
	mVisualEntity = std::make_shared<VisualEntity>(entityData);

	// �V�F�[�_�[�̃Z�b�g
	mVisualEntity->MakeVertexShader<Object3DVertexShader>();
	mVisualEntity->MakePixelShader<LightPixelShader>();

	// �����_���[�}�l�[�W���[�ɓo�^
	RendererManager::GetInstance().RegisterEntity(mVisualEntity, RendererInf::Layer_Object);

	mVisualEntity->SetDrawType(DrawType::Draw_WireFrame, 0);
}

void CapsuleMesh::MakeVertexData(VisualEntityData::Description& _desc)
{
	std::vector<Vertex> vertices = CalucCapsuleVertexPosition();

	// ���_�f�[�^��`��f�[�^�ɃZ�b�g����
	size_t vertexDataSize = vertices.size();
	Vertex* verticesData = new Vertex[vertexDataSize];

	// ���_�f�[�^��������
	for (size_t vertices_i = 0; vertices_i < vertexDataSize; vertices_i++)
	{
		verticesData[vertices_i] = vertices[vertices_i];
	}
	// ���_�f�[�^��std::shared<void>�^�ɑ��
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

	// �C���f�b�N�X����
	for (size_t y_i = 0; y_i < mDivisionVertical; y_i++)
	{
		for (unsigned int x_i = 0; x_i < mDivisionHorizontal; x_i++)
		{
			uint32_t count = static_cast<uint32_t>((mDivisionHorizontal + 1) * y_i + x_i);			// ������W�̃C���f�b�N�X

			// �㔼��
			uint32_t index[3] =
			{
				count,
				count + 1,
				count + 1 + (mDivisionHorizontal + 1)
			};

			indices.emplace_back(index[0]);
			indices.emplace_back(index[1]);
			indices.emplace_back(index[2]);

			// ������
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

	// �C���f�b�N�X�f�[�^��������
	for (size_t indices_i = 0; indices_i < indexDataSize; indices_i++)
	{
		indicesData[indices_i] = indices[indices_i];
	}

	std::shared_ptr<void> indexData(
		indicesData,
		[](void* data) {delete[] static_cast<uint32_t*>(data); }
	);

	// �f�[�^��`��f�[�^�ɃZ�b�g����
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

	// �J�v�Z�� �㔼��
	for (size_t y_i = 0; y_i <= mDivisionVertical / 2; y_i++)
	{
		float elevation = PIFloat * static_cast<float>(y_i) / mDivisionVertical; // �p���v�Z
		float r = mRadius * sinf(elevation);						        // �p�ɉ��������a���v�Z

		for (size_t x_i = 0; x_i <= mDivisionHorizontal; x_i++)
		{
			float azimuth = (2 * DirectX::XM_PI * static_cast<float>(x_i)) / divisionX;	// ���ʊp���Z�b�g

			// ���_�ʒu�����߂�
			Vertex vertex;
			vertex.mPosition.x = r * cosf(azimuth);
			vertex.mPosition.y = mRadius * cosf(elevation) + mHeight;
			vertex.mPosition.z = r * sinf(azimuth);

			// �@�������߂�
			vertex.mNormal = vertex.mPosition;
			vertex.mNormal.Normalize();

			// ���_�J���[
			vertex.mDiffuse = { 1.0f,1.0f,1.0f,1.0f };

			vertices.emplace_back(vertex);
		}
	}

	// �J�v�Z�� ������
	for (size_t y_i = mDivisionVertical / 2; y_i <= mDivisionVertical; y_i++)
	{
		float elevation = PIFloat * static_cast<float>(y_i) / mDivisionVertical; // �p���v�Z
		float r = mRadius * sinf(elevation);						        // �p�ɉ��������a���v�Z

		for (size_t x_i = 0; x_i <= mDivisionHorizontal; x_i++)
		{
			float azimuth = (2 * DirectX::XM_PI * static_cast<float>(x_i)) / divisionX;	// ���ʊp���Z�b�g

			// ���_�ʒu�����߂�
			Vertex vertex;
			vertex.mPosition.x = r * cosf(azimuth);
			vertex.mPosition.y = mRadius * cosf(elevation) - mHeight;
			vertex.mPosition.z = r * sinf(azimuth);

			// �@�������߂�
			vertex.mNormal = vertex.mPosition;
			vertex.mNormal.Normalize();

			// ���_�J���[
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
