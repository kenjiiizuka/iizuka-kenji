//------- INCLUDES --------
#include "CurveFloat.h"
#include "../System/AssetSystem/JsonFile/JsonIncludes.h"
#include "MathLibrary.h"

CurveFloat::CurveFloat()
{
	mCurveKey = { {0.0f,0.5f}, {1.0f,0.5f} };
}

CurveFloat::~CurveFloat()
{
	// �����Ȃ�
}

void CurveFloat::Initialize(std::string_view _filePath)
{
	mFilePath = _filePath.data();

	// �t�@�C�����J��
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<JsonFileProvider>(mFilePath);
	if (!handle->IsValid())
	{
		return;
	}

	// �f�[�^�����邩���m�F
	nlohmann::json& jsonFile = handle->Get<JsonFile>().GetJson();
	if (!jsonFile.contains("NumKey"))
	{
		return;
	}

	// �|�C���g�̐����擾
	size_t keyNum = jsonFile["NumKey"];

	// �T�C�Y�m��
	mCurveKey.resize(keyNum);

	// �|�C���g�̒l���擾
	for (size_t key_i = 0; ImVec2 & key : mCurveKey)
	{
		std::string keyX = "Point X" + std::to_string(key_i);
		std::string keyY = "Point Y" + std::to_string(key_i);
		key.x = jsonFile[keyX];
		key.y = jsonFile[keyY];
		key_i++;
	}
}

void CurveFloat::Edit(std::string_view _label)
{
	ImGui::Begin(_label.data());

	if (ImGui::Button("Save"))
	{
		Save();
	}

	if (ImGui::Button("AddKey"))
	{
		// �����̗v�f�Ɩ����̂ЂƂO�̗v�f�̊Ԃ̒l��ǉ�����
		ImVec2 last = mCurveKey.back();
		ImVec2 last_2 = *std::prev(mCurveKey.end(), 2);
		ImVec2 newPos;
		newPos.x = last.x + last_2.x;
		newPos.y = last.y + last_2.y;
		newPos.x /= 2.0f;
		newPos.y /= 2.0f;
		mCurveKey.emplace_back(newPos);

		// �����̗v�f�̒l��X���ő�ɂȂ�悤�ɓ���ւ���
		mCurveKey[mCurveKey.size() - 1] = last;
		mCurveKey[mCurveKey.size() - 2] = newPos;
	}
	if (ImGui::Button("DecreaseKey"))
	{
		ImVec2 last = mCurveKey.back();
		mCurveKey.resize(mCurveKey.size() - 1);
		mCurveKey.back() = last;
	}

	ImGui::Text("Key Num %d", mCurveKey.size());

	ImGui::Curve("Curve", ImVec2(600, 200), static_cast<int>(mCurveKey.size()), mCurveKey.data());
	
	// �J�[�u�|�C���g�̈ʒu��\��
	for (size_t i = 0; ImVec2 vec : mCurveKey)
	{
		std::string s = std::to_string(i) + "Key";
		DirectX::SimpleMath::Vector2 point = { vec.x, vec.y };
		ImGuiUtility::GetInstance().InputVector2(s, point);
		i++;
	}
	ImGui::End();
}

float CurveFloat::GetValueByTime(const float _time)
{
	MathLibrary::Clamp01(_time);
	return ImGui::CurveValue(_time, static_cast<int>(mCurveKey.size()), mCurveKey.data());
}

void CurveFloat::Save()
{
	// �t�@�C�����J��
	std::shared_ptr<AssetHandle> handle = AssetManager::GetInstance().Load<JsonFileProvider>(mFilePath);
	if (!handle->IsValid())
	{
		return;
	}

	nlohmann::json& jsonFile = handle->Get<JsonFile>().GetJson();

	// �|�C���g�̐����擾
	jsonFile["NumKey"] = mCurveKey.size();

	// �L�[�̒l��ۑ�
	for (size_t key_i = 0; ImVec2 & key : mCurveKey)
	{
		std::string keyX = "Point X" + std::to_string(key_i);
		std::string keyY = "Point Y" + std::to_string(key_i);
		jsonFile[keyX] = key.x;
		jsonFile[keyY] = key.y;
		key_i++;
	}

	// �t�@�C����������
	handle->Get<JsonFile>().WriteFile();

}
