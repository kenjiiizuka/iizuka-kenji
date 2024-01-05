#pragma once
#include "../Scene.h"

/**
* @class AudioTestScene
*/
class AudioTestScene : public Scene
{
public:
	AudioTestScene();


	void Initialize() override;

	void Uninitialize() override;

	void Update() override;

};

