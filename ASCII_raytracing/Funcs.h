#ifndef _FUNCS_H
#define _FUNCS_H
#include <math.h>
#include "Vec2.h"
#include "Vec3.h"

//restriction between min and max
float restrict(float value, float min, float max){
    return fmax(fmin(value, max), min);
}
//Length of a 2D vector
float length(const vec2& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

//Length of a 3D vector
float length(const vec3& vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
//Normalized 3D vector
vec3 normal(vec3 vec) {
    return vec / length(vec);
}
//Dot product for 2 3D vectors
float dotProduct(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
//Reflected vector function
vec3 reflect(vec3 rd, vec3 n) { return rd - n * (2 * dotProduct(n, rd)); }

//Intersection of a sphere with ray from viewpoint
vec2 sphere(vec3 ro, vec3 rd, float r) {
    float b = dotProduct(ro, rd);
    float c = dotProduct(ro, ro) - r * r;
    float h = b * b - c;
    if (h < 0.0) return vec2(-1.0);
    h = sqrt(h);
    return vec2(-b - h, -b + h);
}
//Intersection with a plane
float plane(vec3 ro, vec3 rd, vec3 p, float w) {
    return -(dotProduct(ro, p) + w) / dotProduct(rd, p);
}
//Rotation functions
vec3 rotateX(vec3 a, double angle)
{
    vec3 b = a;
    b.z = a.z * cos(angle) - a.y * sin(angle);
    b.y = a.z * sin(angle) + a.y * cos(angle);
    return b;
}

vec3 rotateY(vec3 a, double angle)
{
    vec3 b = a;
    b.x = a.x * cos(angle) - a.z * sin(angle);
    b.z = a.x * sin(angle) + a.z * cos(angle);
    return b;
}

vec3 rotateZ(vec3 a, double angle)
{
    vec3 b = a;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) + a.y * cos(angle);
    return b;
}






#endif
