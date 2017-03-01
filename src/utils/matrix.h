#ifndef LOVE_MATRIX_H
#define LOVE_MATRIX_H
#include <math.h>
namespace jin
{
namespace util
{

    struct vertex
    {
        unsigned char r, g, b, a;
        float x, y;
        float s, t;
    };
    /**
    * This class is the basis for all transformations in LOVE. Althought not
    * really needed for 2D, it contains 4x4 elements to be compatible with
    * OpenGL without conversions.
    **/
    class Matrix
    {
    private:

        /**
        * | e0 e4 e8  e12 |
        * | e1 e5 e9  e13 |
        * | e2 e6 e10 e14 |
        * | e3 e7 e11 e15 |
        **/
        float e[16];

    public:

        /**
        * Creates a new identity matrix.
        **/
        Matrix();

        /**
        * Destructor.
        **/
        ~Matrix();

        /**
        * Multiplies this Matrix with another Matrix, changing neither.
        * @param m The Matrix to multiply with this Matrix.
        * @return The combined matrix.
        **/
        Matrix operator * (const Matrix & m) const;

        /**
        * Multiplies a Matrix into this Matrix.
        * @param m The Matrix to combine into this Matrix.
        **/
        void operator *= (const Matrix & m);

        /**
        * Gets a pointer to the 16 array elements.
        * @return The array elements.
        **/
        const float * getElements() const;

        /**
        * Resets this Matrix to the identity matrix.
        **/
        void setIdentity();

        /**
        * Resets this Matrix to a translation.
        * @param x Translation along x-axis.
        * @param y Translation along y-axis.
        **/
        void setTranslation(float x, float y);

        /**
        * Resets this Matrix to a rotation.
        * @param r The angle in radians.
        **/
        void setRotation(float r);

        /**
        * Resets this Matrix to a scale transformation.
        * @param sx Scale factor along the x-axis.
        * @param sy Scale factor along the y-axis.
        **/
        void setScale(float sx, float sy);

        /**
        * Resets this Matrix to a shear transformation.
        * @param kx Shear along x-axis.
        * @param ky Shear along y-axis.
        **/
        void setShear(float kx, float ky);

        /**
        * Creates a transformation with a certain position, orientation, scale
        * and offset. Perfect for Drawables -- what a coincidence!
        *
        * @param x The translation along the x-axis.
        * @param y The translation along the y-axis.
        * @param angle The rotation (rad) around the center with offset (ox,oy).
        * @param sx Scale along x-axis.
        * @param sy Scale along y-axis.
        * @param ox The offset for rotation along the x-axis.
        * @param oy The offset for rotation along the y-axis.
        * @param kx Shear along x-axis
        * @param ky Shear along y-axis
        **/
        void setTransformation(float x, float y, float angle, float sx, float sy, float ox, float oy);

        /**
        * Multiplies this Matrix with a translation.
        * @param x Translation along x-axis.
        * @param y Translation along y-axis.
        **/
        void translate(float x, float y);

        /**
        * Multiplies this Matrix with a rotation.
        * @param r Angle in radians.
        **/
        void rotate(float r);

        /**
        * Multiplies this Matrix with a scale transformation.
        * @param sx Scale factor along the x-axis.
        * @param sy Scale factor along the y-axis.
        **/
        void scale(float sx, float sy);

        /**
        * Multiplies this Matrix with a shear transformation.
        * @param kx Shear along the x-axis.
        * @param ky Shear along the y-axis.
        **/
        void shear(float kx, float ky);

        /**
        * Transforms an array of vertices by this Matrix. The sources and
        * destination arrays may be the same.
        *
        * @param dst Storage for the transformed vertices.
        * @param src The source vertices.
        * @param size The number of vertices.
        **/
        void transform(vertex * dst, const vertex * src, int size) const;

    }; 

}
} 

#endif