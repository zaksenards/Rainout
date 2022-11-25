#include <rainout/matrix.h>

using rainout::Mat4f;

int main(void)
{
    Mat4f identity2 = Mat4f::identity();

    Mat4f identity = Mat4f::identity();
    identity = identity*3;
    identity2 = identity2*4;

    identity = identity*identity2;

    return 0;
}
