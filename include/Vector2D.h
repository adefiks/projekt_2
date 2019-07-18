/*
!!! Vector2D.h !!!
    * vectors used in engine with two parameters x,y:
    * vectors 2D have override operators for -> +, -, /, *, +=, -=, *=, /=
    * method for zeroing elements zero()
*/

#pragma once
#include "common.h"

// vector 2D with parameters x,y with override operators
class Vector2D
{
public:
    float x, y; // parameters x,y

    Vector2D();

    // constructor with start parameters x,y
    Vector2D(float x, float y);

    // for adding x,y to vector +=x,y
    Vector2D &Add(const Vector2D &v1);

    // for subtracting x,y to vector -=x,y
    Vector2D &Subtract(const Vector2D &v1);

    // for multiplying x,y to vector *=x,y
    Vector2D &Multiply(const Vector2D &v1);

    // for dividing x,y to vector /=x,y
    Vector2D &Divide(const Vector2D &v1);

    // override operator for adding x,y
    friend Vector2D &operator+(Vector2D &v1, const Vector2D &v2);

    // override operator for subtracting x,y
    friend Vector2D &operator-(Vector2D &v1, const Vector2D &v2);

    // override operator for dividing x,y
    friend Vector2D &operator/(Vector2D &v1, const Vector2D &v2);

    // override operator for multiplying x,y
    friend Vector2D &operator*(Vector2D &v1, const Vector2D &v2);

    // for additional override operators for x,y
    Vector2D &operator+=(Vector2D &v1);
    Vector2D &operator-=(Vector2D &v1);
    Vector2D &operator/=(Vector2D &v1);
    Vector2D &operator*=(Vector2D &v1);

    // for multiply x,y by const int
    Vector2D &operator*(const int &i);

    // for zeroing x,y
    Vector2D &Zero();

    // for printing the x,y position
    friend ostream &operator<<(ostream &stream, const Vector2D &v1);
};