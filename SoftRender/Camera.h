#pragma once

#include "Vector.h"

class Camera {
public:
    Vector position;
    Vector direction;
    Vector up;

    Camera();
    Camera(Vector pos, Vector dir, Vector up);
};
