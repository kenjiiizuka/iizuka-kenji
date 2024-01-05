//--------- INCLUDES ---------
#include <iostream>
#include "BinaryFileProveider.h"
#include "../AssetHandle.h"
#include "BinaryFile.h"


BinaryFileProvider::BinaryFileProvider()
	: mbCreateFile(false)
{
	// �����Ȃ�
}


BinaryFileProvider::~BinaryFileProvider()
{
	// �����Ȃ�
}

std::shared_ptr<IAsset> BinaryFileProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<BinaryFile> newFile = std::make_shared<BinaryFile>();

	// �t�@�C���p�X�������������m�F���邽�߂Ƀt�@�C�����J��
	std::ifstream stream;
	stream.open(_filePath, std::ios_base::binary);

	// �t�@�C��������ɊJ���Ă��邩�m�F����
	if (!stream.is_open())
	{
		// �t�@�C���쐬����ݒ�Ȃ�쐬����
		if (mbCreateFile)
		{
			stream.open(_filePath);
			stream.close();
			stream.open(_filePath, std::ios_base::binary);
		}
		// �쐬���Ȃ��Ȃ�G���[���b�Z�[�W���o��
		else 
		{
			std::cout << _filePath << "���J�����Ƃ��ł��܂���ł���" << std::endl;
			return nullptr;
		}
	}

	// �t�@�C���̃T�C�Y���擾
	stream.seekg(0,std::ios::end);
	newFile->mStreamSize = stream.tellg();
	newFile->mFilePath = _filePath;
	
	// �t�@�C�������
	stream.close();
	return newFile;
}

void BinaryFileProvider::Setting()
{
	// �Z�b�e�B���O�f�[�^���擾����
	std::memcpy(&mbCreateFile, mLoadSetting.data(), sizeof(bool));
}
