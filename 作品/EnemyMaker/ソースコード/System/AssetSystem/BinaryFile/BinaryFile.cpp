#include <iostream>
#include "BinaryFile.h"

BinaryFile::BinaryFile()
	: mStreamSize(0)
{
	// �����Ȃ�
}

BinaryFile::~BinaryFile()
{
	// �����Ȃ�
}

std::streamsize BinaryFile::CheckFileSize(std::istream& _stream)
{
	// �t�@�C���̃T�C�Y���擾 �V�[�N�𖖔��Ɉړ����T�C�Y���擾���V�[�N��擪�Ɉړ�
	std::streamsize size;
	_stream.seekg(0, std::ios::end);
	size = _stream.tellg();
	_stream.seekg(0, std::ios::beg);
	return size;
}

void BinaryFile::Read(std::ifstream& _stream, std::vector<char>& _outputData, const std::streamsize& _readSize)
{
	_outputData.resize(_readSize);
	_stream.read(_outputData.data(), _readSize);
}

void BinaryFile::ReadAllData(std::vector<char>& _outputData)
{
	// �o�C�i�����[�h�ŊJ��
	std::ifstream stream;
	stream.open(mFilePath, std::ios::binary);

	// �J���Ă��邩�`�F�b�N
	if (!stream.is_open())
	{
		std::cout << "�t�@�C���I�[�v�����s �F" << mFilePath << std::endl;
		return;
	}

	// �t�@�C���T�C�Y���`�F�b�N
	mStreamSize = CheckFileSize(stream);

	// �t�@�C�����炷�ׂẴf�[�^��ǂݎ��
	Read(stream, _outputData, mStreamSize);

	// �t�@�C���N���[�Y
	stream.close();
}

void BinaryFile::WriteData(const char* _writeData, const size_t _writeDataSize, const WriteMode _writeMode)
{
	std::ofstream stream;

	// �o�C�i�����[�h�ŊJ��
	stream.open(mFilePath, static_cast<std::ios_base::openmode>(_writeMode));
	// �J���Ă��邩�`�F�b�N
	if (!stream.is_open())
	{
		std::cout << "�t�@�C���I�[�v�����s �F" << mFilePath << std::endl;		
		return;
	}
	
	// ��������
	stream.write(_writeData, static_cast<std::streamsize>(_writeDataSize));
	stream.close();
}

