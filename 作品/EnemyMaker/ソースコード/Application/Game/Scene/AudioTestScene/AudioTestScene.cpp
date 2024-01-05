//------------ INCLUDES -----------
#include "AudioTestScene.h"
#include "../../../System/Audio/audio.h"
#include "../../../ImGui/ImGuiUtility.h"
#include "../../../System/AssetSystem/Audio/AudioProvider.h"
#include "../../../System/AssetSystem/AssetManager.h"
#include "../../Resource/AudioClip.h"
#include "../../../System/Logger/Logger.h"
#include "../../../System/AudioSystem/AudioSystem.h"
#include "../../../Utility/CurveFloat.h"

std::shared_ptr<AudioClip> audioClip;

std::shared_ptr<CurveFloat> curve;

AudioTestScene::AudioTestScene()
{
}

void AudioTestScene::Initialize()
{
	audioClip = std::make_shared<AudioClip>();
	audioClip->Initialize("assets/audio/bgm.wav");
	audioClip->SetLoop(false);

	curve = std::make_shared<CurveFloat>();
	curve->Initialize("assets/Curve.json");
}

void AudioTestScene::Uninitialize()
{
	curve.reset();
}

void AudioTestScene::Update()
{
	ImGui::Begin("SoundPlay");
	if (ImGui::Button("Play"))
	{
		AudioSystem::GetInstance().SpawnAudioEmitterAndPlay(audioClip, { 0,0,0 }, { 0,0,0 });
	}
	else if (ImGui::Button("Stop"))
	{
		audioClip->Stop();
	}
	else if (ImGui::Button("Resume"))
	{
		
	}
	ImGui::End();

	curve->Edit("CurveTest");

	if (!ImGui::Button("Value"))
	{
		return;
	}

	for (float time = 0.01f; time < 1.0f; time += 0.01f)
	{
		std::cout << "Time " << time << "sec" << " : " << "Value " << curve->GetValueByTime(time) << std::endl;
	}


}
