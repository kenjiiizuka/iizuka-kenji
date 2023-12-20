#pragma once
#include <SimpleMath.h>

namespace PrimitiveShape
{
	/**
     * @struct Segment3D
     * @brief 3D空間での線分の情報をもつ構想体
    */
	struct Segment3D
	{
		/** 線分の始点 */
		DirectX::SimpleMath::Vector3 mStartPosition;

		/** 線分の終点 */
		DirectX::SimpleMath::Vector3 mEndPosition;

		/**
		 * @fn GetVector
		 * @brief 始点から終点へのベクトルを返す
		 * @return DirectX::SimpleMaht::Vector3 始点から終点へのベクトル
		*/
		inline DirectX::SimpleMath::Vector3 GetVector() const noexcept;
	};

	//---------- INLINES -------------
	DirectX::SimpleMath::Vector3 Segment3D::GetVector() const noexcept
	{
		return (mEndPosition - mStartPosition);
	}
}
