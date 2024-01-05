//---------- INCLUDES -----------
#include "BattleSoundManager.h"
#include "../../../System/AudioSystem/AudioSystemIncludes.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../Utility/MathLibrary.h"

BattleSoundManager::BattleSoundManager()
{
}

BattleSoundManager::~BattleSoundManager()
{
}

void BattleSoundManager::Initialize()
{
	mBattleBGM = std::make_shared<AudioClip>();
	mBattleBGM->Initialize("assets/Battle/Audio/Battle.wav");
	mBattleBGM->SetLoop(true);
}

void BattleSoundManager::Update()
{

}

void BattleSoundManager::PlayBattleBGM()
{
	mBattleBGM->Play();
	mBattleBGM->SetVolume(0.2f);
}

void BattleSoundManager::StopBattleBGM()
{
	mBattleBGM->Stop();
}
