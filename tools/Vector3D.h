#ifndef BOIDS3D_VECTOR3D_H
#define BOIDS3D_VECTOR3D_H

#include <iostream>
#include <cmath>
#include <random>

# define PI2 6.28318530717958647692
using namespace std;

class Vector3D {
private:
    float X;
    float Y;
    float Z;
public:
    explicit Vector3D(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {

    }

    float DistanceTo(const Vector3D &other) const {
        return static_cast<float>(std::sqrt(std::pow(other.X - X, 2) + std::pow(other.Y - Y, 2) + std::pow(other.Z - Z, 2)));
    }

    float Length() const {
        return static_cast<float>(std::sqrt(std::pow(X, 2) + std::pow(Y, 2) + std::pow(Z, 2)));
    }

    float DotProduct(const Vector3D &v) const {
        return X * v.X + Y * v.Y + Z * v.Z;
    }

    float AngleTo(const Vector3D &v) const {
        float l1 = Length();
        float l2 = v.Length();
        if (l1 == 0 || l2 == 0) {
            return 0;
        }
        return static_cast<float>(std::acos(DotProduct(v) / (l1 * l2)) * 360 / PI2);
    }

    Vector3D Normalized() const {
        float length = Length();
        if (length == 0) {
            return Vector3D();
        }
        return Vector3D(X / length, Y / length, Z / length);
    }

    Vector3D Negative() const {
        return Vector3D(-X, -Y, -Z);
    }

    Vector3D &operator+=(const Vector3D &other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D operator/(float scalar) const {
        return Vector3D(X / scalar, Y / scalar, Z / scalar);
    }

    Vector3D operator*(float scalar) const {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3D operator+(const Vector3D &other) const {
        return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D operator-(const Vector3D &other) const {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    bool operator==(const Vector3D &rhs) const
    {
        return X == rhs.X && Y == rhs.Y && Z == rhs.Z;
    }

    Vector3D ClampLength(float length) const {
        float l = Length();
        if (l > length) {
            return Normalized() * length;
        }
        return *this;
    }

    static Vector3D GetRandomUniform(std::mt19937 &engine) {
        std::uniform_real_distribution<float> thetaRange(0.0f, PI2);
        std::uniform_real_distribution<float> oneRange(0, 1);
        float theta = thetaRange(engine);
        float r = sqrt(oneRange(engine));
        float z = sqrt(1.0f - r * r) * (oneRange(engine) > 0.5f ? -1.0f : 1.0f);
        return Vector3D(r * cos(theta), r * sin(theta), z);
    }

    float getX() const {
        return X;
    }

    float getY() const {
        return Y;
    }

    float getZ() const {
        return Z;
    }

    void setX(float x) {
        this->X = x;
    }

    void setY(float y) {
        this->Y = y;
    }

    void setZ(float z) {
        this->Z = z;
    }
};

#endif //BOIDS3D_VECTOR3D_H
