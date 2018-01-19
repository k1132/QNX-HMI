/**
* \file
* Matrix3x3 structure and operations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MATRIX3X3_H
#define KZC_MATRIX3X3_H


#include <core/util/math/kzc_vector3.h>
#include <core/util/math/kzc_vector2.h>

#include <system/wrappers/kzs_math.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZC_MATRIX3X3_INDEX_AXISX_X 0 /**< Matrix index for coordinate X of X axis. */
#define KZC_MATRIX3X3_INDEX_AXISX_Y 1 /**< Matrix index for coordinate Y of X axis. */
#define KZC_MATRIX3X3_INDEX_AXISX_Z 2 /**< Matrix index for coordinate Z of X axis. */

#define KZC_MATRIX3X3_INDEX_AXISY_X 3 /**< Matrix index for coordinate X of Y axis. */
#define KZC_MATRIX3X3_INDEX_AXISY_Y 4 /**< Matrix index for coordinate Y of Y axis. */
#define KZC_MATRIX3X3_INDEX_AXISY_Z 5 /**< Matrix index for coordinate Z of Y axis. */

#define KZC_MATRIX3X3_INDEX_AXISZ_X 6 /**< Matrix index for coordinate X of Z axis. */
#define KZC_MATRIX3X3_INDEX_AXISZ_Y 7 /**< Matrix index for coordinate Y of Z axis. */
#define KZC_MATRIX3X3_INDEX_AXISZ_Z 8 /**< Matrix index for coordinate Z of Z axis. */

#define KZC_MATRIX3X3_INDEX_TRANSLATION_X 6 /**< Matrix index for X translation. */
#define KZC_MATRIX3X3_INDEX_TRANSLATION_Y 7 /**< Matrix index for Y translation. */


/* Forward declaration structures. */
struct KzcVector2;
struct KzcVector3;


/** Structure for 3x3 matrix. Uses column-major notation. */
struct KzcMatrix3x3
{
    kzFloat data[9]; /**< Matrix data */
};


/** Constant for identity matrix. */
extern const struct KzcMatrix3x3 KZC_MATRIX3X3_IDENTITY;


/** Creates a matrix with given values.
 *
 * Note that because matrices are internally represented as column-major instead of the scientific row-major notation,
 * matrix specified in using this function actually looks like a transpose of itself in code.
 */
KZ_INLINE struct KzcMatrix3x3 kzcMatrix3x3(kzFloat a11, kzFloat a12, kzFloat a13, 
                                           kzFloat a21, kzFloat a22, kzFloat a23 , 
                                           kzFloat a31, kzFloat a32, kzFloat a33)
{
    struct KzcMatrix3x3 matrix;
    matrix.data[0] = a11;
    matrix.data[1] = a21;
    matrix.data[2] = a31;
    matrix.data[3] = a12;
    matrix.data[4] = a22;
    matrix.data[5] = a32;
    matrix.data[6] = a13;
    matrix.data[7] = a23 ;
    matrix.data[8] = a33;
    return matrix;
}


/** Create a copy of matrix. */
void kzcMatrix3x3Copy(const struct KzcMatrix3x3* sourceMatrix, struct KzcMatrix3x3* targetMatrix);
/** Sets an identity matrix. */
void kzcMatrix3x3SetIdentity(struct KzcMatrix3x3* matrix);
/** Sets an invalid matrix filled with NaNs. */
void kzcMatrix3x3SetInvalid(struct KzcMatrix3x3* matrix);
/** Sets a 3x3 matrix top left 2x2 part as identity. */
void kzcMatrix3x3SetIdentity2x2(struct KzcMatrix3x3* matrix);
/** Sets a 3x3 matrix translation columns to zero. */
void kzcMatrix3x3ResetTranslation(struct KzcMatrix3x3* matrix);
/** Creates a 3x3 translation matrix. */
void kzcMatrix3x3SetTranslation(struct KzcMatrix3x3* matrix, kzFloat translateX, kzFloat translateY);

/** Applies a transpose to a matrix. out_matrix cannot be same as input matrix. */
void kzcMatrix3x3Transpose(const struct KzcMatrix3x3* matrix, struct KzcMatrix3x3* out_matrix);
/**
 * Applies an inversion to an affine matrix. out_matrix cannot be same as input matrix.
 * Returns KZ_TRUE if the matrix was invertible, KZ_FALSE otherwise.
 */
kzBool kzcMatrix3x3InverseAffine(const struct KzcMatrix3x3* matrix, struct KzcMatrix3x3* out_matrix);
/** Translates matrix by given vector2 in matrix's base.
*
* i.e. kzcMatrix3x3Translate(matrix M, vector T) adds M * T to the translation part of the matrix. */
void kzcMatrix3x3Translate(struct KzcMatrix3x3* matrix, kzFloat x, kzFloat y);
/** Translates matrix by given vector2 in matrix's base.
*
* i.e. kzcMatrix3x3Translate(matrix M, vector T) adds M * T to the translation part of the matrix. */
void kzcMatrix3x3TranslateVector2(struct KzcMatrix3x3* matrix, const struct KzcVector2* translation);

/** Multiplies matrix from right by a rotation matrix, angle is in radians. */
void kzcMatrix3x3Rotate(struct KzcMatrix3x3* matrix, kzFloat angleInRadians);
/** Creates a 3x3 rotation matrix from rotation angle in radians. */
void kzcMatrix3x3SetRotation(struct KzcMatrix3x3* matrix, kzFloat angleInRadians);
/** Get the rotation (over imaginary Z axis) of given matrix in radians. */
kzFloat kzcMatrix3x3GetRotation(const struct KzcMatrix3x3* matrix);

/** Multiplies matrix from right by a rotation matrix, angle is in degrees. */
KZ_INLINE void kzcMatrix3x3RotateInDegrees(struct KzcMatrix3x3* matrix, kzFloat angleInDegrees)
{
    kzcMatrix3x3Rotate(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Creates a 3x3 rotation matrix from rotation angle in degrees. */
KZ_INLINE void kzcMatrix3x3SetRotationInDegrees(struct KzcMatrix3x3* matrix, kzFloat angleInDegrees)
{
    kzcMatrix3x3SetRotation(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Get the rotation (over imaginary Z axis) of given matrix in degrees. */
KZ_INLINE kzFloat kzcMatrix3x3GetRotationInDegrees(const struct KzcMatrix3x3* matrix)
{
    return kzsRadiansToDegrees(kzcMatrix3x3GetRotation(matrix));
}

/** Applies a uniform scaling to a matrix */
void kzcMatrix3x3ScaleUniform(struct KzcMatrix3x3* matrix, kzFloat scale);
/** Applies a scaling for a matrix. */
void kzcMatrix3x3Scale(struct KzcMatrix3x3* matrix, kzFloat scaleX, kzFloat scaleY);
/** Gets scaling factor from matrix for its X axis. Assumes an affine matrix. */
kzFloat kzcMatrix3x3GetScaleX(const struct KzcMatrix3x3* matrix);
/** Gets scaling factor from matrix for its Y axis. Assumes an affine matrix. */
kzFloat kzcMatrix3x3GetScaleY(const struct KzcMatrix3x3* matrix);
/** Applies a scaling for a matrix on axis X. */
void kzcMatrix3x3ScaleX(struct KzcMatrix3x3* matrix, kzFloat scale);
/** Applies a scaling for a matrix on axis Y. */
void kzcMatrix3x3ScaleY(struct KzcMatrix3x3* matrix, kzFloat scale);

/** Normalizes the given matrix, result in out_matrix. The matrix must be an affine transformation. */
void kzcMatrix3x3Normalize(const struct KzcMatrix3x3* matrix, struct KzcMatrix3x3* out_matrix);
/** Multiplies two matrices. The result, product 'matrix1' * 'matrix2', is set to out_matrix. out_matrix cannot be any of the input matrices. */
void kzcMatrix3x3Multiply(const struct KzcMatrix3x3* matrix1, const struct KzcMatrix3x3* matrix2, struct KzcMatrix3x3* out_matrix);
/** Multiplies matrix and vector2 defined as vea33(vector2.xy, 1.0). out_vector cannot be same as input vector. */
void kzcMatrix3x3MultiplyVector2(const struct KzcMatrix3x3* matrix, const struct KzcVector2* vector, struct KzcVector2* out_vector);
/** Multiplies matrix and vector2. Translation component of matrix is ignored. out_vector cannot be same as input vector. */
void kzcMatrix3x3MultiplyVector2By2x2(const struct KzcMatrix3x3* matrix, const struct KzcVector2* vector, struct KzcVector2* out_vector);
/** Multiplies matrix and vector3. out_vector cannot be same as input vector. */
void kzcMatrix3x3MultiplyVector3(const struct KzcMatrix3x3* matrix, const struct KzcVector3* vector, struct KzcVector3* out_vector);

/** Check if the matrix transformation is scaling-only. */
kzBool kzcMatrix3x3IsScalingOnly(const struct KzcMatrix3x3* matrix);
/**
 * Check if the matrix transformation is translation-only.
 * This is a subset of scaling-only.
 */
kzBool kzcMatrix3x3IsTranslationOnly(const struct KzcMatrix3x3* matrix);

/** Creates matrix from scale, rotation and translation. Rotation angle in radians. */
void kzcMatrix3x3CreateSRT(struct KzcMatrix3x3* matrix, kzFloat scaleX, kzFloat scaleY, kzFloat rotationAngleInRadians, kzFloat translateX, kzFloat translateY);
/** Gets the matrix SRT values, rotation angle in radians. */
void kzcMatrix3x3GetSRT(const struct KzcMatrix3x3* matrix, struct KzcVector2* out_scale, kzFloat* out_rotationAngleInRadians, struct KzcVector2* out_translate);

/** Creates matrix from scale, rotation and translation. Rotation angle in degrees. */
KZ_INLINE void kzcMatrix3x3CreateSRTInDegrees(struct KzcMatrix3x3* matrix, kzFloat scaleX, kzFloat scaleY, kzFloat rotationAngleInDegrees, kzFloat translateX, kzFloat translateY)
{
    kzcMatrix3x3CreateSRT(matrix, scaleX, scaleY, kzsDegreesToRadians(rotationAngleInDegrees), translateX, translateY);
}
/** Gets the matrix SRT values, rotation angle in degrees. */
KZ_INLINE void kzcMatrix3x3GetSRTInDegrees(const struct KzcMatrix3x3* matrix, struct KzcVector2* out_scale, kzFloat* out_rotationAngleInDegrees, struct KzcVector2* out_translate)
{
    struct KzcVector2 translation;
    kzFloat rotate;
    struct KzcVector2 scale;

    kzcMatrix3x3GetSRT(matrix, &scale, &rotate, &translation);

    rotate = kzsRadiansToDegrees(rotate);

    *out_scale = scale;
    *out_rotationAngleInDegrees = rotate;
    *out_translate = translation;
}

/** Returns the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3GetAxisX(const struct KzcMatrix3x3* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX3X3_INDEX_AXISX_X],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISX_Y],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISX_Z]);
}
/** Returns the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3GetAxisY(const struct KzcMatrix3x3* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX3X3_INDEX_AXISY_X],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISY_Y],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISY_Z]);
}
/** Returns the Z axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3GetAxisZ(const struct KzcMatrix3x3* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_X],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_Y],
                            matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_Z]);
}
/** Returns the translation vector of the matrix. */
KZ_INLINE void kzcMatrix3x3GetTranslation(const struct KzcMatrix3x3* matrix, struct KzcVector2* out_translation)
{
    kzcVector2Set(out_translation, matrix->data[KZC_MATRIX3X3_INDEX_TRANSLATION_X],
                                   matrix->data[KZC_MATRIX3X3_INDEX_TRANSLATION_Y]);
}

/** Sets the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3SetAxisXVector3(struct KzcMatrix3x3* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX3X3_INDEX_AXISX_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISX_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISX_Z] = kzcVector3GetZ(axis);
}
/** Sets the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3SetAxisYVector3(struct KzcMatrix3x3* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX3X3_INDEX_AXISY_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISY_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISY_Z] = kzcVector3GetZ(axis);
}
/** Sets the Z axis vector of the matrix. */
KZ_INLINE void kzcMatrix3x3SetAxisZVector3(struct KzcMatrix3x3* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX3X3_INDEX_AXISZ_Z] = kzcVector3GetZ(axis);
}
/** Sets the translation vector of the matrix. */
KZ_INLINE void kzcMatrix3x3SetTranslationVector2(struct KzcMatrix3x3* matrix, const struct KzcVector2* translation)
{
    matrix->data[KZC_MATRIX3X3_INDEX_TRANSLATION_X] = kzcVector2GetX(translation);
    matrix->data[KZC_MATRIX3X3_INDEX_TRANSLATION_Y] = kzcVector2GetY(translation);
}

/** Calculates the determinant of the matrix. */
kzFloat kzcMatrix3x3Determinant(const struct KzcMatrix3x3* matrix);

/** Returns matrix's trace. */
kzFloat kzcMatrix3x3Trace(const struct KzcMatrix3x3* matrix);


/** Compares 2 matrices if they are equal. */
KZ_INLINE kzBool kzcMatrix3x3IsEqual(const struct KzcMatrix3x3* matrixA, const struct KzcMatrix3x3* matrixB)
{
    kzInt i;
    kzBool isEqualMatrix = KZ_TRUE;

    for(i = 0; i < 9; ++i)
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
