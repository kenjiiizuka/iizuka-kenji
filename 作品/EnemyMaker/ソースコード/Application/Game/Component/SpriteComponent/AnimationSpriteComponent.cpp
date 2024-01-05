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
	// �����Ȃ�
}

AnimationSpriteComponent::~AnimationSpriteComponent()
{
	// �����Ȃ�
}

void AnimationSpriteComponent::Init(DirectX::SimpleMath::Vector2 _pos, DirectX::SimpleMath::Vector2 _size, DirectX::SimpleMath::Vector4 _vertexColor)
{
	SpriteComponent::Init(_pos, _size, _vertexColor);
}

void AnimationSpriteComponent::Update(const double _deltaTime)
{
	// �A�j���[�V�������Đ����Ă��Ȃ���Ώ������Ȃ�
	if (!mbIsPlay)
	{
		return;
	}

	// UV���W���v�Z����
	size_t table_i = static_cast<size_t>((mElapsedTime)) % mAnimationTable.size();
	mCurrentX = mAnimationTable[table_i];

	// �o�ߎ��ԉ��Z
	mElapsedTime += static_cast<float>(_deltaTime) * mAnimationFrame;

	// �O�t���[����X�̉E�[�ŁA�����w�̍��[�ɂȂ��Ă���΂x�����ɂ��炷
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

	// �O�t���[����X�̈ʒu�Ƃ��ĕۑ�
	mPrevX = mCurrentX;

	// UV�̈ʒu���v�Z
	float left = mUVSize.x * mCurrentX;
	float right = left + mUVSize.x;
	float top = mUVSize.y * mCurrentY;
	float bottom = top + mUVSize.y;

	// ���_�̂t�u�ʒu�𓮂���
	Vertex* vertices = GetVertices();
	// ����
	vertices[0].mTexCoord = { left,top };
	// �E��
	vertices[1].mTexCoord = { right,top };
	// ����
	vertices[2].mTexCoord = { left,bottom };
	// �E��
	vertices[3].mTexCoord = { right,bottom };

	MapVertices(vertices);
}

void AnimationSpriteComponent::SetupAnimationTable(const float _xSplit, const float _ySplit)
{
	mSplit = { _xSplit, _ySplit };
	mUVSize = { 1.0f / _xSplit, 1.0f / _ySplit };

	// �T�C�Y�̊m��
	mAnimationTable.resize(static_cast<size_t>(_xSplit));

	for (size_t table_i = 0; uint8_t & table : mAnimationTable)
	{
		table = static_cast<uint8_t>(table_i);
		table_i++;
	}
}

