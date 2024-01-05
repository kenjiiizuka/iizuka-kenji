//------------- INCLUDES -------------
#include "SkeletalMeshAsset.h"


SkeletalMeshAsset::SkeletalMeshAsset()
{
	// �����Ȃ�
}

SkeletalMeshAsset::~SkeletalMeshAsset()
{
	// �����Ȃ�
}

SkeletalMeshAsset::Vertex::Vertex()
	: mBoneIndices()
	, mWeights()
{
	// �z��̏�����
	for (size_t i = 0; i < 4; i++)
	{
		mBoneIndices[i] = -1;
		mWeights[i] = -1;
	}	
}

SkeletalMeshAsset::Vertex::Vertex(const DirectX::SimpleMath::Vector3 _position, const DirectX::SimpleMath::Vector3 _normal, const DirectX::SimpleMath::Vector2 _uv, const DirectX::SimpleMath::Vector4 _color)
	: mPosition(_position)
	, mNormal(_normal)
	, mUV(_uv)
	, mColor(_color)
	, mBoneIndices()
	, mWeights()
{
	// �z��̏�����
	for (size_t i = 0; i < 4; i++)
	{
		mBoneIndices[i] = -1;
		mWeights[i] = -1;
	}
}
