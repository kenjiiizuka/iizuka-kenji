//--------- INCLUDES ----------
#include "MathLibrary.h"

std::random_device MathLibrary::mRandomDevice;
std::mt19937 MathLibrary::mRandomEngine(mRandomDevice());

using namespace DirectX::SimpleMath;

/**
 * @fn RotateVector
 * @brief　ベクトルを回転させる関数
 * @param (_vector) 回転させるベクトル
 * @param (_rotation) 回転　
 * @return Vector3 回転したベクトル
*/
DirectX::SimpleMath::Vector3 MathLibrary::RotateVector(DirectX::SimpleMath::Vector3 _vector, DirectX::SimpleMath::Vector3 _rotation)
{
    Matrix rotationMatrix = Conv_RotationToMatrix(_rotation);
    return RotateVector(_vector, rotationMatrix);
}


/**
 * @fn RotateVector
 * @brief　ベクトルを回転させる関数
 * @param (_vector) 回転させるベクトル
 * @param (_rotation) 回転行列
 * @return Vector3 回転したベクトル
*/
DirectX::SimpleMath::Vector3 MathLibrary::RotateVector(DirectX::SimpleMath::Vector3 _vector, DirectX::SimpleMath::Matrix& _rotation)
{
    return Vector3::Transform(_vector, _rotation);
}

/**
 * @fn Conv_RotationToMatrix
 * @brief　回転を回転行列に変換する関数
 * @param (_rotation) 変換したい回転
 * @return Matrix 変換した回転行列
*/
DirectX::SimpleMath::Matrix MathLibrary::Conv_RotationToMatrix(DirectX::SimpleMath::Vector3 _rotation)
{
    return Matrix::CreateFromYawPitchRoll(_rotation.y, _rotation.x, _rotation.z);
}

/**
 * @fn Conv_VectorToRotation
 * @brief　ベクトルを回転に変換する関数
 * @param (_vector) 変換したいベクトル
 * @return Vector3 回転に変換した値
*/
DirectX::SimpleMath::Vector3 MathLibrary::Conv_VectorToRotation(DirectX::SimpleMath::Vector3 _vector)
{
    Vector3 normalizedVector = _vector;
    normalizedVector.Normalize();

    // Yawを求める
    float yaw = std::atan2(normalizedVector.x, normalizedVector.z);
    // Pitchを求める
    float pitch = std::asin(normalizedVector.y);

    // ベクトルをＹ軸周りに回転させて、ＸＺ平面に射影
    Quaternion quaternion = Quaternion::CreateFromYawPitchRoll(yaw, pitch, 0.0f);
    Vector3 rotatedVector = Vector3::Transform(_vector, quaternion);
    rotatedVector.y = 0.0f;
    rotatedVector.Normalize();
    float roll = std::acos(Vector3::UnitX.Dot(rotatedVector));

    return Vector3(pitch, yaw, roll);
}

float MathLibrary::LerpFloat(const float _min, const float _max, const float _t)
{
    return (_max - _min ) * _t + _min;
}

float MathLibrary::Clamp01(const float _value)
{ 
    return (_value < 0.0f) ? 0.0f : ((_value > 1.0f) ? 1.0f : _value);
}

double MathLibrary::Clamp01(const double _value)
{
    return (_value < 0.0f) ? 0.0f : ((_value > 1.0f) ? 1.0f : _value);
}

float MathLibrary::ClampMinus1Plus1(float _value)
{
    return (_value < -1.0f) ? -1.0f : ((_value > 1.0f) ? 1.0f : _value);
}

float MathLibrary::Atan2(float _x, float _y)
{
    return std::atan2(_y, _x); 
}

float MathLibrary::Abs(float _value)
{ 
    return _value < 0.0f ? _value * -1 : _value;
}

DirectX::SimpleMath::Vector3 MathLibrary::AbsVector(Vector3 _vector)
{
    Vector3 absVec;
    absVec.x = Abs(_vector.x);
    absVec.y = Abs(_vector.y);
    absVec.z = Abs(_vector.z);
    return absVec;
}

DirectX::SimpleMath::Vector3 MathLibrary::RotationInterpTo(DirectX::SimpleMath::Vector3 _current, DirectX::SimpleMath::Vector3 _target, float _deltaTime, float _interpSpeed)
{
    // デルタタイムが０か、すでに同じ向きなら_currnetを返す
    if (_deltaTime == 0.0f || _current == _target)
    {
        return _current;
    }

    // interpSpeedが0以下なら_targetを返す
    if (_interpSpeed <= 0.0f)
    {
        return _target;
    } 
    const Vector3 diff = (_target - _current);
    if (VectorIsNearyZero(diff, 0.01f))
    {
        return _target;
    }

    const float deltaInterpSpeed = _interpSpeed * _deltaTime;
    const Vector3 deltaMove = diff * Clamp01(deltaInterpSpeed);
    return (_current + deltaMove);
}

DirectX::SimpleMath::Vector3 MathLibrary::LerpQuaternion(DirectX::SimpleMath::Quaternion _quat1, DirectX::SimpleMath::Quaternion _quat2, float _deltaTime, float _interpSpeed)
{
    float t = Clamp01(_deltaTime * _interpSpeed);
    Quaternion lerpedQuat = Quaternion::Lerp(_quat1, _quat2, t);
    return lerpedQuat.ToEuler();
}

bool MathLibrary::VectorIsZero(DirectX::SimpleMath::Vector3 _vector)
{ 
    return (_vector.x == 0 && _vector.y == 0 && _vector.z == 0) ? true : false;
}

bool MathLibrary::VectorIsNearyZero(DirectX::SimpleMath::Vector3 _vector, float _near)
{
    return (-_near < _vector.x && _vector.x < _near)
        && (-_near < _vector.y && _vector.y < _near) 
        && (-_near < _vector.z && _vector.z < _near);
}

DirectX::SimpleMath::Vector3 MathLibrary::CalculateRotationDifference(DirectX::SimpleMath::Vector3 _rotation1, DirectX::SimpleMath::Vector3 _rotation2)
{ 
    return DirectX::SimpleMath::Vector3();
}

void MathLibrary::DecomposeMatrix(DirectX::SimpleMath::Matrix& _matrix, Transform& _transform)
{
    Quaternion quat;
    _matrix.Decompose(_transform.mScale,quat, _transform.mPosition);
    _transform.mRotation = quat.ToEuler();
}

void MathLibrary::DecomposeMatrix(DirectX::SimpleMath::Vector3& _position, DirectX::SimpleMath::Vector3& _scale, DirectX::SimpleMath::Quaternion& _quaternion, DirectX::SimpleMath::Matrix& _matrix)
{
    _matrix.Decompose(_scale, _quaternion, _position);
}

void MathLibrary::GetTranslationFromMatrix(DirectX::SimpleMath::Matrix& _matrix, DirectX::SimpleMath::Vector3& _translation)
{
    Vector3 scale;
    Quaternion quaternion;
    _matrix.Decompose(scale, quaternion, _translation);
}

void MathLibrary::RemoveScaleFromMatrix(DirectX::SimpleMath::Matrix& _matrix, DirectX::SimpleMath::Matrix& _removedMatrix)
{
    Vector3 position;
    Vector3 scale;
    Quaternion quat;
    _matrix.Decompose(scale, quat, position);
    
    Matrix rotation = Matrix::CreateFromYawPitchRoll(quat.ToEuler().y, quat.ToEuler().x, quat.ToEuler().z);
    Matrix translation = Matrix::CreateTranslation(position.x, position.y, position.z);
    _removedMatrix = rotation * translation;
}

void MathLibrary::CreateTranslationMatrix(const DirectX::SimpleMath::Vector3& _vector, DirectX::SimpleMath::Matrix& _outPutMatrix)
{
    _outPutMatrix = Matrix::CreateTranslation(_vector.x, _vector.y, _vector.z);
}

void MathLibrary::CreateRotationMatrix(const DirectX::SimpleMath::Vector3& _rotaion, DirectX::SimpleMath::Matrix& _outPutMatrix)
{
    _outPutMatrix = Matrix::CreateFromYawPitchRoll(_rotaion.y, _rotaion.x, _rotaion.z);
}

void MathLibrary::MakeWorldMatrix(const DirectX::SimpleMath::Vector3& _position, const DirectX::SimpleMath::Vector3& _scale, const DirectX::SimpleMath::Quaternion& _quaternion, DirectX::SimpleMath::Matrix& _outPutMatrix)
{
    Matrix translation = Matrix::CreateTranslation(_position.x, _position.y, _position.z);
    Matrix scale = Matrix::CreateScale(_scale.x, _scale.y, _scale.z);
    Matrix rotation = Matrix::CreateFromQuaternion(_quaternion);
    _outPutMatrix = scale * rotation * translation;
}

void MathLibrary::CalucTransformDifference(const Transform& _transform1, const Transform& _transform2, Transform& _difference)
{
    _difference.mPosition = _transform1.mPosition - _transform2.mPosition;
    _difference.mRotation = _transform1.mRotation - _transform2.mRotation;
    _difference.mScale = _transform1.mScale - _transform2.mScale;
}

DirectX::SimpleMath::Vector3 MathLibrary::GetRightVector(const DirectX::SimpleMath::Vector3& _rotation)
{
    Matrix rotationMatrix;
    CreateRotationMatrix(_rotation, rotationMatrix); 
    DirectX::SimpleMath::Vector3 right;
    right.x = rotationMatrix._11;
    right.y = rotationMatrix._12;
    right.z = rotationMatrix._13;
    right.Normalize();
    return right;
}

DirectX::SimpleMath::Vector3 MathLibrary::GetUpVector(const DirectX::SimpleMath::Vector3& _rotation)
{
    Matrix rotationMatrix;
    CreateRotationMatrix(_rotation, rotationMatrix);  
    DirectX::SimpleMath::Vector3 Up;
    Up.x = rotationMatrix._21;
    Up.y = rotationMatrix._22;
    Up.z = rotationMatrix._23;
    Up.Normalize();
    return Up; 
}

DirectX::SimpleMath::Vector3 MathLibrary::GetForwardVector(const DirectX::SimpleMath::Vector3& _rotation)
{
    Matrix rotationMatrix;
    CreateRotationMatrix(_rotation, rotationMatrix);
    Vector3 forward;
    forward.x = rotationMatrix._31;
    forward.y = rotationMatrix._32;
    forward.z = rotationMatrix._33;
    forward.Normalize();
    return forward;
}

float MathLibrary::Clamp(const float _value, const float _min, const float _max)
{
    return (_value < _min) ? _min : (_value > _max) ? _max : _value;
}

int MathLibrary::RandomIntInRange(const int _min, const int _max)
{
    std::uniform_int_distribution dis(_min, _max);
    return dis(mRandomEngine);
}

float MathLibrary::RandomFloatInRange(const float _min, const float _max)
{
    std::uniform_real_distribution<float> dis(_min, _max);
    return dis(mRandomEngine);
}

bool MathLibrary::InRange(const float _value, const float _min, const float _max) noexcept
{
    return (_min < _value) && (_value < _max);
}

void MathLibrary::ConvRotationToQuaternion(const DirectX::SimpleMath::Vector3 _rotation, DirectX::SimpleMath::Quaternion& _quaternion) noexcept
{
    Matrix matrix;
    MathLibrary::CreateRotationMatrix(_rotation, matrix);
    _quaternion = Quaternion::CreateFromRotationMatrix(matrix);
}

uint8_t MathLibrary::GetDigitValue(const uint16_t _number, const uint8_t _digit) noexcept
{
    uint16_t deviser = static_cast<uint16_t>(std::pow(10, _digit));
    return  (_number / deviser) % 10;
}

float MathLibrary::LookAtYaw(const DirectX::SimpleMath::Vector3 _pos1, const DirectX::SimpleMath::Vector3 _pos2)
{
    Vector3 toPos2 = _pos2 - _pos1;
    toPos2.Normalize(); 
    return Conv_VectorToRotation(toPos2).y; 
}

DirectX::SimpleMath::Matrix MathLibrary::MakeWorldMatrix(const Transform& _transform)
{
    Matrix translation = Matrix::CreateTranslation(_transform.mPosition.x, _transform.mPosition.y, _transform.mPosition.z);
    Matrix rotation = Matrix::CreateFromYawPitchRoll(_transform.mRotation.y, _transform.mRotation.x, _transform.mRotation.z);
    Matrix scale = Matrix::CreateScale(_transform.mScale.x, _transform.mScale.y,_transform.mScale.z);
    return scale * rotation * translation;
}
