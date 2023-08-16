//
// Created by johnk on 2023/6/21.
//

#pragma once

#include <Common/Math/Vector.h>
#include <Common/Math/Matrix.h>
#include <Common/Math/Quaternion.h>

namespace Common {
    template <typename T>
    requires isFloatingPointV<T>
    struct TransformBase {
        Vector<T, 3> scale;
        Quaternion<T> rotation;
        Vector<T, 3> translation;
    };

    template <typename T>
    struct Transform : public TransformBase<T> {
        static inline Transform LookAt(const Vector<T, 3>& inPosition, const Vector<T, 3>& inTargetPosition, const Vector<T, 3>& inUpDirection = VecConsts<T, 3>::unitZ);

        inline Transform();
        inline Transform(Quaternion<T> inRotation, Vector<T, 3> inTranslation);
        inline Transform(Vector<T, 3> inScale, Quaternion<T> inRotation, Vector<T, 3> inTranslation);
        inline Transform(const Transform& other);
        inline Transform(Transform&& other) noexcept;
        inline Transform& operator=(const Transform& other);

        inline bool operator==(const Transform& rhs) const;
        inline bool operator!=(const Transform& rhs) const;

        inline Transform operator+(const Vector<T, 3>& inTranslation) const;
        inline Transform operator|(const Quaternion<T>& inRotation) const;
        inline Transform operator*(const Vector<T, 3>& inScale) const;

        inline Transform& operator+=(const Vector<T, 3>& inTranslation);
        inline Transform& operator|=(const Quaternion<T>& inRotation);
        inline Transform& operator*=(const Vector<T, 3>& inScale);

        inline Transform& Translate(const Vector<T, 3>& inTranslation);
        inline Transform& Rotate(const Quaternion<T>& inRotation);
        inline Transform& Scale(const Vector<T, 3>& inScale);
        inline Transform& LookTo(const Vector<T, 3>& inPosition, const Vector<T, 3>& inTargetPosition, const Vector<T, 3>& inUpDirection = VecConsts<T, 3>::unitZ);

        Matrix<T, 4, 4> GetTranslationMatrix() const;
        Matrix<T, 4, 4> GetRotationMatrix() const;
        Matrix<T, 4, 4> GetScaleMatrix() const;
        // scale -> rotate -> translate
        Matrix<T, 4, 4> GetTransformMatrix() const;
        // rotate -> translate
        Matrix<T, 4, 4> GetTransformMatrixNoScale() const;
        Vector<T, 3> TransformPosition(const Vector<T, 3>& inPosition) const;
        Vector<T, 4> TransformPosition(const Vector<T, 4>& inPosition) const;

        template <typename IT>
        Transform<IT> CastTo() const;
    };

    using HTransform = Transform<HFloat>;
    using FTransform = Transform<float>;
    using DTransform = Transform<double>;
}

namespace Common {
    template <typename T>
    Transform<T> Transform<T>::LookAt(const Vector<T, 3>& inPosition, const Vector<T, 3>& inTargetPosition, const Vector<T, 3>& inUpDirection)
    {
        Transform<T> result;
        result.LookTo(inPosition, inTargetPosition, inUpDirection);
        return result;
    }

    template <typename T>
    Transform<T>::Transform()
    {
        this->scale = VecConsts<T, 3>::unit;
        this->rotation = QuatConsts<T>::identity;
        this->translation = VecConsts<T, 3>::zero;
    }

    template <typename T>
    Transform<T>::Transform(Quaternion<T> inRotation, Vector<T, 3> inTranslation)
    {
        this->scale = VecConsts<T, 3>::unit;
        this->rotation = inRotation;
        this->translation = inTranslation;
    }

    template <typename T>
    Transform<T>::Transform(Vector<T, 3> inScale, Quaternion<T> inRotation, Vector<T, 3> inTranslation)
    {
        this->scale = inScale;
        this->rotation = inRotation;
        this->translation = inTranslation;
    }

    template <typename T>
    Transform<T>::Transform(const Transform& other)
    {
        this->scale = other.scale;
        this->rotation = other.rotation;
        this->translation = other.translation;
    }

    template <typename T>
    Transform<T>::Transform(Transform&& other) noexcept
    {
        this->scale = std::move(other.scale);
        this->rotation = std::move(other.rotation);
        this->translation = std::move(other.translation);
    }

    template <typename T>
    Transform<T>& Transform<T>::operator=(const Transform& other)
    {
        this->scale = other.scale;
        this->rotation = other.rotation;
        this->translation = other.translation;
        return *this;
    }

    template <typename T>
    bool Transform<T>::operator==(const Transform& rhs) const
    {
        return this->scale == rhs.scale
            && this->rotation == rhs.rotation
            && this->translation == rhs.translation;
    }

    template <typename T>
    bool Transform<T>::operator!=(const Transform& rhs) const
    {
        return !this->operator==(rhs);
    }

    template <typename T>
    Transform<T> Transform<T>::operator+(const Vector<T, 3>& inTranslation) const
    {
        Transform<T> result;
        result.scale = this->scale;
        result.rotation = this->rotation;
        result.translation = this->translation + inTranslation;
        return result;
    }

    template <typename T>
    Transform<T> Transform<T>::operator|(const Quaternion<T>& inRotation) const
    {
        Transform<T> result;
        result.scale = this->scale;
        result.rotation = this->rotation * inRotation;
        result.translation = this->translation;
        return result;
    }

    template <typename T>
    Transform<T> Transform<T>::operator*(const Vector<T, 3>& inScale) const
    {
        Transform<T> result;
        result.scale = this->scale * inScale;
        result.rotation = this->rotation;
        result.translation = this->translation;
        return result;
    }

    template <typename T>
    Transform<T>& Transform<T>::operator+=(const Vector<T, 3>& inTranslation)
    {
        return Translate(inTranslation);
    }

    template <typename T>
    Transform<T>& Transform<T>::operator|=(const Quaternion<T>& inRotation)
    {
        return Rotate(inRotation);
    }

    template <typename T>
    Transform<T>& Transform<T>::operator*=(const Vector<T, 3>& inScale)
    {
        return Scale(inScale);
    }

    template <typename T>
    Transform<T>& Transform<T>::Translate(const Vector<T, 3>& inTranslation)
    {
        this->translation += inTranslation;
        return *this;
    }

    template <typename T>
    Transform<T>& Transform<T>::Rotate(const Quaternion<T>& inRotation)
    {
        this->rotation *= inRotation;
        return *this;
    }

    template <typename T>
    Transform<T>& Transform<T>::Scale(const Vector<T, 3>& inScale)
    {
        this->scale *= inScale;
        return *this;
    }

    template <typename T>
    Transform<T>& Transform<T>::LookTo(const Vector<T, 3>& inPosition, const Vector<T, 3>& inTargetPosition, const Vector<T, 3>& inUpDirection)
    {
        Vector<T, 3> forward(inTargetPosition - inPosition);
        Vector<T, 3> f = forward.Normalized();

        Vector<T, 3> side = inUpDirection.Cross(f);
        Vector<T, 3> s = side.Normalized();

        Vector<T, 3> u = f.Cross(s);

        // Matrix<T, 4, 4> lookAtMat {
        //     s.x, s.y, s.z, -s.Dot(inPosition),
        //     u.x, u.y, u.z, -u.Dot(inPosition),
        //     f.x, f.y. f.z, -f.Dot(inPosition),
        //     0, 0, 0, 1
        // };
        // Transform of an object(camera) is the inverse of transform represented in lookAtMatrix

        // Translation is easy to get
        this->translation = Vector<T, 3> {s.Dot(inPosition), u.Dot(inPosition), f.Dot(inPosition)};

        // Rotaion matrix is orthogonal, its inverse equals to its transpose
        // So, we get quaternion from the transposed rotation part of lookAtMatrix
        // Algorithm: https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/

        Matrix<T, 3, 3> rotMat {
            s.x, u.x, f.x,
            s.y, u.y, f.y,
            s.z, u.z, f.z
        };

        T trace = rotMat.At(0, 0) + rotMat.At(1, 1) + rotMat.At(2, 2);
        if (trace > static_cast<T>(0)) {
            T root = sqrt(trace + static_cast<T>(1.0));
            this->rotation.w = static_cast<T>(0.5) * root;

            root = static_cast<T>(0.5) / root;
            this->rotation.x = root * (rotMat.At(2, 1) - rotMat.At(1, 2));
            this->rotation.y = root * (rotMat.At(0, 2) - rotMat.At(2, 0));
            this->rotation.z = root * (rotMat.At(1, 0) - rotMat.At(0, 1));
        } else if (rotMat.At(0, 0) > rotMat.At(1, 1) && rotMat.At(0, 0) > rotMat.At(2, 2)) {
            T root = sqrt(rotMat.At(0, 0) - rotMat.At(1, 1) - rotMat.At(2, 2) + static_cast<T>(1.0));
            this->rotation.x = static_cast<T>(0.5) * root;

            root = static_cast<T>(0.5) / root;
            this->rotation.y = root * (rotMat.At(0, 1) + rotMat.At(1, 0));
            this->rotation.z = root * (rotMat.At(0, 2) + rotMat.At(2, 0));
            this->rotation.w = root * (rotMat.At(2, 1) - rotMat.At(1, 2));
        } else if (rotMat.At(1, 1) > rotMat.At(2, 2)) {
            T root = sqrt(rotMat.At(1, 1) - rotMat.At(0, 0) - rotMat.At(2, 2) + static_cast<T>(1.0));
            this->rotation.y = static_cast<T>(0.5) * root;

            root = static_cast<T>(0.5) / root;
            this->rotation.x = root * (rotMat.At(0, 1) + rotMat.At(1, 0));
            this->rotation.z = root * (rotMat.At(1, 2) + rotMat.At(2, 1));
            this->rotation.w = root * (rotMat.At(0, 2) - rotMat.At(2, 0));
        } else {
            T root = sqrt(rotMat.At(2, 2) - rotMat.At(0, 0) - rotMat.At(1, 1) + static_cast<T>(1.0));
            this->rotation.z = static_cast<T>(0.5) * root;

            root = static_cast<T>(0.5) / root;
            this->rotation.x = root * (rotMat.At(0, 2) + rotMat.At(2, 0));
            this->rotation.y = root * (rotMat.At(1, 2) + rotMat.At(2, 1));
            this->rotation.w = root * (rotMat.At(1, 0) - rotMat.At(0, 1));
        }

        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> Transform<T>::GetTranslationMatrix() const
    {
        Matrix<T, 4, 4> result = MatConsts<T, 4, 4>::identity;
        result.SetCol(3, this->translation.x, this->translation.y, this->translation.z, 1);
        return result;
    }

    template <typename T>
    Matrix<T, 4, 4> Transform<T>::GetRotationMatrix() const
    {
        return this->rotation.GetRotationMatrix();
    }

    template <typename T>
    Matrix<T, 4, 4> Transform<T>::GetScaleMatrix() const
    {
        Matrix<T, 4, 4> result = MatConsts<T, 4, 4>::identity;
        result.At(0, 0) = this->scale.x;
        result.At(1, 1) = this->scale.y;
        result.At(2, 2) = this->scale.z;
        return result;
    }

    template <typename T>
    Matrix<T, 4, 4> Transform<T>::GetTransformMatrix() const
    {
        return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
    }

    template <typename T>
    Matrix<T, 4, 4> Transform<T>::GetTransformMatrixNoScale() const
    {
        return GetTranslationMatrix() * GetRotationMatrix();
    }

    template <typename T>
    Vector<T, 3> Transform<T>::TransformPosition(const Vector<T, 3>& inPosition) const
    {
        Matrix<T, 4, 1> posColMat = Matrix<T, 4, 1>::FromColVecs(Vector<T, 4>(inPosition.x, inPosition.y, inPosition.z, 1));
        return (GetTransformMatrix() * posColMat).Col(0).template SubVec<0, 1, 2>();
    }

    template <typename T>
    Vector<T, 4> Transform<T>::TransformPosition(const Vector<T, 4>& inPosition) const
    {
        Matrix<T, 4, 1> posColMat = Matrix<T, 4, 1>::FromColVecs(inPosition);
        return (GetTransformMatrix() * posColMat).Col(0);
    }

    template <typename T>
    template <typename IT>
    Transform<IT> Transform<T>::CastTo() const
    {
        Transform<IT> result;
        result.translation = this->translation.template CastTo<IT>();
        result.rotation = this->rotation.template CastTo<IT>();
        result.scale = this->scale.template CastTo<IT>();
        return result;
    }
}
