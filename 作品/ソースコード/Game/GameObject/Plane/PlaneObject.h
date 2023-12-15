#pragma once
#include "../GameObject.h"

class PlaneComponent;

class PlaneObject : public GameObject
{
private:
	std::weak_ptr<PlaneComponent> mPlane;

public:
	void Init(const std::string& _textureFilePaht, float _size, bool _isLighting = true);
	void Draw() override;
};

