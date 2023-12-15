/**
* @file CommandObject.h
* @brief CommandObject�N���X�̒�`
*/

#pragma once

//---------- INCLUDES -----------
#include "../GameObject.h"

//---------- �O���錾 -----------
class SpriteComponent;

/**
* @class CommandObject
* @brief �^�C�g���⃊�U���g�ŕ\������R�}���h
*/
class CommandObject : public GameObject
{
public:
	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CommandObject();

	/**
	* �f�X�g���N�^
	*/
	~CommandObject();

private:
	/** �R�}���h�\���p�X�v���C�g */
	std::weak_ptr<SpriteComponent> mCommandSprite;

public:
	/**
	* @fn Init
	* @brief ����������
	* @detail �g�p����X�v���C�g�R���|�[�l���g�̏��������Ă���
	* @param const DirectX::SimpleMath::Vector2 (_pos)  �X�v���C�g�̕\���ʒu
	* @param const DirectX::SimpleMath::Vector2 (_size) �X�v���C�g�̃T�C�Y
	* @param std::string_view (_filePath) �g�p����e�N�X�`���̃t�@�C���p�X
	* @return void
	*/
	void Init(const DirectX::SimpleMath::Vector2 _pos, const DirectX::SimpleMath::Vector2 _size, std::string_view _filePath);

	/**
	* @fn GetCommandSprite
	* @brief �R�}���h�\���p�X�v���C�g��Ԃ�
	* @return std::weak_ptr<SpriteComponent>
	*/
	inline std::weak_ptr<SpriteComponent> GetCommandSprite() const noexcept;

};

//---------- INLINES ----------

inline std::weak_ptr<SpriteComponent> CommandObject::GetCommandSprite() const noexcept
{
	return mCommandSprite;
}

