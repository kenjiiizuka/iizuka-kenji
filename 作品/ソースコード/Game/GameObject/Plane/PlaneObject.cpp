#include "PlaneObject.h"
#include "../../Component/PlaneComponent/PlaneComponent.h"

using namespace DirectX::SimpleMath;

void PlaneObject::Init(const std::string& _textureFilePaht, float _size, bool _isLighting)
{
	std::shared_ptr<PlaneComponent> plane = AddComponent<PlaneComponent>();
	plane->Init({ _size,0.0f,_size }, { 0.0f,0.0f,0.0f }, _textureFilePaht, _isLighting);
}

void PlaneObject::Draw()
{
	
}
