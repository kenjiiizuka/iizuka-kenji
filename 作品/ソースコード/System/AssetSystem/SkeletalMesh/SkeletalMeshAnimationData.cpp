#include "SkeletalMeshAnimationData.h"

Channel::Channel()
	: mNumPositionKey(0)
	, mNumRotationKey(0)
	, mNumScaleKey(0)
	, bRoot(false)
{
	// 処理なし
}

void Channel::GetCurrentPositionKey(double _currentPlayTime, VectorKey& _currentKey)
{
	double nearestDifference = std::abs(_currentPlayTime - mPositionKeys[0].mTime);
	_currentKey = mPositionKeys[0];

	for (VectorKey& key : mPositionKeys)
	{
		double difference = std::abs(_currentPlayTime - key.mTime);
		if (difference <= nearestDifference)
		{
			nearestDifference = difference;
			_currentKey = key;
		}
	}
}

void Channel::GetCurrentRotationKey(double _currentPlayTime, QuaternionKey& _currentKey)
{
	double nearestDifference = std::abs(_currentPlayTime - mRotationKeys[0].mTime);
	_currentKey = mRotationKeys[0];

	for (QuaternionKey& key : mRotationKeys)
	{
		double difference = std::abs(_currentPlayTime - key.mTime);
		if (difference < nearestDifference)
		{
			nearestDifference = difference;
			_currentKey = key;
		}
	}
}

void Channel::GetCurrentScaleKey(double _currentPlayTime, VectorKey& _currentKey)
{
	double nearestDifference = std::abs(_currentPlayTime - mScaleKeys[0].mTime);
	_currentKey = mScaleKeys[0];

	for (VectorKey& key : mScaleKeys)
	{
		double difference = std::abs(_currentPlayTime - key.mTime);
		if (difference < nearestDifference)
		{
			nearestDifference = difference;
			_currentKey = key;
		}
	}
}

bool Channel::GetNextPositionKey(VectorKey& _currentKey, VectorKey& _nextPositionKey)
{
	// サイズのチェック
	size_t nextIndex = _currentKey.mIndex + 1;
	if (mPositionKeys.size() > nextIndex)
	{
		_nextPositionKey = mPositionKeys[nextIndex];
		return true;
	}
	return false;
}

bool Channel::GetNextScaleKey(VectorKey& _currentKey, VectorKey& _nextScaleKey)
{
	// サイズのチェック
	size_t nextIndex = _currentKey.mIndex + 1;
	if (mScaleKeys.size() > nextIndex)
	{
		_nextScaleKey = mScaleKeys[nextIndex];
		return true;
	}
	return false;
}


bool Channel::GetNextRotationKey(QuaternionKey& _currentKey, QuaternionKey& _nextRotationKey)
{
	// サイズのチェック
	size_t nextIndex = _currentKey.mIndex + 1;
	if (mScaleKeys.size() > nextIndex)
	{
		_nextRotationKey = mRotationKeys[nextIndex];
		return true;
	}
	return false;
}

QuaternionKey::QuaternionKey()
	: mTime(0.0f)
	, mIndex(0)
{
	// 処理なし
}

VectorKey::VectorKey()
	: mTime(0.0f)
	, mIndex(0)
{
	// 処理なし
}

SkeletalMeshAnimationData::SkeletalMeshAnimationData()
	: mDuration(0.0f)
	, mTickPerSecond(0.0f)
{
	// 処理なし
}

SkeletalMeshAnimationData::~SkeletalMeshAnimationData()
{
	// 処理なし
}

