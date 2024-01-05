#include "Singleton.h"

// ������Ԃɕϐ���錾���邱�Ƃ�Static�ȃN���X�̕ϐ��ł��B�؂��ł���
namespace 
{
	/** �t�@�C�i���C�U�[�̍ő�T�C�Y */
	constexpr int cMaxFinalizerSize = 256;

	/** �r������p */
	std::mutex gMutex;

	// ���݂̃t�@�C�i���C�U�[�̐�
	size_t gFinalizersCount = 0;                                      

	/** �j���֐����i�[����z�� */
	SingletonFinalizer::FinalizerFunc gFinalizers[cMaxFinalizerSize];
}


void SingletonFinalizer::AddFinalizer(FinalizerFunc _func)
{
	// �}���`�X���b�h�ɂȂ����Ƃ��ł��r���I�ɐ���ł���悤�Ƀ��b�N��������
	std::lock_guard<std::mutex> lock(gMutex);

	// �T�C�Y�𒴂��Ă��Ȃ����`�F�b�N
	assert(gFinalizersCount < cMaxFinalizerSize); 

	gFinalizers[gFinalizersCount] = _func;
	gFinalizersCount++;
}

void SingletonFinalizer::Finalize()
{
	// Lock��������
	std::lock_guard<std::mutex> lock(gMutex); 

	// �t���Ƀt�@�C�i���C�Y�����s
	for (size_t i = gFinalizersCount - 1; (i < cMaxFinalizerSize && i >= 0); i--)
	{
		if (i >= cMaxFinalizerSize)
		{
			continue;
		}
		(*gFinalizers[i])();
	}
	gFinalizersCount = 0;
}
