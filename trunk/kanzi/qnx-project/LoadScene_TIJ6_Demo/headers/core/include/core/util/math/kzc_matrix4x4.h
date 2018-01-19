/**
* \file
* Matrix4x4 structure and operations.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_MATRIX4X4_H
#define KZC_MATRIX4X4_H


#include <core/util/math/kzc_vector3.h>

#include <system/wrappers/kzs_math.h>
#include <system/kzs_types.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


#define KZC_MATRIX4X4_INDEX_AXISX_X 0 /**< Matrix index for coordinate X of X axis. */
#define KZC_MATRIX4X4_INDEX_AXISX_Y 1 /**< Matrix index for coordinate Y of X axis. */
#define KZC_MATRIX4X4_INDEX_AXISX_Z 2 /**< Matrix index for coordinate Z of X axis. */

#define KZC_MATRIX4X4_INDEX_AXISY_X 4 /**< Matrix index for coordinate X of Y axis. */
#define KZC_MATRIX4X4_INDEX_AXISY_Y 5 /**< Matrix index for coordinate Y of Y axis. */
#define KZC_MATRIX4X4_INDEX_AXISY_Z 6 /**< Matrix index for coordinate Z of Y axis. */

#define KZC_MATRIX4X4_INDEX_AXISZ_X 8 /**< Matrix index for coordinate X of Z axis. */
#define KZC_MATRIX4X4_INDEX_AXISZ_Y 9 /**< Matrix index for coordinate Y of Z axis. */
#define KZC_MATRIX4X4_INDEX_AXISZ_Z 10 /**< Matrix index for coordinate Z of Z axis. */

#define KZC_MATRIX4X4_INDEX_TRANSLATION_X 12 /**< Matrix index for X translation. */
#define KZC_MATRIX4X4_INDEX_TRANSLATION_Y 13 /**< Matrix index for Y translation. */
#define KZC_MATRIX4X4_INDEX_TRANSLATION_Z 14 /**< Matrix index for Z translation. */


/* Forward declaration structures. */
struct KzcMatrix3x3;
struct KzcVector4;


/** 
* Structure for 4x4 matrix. Uses column-major notation.
*
* The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix,
* where indices are numbered from 1 to 16 as described in section 2.11.2 of the OpenGL 2.1 Specification.
*/
struct KzcMatrix4x4
{
    kzFloat data[16]; /**< Matrix data. */
};


/** Constant for identity matrix. */
extern const struct KzcMatrix4x4 KZC_MATRIX4X4_IDENTITY;
/** Constant for NaN matrix. */
extern const struct KzcMatrix4x4 KZC_MATRIX4X4_NAN;
/** Constant for shadow map bias matrix. */
extern const struct KzcMatrix4x4 KZC_MATRIX4X4_SHADOW_MAP_BIAS;


/** 
 * Creates a matrix with given values. 
 * The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix,
 * where indices are numbered from 1 to 16 as described in section 2.11.2 of the OpenGL 2.1 Specification.
 */
KZ_INLINE struct KzcMatrix4x4 kzcMatrix4x4(kzFloat a11, kzFloat a12, kzFloat a13, kzFloat a14,
                                           kzFloat a21, kzFloat a22, kzFloat a23, kzFloat a24,
                                           kzFloat a31, kzFloat a32, kzFloat a33, kzFloat a34,
                                           kzFloat a41, kzFloat a42, kzFloat a43, kzFloat a44)
{
    struct KzcMatrix4x4 matrix;
    matrix.data[0] = a11;
    matrix.data[1] = a21;
    matrix.data[2] = a31;
    matrix.data[3] = a41;
    matrix.data[4] = a12;
    matrix.data[5] = a22;
    matrix.data[6] = a32;
    matrix.data[7] = a42;
    matrix.data[8] = a13;
    matrix.data[9] = a23;
    matrix.data[10] = a33;
    matrix.data[11] = a43;
    matrix.data[12] = a14;
    matrix.data[13] = a24;
    matrix.data[14] = a34;
    matrix.data[15] = a44;
    return matrix;
}

/** Create a copy of matrix. */
void kzcMatrix4x4Copy(const struct KzcMatrix4x4* sourceMatrix, struct KzcMatrix4x4* targetMatrix);
/** Expands a 4x4 matrix from 3x3 matrix by omitting the Z axis. */
struct KzcMatrix4x4 kzcMatrix4x4From3x3(const struct KzcMatrix3x3* matrix);

/** Sets a identity matrix. */
void kzcMatrix4x4SetIdentity(struct KzcMatrix4x4* matrix);
/** Sets an invalid matrix filled with NaNs. */
void kzcMatrix4x4SetInvalid(struct KzcMatrix4x4* matrix);
/** Sets a 4x4 matrix top left 3x3 part as identity. */
void kzcMatrix4x4SetIdentity3x3(struct KzcMatrix4x4* matrix);
/** Sets a 4x4 matrix translation columns to zero. */
void kzcMatrix4x4ResetTranslation(struct KzcMatrix4x4* matrix);

/** Applies a transpose to a matrix. out_matrix cannot be same as input matrix. */
void kzcMatrix4x4Transpose(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);
/**
 * Applies an inversion to an affine matrix. out_matrix cannot be same as input matrix.
 * Returns KZ_TRUE if the matrix was invertible, KZ_FALSE otherwise.
 */
kzBool kzcMatrix4x4Inverse(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);
/**
 * Applies an inversion to an orthogonal affine matrix. out_matrix cannot be same as input matrix.
 * Returns KZ_TRUE if the matrix was invertible, KZ_FALSE otherwise.
 */
kzBool kzcMatrix4x4InverseOrthogonal(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);
/** Translates matrix by given vector3 in matrix's base.
*
* i.e. kzcMatrix4x4Translate(matrix M, vector T) adds M * T to the translation part of the matrix. */
void kzcMatrix4x4Translate(struct KzcMatrix4x4* matrix, kzFloat x, kzFloat y, kzFloat z);
/** Translates matrix by given vector3 in matrix's base.
*
* i.e. kzcMatrix4x4Translate(matrix M, vector T) adds M * T to the translation part of the matrix. */
void kzcMatrix4x4TranslateVector3(struct KzcMatrix4x4* matrix, const struct KzcVector3* translation);

/** Multiplies matrix from right by a rotation around X axis. Angle is in radians. */
void kzcMatrix4x4RotateX(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Multiplies matrix from right by a rotation around Y axis. Angle is in radians. */
void kzcMatrix4x4RotateY(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Multiplies matrix from right by a rotation around Z axis. Angle is in radians. */
void kzcMatrix4x4RotateZ(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Multiplies matrix from right by a rotation around arbitrary axis. Angle is in radians.
*
* Similar to glRotatef.
* The rotation axis needs not be normalized. */
void kzcMatrix4x4Rotate(struct KzcMatrix4x4* matrix, kzFloat angleInRadians, kzFloat x, kzFloat y, kzFloat z);
/** Creates a X rotation matrix. */
void kzcMatrix4x4SetRotationX(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Creates a Y rotation matrix. */
void kzcMatrix4x4SetRotationY(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Creates a Z rotation matrix. */
void kzcMatrix4x4SetRotationZ(struct KzcMatrix4x4* matrix, kzFloat angleInRadians);
/** Creates a rotation matrix over an arbitrary axis.
*
* Similar to the matrix used by glRotatef.
* The rotation axis needs not be normalized. */
void kzcMatrix4x4SetRotation(struct KzcMatrix4x4* matrix, kzFloat angleInRadians, kzFloat x, kzFloat y, kzFloat z);

/** Multiplies matrix from right by a rotation around X axis. Angle is in degrees. */
KZ_INLINE void kzcMatrix4x4RotateXInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4RotateX(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Multiplies matrix from right by a rotation around Y axis. Angle is in degrees. */
KZ_INLINE void kzcMatrix4x4RotateYInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4RotateY(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Multiplies matrix from right by a rotation around Z axis. Angle is in degrees. */
KZ_INLINE void kzcMatrix4x4RotateZInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4RotateZ(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Multiplies matrix from right by a rotation around arbitrary axis. Angle is in degrees.
*
* Similar to glRotatef.
* The rotation axis needs not be normalized. */
KZ_INLINE void kzcMatrix4x4RotateInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees, kzFloat x, kzFloat y, kzFloat z)
{
    kzcMatrix4x4Rotate(matrix, kzsDegreesToRadians(angleInDegrees), x, y, z);
}
/** Creates a X rotation matrix, rotation angle in degrees. */
KZ_INLINE void kzcMatrix4x4SetRotationXInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4SetRotationX(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Creates a Y rotation matrix, rotation angle in degrees. */
KZ_INLINE void kzcMatrix4x4SetRotationYInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4SetRotationY(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Creates a Z rotation matrix, rotation angle in degrees. */
KZ_INLINE void kzcMatrix4x4SetRotationZInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees)
{
    kzcMatrix4x4SetRotationZ(matrix, kzsDegreesToRadians(angleInDegrees));
}
/** Creates a rotation matrix over an arbitrary axis.
*
* Similar to the matrix used by glRotatef.
* The rotation axis needs not be normalized, rotation angle in degrees. */
KZ_INLINE void kzcMatrix4x4SetRotationInDegrees(struct KzcMatrix4x4* matrix, kzFloat angleInDegrees, kzFloat x, kzFloat y, kzFloat z)
{
    kzcMatrix4x4SetRotation(matrix, kzsDegreesToRadians(angleInDegrees), x, y, z);
}

/** Applies an uniform scaling for a matrix */
void kzcMatrix4x4ScaleUniform(struct KzcMatrix4x4* matrix, kzFloat scale);
/** Applies a scaling for a matrix */
void kzcMatrix4x4Scale(struct KzcMatrix4x4* matrix, kzFloat scaleX, kzFloat scaleY, kzFloat scaleZ);
/** Gets scaling factor from matrix for its X axis. Assumes an affine matrix. */
kzFloat kzcMatrix4x4GetScaleX(const struct KzcMatrix4x4* matrix);
/** Gets scaling factor from matrix for its Y axis. Assumes an affine matrix. */
kzFloat kzcMatrix4x4GetScaleY(const struct KzcMatrix4x4* matrix);
/** Gets scaling factor from matrix for its Z axis. Assumes an affine matrix. */
kzFloat kzcMatrix4x4GetScaleZ(const struct KzcMatrix4x4* matrix);
/** Scales X vector of a transformation matrix. */
void kzcMatrix4x4ScaleX(struct KzcMatrix4x4* matrix, kzFloat scale);
/** Scales Y vector of a transformation matrix. */
void kzcMatrix4x4ScaleY(struct KzcMatrix4x4* matrix, kzFloat scale);
/** Scales Z vector of a transformation matrix. */
void kzcMatrix4x4ScaleZ(struct KzcMatrix4x4* matrix, kzFloat scale);

/** Normalizes base vectors of the given matrix. The result is in out_matrix. The matrix must be an affine transformation. */
void kzcMatrix4x4NormalizeBase(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);
/**
* Orthonormalizes base vectors of the given matrix. The result is in out_matrix. 
* The orthonormalization is done using the Gram-Schmidt process. Z axis is kept still, then Y is handled, then X.
* This function can be used to prevent value drift.
*/
void kzcMatrix4x4OrthonormalizeBase(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);
/**
* Orthogonalizes base vectors of the given matrix. The result is in out_matrix.
* This function preserves lengths of the axis vectors so it won't help in preventing all potential drifting.
*/
void kzcMatrix4x4OrthogonalizeBase(const struct KzcMatrix4x4* matrix, struct KzcMatrix4x4* out_matrix);

/** Get the the cosine of the shortest angle between the 3x3 transformations in two matrices. */
kzFloat kzcMatrix4x4OrthogonalGetAngleCosine(const struct KzcMatrix4x4* matrix1, const struct KzcMatrix4x4* matrix2);

/** Multiplies two matrices. The result, product 'matrix1' * 'matrix2', is set to out_matrix. out_matrix cannot be any of the input matrices. */
void kzcMatrix4x4Multiply(const struct KzcMatrix4x4* matrix1, const struct KzcMatrix4x4* matrix2, struct KzcMatrix4x4* out_matrix);

/** Multiplies two affine matrices. The result, product 'matrix1' * 'matrix2', is set to out_matrix. out_matrix cannot be any of the input matrices. */
void kzcMatrix4x4MultiplyAffine(const struct KzcMatrix4x4* matrix1, const struct KzcMatrix4x4* matrix2, struct KzcMatrix4x4* out_matrix);

/** Gets translation Z value from product 'matrix1' * 'matrix2', where both are affine transformations. */
kzFloat kzcMatrix4x4MultiplyAffineGetTranslationZ(const struct KzcMatrix4x4* matrix1, const struct KzcMatrix4x4* matrix2);

/** Multiplies matrix and vector3 defined as vec34(vector3.xyz, 1.0). */
void kzcMatrix4x4MultiplyVector3(const struct KzcMatrix4x4* matrix, const struct KzcVector3* vector, struct KzcVector3* out_vector);
/** Multiplies matrix and vector3 by using 3x3 top left corner of matrix (orientation & scale only). */
void kzcMatrix4x4MultiplyVector3By3x3(const struct KzcMatrix4x4* matrix, const struct KzcVector3* vector, struct KzcVector3* out_vector);
/** Multiplies matrix and vector4. out_vector cannot be same as input vector. */
void kzcMatrix4x4MultiplyVector4(const struct KzcMatrix4x4* matrix, const struct KzcVector4* vector, struct KzcVector4* out_vector);
/** Creates projection matrix for orthogonal projection. */
void kzcMatrix4x4CreateOrthogonalProjection(struct KzcMatrix4x4* matrix, kzFloat left, kzFloat right, kzFloat bottom, kzFloat top, kzFloat near, kzFloat far);
/** Interpolates 2 SRT matrices, t clamped to range [0, 1]. */
void kzcMatrix4x4Interpolate(const struct KzcMatrix4x4* matrix1, const struct KzcMatrix4x4* matrix2, kzFloat t, struct KzcMatrix4x4* out_matrix);

/** Creates matrix from scale, rotation and translation. Rotation angles in radians. */
void kzcMatrix4x4CreateSRT(struct KzcMatrix4x4* matrix, kzFloat scaleX, kzFloat scaleY, kzFloat scaleZ, 
                           kzFloat rotateXInRadians, kzFloat rotateYInRadians, kzFloat rotateZInRadians,
                           kzFloat translateX, kzFloat translateY, kzFloat translateZ);
/** Gets the matrix SRT values, rotation angles in radians. */
void kzcMatrix4x4GetSRT(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_scale, struct KzcVector3* out_rotateAnglesInRadians, struct KzcVector3* out_translate);

/** Creates matrix from scale, rotation and translation. Rotation angles in degrees. */
KZ_INLINE void kzcMatrix4x4CreateSRTInDegrees(struct KzcMatrix4x4* matrix, kzFloat scaleX, kzFloat scaleY, kzFloat scaleZ, 
                                              kzFloat rotateXInDegrees, kzFloat rotateYInDegrees, kzFloat rotateZInDegrees,
                                              kzFloat translateX, kzFloat translateY, kzFloat translateZ)
{
    kzcMatrix4x4CreateSRT(matrix, scaleX, scaleY, scaleZ, kzsDegreesToRadians(rotateXInDegrees), kzsDegreesToRadians(rotateYInDegrees), kzsDegreesToRadians(rotateZInDegrees),
                          translateX, translateY, translateZ);
}
/** Gets the matrix SRT values, rotation angles in degrees. */
KZ_INLINE void kzcMatrix4x4GetSRTInDegrees(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_scale, struct KzcVector3* out_rotateAnglesInDegrees, struct KzcVector3* out_translate)
{
    struct KzcVector3 translation;
    struct KzcVector3 eulerAnglesInDegrees;
    struct KzcVector3 rotate;
    struct KzcVector3 scale;

    kzcMatrix4x4GetSRT(matrix, &scale, &rotate, &translation);

    kzcVector3Scale(&rotate, 180.0f / KZS_PI, &eulerAnglesInDegrees);

    *out_scale = scale;
    *out_rotateAnglesInDegrees = eulerAnglesInDegrees;
    *out_translate = translation;
}

/** Returns the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4GetAxisX(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX4X4_INDEX_AXISX_X],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISX_Y],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISX_Z]);
}

/** Returns the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4GetAxisY(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX4X4_INDEX_AXISY_X],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISY_Y],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISY_Z]);
}
/** Returns the Z axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4GetAxisZ(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_axis)
{
    kzcVector3Set(out_axis, matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_X],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_Y],
                            matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_Z]);
}
/** Returns the translation vector of the matrix. */
KZ_INLINE void kzcMatrix4x4GetTranslation(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_translation)
{
    kzcVector3Set(out_translation, matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_X],
                                   matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_Y],
                                   matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_Z]);
}

/** Sets the X axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4SetAxisXVector3(struct KzcMatrix4x4* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX4X4_INDEX_AXISX_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISX_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISX_Z] = kzcVector3GetZ(axis);
}
/** Sets the Y axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4SetAxisYVector3(struct KzcMatrix4x4* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX4X4_INDEX_AXISY_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISY_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISY_Z] = kzcVector3GetZ(axis);
}
/** Sets the Z axis vector of the matrix. */
KZ_INLINE void kzcMatrix4x4SetAxisZVector3(struct KzcMatrix4x4* matrix, const struct KzcVector3* axis)
{
    matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_X] = kzcVector3GetX(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_Y] = kzcVector3GetY(axis);
    matrix->data[KZC_MATRIX4X4_INDEX_AXISZ_Z] = kzcVector3GetZ(axis);
}
/** Sets the translation vector of the matrix. */
KZ_INLINE void kzcMatrix4x4SetTranslationVector3(struct KzcMatrix4x4* matrix, const struct KzcVector3* translation)
{
    matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_X] = kzcVector3GetX(translation);
    matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_Y] = kzcVector3GetY(translation);
    matrix->data[KZC_MATRIX4X4_INDEX_TRANSLATION_Z] = kzcVector3GetZ(translation);
}

/** Calculates Euler angles (in radians) from given matrix. */
void kzcMatrix4x4GetEulerAngles(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_anglesInRadians);

/** Calculates Euler angles (in degrees) from given matrix. */
KZ_INLINE void kzcMatrix4x4GetEulerAnglesInDegrees(const struct KzcMatrix4x4* matrix, struct KzcVector3* out_anglesInDegrees)
{
    struct KzcVector3 anglesInRadians;
    struct KzcVector3 anglesInDegrees;

    kzcMatrix4x4GetEulerAngles(matrix, &anglesInRadians);
    kzcVector3Scale(&anglesInRadians, 180.0f / KZS_PI, &anglesInDegrees);

    *out_anglesInDegrees = anglesInDegrees;
}

/** Calculates the determinant of the matrix. */
kzFloat kzcMatrix4x4Determinant(const struct KzcMatrix4x4* matrix);

/** Returns matrix's trace. */
kzFloat kzcMatrix4x4Trace(const struct KzcMatrix4x4* matrix);

/** Determines if a matrix has only right angle rotations. */
kzBool kzcMatrix4x4IsRightAngleRotation(const struct KzcMatrix4x4* matrix, kzFloat epsilon);

/** Determines if a matrix is a simple layout matrix - has only scale and right-angle rotations. */
kzBool kzcMatrix4x4IsSimpleLayout(const struct KzcMatrix4x4* matrix, kzFloat epsilon);

/** Determines if a matrix is translation only. */
kzBool kzcMatrix4x4IsTranslationOnly(const struct KzcMatrix4x4* matrix);


/** Compares 2 matrices if they are equal. */
KZ_INLINE kzBool kzcMatrix4x4IsEqual(const struct KzcMatrix4x4* matrixA, const struct KzcMatrix4x4* matrixB)
{
    kzInt i;
    kzBool isEqualMatrix = KZ_TRUE;

    for(i = 0; i < 16; ++i)
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
