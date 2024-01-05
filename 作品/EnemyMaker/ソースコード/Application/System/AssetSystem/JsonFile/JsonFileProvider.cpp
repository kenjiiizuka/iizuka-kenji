//---------- INCLUDES -----------
#include <fstream>
#include "JsonFile.h"
#include "JsonFileProvider.h"

JsonFileProvider::JsonFileProvider()
	: mbCreateFile(false)
{
	// �����Ȃ�
}

JsonFileProvider::~JsonFileProvider()
{
	// �����Ȃ�
}

std::shared_ptr<IAsset> JsonFileProvider::Load(const std::string& _filePath) const
{
	std::shared_ptr<JsonFile> newJson = std::make_shared<JsonFile>();

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
		}
		// �쐬���Ȃ��Ȃ�G���[���b�Z�[�W���o��
		else
		{
			std::cout << _filePath << "���J�����Ƃ��ł��܂���ł���" << std::endl;
			return nullptr;
		}
	}

	// �t�@�C���̃T�C�Y���擾 �V�[�N�𖖔��Ɉړ����T�C�Y���擾���V�[�N��擪�Ɉړ�
	std::streamsize size;
	stream.seekg(0, std::ios::end);
	size = stream.tellg();
	stream.seekg(0, std::ios::beg);
	// �t�@�C���T�C�Y��0���傫�����json�I�u�W�F�N�g�ɑ������
	if (size > 0)
	{
		stream >> newJson->mJson;
	}

	// �t�@�C�������
	stream.close();

	newJson->mFilePath = _filePath;

	return newJson;
}

void JsonFileProvider::Setting()
{
	// �Z�b�e�B���O�f�[�^���擾����
	std::memcpy(&mbCreateFile, mLoadSetting.data(), sizeof(bool));
}

