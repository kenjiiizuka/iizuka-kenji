//------------- INCLUDES --------------
#include "SphereMesh.h"
#include "../../../System/RendererSystem/Shader/VertexShader/Object3DVertexShader.h"
#include "../../../System/RendererSystem/Shader/PixelShader/LightPixelShader.h"
#include "../../../System/RendererSystem/RendererManager.h"

SphereMesh::SphereMesh()
	: mRadius(1.0f)
	, mDivisionHorizontal(100)
	, mDivisionVertical(100)
{
	// �����Ȃ�
}

SphereMesh::~SphereMesh()
{
	// �����Ȃ�
}

void SphereMesh::Initialize(const float _radius, const uint16_t _divisionHorizontal, const uint16_t _divisionVertical)
{
	mRadius = _radius;
	mDivisionHorizontal = _divisionHorizontal;
	mDivisionVertical = _divisionVertical;

	CreateVisualEntity();
}

void SphereMesh::CreateVisualEntity()
{
	VisualEntityData::Description desc;
	desc.mbAbleMap = true; // Map�\�ɐݒ�

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
}

void SphereMesh::MakeVertexData(VisualEntityData::Description& _desc)
{
	std::vector<Vertex> vertices;
	float divisionX = static_cast<float>(mDivisionHorizontal);
	float divisionY = static_cast<float>(mDivisionVertical);

	// ���ʊp�Ƌp���狅���b�V���̒��_�f�[�^���쐬
	for (size_t y_i = 0; y_i <= mDivisionVertical; y_i++) 
	{
		float elevation = (2 * DirectX::XM_PI * static_cast<float>(y_i)) / divisionY; // �p���Z�b�g
		float r = mRadius * sinf(elevation);						        // �p�ɉ��������a���v�Z
		
		for (size_t x_i = 0; x_i <= mDivisionHorizontal; x_i++) 
		{
			float azimuth = (2 * DirectX::XM_PI * static_cast<float>(x_i)) / divisionX;	// ���ʊp���Z�b�g

			// ���_�ʒu�����߂�
			Vertex vertex;
			vertex.mPosition.x = r * cosf(azimuth);
			vertex.mPosition.y = mRadius * cosf(elevation);
			vertex.mPosition.z = r * sinf(azimuth);

			// �@�������߂�
			vertex.mNormal = vertex.mPosition;
			vertex.mNormal.Normalize();

			// ���_�J���[
			vertex.mDiffuse = { 1.0f,1.0f,1.0f,1.0f };				

			vertices.emplace_back(vertex);
		}
	}

	// ���_�f�[�^��`��f�[�^�ɃZ�b�g����
	Vertex* verticesData = new Vertex[vertices.size()];

	// ���_�f�[�^��������
	for (size_t vertices_i = 0; vertices_i < vertices.size(); vertices_i++)
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

void SphereMesh::MakeIndexData(VisualEntityData::Description& _desc)
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

	uint32_t* indicesData = new uint32_t[indices.size()];

	// �C���f�b�N�X�f�[�^��������
	for (size_t indices_i = 0; indices_i < indices.size(); indices_i++)
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
