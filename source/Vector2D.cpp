#include "Vector2D.h"

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D &Vector2D::Add(const Vector2D &v1)
{
    this->x += v1.x;
    this->y += v1.y;

    return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &v1)
{
    this->x -= v1.x;
    this->y -= v1.y;

    return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &v1)
{
    this->x /= v1.x;
    this->y /= v1.y;

    return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &v1)
{
    this->x *= v1.x;
    this->y *= v1.y;

    return *this;
}

Vector2D &operator+(Vector2D &v1, const Vector2D &v2)
{
    return v1.Add(v2);
}

Vector2D &operator-(Vector2D &v1, const Vector2D &v2)
{
    return v1.Subtract(v2);
}

Vector2D &operator/(Vector2D &v1, const Vector2D &v2)
{
    return v1.Divide(v2);
}

Vector2D &operator*(Vector2D &v1, const Vector2D &v2)
{
    return v1.Multiply(v2);
}

Vector2D &Vector2D::operator+=(Vector2D &v1)
{
    return this->Add(v1);
}

Vector2D &Vector2D::operator-=(Vector2D &v1)
{
    return this->Subtract(v1);
}

Vector2D &Vector2D::operator/=(Vector2D &v1)
{
    return this->Divide(v1);
}

Vector2D &Vector2D::operator*=(Vector2D &v1)
{
    return this->Multiply(v1);
}

Vector2D &Vector2D::operator*(const int &i)
{
    this->x *= i;
    this->y *= i;

    return *this;
}

Vector2D &Vector2D::Zero()
{
    this->x = 0;
    this->y = 0;

    return *this;
}

ostream &operator<<(ostream &stream, const Vector2D &v1)
{
    stream << "pos(" << v1.x << "," << v1.y << ")";
    return stream;
}
