#ifndef RAINOUT_VECTOR_H
#define RAINOUT_VECTOR_H

#include <cmath>

namespace rainout
{
    struct Vec2f
    {
        float x, y;
        Vec2f(float nx, float ny):x(nx),y(ny){}
        Vec2f():x(0.0f),y(0.0f){}

        double magnitude()
        {
            double nx = pow(x,2); 
            double ny = pow(y,2);
            return sqrt(nx+ny);
        }

        Vec2f normalize()
        {
            float length = (float) magnitude();
            float ux = x/length;
            float uy = y/length;
            return Vec2f(ux,uy);
        }

        Vec2f negative()
        {
            Vec2f(-x,-y);
        }

        void operator=(Vec2f right)
        {
            x = right.x;
            y = right.y;
        }

        Vec2f operator+(Vec2f right)
        {
            return Vec2f(x+right.x, y+right.y);
        }

        void operator+=(Vec2f right)
        {
            x+=right.x;
            y+=right.y; 
        }


        Vec2f operator-(Vec2f right)
        {
            return Vec2f(x-right.x, y-right.y);
        }
    };


    struct Vec3f
    {
        float x, y, z;
        Vec3f(float nx, float ny, float nz):x(nx),y(ny),z(nz){}
        Vec3f():x(0.0f),y(0.0f),z(0.0f){}

        void operator=(Vec3f right)
        {
            x = right.x;
            y = right.y;
            z = right.z;
        }

        void operator+=(Vec3f right)
        {
            x+=right.x;
            y+=right.y; 
            z+=right.z;
        }
    };
}

#endif//RAINOUT_VECTOR_H
