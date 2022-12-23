#ifndef RAINOUT_MATRIX_H
#define RAINOUT_MATRIX_H
#include <rainout/vector.h>
#include <cstdio>
#include <cmath>

namespace rainout
{
    struct Mat4f
    {
        float e[4][4];

        Mat4f()
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[line][column] = 0.0f; 
                }
            }
        }

        static Mat4f scale(Mat4f m, Vec2f scale)
        {
            m.e[0][0] = m.e[0][0]*scale.x;
            m.e[1][1] = m.e[1][1]*scale.y;
            return m;
        }

        static Mat4f translate(Mat4f matrix, Vec2f translation)
        {
            matrix.e[3][0] = matrix.e[3][0]+translation.x;
            matrix.e[3][1] = matrix.e[3][1]+translation.y;
            return matrix;
        }

        static Mat4f rotate(Mat4f m, Vec3f rotation, float angle)
        {
            const float c = (float)cos(angle);
            const float s = (float)sin(angle);
            const float d = (float)1-c;

            m.e[0][0] = rotation.x*rotation.x*d+c;
            m.e[0][1] = rotation.x*rotation.y*d+rotation.z*s;
            m.e[0][2] = rotation.x*rotation.z*d-rotation.y*s; 
                    
            m.e[1][0] = rotation.y*rotation.x*d-rotation.z*s;
            m.e[1][1] = rotation.y*rotation.y*d+c;
            m.e[1][2] = rotation.y*rotation.z*d+rotation.x*s;
                    
            m.e[2][0] = -rotation.z*rotation.z*d+rotation.y*s;
            m.e[2][1] =  rotation.z*rotation.y*d-rotation.x*s;
            m.e[2][2] =  rotation.z*rotation.z*d+c;

            return m;
        }

        void operator=(Mat4f right)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[line][column] = right.e[line][column]; 
                }
            }
        }

        Mat4f operator+(Mat4f right)
        {
            Mat4f m = Mat4f::identity(); 

            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    m.e[line][column] = e[line][column] + right.e[line][column]; 
                }
            }

            return m;
        }

        void operator+=(Mat4f right)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[line][column] = e[line][column] + right.e[line][column]; 
                }
            }
        }

        Mat4f operator-(Mat4f right)
        {
            Mat4f m = Mat4f::identity(); 
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    m.e[line][column] = e[line][column] - right.e[line][column]; 
                }
            }
            return m;
        }

        void operator-=(Mat4f right)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[line][column] = e[line][column] - right.e[line][column]; 
                }
            }
        }

        Mat4f operator*(float value)
        {
            Mat4f m = Mat4f::identity(); 
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    m.e[line][column] = e[line][column] * value; 
                }
            }
            return m;
        }

        void operator*=(float value)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[line][column] = e[line][column] * value; 
                }
            }
        }

        Mat4f operator*(Mat4f right)
        {
            Mat4f m = {};

            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    m.e[line][column] = e[0][column] * right.e[line][0] + e[1][column] * right.e[line][1] + e[2][column] * right.e[line][2] + e[3][column] * right.e[3][line];
                }
            }
            return m;
        }

        void operator*=(Mat4f right)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[column][line] = e[column][0] * right.e[0][line] + e[column][1] * right.e[1][line] + e[column][2] * right.e[2][line] + e[column][3] * right.e[line][3];
                }
            }
        }

        static Mat4f identity()
        {
            Mat4f m = Mat4f();
            m.e[0][0] = m.e[1][1] = m.e[2][2] = m.e[3][3] = 1.0f; 
            return m;
        }
    };
}

#endif
