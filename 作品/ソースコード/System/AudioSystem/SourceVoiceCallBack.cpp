#include "SourceVoiceCallBack.h"

SourceVoiceCallback::SourceVoiceCallback(SourceState& _state)
	: mState(_state)
{
	// èàóùÇ»Çµ
}

SourceVoiceCallback::~SourceVoiceCallback()
{
	// èàóùÇ»Çµ
}

STDMETHODIMP_(void __stdcall) SourceVoiceCallback::OnStreamEnd()
{	
	mState = SourceState_Finish;
}

STDMETHODIMP_(void __stdcall) SourceVoiceCallback::OnBufferEnd(void* pBufferContext)
{
	mState = SourceState_None;
}

STDMETHODIMP_(void __stdcall) SourceVoiceCallback::OnBufferStart(void* pBufferContext)
{
	mState = SourceState_Play;
}


