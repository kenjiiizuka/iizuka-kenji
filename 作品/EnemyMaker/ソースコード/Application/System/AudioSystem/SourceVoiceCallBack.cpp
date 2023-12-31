#include "SourceVoiceCallBack.h"

SourceVoiceCallback::SourceVoiceCallback(SourceState& _state)
	: mState(_state)
{
	// 処理なし
}

SourceVoiceCallback::~SourceVoiceCallback()
{
	// 処理なし
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


