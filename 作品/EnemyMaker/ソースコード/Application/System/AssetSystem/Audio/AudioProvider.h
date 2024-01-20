/**
* @file AudioProvider.h
* @brief AudioProviderクラスの作成
*/

#pragma once

//---------- INCLUDES -----------
#include "../IAssetProvider.h"
#include <xaudio2.h>

/**
* @class AudioProvider
* @brief wavファイルの読み込みをする
* @detail XAudio2で使用されるRIFFファイルであるwavファイルの読み込みをする
*/
class AudioProvider : public IAssetProvider
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	AudioProvider();

	/**
	* デストラクタ
	*/
	~AudioProvider();

private:
	/**
	* @fn LoadBase
	* @brief アセット読み込みを実際に実行する処理
	* @detail 読み込みが完了するとキャッシュマップに登録する
	* @param const std::string& _filePath
	*/
	virtual std::shared_ptr<IAsset> Load(const std::string& _filePath) const;

	/**
	* @fn Setting
	* @brief セッティングのデータを実際に使用できる値に変換している
	* @return void
	*/
	virtual void Setting();

	/**
	* @fn FindChunk
	* @brief wavファイルからチャンクデータを見つける
	* @detail マイクロソフト公式リファレンスを参照した　wavファイルからチャンクを見つける関数
	*         https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
	* @param HANDLE (_hFile) 読み取りたいwavファイル
	* @param DWORD  (_fourcc)
	* @param DWORD& (_dwChunkSize) チャンクサイズ
	* @param DWORD& (_dwChunkDataPosition)
	* @return HRESULT チャンクを見つけれたかを返す
	*/
	HRESULT FindChunk(HANDLE _hFile, DWORD _fourcc, DWORD& _dwChunkSize, DWORD& _dwChunkDataPosition) const;

	/**
	* @fn ReadChunkData
	* @brief チャンクを読み取る関数
	* @detail マイクロソフト公式リファレンスを参照した　wavファイルからチャンクを読み取る関数
	*         https://learn.microsoft.com/ja-jp/windows/win32/xaudio2/how-to--load-audio-data-files-in-xaudio2
	* @param HANDLE (_hFile)
	* @param void* (_buffer)
	* @param DWORD (_buffersize)
	* @param DWORD (_bufferoffset)
	*/
	HRESULT ReadChunkData(HANDLE _hFile, void* _buffer, DWORD _buffersize, DWORD _bufferoffset) const;

public:
	/**
	* @fn GetProviderType
	* @brief プロバイターのTypeを返す
	* @detail typeidを使用してプロバイターの型を返している
	* @return std::type_info プロバイダーの型
	*/
	inline virtual const std::type_info& GetProviderType() const;

};

//--------- INLINES ----------

inline const std::type_info& AudioProvider::GetProviderType() const
{
	return typeid(AudioProvider);
}
