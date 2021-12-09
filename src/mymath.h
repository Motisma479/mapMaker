#pragma once

#include <cmath>

#include "raylib.h"

inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

inline Vector2 operator*(const Vector2& v1, float value)
{
    return (Vector2){v1.x * value, v1.y * value};
}

inline Vector2 operator*(float value, const Vector2& v1)
{
    return (Vector2){v1.x * value, v1.y * value};
}

inline Vector2 operator+=(const Vector2& v1, const Vector2& v2)
{
    Vector2 tmp(v1);
    tmp.x += v2.x;
    tmp.y += v2.y;
    return tmp;
}

inline Vector2 operator-=(const Vector2& v1, const Vector2& v2)
{
    Vector2 tmp(v1);
    tmp.x -= v2.x;
    tmp.y -= v2.y;
    return tmp;
}

inline Vector2 operator*=(const Vector2& v1, float value)
{
    Vector2 tmp(v1);
    tmp.x *= value;
    tmp.y *= value;
    return tmp;
}