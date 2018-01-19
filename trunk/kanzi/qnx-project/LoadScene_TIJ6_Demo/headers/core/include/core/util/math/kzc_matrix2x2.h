/**
* \file
* Matrix2x2 structure and operations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MATRIX2X2_H
#define KZC_MATRIX2X2_H


#include <core/util/math/kzc_vector2.h>

#include <system/wrappers/kzs_math.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZC_MATRIX2X2_INDEX_AXISX_X 0 /**< Matrix index for coordinate X of X axis. */
#define KZC_MATRIX2X2_INDEX_AXISX_Y 1 /**< Matrix index for coordinate Y of X axis. */

#define KZC_MATRIX2X2_INDEX_AXISY_X 2 /**< Matrix index for coordinate X of Y axis. */
#define KZC_MATRIX2X2_INDEX_AXISY_Y 3 /**< Matrix index for coordinate Y of Y axis. */


/* Forward declarations */
struct KzcVector2;


/** Structure for 2x2 matrix. Uses column-major notation. */
struct KzcMatrix2x2
{
    kzFloat data[4]; /**< Matrix data */
};


/** Constant for identity matrix. */
extern const struct KzcMatrix2x2 KZC_MATRIX2X2_IDENTITY;


/** 
 * Creates a matrix with given values. 
 */
KZ_INLINE struct KzcMatrix2x2 kzcMatrix2x2(kzFloat a11, kzFloat a12, 
                                           kzFloat a21, kzFloat a22)
{
    struct KzcMatrix2x2 matrix;
    matrix.data[0] = a11;
    matrix.data[1] = a21;
    matrix.data[2] = a12;
    matrix.data[3] = a22;
    return matrix;
}

/** Create a copy of matrix. */
void kzcMatrix2x2Copy(const struct KzcMatrix2x2* sourceMatrix, struct KzcMatrix2x2* targetMatrix);
/** Sets an identity matrix. */
void kzcMatrix2x2SetIdentity(struct KzcMatrix2x2* matrix);
/** Sets an invalid matrix filled with NaNs. */
void kzcMatrix2x2SetInvalid(struct KzcMatrix2x2* matrix);


/** Applies a transpose to a matrix. out_matrix cannot be same as input matrix. */
void kzcMatrix2x2Transpose(const struct KzcMatrix2x2* matrix, struct KzcMatrix2x2* out_matrix);
/**
 * Applies an inversion to a matrix. out_matrix cannot be same as input matrix.
 * Returns KZ_TRUE if the matrix was invertible, KZ_FALSE otherwise.
 */
kzBool kzcMatrix2x2Inverse(const struct KzcMatrix2x2* matrix, struct KzcMatrix2x2* out_matrix);
/** Applies rotation to a matrix, rotation angle in radians. */
void kzcMatrix2x2Rotate(struct KzcMatrix2x2* matrix, kzFloat angleInRadians);
/** Applies rotation to a matrix, rotation angle in degrees. */
KZ_INLINE void kzcMatrix2x2RotateInDegrees(struct KzcMatrix2x2* matrix, kzFloat angleInDegrees)
{
    kzcMatrix2x2Rotate(matrix, kzsDegreesToRadians(angleInDegrees));
}

/** Applies an uniform scaling for a matrix */
void kzcMatrix2x2ScaleUniform(struct KzcMatrix2x2* matrix, kzFloat scale);
/** Applies a scaling for a matrix. */
void kzcMatrix2x2Scale(struct KzcMatrix2x2* matrix, kzFloat scaleX, kzFloat scaleY);
/** Gets scaling factor from matrix for its X axis. Does not treat matrix as affine. */
kzFloat kzcMatrix2x2GetScaleX(const struct KzcMatrix2x2* matrix);
/** Gets scaling factor from matrix for its Y axis. Does not treat matrix as affine. */
kzFloat kzcMatrix2x2GetScaleY(const struct KzcMatrix2x2* matrix);
/** Applies a scaling for a matrix on axis X. */
void kzcMatrix2x2ScaleX(struct KzcMatrix2x2* matrix, kzFloat scale);
/** Applies a scaling for a matrix on axis Y. */
void kzcMatrix2x2ScaleY(struct KzcMatrix2x2* matrix, kzFloat scale);


/** Returns the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix2x2GetAxisX(const struct KzcMatrix2x2* matrix, struct KzcVector2* out_axis)
{
    kzcVector2Set(out_axis, matrix->data[KZC_MATRIX2X2_INDEX_AXISX_X],
                            matrix->data[KZC_MATRIX2X2_INDEX_AXISX_Y]);
}
/** Returns the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix2x2GetAxisY(const struct KzcMatrix2x2* matrix, struct KzcVector2* out_axis)
{
    kzcVector2Set(out_axis, matrix->data[KZC_MATRIX2X2_INDEX_AXISY_X],
                            matrix->data[KZC_MATRIX2X2_INDEX_AXISY_Y]);
}

/** Sets the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix2x2SetAxisXVector2(struct KzcMatrix2x2* matrix, const struct KzcVector2* axis)
{
    matrix->data[KZC_MATRIX2X2_INDEX_AXISX_X] = kzcVector2GetX(axis);
    matrix->data[KZC_MATRIX2X2_INDEX_AXISX_Y] = kzcVector2GetY(axis);
}
/** Sets the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix2x2SetAxisYVector2(struct KzcMatrix2x2* matrix, const struct KzcVector2* axis)
{
    matrix->data[KZC_MATRIX2X2_INDEX_AXISY_X] = kzcVector2GetX(axis);
    matrix->data[KZC_MATRIX2X2_INDEX_AXISY_Y] = kzcVector2GetY(axis);
}

/** Multiplies two matrices. The result, product 'matrix1' * 'matrix2', is set to out_matrix. out_matrix cannot be any of the input matrices. */
void kzcMatrix2x2Multiply(const struct KzcMatrix2x2* matrix1, const struct KzcMatrix2x2* matrix2, struct KzcMatrix2x2* out_matrix);

/** Multiplies matrix and vector2. out_vector cannot be same as input vector. */
void kzcMatrix2x2MultiplyVector2(const struct KzcMatrix2x2* matrix, const struct KzcVector2* vector, struct KzcVector2* out_vector);


/** Returns matrix's trace. */
kzFloat kzcMatrix2x2Trace(const struct KzcMatrix2x2* matrix);

/** Returns the determinant of the matrix. */
kzFloat kzcMatrix2x2Determinant(const struct KzcMatrix2x2* matrix);

/** Compares 2 matrices if they are equal. */
KZ_INLINE kzBool kzcMatrix2x2IsEqual(const struct KzcMatrix2x2* matrixA, const struct KzcMatrix2x2* matrixB)
{
    kzInt i;
    kzBool isEqualMatrix = KZ_TRUE;

    for(i = 0; i < 4; ++i)
    {
        if(!kzsFloatIsEqual(matrixA->data[i], matrixB->data[i]))
        {
            isEqualMatrix = KZ_FALSE;
            break;
        }
    }

    return isEqualMatrix;
}


KZ_HEADER_END


#endif
