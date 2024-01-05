//------------- INCLUDES ------------
#include "StaticMeshAsset.h"

StaticMeshAsset::StaticMeshAsset()
{
	// ˆ—‚È‚µ
}

StaticMeshAsset::~StaticMeshAsset()
{
	// ˆ—‚È‚µ
}

StaticMeshAsset::Vertex::Vertex()
{
	// ˆ—‚È‚µ
}

StaticMeshAsset::Vertex::Vertex(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _normal, const DirectX::SimpleMath::Vector2& _uv, const DirectX::SimpleMath::Vector4& _color)
	: mPosition(_position)
	, mNormal(_normal)
	, mUV(_uv)
	, mColor(_color)
{
	// ˆ—‚È‚µ
}
