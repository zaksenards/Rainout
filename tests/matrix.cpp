#include <rainout/matrix.h>

using rainout::Mat4f;
using rainout::Vec2f;
using rainout::Vec3f;

void printMatrix(Mat4f matrix)
{
    for(int i = 0; i <= 3; i++)
    {
        for(int j = 0; j <= 3; j++)
        {
            printf("%f ",matrix.e[j][i]);
        }
        printf("\n");
    }
}

int main(void)
{

    Mat4f identity = Mat4f::identity();
    printf("Identity:\n");
    printMatrix(identity);

    identity = Mat4f::scale(identity, Vec2f(4.0, 4.0));
    printf("Scale:\n");
    printMatrix(identity);

    identity = Mat4f::translate(identity,Vec2f(-0.5, -0.5)); 
    printf("Translation:\n");
    printMatrix(identity);

    identity = Mat4f::rotate(identity,Vec3f(0, 1, 0),10.0f); 
    printf("Rotation:\n");
    printMatrix(identity);

    return 0;
}
