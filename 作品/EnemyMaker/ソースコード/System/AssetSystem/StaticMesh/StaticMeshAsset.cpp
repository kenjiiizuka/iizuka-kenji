//------------- INCLUDES ------------
#include "StaticMeshAsset.h"

StaticMeshAsset::StaticMeshAsset()
{
	// �����Ȃ�
}

StaticMeshAsset::~StaticMeshAsset()
{
	// �����Ȃ�
}

StaticMeshAsset::Vertex::Vertex()
{
	// �����Ȃ�
}

StaticMeshAsset::Vertex::Vertex(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _normal, const DirectX::SimpleMath::Vector2& _uv, const DirectX::SimpleMath::Vector4& _color)
	: mPosition(_position)
	, mNormal(_normal)
	, mUV(_uv)
	, mColor(_color)
{
	// �����Ȃ�
}
