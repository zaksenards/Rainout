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
                    e[column][line] = 0.0f; 
                }
            }
        }

        static Mat4f scale(Mat4f matrix, Vec2f scale)
        {
            Mat4f m = Mat4f::identity();
            m.e[0][0] = matrix.e[0][0]+scale.x;
            m.e[1][1] = matrix.e[1][1]+scale.y;
            return m;
        }

        static Mat4f rotate(Mat4f matrix, Vec2f rotation)
        {
            Mat4f m = Mat4f::identity();
            m.e[0][0] =  cos(matrix.e[0][0])*rotation.x;
            m.e[2][0] = -sin(matrix.e[2][0])*rotation.x;
            return m;
        }

        static Mat4f translate(Mat4f matrix, Vec2f translation)
        {
            Mat4f m = Mat4f::identity();
            m.e[3][0] = matrix.e[3][0]+translation.x;
            m.e[3][1] = matrix.e[3][1]+translation.y;
            return m;
        }

        void operator=(Mat4f right)
        {
            for(int column = 0; column < 4;column++)
            {
                for(int line = 0; line < 4; line++)
                {
                    e[column][line] = right.e[column][line]; 
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
                    m.e[column][line] = e[column][line] + right.e[column][line]; 
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
                    e[column][line] = e[column][line] + right.e[column][line]; 
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
                    m.e[column][line] = e[column][line] - right.e[column][line]; 
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
                    e[column][line] = e[column][line] - right.e[column][line]; 
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
                    m.e[column][line] = e[column][line] * value; 
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
                    e[column][line] = e[column][line] * value; 
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
                    m.e[column][line] = e[column][0] * right.e[0][line] + e[column][1] * right.e[1][line] + e[column][2] * right.e[2][line] + e[column][3] * right.e[line][3];
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
