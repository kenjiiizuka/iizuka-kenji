#pragma once
#include "../Scene.h"
class DebugScene : public Scene
{
private:
  // std::weak_ptr<class Transition> mTransition;
public:
    void Initialize() override;
    void Update() override;
    void Uninitialize() override; 
};

