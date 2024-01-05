//--------- INCLUES ---------
#include "CinematicCamera.h"
#include "../../../System/RendererSystem/DebugRenderer/DebugRendererManager.h"
#include "../../../System/AssetSystem/JsonFile/JsonIncludes.h"
#include"../../../ImGui/ImGuiUtility.h"
#include "../../../Utility/MathLibrary.h"
#include "../../Resource/Bone.h"
#include "CameraIncludes.h"


CinematicCamera::CinematicCamera()
	: mbPlay(false)
	, mCurrentPlayTime(0.0)
	, mDuration(0.0f)
{
	// �����Ȃ�
}

CinematicCamera::~CinematicCamera()
{
	// �����Ȃ�
}

void CinematicCamera::Init(std::string_view _filepath)
{
	mSaveFilePath = _filepath.data();
	if (Load())
	{
		// �Ō�̃L�[���Đ����Ԃɐݒ�
		mDuration = mLocalAnimKeys.back().mTime;
	}
}

void CinematicCamera::Update(const double _deltaTime)
{
	// �J�����A�j���[�V�����̏���
	CameraAnimation(_deltaTime);

	Camera::Update(_deltaTime);	
}

void CinematicCamera::CameraAnimation(const double _deltaTime)
{
	if (!mbPlay)
	{
		return;
	}

	// ��Ԍ��A��Ԑ�̃L�[���擾
	CameraAnimationKey keyBase, keyTo;
	GetKey(keyBase, keyTo);

	// �x�[�X���J�b�g�̐ݒ�łȂ��ꍇ�̂ݕ⊮����
	if (!keyBase.mbCut)
	{
		// �J�����ʒu���v�Z
		DirectX::SimpleMath::Vector3 cameraPos;
		InterpCameraAnimationKeyPosition(keyBase, keyTo, cameraPos);
		mTransform.lock()->SetPosition(cameraPos);
	}

	mCurrentPlayTime += _deltaTime;

	// �Đ��I���`�F�b�N
	if (mCurrentPlayTime >= mDuration)
	{
		mbPlay = false;
	}
}

void CinematicCamera::InterpCameraAnimationKeyPosition(CameraAnimationKey& _keyBase, CameraAnimationKey& _keyTo, DirectX::SimpleMath::Vector3& _position)
{
	// �L�[�Ԃł̍Đ����Ԃɐ��K��
	double time = mCurrentPlayTime - _keyBase.mTime;

	// ��ԂɎg���䗦�����߂�
	double t = MathLibrary::Clamp01(time / (_keyTo.mTime - _keyBase.mTime));

	// ���
	_position = DirectX::SimpleMath::Vector3::Lerp(_keyBase.mPosition, _keyTo.mPosition, t);
}

void CinematicCamera::GetKey(CameraAnimationKey& _key1, CameraAnimationKey& _key2)
{
	// �L�[��Time�������Ɋi�[����Ă���̂�Time�����݂̍Đ����Ԃ𒴂�������key�ƂЂƂO��Key���擾
	for (size_t key_i = 0; const CameraAnimationKey& key : mWorldAnimKeys)
	{
		if (mCurrentPlayTime < key.mTime)
		{
			_key1 = mWorldAnimKeys[key_i - 1];
			_key2 = key;
			break;
		}
		key_i++;
	}
}

void CinematicCamera::CalcuFocusPosition()
{
	if (mTargetObject.lock())
	{
		mFocusPosition = mTargetObject.lock()->GetComponent<TransformComponent>()->GetPosition();
		return;
	}

	if (mTargetBone.lock())
	{
	 	DirectX::SimpleMath::Matrix boneMatrix = mTargetBone.lock()->GetBoneWorldMatrix();
		MathLibrary::GetTranslationFromMatrix(boneMatrix, mFocusPosition);
		return;
	}

	// �����_���v�Z����
	Camera::CalcuFocusPosition();
}

void CinematicCamera::ConvertTargetWorldPosition()
{
	// �R�s�[
	mWorldAnimKeys = mLocalAnimKeys;

	// �Ώۂ̃��[���h�s��
	DirectX::SimpleMath::Matrix targetWorldMatrix;

	if (mTargetObject.lock())
	{
		targetWorldMatrix = mTargetObject.lock()->GetComponent<TransformComponent>()->GetWorldMatrix();
	}

	// �{�[�����Z�b�g����Ă���΃{�[���̍s����擾
	if (mTargetBone.lock())
	{
		targetWorldMatrix = mTargetBone.lock()->GetBoneWorldMatrix();	
	}

	// ���[���h�ϊ�
	for (CameraAnimationKey& key : mWorldAnimKeys)
	{
		// ���[���h�ϊ�
		DirectX::SimpleMath::Matrix translation;
		MathLibrary::CreateTranslationMatrix(key.mPosition, translation);
		translation *= targetWorldMatrix;

		// �ʒu�v�f�̎擾
		MathLibrary::GetTranslationFromMatrix(translation, key.mPosition);
	}
}

void CinematicCamera::Save()
{
	std::shared_ptr<AssetHandle> jsonFile = AssetManager::GetInstance().Load<JsonFileProvider>(mSaveFilePath);

	if (!jsonFile->IsValid())
	{
		return;
	}

	nlohmann::json& json = jsonFile->Get<JsonFile>().GetJson();
	json["NumKey"] = mLocalAnimKeys.size();
	for (size_t key_i = 0; const CameraAnimationKey& key : mLocalAnimKeys)
	{
		std::string keyName = std::to_string(key_i) + "Position X";
		json[keyName] = key.mPosition.x;

		keyName = std::to_string(key_i) + "Position Y";
		json[keyName] = key.mPosition.y;

		keyName = std::to_string(key_i) + "Position Z";
		json[keyName] = key.mPosition.z;

		keyName = std::to_string(key_i) + "Time";
		json[keyName] = key.mTime;

		keyName = std::to_string(key_i) + "Cut";
		json[keyName] = key.mbCut;

		key_i++;
	}

	jsonFile->Get<JsonFile>().WriteFile();
}

bool CinematicCamera::Load()
{
	std::shared_ptr<AssetHandle> jsonFile = AssetManager::GetInstance().Load<JsonFileProvider>(mSaveFilePath);

	if (!jsonFile->IsValid())
	{
		return false;
	}

	nlohmann::json json = jsonFile->Get<JsonFile>().GetJson();

	if (!json.contains("NumKey"))
	{
		return false;
	}

	// �z��̊m��
	mLocalAnimKeys.resize(json["NumKey"]);

	for (size_t key_i = 0; CameraAnimationKey & key : mLocalAnimKeys)
	{
		std::string keyName = std::to_string(key_i) + "Position X";
		key.mPosition.x = json[keyName];

		keyName = std::to_string(key_i) + "Position Y";
		key.mPosition.y = json[keyName];

		keyName = std::to_string(key_i) + "Position Z";
		key.mPosition.z = json[keyName];

		keyName = std::to_string(key_i) + "Time";
		key.mTime = json[keyName];

		keyName = std::to_string(key_i) + "Cut";
		key.mbCut = json[keyName];

		key_i++;
	}

	return true;
}

void CinematicCamera::EditAnimation(std::string_view _label)
{
	// �f�o�b�O�łȂ���Ώ������Ȃ�
#ifndef _DEBUG
	return;
#endif // _DEBUG

	ImGuiUtility& imgui = ImGuiUtility::GetInstance();

	ImGui::Begin(_label.data());

	ImGui::Text("CurrentPlayTime %f", mCurrentPlayTime);
	ImGui::Text("Duration %f", mDuration);

	if (ImGui::Button("Play"))
	{
		Play();
	}
	if (ImGui::Button("Stop"))
	{
		mbPlay = false;

	}

	if (ImGui::Button("Save"))
	{
		Save();
	}
	if (ImGui::Button("AddKey"))
	{
		CameraAnimationKey newKey;
		newKey.mPosition = { 0,0,0 };
		newKey.mTime = 0;
		mLocalAnimKeys.emplace_back(newKey);
	}

	// �폜����L�[�̓Y����
	static int deleteKey_i = 0;
	ImGui::InputInt("DeleteKey Index", &deleteKey_i);
	if (ImGui::Button("DeleteKey"))
	{	
		if (deleteKey_i < mLocalAnimKeys.size())
		{
			mLocalAnimKeys.erase(mLocalAnimKeys.begin() + deleteKey_i);
		}
	}

	ImGui::SeparatorText("Key");

	// �L�[�̈ʒu�A���Ԃ̏���\��
	for (size_t key_i = 0; CameraAnimationKey& key : mLocalAnimKeys)
	{		
		imgui.InputVector3((std::to_string(key_i) + ": Position").c_str(), key.mPosition);
		ImGui::InputDouble((std::to_string(key_i) + ": Time").c_str(), &key.mTime);
		ImGui::Checkbox((std::to_string(key_i) + ": Cut").c_str(), &key.mbCut);
		key_i++;
	}
	ImGui::End();

	if (!mbPlay)
	{
		ConvertTargetWorldPosition();
	}
	

	// �Ō�̃L�[���Đ����Ԃɐݒ�
	if (!mLocalAnimKeys.empty())
	{
		mDuration = mLocalAnimKeys.back().mTime;
	}
	
#ifdef _DEBUG
	// �f�o�b�O�\��
	for (CameraAnimationKey & key : mWorldAnimKeys)
	{
		DebugRendererManager::GetInstance().DrawSphere(key.mPosition, 1.0f);
	}
#endif
}

void CinematicCamera::Play()
{
	// �f�[�^�����邩���m�F
	if (mLocalAnimKeys.empty())
	{
		return;
	}

	// ���[���h��ԂɃR���o�[�g����
	ConvertTargetWorldPosition();
	mbPlay = true;

	// �Ō�̃L�[���Đ����Ԃɐݒ�
	mDuration = mLocalAnimKeys.back().mTime;

	mCurrentPlayTime = 0.0f;

	// �J�n�ʒu�̃Z�b�g
	mTransform.lock()->SetPosition(mWorldAnimKeys[0].mPosition);

	// ���C���J�����ɃZ�b�g����
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->SetMainCameraByName(mName);

}

CinematicCamera::CameraAnimationKey::CameraAnimationKey()
	: mTime(0.0f)
	, mbCut(false)
{
}
