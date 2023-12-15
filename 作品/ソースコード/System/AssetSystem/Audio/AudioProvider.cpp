//------------ INCLUDES -------------
#include "AudioProvider.h"
#include "../../../Utility/StringEncoding.h"
#include "AudioAsset.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

AudioProvider::AudioProvider()
{
	// 処理なし
}

AudioProvider::~AudioProvider()
{
	// 処理なし
}

std::shared_ptr<IAsset> AudioProvider::Load(const std::string& _filePath) const
{
    std::shared_ptr<AudioAsset> newAudio = std::make_shared<AudioAsset>();


    // stringからwStringに変換
    std::wstring wFilePath = ::SJIS_To_Wide(_filePath);

    HANDLE fileHandle = CreateFile(
        wFilePath.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
   );

    // ファイル作成できたか確認
    if (INVALID_HANDLE_VALUE == fileHandle)
    {
        HRESULT_FROM_WIN32(GetLastError());
        return std::shared_ptr<IAsset>();
    }

    if (INVALID_SET_FILE_POINTER == SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN))
    {
        HRESULT_FROM_WIN32(GetLastError());
        return std::shared_ptr<IAsset>();
    }

    DWORD dwChunkSize;
    DWORD dwChunkPosition;
  
    FindChunk(fileHandle, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize]; 
    ReadChunkData(fileHandle, pDataBuffer, dwChunkSize, dwChunkPosition);

    // カスタムデリータを設定する
    std::shared_ptr<BYTE> dataBuffer(
        pDataBuffer,
        [](BYTE* _data) {delete[] _data; }
    );

    newAudio->mDataBuffer = dataBuffer;
    newAudio->mXAudio2Buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    newAudio->mXAudio2Buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    newAudio->mXAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	return newAudio;
}

void AudioProvider::Setting()
{
	// 処理なし
}


HRESULT AudioProvider::FindChunk(HANDLE _hFile, DWORD _fourcc, DWORD& _dwChunkSize, DWORD& _dwChunkDataPosition) const
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(_hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(_hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(_hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(_hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(_hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == _fourcc)
        {
            _dwChunkSize = dwChunkDataSize;
            _dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;
}

HRESULT AudioProvider::ReadChunkData(HANDLE _hFile, void* _buffer, DWORD _buffersize, DWORD _bufferoffset) const
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(_hFile, _bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if (0 == ReadFile(_hFile, _buffer, _buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}