//---------- INCLUDES -----------
#include "PlaneObject.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"

using namespace DirectX::SimpleMath;

void PlaneObject::Init(const std::string& _textureFilePaht, float _size, bool _isLighting)
{
	std::shared_ptr<PlaneComponent> plane = AddComponent<PlaneComponent>();
	RendererInf::Layer layer = _isLighting ? RendererInf::Layer_Object : RendererInf::Layer_BackGround;
	plane->Init({ _size,0.0f,_size }, { 0.0f,0.0f,0.0f }, _textureFilePaht, layer,_isLighting);
	mPlane = plane;
}

void PlaneObject::Draw()
{
	mPlane.lock()->SetWorldMatrix(mTransform.lock()->GetWorldMatrix());
}
