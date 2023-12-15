//------------ INCLUDES -----------
#include "AnimationSpriteComponent.h"
#include "../../../System/RendererSystem/Shader/VertexShader/VertexObject2DShader.h"

AnimationSpriteComponent::AnimationSpriteComponent()
	: mAnimationFrame(30.0f)
	, mCurrentX(0)
	, mPrevX(0)
	, mCurrentY(0)
	, mElapsedTime(0.0f)
	, mbIsLoop(false)
	, mbIsPlay(false)
{
	// 処理なし
}

AnimationSpriteComponent::~AnimationSpriteComponent()
{
	// 処理なし
}

void AnimationSpriteComponent::Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _vertexColor)
{
	SpriteComponent::Init(_pos, _size, _vertexColor);
}

void AnimationSpriteComponent::Update(const double _deltaTime)
{
	// アニメーションを再生していなければ処理しない
	if (!mbIsPlay)
	{
		return;
	}

	// UV座標を計算する
	size_t table_i = static_cast<size_t>((mElapsedTime)) % mAnimationTable.size();
	mCurrentX = mAnimationTable[table_i];

	// 経過時間加算
	mElapsedTime += static_cast<float>(_deltaTime) * mAnimationFrame;

	// 前フレームがXの右端で、今がＸの左端になっていればＹを下にずらす
	if (mPrevX == mAnimationTable.size() - 1 && mCurrentX == 0)
	{
		if (mCurrentY == mSplit.y - 1)
		{
			if (mbIsLoop)
			{
				mCurrentY = 0;
			}
			else
			{
				mbIsPlay = false;
				return;
			}
		}
		else
		{
			mCurrentY++;
		}
	}

	// 前フレームのXの位置として保存
	mPrevX = mCurrentX;

	// UVの位置を計算
	float left = mUVSize.x * mCurrentX;
	float right = left + mUVSize.x;
	float top = mUVSize.y * mCurrentY;
	float bottom = top + mUVSize.y;

	// 頂点のＵＶ位置を動かす
	Vertex* vertices = GetVertices();
	// 左上
	vertices[0].mTexCoord = { left,top };
	// 右上
	vertices[1].mTexCoord = { right,top };
	// 左下
	vertices[2].mTexCoord = { left,bottom };
	// 右下
	vertices[3].mTexCoord = { right,bottom };

	MapVertices(vertices);
}

void AnimationSpriteComponent::SetupAnimationTable(const float _xSplit, const float _ySplit)
{
	mSplit = { _xSplit, _ySplit };
	mUVSize = { 1.0f / _xSplit, 1.0f / _ySplit };

	// サイズの確保
	mAnimationTable.resize(static_cast<size_t>(_xSplit));

	for (size_t table_i = 0; uint8_t & table : mAnimationTable)
	{
		table = static_cast<uint8_t>(table_i);
		table_i++;
	}
}

