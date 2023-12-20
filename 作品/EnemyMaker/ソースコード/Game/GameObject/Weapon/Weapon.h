/**
* @file  Weapon.h
* @brief Weaponクラスの定義
*/

#pragma once

//----------- INCLUDES ------------
#include "../GameObject.h"


//------------ 前方宣言 ------------
class Bone;
class SkeletalMesh;
class BoneAttachComponent;

/**
* @class Weapon
* @brief プレイヤーや敵が持つ武器の基底クラス
*/
class Weapon : public GameObject
{
public:
	/**
	* デフォルトコンストラクタ
	*/
	Weapon();

	/**
	* デストラクタ
	*/
	virtual ~Weapon();

private:	
	/** アタッチするボーン */
	std::weak_ptr<Bone> mAttachBone;

protected:
	/** コリジョンのオフセットトランスフォーム */
	Transform mCollisionOffsetTransform;

public:
	/**
	 * @fn Init
	 * @brief 初期化処理
	 * @param const std::string&            (_filePath)          読み込む武器メッシュのファイルパス
	 * @param std::shared_ptr<Bone>         (_attachBone)        アタッチするボーン
	 * @param std::shared_ptr<SkeletalMesh> (_skeletalMesh)      アタッチするボーンを持っているスケルタルメッシュ
	 * @return void
	*/
	virtual void Init(const std::string& _filePath, std::shared_ptr<Bone> _attachBone, std::shared_ptr<SkeletalMesh> _skeletalMesh);

	/**
	* @fn Update
	* @brief 更新処理
	* @return void
	*/
	virtual void Update(const double _deltaTime) override;


};


