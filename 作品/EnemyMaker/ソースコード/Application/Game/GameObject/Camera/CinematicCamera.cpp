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
	// 処理なし
}

CinematicCamera::~CinematicCamera()
{
	// 処理なし
}

void CinematicCamera::Init(std::string_view _filepath)
{
	mSaveFilePath = _filepath.data();
	if (Load())
	{
		// 最後のキーを再生時間に設定
		mDuration = mLocalAnimKeys.back().mTime;
	}
}

void CinematicCamera::Update(const double _deltaTime)
{
	// カメラアニメーションの処理
	CameraAnimation(_deltaTime);

	Camera::Update(_deltaTime);	
}

void CinematicCamera::CameraAnimation(const double _deltaTime)
{
	if (!mbPlay)
	{
		return;
	}

	// 補間元、補間先のキーを取得
	CameraAnimationKey keyBase, keyTo;
	GetKey(keyBase, keyTo);

	// ベースがカットの設定でない場合のみ補完する
	if (!keyBase.mbCut)
	{
		// カメラ位置を計算
		DirectX::SimpleMath::Vector3 cameraPos;
		InterpCameraAnimationKeyPosition(keyBase, keyTo, cameraPos);
		mTransform.lock()->SetPosition(cameraPos);
	}

	mCurrentPlayTime += _deltaTime;

	// 再生終了チェック
	if (mCurrentPlayTime >= mDuration)
	{
		mbPlay = false;
	}
}

void CinematicCamera::InterpCameraAnimationKeyPosition(CameraAnimationKey& _keyBase, CameraAnimationKey& _keyTo, DirectX::SimpleMath::Vector3& _position)
{
	// キー間での再生時間に正規化
	double time = mCurrentPlayTime - _keyBase.mTime;

	// 補間に使う比率を求める
	double t = MathLibrary::Clamp01(time / (_keyTo.mTime - _keyBase.mTime));

	// 補間
	_position = DirectX::SimpleMath::Vector3::Lerp(_keyBase.mPosition, _keyTo.mPosition, t);
}

void CinematicCamera::GetKey(CameraAnimationKey& _key1, CameraAnimationKey& _key2)
{
	// キーはTimeが昇順に格納されているのでTimeが現在の再生時間を超えた時のkeyとひとつ前のKeyを取得
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

	// 注視点を計算する
	Camera::CalcuFocusPosition();
}

void CinematicCamera::ConvertTargetWorldPosition()
{
	// コピー
	mWorldAnimKeys = mLocalAnimKeys;

	// 対象のワールド行列
	DirectX::SimpleMath::Matrix targetWorldMatrix;

	if (mTargetObject.lock())
	{
		targetWorldMatrix = mTargetObject.lock()->GetComponent<TransformComponent>()->GetWorldMatrix();
	}

	// ボーンがセットされていればボーンの行列を取得
	if (mTargetBone.lock())
	{
		targetWorldMatrix = mTargetBone.lock()->GetBoneWorldMatrix();	
	}

	// ワールド変換
	for (CameraAnimationKey& key : mWorldAnimKeys)
	{
		// ワールド変換
		DirectX::SimpleMath::Matrix translation;
		MathLibrary::CreateTranslationMatrix(key.mPosition, translation);
		translation *= targetWorldMatrix;

		// 位置要素の取得
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

	// 配列の確保
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
	// デバッグでなければ処理しない
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

	// 削除するキーの添え字
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

	// キーの位置、時間の情報を表示
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
	

	// 最後のキーを再生時間に設定
	if (!mLocalAnimKeys.empty())
	{
		mDuration = mLocalAnimKeys.back().mTime;
	}
	
#ifdef _DEBUG
	// デバッグ表示
	for (CameraAnimationKey & key : mWorldAnimKeys)
	{
		DebugRendererManager::GetInstance().DrawSphere(key.mPosition, 1.0f);
	}
#endif
}

void CinematicCamera::Play()
{
	// データがあるかを確認
	if (mLocalAnimKeys.empty())
	{
		return;
	}

	// ワールド空間にコンバートする
	ConvertTargetWorldPosition();
	mbPlay = true;

	// 最後のキーを再生時間に設定
	mDuration = mLocalAnimKeys.back().mTime;

	mCurrentPlayTime = 0.0f;

	// 開始位置のセット
	mTransform.lock()->SetPosition(mWorldAnimKeys[0].mPosition);

	// メインカメラにセットする
	SceneManager::GetInstance().GetCurrentScene().lock()->GetCameraManager()->SetMainCameraByName(mName);

}

CinematicCamera::CameraAnimationKey::CameraAnimationKey()
	: mTime(0.0f)
	, mbCut(false)
{
}
