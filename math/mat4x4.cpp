#include "mat4x4.h"

using radium::math::Mat4x4;

const Mat4x4 Mat4x4::IDENTITY;

const Mat4x4 Mat4x4::ZERO(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
);
