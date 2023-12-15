/**
* @file StaticMeshObject.h
* @brief StaticMeshObject�N���X�̒�`
*/

#pragma once

//---------- INCLUDES ----------
#include "../GameObject.h"

/**
* @class StaticMeshObject
* @brief �X�e�B�b�N���b�V���I�u�W�F�N�g�̕\��������N���X
* @detail �f�t�H���g�ŃA�E�g���C�����t��
*/
class StaticMeshObject : public GameObject
{
public:
    /**
    * �f�t�H���g�R���X�g���N�^
    */
    StaticMeshObject();

    /**
    * �f�X�g���N�^
    */
    ~StaticMeshObject();


    /**
    * @fn Init
    * @brief ����������
    * @detail ���b�V���̓ǂݍ��݁A�V�F�[�_�[�̃Z�b�g�����Ă���
    * @param std::string_view (_filePath)
    * @return void
    */
    void Init(std::string_view _filePath);

    /**
    * @fn Update
    * @brief �X�V����
    * @detail StaticMesh�̃��[���h�}�g���b�N�X��ݒ肵�Ă���
    * @param const double (_deltaTime)
    * @return void
    */
    void Update(const double _deltaTime) override;
};