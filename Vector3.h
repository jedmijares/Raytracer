#ifndef VECTOR3
#define VECTOR3

#include <cmath>

class Vector3
{
private:
    // float x, y, z;

public:
    float x, y, z;

    Vector3(float xIn, float yIn, float zIn);
    Vector3();
    ~Vector3();

    float length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    float dot(Vector3 const &other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 operator-()
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator-(Vector3 const &other)
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator+(Vector3 const &other)
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator*(float scalar)
    {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
};

Vector3::Vector3(float xIn, float yIn, float zIn)
{
    x = xIn;
    y = yIn;
    z = zIn;
}

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::~Vector3()
{
}

#endif