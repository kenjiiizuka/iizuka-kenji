#pragma once

/**
* @file  ICollisionDetector.h
* @brief ICollisionDetectorクラスの定義
*/

//------ 前方宣言 -------
class PrimitiveComponent;

/**
* @interface ICollisionDetector
* @brief コリジョン検出機能を持つクラスのインターフェース
*/
class ICollisionDetector
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	ICollisionDetector() { /* 処理なし */ };

	/**
	* デストラクタ
	*/
	virtual ~ICollisionDetector() {/* 処理なし */ }

public:
	/**
　　 * @fn DetectorOverlap
	 * @brief 渡されたコリジョン同士で重なりを検出する
	 * @param PrimitiveComponent* (_subject1)
	 * @param PrimitiveComponent* (_subject2)
　　 * @return bool (true 重なり検出　false 重なり無し)
　　*/
	virtual void DetectorOverlap(PrimitiveComponent* _subject1, PrimitiveComponent* _subject2) = 0;

};

