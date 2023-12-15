/**
* @file AudioAsset.h
* @brief AudioAssetクラスの定義
*/

#pragma once

//--------- INCLUDES ---------
#include "../IAsset.h"
#include <memory>
#include <xaudio2.h>

/**
* @class AudioClip
* @brief XAudioで再生可能なAudioアセット
*/
class AudioAsset : public IAsset
{
	/**-----------------------------------------------------------------------
	* データのセットをAudioProviderクラスからのみに限定するためにフレンド指定
	-------------------------------------------------------------------------*/
	friend class AudioProvider;

public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioAsset();

	/**
	* デストラクタ
	*/
	~AudioAsset();

private:
	/** オーディオデータバッファー */
	XAUDIO2_BUFFER mXAudio2Buffer;

	/** データバッファー mXAudio2Bufferの元 */
	std::shared_ptr<BYTE> mDataBuffer;

public:
	/**
	* @fn GetAssetType
	* @brief アセットのタイプを返す
	* @detail typeidを使用して型判別をしている
	* @return const std::type_info&
	*/
	inline virtual const std::type_info& GetAssetType() const noexcept;

	/**
	* @fn GetXAudio2Buffer
	* @brief XAUDIO2_BUFFERを返す
	* @return XAUDIO2_BUFFER
	*/
	inline XAUDIO2_BUFFER GetXAudio2Buffer() const noexcept;

	/**
	* @fn GetAudioDataBuffer
	* @brief オーディオデータバッファーを返す
	* @return std::weak_ptr<BYTE>
	*/
	inline std::weak_ptr<BYTE> GetAudioDataBuffer() const noexcept;

};

//---------- INLINES -----------

inline const std::type_info& AudioAsset::GetAssetType() const noexcept
{
	return typeid(AudioAsset);
}

inline XAUDIO2_BUFFER AudioAsset::GetXAudio2Buffer() const noexcept
{
	return mXAudio2Buffer;
}

inline std::weak_ptr<BYTE> AudioAsset::GetAudioDataBuffer() const noexcept
{
	return mDataBuffer;
}
