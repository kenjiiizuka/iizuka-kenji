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
	AudioSystem::GetInstance().SpawnAudioEmitterAndPlay(mBattleBGM, {0.0f,0.0f,0.0f}, { 100.0f,0.0f,100.0f }, 150.0f);
	mBattleBGM->SetVolume(1.0f);
}

void BattleSoundManager::StopBattleBGM()
{
	mBattleBGM->Stop();
}
