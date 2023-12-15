#include "SwapChain.h"

SwapChain::SwapChain()
	: mSwapChain(nullptr)
	, mSwapChainDesc({})
{
}

SwapChain::~SwapChain()
{
}

void SwapChain::SetupSwapChainDesc(const HWND& _outPutWindow, const UINT& _bufferWidth, const UINT& _bufferHeight, const BOOL& _windowMode)
{
	mSwapChainDesc.BufferCount = 1;                                 // �X���b�v�`�F�[�������o�b�t�@�̐�
	mSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;   // �X���b�v�`�F�[�������o�b�t�@�̎g�p���@�@�����_�[�^�[�Q�b�g�Ƃ��Ďg�p����
	mSwapChainDesc.OutputWindow = _outPutWindow;                    // �X���b�v�`�F�[���̏o�͐�̃E�B���h�E
	mSwapChainDesc.SampleDesc.Count = 1;                            // �}���`�T���v�����O�̐ݒ�
	mSwapChainDesc.SampleDesc.Quality = 0;                          // �}���`�T���v�����O�̕i���̐ݒ�
	mSwapChainDesc.BufferDesc.Width = _bufferWidth;                 // �o�b�t�@�̕���ݒ�i��ʃT�C�Y�j
	mSwapChainDesc.BufferDesc.Height = _bufferHeight;               // �o�b�t�@�̍�����ݒ� (��ʃT�C�Y)
	mSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �o�b�t�@�̃t�H�[�}�b�g�̐ݒ� (8�r�b�g��RGBA)
	mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;          // �o�b�t�@�̃��t���b�V�����[�g�̕���
	mSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;           // �o�b�t�@�̃��t���b�V�����[�g�̕��q
	mSwapChainDesc.Windowed = _windowMode;                          // �E�B���h�E���[�h
}

void SwapChain::Release()
{
	mSwapChain->Release();
}

void SwapChain::Present()
{
	mSwapChain->Present(1, 0);
}
