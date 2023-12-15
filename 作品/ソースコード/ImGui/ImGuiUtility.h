/**
* @file ImGuiUtility
* @brief ImGuiUtility�N���X�̒�`
*/
#pragma once

//--------- INCLUDES ---------
#include <Windows.h>
#include <string>
#include "../System/Singleton.h"
#include "../Game/Component/TransformComponent/Transform.h"
#include "imgui.h"


/**
* @class ImGuiUtility
* @brief ImGui���g���₷���悤�Ƀ��b�v�����N���X
*/
class ImGuiUtility : public Singleton<ImGuiUtility>
{
	/**----------------------------------------------------------------------------------------------
	* ���N���X��Singleton�N���X����R���X�g���N�^�ƁA�f�X�g���N�^�ɃA�N�Z�X���邽�߂ɕK�v�ł���
	* �N���X�O���琶���A�j���ł��Ȃ��悤�ɂ��邽�߂Ƀt�����h�w�肷��
	------------------------------------------------------------------------------------------------*/
	friend class Singleton<ImGuiUtility>;

private:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	ImGuiUtility()
	{
		// �����Ȃ�
	}

	/**
	* �f�X�g���N�^
	*/
	~ImGuiUtility()
	{
		// �����Ȃ�
	}

	/**
	* �R�s�[�R���X�g���N�^
	* �R�s�[�֎~�̂��� delete�w��
	*/
	ImGuiUtility(const ImGuiUtility&) = delete;

	/**
	* =���Z�q�̃I�[�o�[���[�h
	* ����֎~�̂��� delete�w��
	*/
	void operator=(const ImGuiUtility&) = delete;

public:
	/**
	* @fn Initialize
	* @brief ImGui�̏��������s��
	* @param const HWND& (_windowHandle) ImGui��`�悵����WindowHandle
	* @return void
	*/
	void Initialize(const HWND& _windowHandle);

	/**
	* @fn Uninitialize
	* @brief ImGui�̏I���������s��
	* @return void
	*/
	void Uninitialize();

	/**
	* @fn Update
	* @brief ImGui�̍X�V����
	* @detail NewFrame�֐����Ăяo���Ă���
	* @return void
	*/
	void Update();

	/**
	* @fn Draw
	* @brief ImGui�̕`�揈��
	* @detail ImGui�̃����_�����O�֐����Ăяo���Ă���
	* @return void
	*/
	void Draw();

	/**
	 * @fn VerticalColorSliderFloat
	 * @brief �J���[���o�[�e�B�J���X���C�_�[��\������
	 * @param const std::string&  (_label)
	 * @param const ImVec2 (_size)
	 * @param float& (_value)
	 * @param const float (_min)
	 * @param const float (_max)
	 * @param const ImColor (_color)
	 * @param const ImVec4 (_densityChanges)
	 * @param const std::string& (_format)
	 * @return void
	*/
	void VerticalColorSliderFloat(const std::string& _label, const ImVec2 _size, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format = "%.3f");

	/**
	 * @fn ColorSliderFloat
	 * @brief �J���[���o�[�e�B�J���X���C�_�[��\������
	 * @param const std::string&  (_label)
	 * @param float& (_value)
	 * @param const float (_min)
	 * @param const float (_max)
	 * @param const ImColor (_color)
	 * @param const ImVec4 (_densityChanges)
	 * @param const std::string& (_format)
	 * @return void
	*/
	void ColorSliderFloat(const std::string& _label, float& _value, const float _min, const float _max, const ImColor _color, const ImVec4 _densityChanges, const std::string& _format = "%.3f");

	/**
	* @fn DrawTransform
	* @brief �g�����X�t�H�[����Drag�ŕ\������
	* @param std::string_view (_label)
	* @param Transform& (_transform)
	* @return void
	*/
	void DragTransform(std::string_view _label, Transform& _transform);

	/**
	* @fn DragFloat
	* @brief ImGui::DragFloat �����b�v���AID��ݒ肵�Ă��܂�
	* @param std::string_view (_label)
	* @param float& (_value)
	* @param const float (_min)
	* @param const float (_max)
	* @return void
	*/
	void DragFloat(std::string_view _label, float& _value, const float _min = 0.0f, const float _max = 0.0f);

	/**
	* @fn ComboEnum
	* @brief ImGui::Combo�����b�v�����֐�
	* @param std::string_view (_label)
	* @param std::vector<std::string> (_item)
	* @param int& (_current)
	* @return void 
	*/
	void Combo(std::string_view _label, std::vector<std::string> _item, int& _current);

	/**
	* @fn InputVector2
	* @brief Vector2��InputFloat2�ŕ\���ł���悤�Ƀ��b�v���֐�
	* @param std::string_view (_label)
	* @param DirectX::SimpleMath::Vector2& (_vector)
	* @return void
	*/
	void InputVector2(std::string_view _label, DirectX::SimpleMath::Vector2& _vector);
};

