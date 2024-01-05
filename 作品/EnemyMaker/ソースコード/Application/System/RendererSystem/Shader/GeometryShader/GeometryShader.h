/**
* @file GeometryShader.h
* @brief GeometryShader�N���X�̒�`
*/

#pragma once

//------- INCLUDES ---------
#include "../Shader.h"

/**
* @class GeometryShader
* @brief �W�I���g���V�F�[�_�[�N���X
* @detail �W�I���g���V�F�[�_�[�̏��������s��
*/
class GeometryShader : public Shader
{
public:
	/**
	* �R���X�g���N�^
	* 
	* @param VisualEntity* (_visualEntity) �W�I���g���V�F�[�_�[���g���`��I�u�W�F�N�g
	*/
	GeometryShader(VisualEntity* _visualEntity);

	/**
	* �f�X�g���N�^
	*/
	~GeometryShader();

private:
	/** �ǂݍ��񂾃V�F�[�_�[���Ǘ����邽�߂�Map */
	static std::unordered_map<std::string, ID3D11GeometryShader*> mGeometryShaders;

	/** ���݊��蓖�Ă��Ă���V�F�[�_�[�̖��O */
	static std::string mCurrentBindShaderName;

	/** ���g�������V�F�[�_�[�̃|�C���^ */
	ID3D11GeometryShader* mGeometryShader;

public:
	/**
	* @fn Uninit
	* @brief �I������
	* @return void
	*/
	void Uninit() override;

	/**
	* @fn UpdateBuffer
	* @brief �萔�o�b�t�@�̍X�V����
	* @param uint8_t (_dataID) �`�悷�郁�b�V��ID
	* @return void
	*/
	virtual void UpdateBuffer(uint8_t _dataID);

	/**
�@�@* @fn BindShader
	* @brief �V�F�[�_�[�̊��蓖��
�@�@* @return void
�@�@*/
	void BindShader() override;

	/**
	* @fn Deallocate
	* @brief �V�F�[�_�[�̊��蓖�ĉ���
	* @return void
	*/
	static void Deallocate();

protected:
	/**
�@�@* @fn MakeShader
	* @brief �V�F�[�_�[���쐬����
	* @param void* (_pData)
	* @param UINT (_fileSize)
	* @param std::string (_shaderName)
�@�@* @return HRESULT
�@�@*/
	HRESULT MakeShader(void* _pData, UINT _fileSize, std::string _shaderName) override;

	/**
�@�@ * @fn MakeBuffer
	 * @brief �萔�o�b�t�@�쐬�֐� ���t���N�V�����œǂݎ�����f�[�^����萔�o�b�t�@���쐬����
	 * @param void* (_pData)
	 * @param UINT (_fileSize)
�@�@ * @return HRESULT
�@�@*/
	HRESULT MakeBuffer(void* _pData, UINT _fileSize) override;

	/**
�@�@* @fn CheckDuplication
	* @brief ��d�ǂݍ��݃`�F�b�N
	* @param std::string (_shaderName)
�@�@* @return bool true �d���Ȃ� false �d��
�@�@*/
	bool CheckDuplication(std::string _shaderName) override;

private:



};

