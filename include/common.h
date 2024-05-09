#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#include<windows.h>
#include <unistd.h>
#include<iostream>
#include<gl/gl.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<time.h>
#include<math.h>
#include <GLTimer.h>
#include<SOIL.h>
#include<sounds/irrKlang.h>
#define PI 3.14
#define GRAVITY 9.81

using namespace std;
using namespace irrklang;

typedef struct{   // shader positions in 3D
    float x;
    float y;
    float z;
    float w;
}vec4;


typedef struct{  //  positions in 3D graphics
    float x;
    float y;
    float z;
}vec3;

typedef struct{  //  positions in 3D graphics
    float x;
    float y;
}vec2;

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}


#endif // COMMON_H_INCLUDED
