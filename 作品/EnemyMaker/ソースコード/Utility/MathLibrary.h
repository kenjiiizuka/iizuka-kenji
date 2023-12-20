#pragma once

//------------ INCLUDES -------------
#include <SimpleMath.h>
#include <random>
#include "../Game/Component/TransformComponent/Transform.h"

/** 円周率 */
constexpr double PI = 3.14159265359;

/** 円周率 float */
constexpr float PIFloat = 3.14159265f;

class MathLibrary
{
private:
	/** 乱数生成デバイス */
	static std::random_device mRandomDevice;

	/** 乱数生成エンジン */
	static std::mt19937 mRandomEngine;

 public: 
	/**
	* @fn RotateVector
	* @brief ベクトルを回転させる関数
	* @param DirectX::SimpleMath::Vector3 (_vector)
	* @param DirectX::SimpleMath::Vector3 (_rotation)
	* @return RotateVector
	* 
	*/
	static DirectX::SimpleMath::Vector3 RotateVector(DirectX::SimpleMath::Vector3 _vector, DirectX::SimpleMath::Vector3 _rotation);

	/**
	 * @fn RotateVector
	 * @brief　ベクトルを回転させる関数
	 * @param (_vector) 回転させるベクトル
	 * @param (_rotation) 回転行列
	 * @return Vector3 回転したベクトル
	*/
	static DirectX::SimpleMath::Vector3 RotateVector(DirectX::SimpleMath::Vector3 _vector, DirectX::SimpleMath::Matrix& _rotaition);

	// Matrix
	static DirectX::SimpleMath::Matrix Conv_RotationToMatrix(DirectX::SimpleMath::Vector3 _rotation);
	static DirectX::SimpleMath::Vector3 Conv_VectorToRotation(DirectX::SimpleMath::Vector3 _vector);

	static float Clamp01(float _value);
	static float ClampMinus1Plus1(float _value);
	static float Atan2(float _x, float _y);
	static float Abs(float _value);
	static DirectX::SimpleMath::Vector3 AbsVector(DirectX::SimpleMath::Vector3 _vector);
	
	static DirectX::SimpleMath::Vector3 RotationInterpTo(DirectX::SimpleMath::Vector3 _currnet, DirectX::SimpleMath::Vector3 _target, float _deltaTime, float _interpSpeed);
	static DirectX::SimpleMath::Vector3 LerpQuaternion(DirectX::SimpleMath::Quaternion _quat1, DirectX::SimpleMath::Quaternion _quat2, float _deltaTime, float _interpSpeed);
	static bool VectorIsZero(DirectX::SimpleMath::Vector3 _vector);
	static bool VectorIsNearyZero(DirectX::SimpleMath::Vector3 _vector, float _near = 10.f);

	static DirectX::SimpleMath::Vector3 CalculateRotationDiffrence(DirectX::SimpleMath::Vector3 _rotation1, DirectX::SimpleMath::Vector3 _rotation2);

	/**
	 * @fn MakeWorldMatrix
	 * @brief トランスフォームかワールド行列を作成する関数
	 * @param const Transform (_transform) トランスフォーム
	 * @return DirectX::SimpleMath::Matrix ワールド行列
	*/
	static DirectX::SimpleMath::Matrix MakeWorldMatrix(const Transform& _transform);

	/**
	 * @fn DecomposeMatrix
	 * @brief 行列から位置,回転,スケールの要素を取り出しトランスフォームに代入する
	 * @param DirectX::SimpleMath::Matrix& (_matrix) 行列
	 * @param Transform& (_transform) トランスフォーム
	 * @return void
	*/
	static void DecomposeMatrix(DirectX::SimpleMath::Matrix& _matrix, Transform& _transform);

	/**
	* @fn DecomposeMatrix
	* @brief 行列の分解
	* @param DirectX::SimpleMath::Vector3&    (_position)
	* @param DirectX::SimpleMath::Vector3&    (_scale)
	* @param DirectX::SimpleMath::Quaternion& (_quaternion)
	* @param DirectX::SimpleMath::Matrix&     (_matrix)
	* @return void
	*/
	static void DecomposeMatrix(DirectX::SimpleMath::Vector3& _position, DirectX::SimpleMath::Vector3& _scale, DirectX::SimpleMath::Quaternion& _quaternion, DirectX::SimpleMath::Matrix& _matrix);

	/**
	 * @fn RemoveScaleFromMatrix
	 * @brief 第一引数の行列からスケールの要素を除いた行列を第二引数に代入する
	 * @param DirectX::SimpleMath::Matrix& (_matrix) 
	 * @param DirectX::SimpleMath::Matrix& (_removedMatrix)
	 * @return void
	*/
	static void RemoveScaleFromMatrix(DirectX::SimpleMath::Matrix& _matrix, DirectX::SimpleMath::Matrix& _removedMatrix);

	/**
	 * @fn CreateTranslationMatrix
	 * @brief 渡されたベクトルから平行移動行列を作成する
	 * @param const DirectX::SimpleMath::Vector3& (_vector)
	 * @param DirectX::SimpleMath::Matrix& (_outPutMatrix)
	 * @return void
	*/
	static void CreateTranslationMatrix(const DirectX::SimpleMath::Vector3& _vector,DirectX::SimpleMath::Matrix& _outPutMatrix );

	/**
	 * @fn CreateRotationMatrix
	 * @brief 渡されたベクトルから平行移動行列を作成する
	 * @param const DirectX::SimpleMath::Vector3& (_rotaion)
	 * @param DirectX::SimpleMath::Matrix& (_outPutMatrix)
	 * @return void
	*/
	static void CreateRotationMatrix(const DirectX::SimpleMath::Vector3& _rotaion, DirectX::SimpleMath::Matrix& _outPutMatrix);

	/**
	* @fn CalucWorldMatrix
	* @brief ワールド行列を作成する			   
	* @param const DirectX::SimpleMath::Vector3&    (_position)
	* @param const DirectX::SimpleMath::Vector3&    (_scale)
	* @param const DirectX::SimpleMath::Quaternion& (_quaternion)
	* @param DirectX::SimpleMath::Matrix&           (_outPutMatrix)
	* @return void
	*/
	static void MakeWorldMatrix(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _scale, const DirectX::SimpleMath::Quaternion& _quaternion, DirectX::SimpleMath::Matrix& _outPutMatrix);

	/**
	* @fn CalucTransformDifference
	* @brief 渡されたトランスフォームの各要素の差分を求める
	* @detail _transform1 から _transform2を減算し結果を _differenceを入れる
	* @param const Transform& (_transform1)
	* @param const Transform& (_transform2)
	* @param Transform& (_difference)
	* @return void
	*/
	static void CalucTransformDifference(const Transform& _transform1, const Transform& _transform2, Transform& _difference);

	/**
	 * @fn DegreeToRadian
	 * @brief デグリーからラディアンに変換する
	 * @param const double (_degree)
	 * @return double
	*/
	static inline double DegreeToRadian(const double _degree);

	/**
	* @fn FloatDegreeToRadian
	* @brief デグリーからラディアンに変換する (float型)
	* @param const double (_degree)
	* @return float 
	*/
	static inline float FloatDegreeToRadian(const double _degree);

	/**
	* @fn GetRightVector
	* @param const DirectX::SimpleMath::Vector3& (_rotation)
	* @brief 渡された回転の右向きベクトルを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	static DirectX::SimpleMath::Vector3 GetRightVector(const DirectX::SimpleMath::Vector3& _rotation);

	/**
	* @fn GetUpVector
	* @param const DirectX::SimpleMath::Vector3& (_rotation)
	* @brief 渡された回転の上向きベクトルを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	static DirectX::SimpleMath::Vector3 GetUpVector(const DirectX::SimpleMath::Vector3& _rotation);

	/**
	* @fn GetForwardVector
	* @param const DirectX::SimpleMath::Vector3& (_rotation)
	* @brief 渡された回転の前向きベクトルを返す
	* @return DirectX::SimpleMath::Vector3
	*/
	static DirectX::SimpleMath::Vector3 GetForwardVector(const DirectX::SimpleMath::Vector3& _rotation);

	/**
	* @fn Clamp
	* @brief クランプ
	* @param const float (_value)
	* @param const float (_min)
	* @param const float (_max)
	* @return void
	*/
	static float Clamp(const float _value, const float _min, const float _max);

	/**
	* @fn RandomIntInRange
	* @brief 指定された範囲ないでランダムな値を返す
	* @param const inr (_min)
	* @param const inr (_max)
	* @return int
	*/
	static int RandomIntInRange(const int _min, const int max);

	/**
	* @fn RandomFloatInRange
	* @brief 指定された範囲内のランダムな値を返す
	* @param const float (_min)
	* @param const float (_max)
	* @return float
	*/
	static float RandomFloatInRange(const float _min, const float _max);

	/**
	* @fn InRange
	* @brief 渡された値が範囲内になるかを判定する
	* @param const float (_value)
	* @param const float (_min)
	* @param const float (_max)
	* @return true 範囲内 false 範囲外
	*/
	static bool InRange(const float _value, const float _min ,const float _max) noexcept;
};

//----------- INLINES -----------

inline double MathLibrary::DegreeToRadian(const double _degree)
{
	return _degree * PI / 180.0f;
}

inline float MathLibrary::FloatDegreeToRadian(const double _degree)
{
	return static_cast<float>(DegreeToRadian(_degree));
}

