#include "Camera.h"

Camera::Camera() : position(), direction(), up(0, 1, 0) {}

Camera::Camera(Vector pos, Vector dir, Vector up) : position(pos), direction(dir), up(up) {}