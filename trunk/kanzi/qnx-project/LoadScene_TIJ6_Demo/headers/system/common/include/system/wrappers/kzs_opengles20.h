/**
* \file
* OpenGL ES 2.0 wrappers.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_OPENGLES20_H
#define KZS_OPENGLES20_H


#include "kzs_opengl_base.h"

#include <system/kzs_types.h>
#include <system/debug/kzs_counter.h>
#include <system/kzs_header.h>

#ifdef IOS
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> /*lint -efile(766,GLES2/gl2ext.h) This file is referenced inside macros. */
#endif

#if KZ_OPENGL_PLATFORM == KZ_PLATFORM_IMG
#include <GLES2/gl2extimg.h>
#endif

KZ_HEADER_BEGIN


#define KZS_OPENGL_MAJOR 2 /**< Required major version. */
#define KZS_OPENGL_MINOR 0 /**< Required minor version. */

/** If this is enabled, then all OpenGL calls will be checked for errors. */
#ifdef _DEBUG
#define DEBUG_OPENGL 1
#else
#define DEBUG_OPENGL 0
#endif

#if DEBUG_OPENGL
#include <system/debug/kzs_log.h>


static void kzsGlErrorNotify(GLenum error)
{
    kzString errorString;

    switch (error)
    {
        case GL_INVALID_VALUE:                 errorString = "GL_INVALID_VALUE";                 break;
        case GL_INVALID_ENUM:                  errorString = "GL_INVALID_ENUM";                  break;
        case GL_INVALID_OPERATION:             errorString = "GL_INVALID_OPERATION";             break;
        case GL_OUT_OF_MEMORY:                 errorString = "GL_OUT_OF_MEMORY";                 break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: errorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break; /* This case is allowed. */
        default:                               errorString = "Unknown OpenGL error";             break;
    }

    kzsLog(KZS_LOG_LEVEL_WARNING, errorString);
}

static void kzsGlErrorTest(void)
{
    const kzInt maxErrors = 8;
    kzInt i = 0;
    GLenum error;

    for (;;)
    {
        error = glGetError();
        if (error == GL_NO_ERROR)
        {
            break;
        }

        if (i >= maxErrors)
        {
            kzsLog(KZS_LOG_LEVEL_WARNING, "Additional OpenGL errors suppressed...");
            break;
        }

        /* Invalid framebuffer operation is handled separately. */
        if (error != GL_INVALID_FRAMEBUFFER_OPERATION)
        {
            kzsGlErrorNotify(error);
        }

        ++i;        
    }
}
#else
#define kzsGlErrorTest()
#endif


KZ_INLINE GLboolean kzsGetGLBoolean_private(kzBool value)
{
    return value ? GL_TRUE : GL_FALSE;
}


/* ClearBufferMask */
#define KZS_GL_DEPTH_BUFFER_BIT               GL_DEPTH_BUFFER_BIT 
#define KZS_GL_STENCIL_BUFFER_BIT             GL_STENCIL_BUFFER_BIT
#define KZS_GL_COLOR_BUFFER_BIT               GL_COLOR_BUFFER_BIT

/* Boolean */
#define KZS_GL_FALSE                          GL_FALSE
#define KZS_GL_TRUE                           GL_TRUE

/* BeginMode */
#define KZS_GL_POINTS                         GL_POINTS
#define KZS_GL_LINES                          GL_LINES
#define KZS_GL_LINE_LOOP                      GL_LINE_LOOP
#define KZS_GL_LINE_STRIP                     GL_LINE_STRIP
#define KZS_GL_TRIANGLES                      GL_TRIANGLES
#define KZS_GL_TRIANGLE_STRIP                 GL_TRIANGLE_STRIP
#define KZS_GL_TRIANGLE_FAN                   GL_TRIANGLE_FAN

/* BlendingFactorDest */
#define KZS_GL_ZERO                           GL_ZERO
#define KZS_GL_ONE                            GL_ONE
#define KZS_GL_SRC_COLOR                      GL_SRC_COLOR
#define KZS_GL_ONE_MINUS_SRC_COLOR            GL_ONE_MINUS_SRC_COLOR
#define KZS_GL_SRC_ALPHA                      GL_SRC_ALPHA
#define KZS_GL_ONE_MINUS_SRC_ALPHA            GL_ONE_MINUS_SRC_ALPHA
#define KZS_GL_DST_ALPHA                      GL_DST_ALPHA
#define KZS_GL_ONE_MINUS_DST_ALPHA            GL_ONE_MINUS_DST_ALPHA

/* BlendingFactorSrc */
#define KZS_GL_DST_COLOR                      GL_DST_COLOR
#define KZS_GL_ONE_MINUS_DST_COLOR            GL_ONE_MINUS_DST_COLOR
#define KZS_GL_SRC_ALPHA_SATURATE             GL_SRC_ALPHA_SATURATE

/* BlendEquationSeparate */
#define KZS_GL_FUNC_ADD                       GL_FUNC_ADD
#define KZS_GL_BLEND_EQUATION                 GL_BLEND_EQUATION
#define KZS_GL_BLEND_EQUATION_RGB             GL_BLEND_EQUATION_RGB    /* same as BLEND_EQUATION */
#define KZS_GL_BLEND_EQUATION_ALPHA           GL_BLEND_EQUATION_ALPHA

/* BlendSubtract */
#define KZS_GL_FUNC_SUBTRACT                  GL_FUNC_SUBTRACT
#define KZS_GL_FUNC_REVERSE_SUBTRACT          GL_FUNC_REVERSE_SUBTRACT

/* Separate Blend Functions */
#define KZS_GL_BLEND_DST_RGB                  GL_BLEND_DST_RGB
#define KZS_GL_BLEND_SRC_RGB                  GL_BLEND_SRC_RGB
#define KZS_GL_BLEND_DST_ALPHA                GL_BLEND_DST_ALPHA
#define KZS_GL_BLEND_SRC_ALPHA                GL_BLEND_SRC_ALPHA
#define KZS_GL_CONSTANT_COLOR                 GL_CONSTANT_COLOR
#define KZS_GL_ONE_MINUS_CONSTANT_COLOR       GL_ONE_MINUS_CONSTANT_COLOR
#define KZS_GL_CONSTANT_ALPHA                 GL_CONSTANT_ALPHA
#define KZS_GL_ONE_MINUS_CONSTANT_ALPHA       GL_ONE_MINUS_CONSTANT_ALPHA
#define KZS_GL_BLEND_COLOR                    GL_BLEND_COLOR

/* Buffer Objects */
#define KZS_GL_ARRAY_BUFFER                   GL_ARRAY_BUFFER
#define KZS_GL_ELEMENT_ARRAY_BUFFER           GL_ELEMENT_ARRAY_BUFFER
#define KZS_GL_ARRAY_BUFFER_BINDING           GL_ARRAY_BUFFER_BINDING
#define KZS_GL_ELEMENT_ARRAY_BUFFER_BINDING   GL_ELEMENT_ARRAY_BUFFER_BINDING

#define KZS_GL_STREAM_DRAW                    GL_STREAM_DRAW
#define KZS_GL_STATIC_DRAW                    GL_STATIC_DRAW
#define KZS_GL_DYNAMIC_DRAW                   GL_DYNAMIC_DRAW

#define KZS_GL_BUFFER_SIZE                    GL_BUFFER_SIZE
#define KZS_GL_BUFFER_USAGE                   GL_BUFFER_USAGE

#define KZS_GL_CURRENT_VERTEX_ATTRIB          GL_CURRENT_VERTEX_ATTRIB

/* CullFaceMode */
#define KZS_GL_FRONT                          GL_FRONT
#define KZS_GL_BACK                           GL_BACK
#define KZS_GL_FRONT_AND_BACK                 GL_FRONT_AND_BACK

/* EnableCap */
#define KZS_GL_TEXTURE_2D                     GL_TEXTURE_2D
#define KZS_GL_CULL_FACE                      GL_CULL_FACE
#define KZS_GL_BLEND                          GL_BLEND
#define KZS_GL_DITHER                         GL_DITHER
#define KZS_GL_STENCIL_TEST                   GL_STENCIL_TEST
#define KZS_GL_DEPTH_TEST                     GL_DEPTH_TEST
#define KZS_GL_SCISSOR_TEST                   GL_SCISSOR_TEST
#define KZS_GL_POLYGON_OFFSET_FILL            GL_POLYGON_OFFSET_FILL
#define KZS_GL_SAMPLE_ALPHA_TO_COVERAGE       GL_SAMPLE_ALPHA_TO_COVERAGE
#define KZS_GL_SAMPLE_COVERAGE                GL_SAMPLE_COVERAGE

/* ErrorCode */
#define KZS_GL_NO_ERROR                       GL_NO_ERROR
#define KZS_GL_INVALID_ENUM                   GL_INVALID_ENUM
#define KZS_GL_INVALID_VALUE                  GL_INVALID_VALUE
#define KZS_GL_INVALID_OPERATION              GL_INVALID_OPERATION
#define KZS_GL_OUT_OF_MEMORY                  GL_OUT_OF_MEMORY

/* FrontFaceDirection */
#define KZS_GL_CW                             GL_CW
#define KZS_GL_CCW                            GL_CCW

/* GetPName */
#define KZS_GL_LINE_WIDTH                     GL_LINE_WIDTH
#define KZS_GL_ALIASED_POINT_SIZE_RANGE       GL_ALIASED_POINT_SIZE_RANGE
#define KZS_GL_ALIASED_LINE_WIDTH_RANGE       GL_ALIASED_LINE_WIDTH_RANGE
#define KZS_GL_CULL_FACE_MODE                 GL_CULL_FACE_MODE
#define KZS_GL_FRONT_FACE                     GL_FRONT_FACE
#define KZS_GL_DEPTH_RANGE                    GL_DEPTH_RANGE
#define KZS_GL_DEPTH_WRITEMASK                GL_DEPTH_WRITEMASK
#define KZS_GL_DEPTH_CLEAR_VALUE              GL_DEPTH_CLEAR_VALUE
#define KZS_GL_DEPTH_FUNC                     GL_DEPTH_FUNC
#define KZS_GL_STENCIL_CLEAR_VALUE            GL_STENCIL_CLEAR_VALUE
#define KZS_GL_STENCIL_FUNC                   GL_STENCIL_FUNC
#define KZS_GL_STENCIL_FAIL                   GL_STENCIL_FAIL
#define KZS_GL_STENCIL_PASS_DEPTH_FAIL        GL_STENCIL_PASS_DEPTH_FAIL
#define KZS_GL_STENCIL_PASS_DEPTH_PASS        GL_STENCIL_PASS_DEPTH_PASS
#define KZS_GL_STENCIL_REF                    GL_STENCIL_REF
#define KZS_GL_STENCIL_VALUE_MASK             GL_STENCIL_VALUE_MASK
#define KZS_GL_STENCIL_WRITEMASK              GL_STENCIL_WRITEMASK
#define KZS_GL_STENCIL_BACK_FUNC              GL_STENCIL_BACK_FUNC
#define KZS_GL_STENCIL_BACK_FAIL              GL_STENCIL_BACK_FAIL
#define KZS_GL_STENCIL_BACK_PASS_DEPTH_FAIL   GL_STENCIL_BACK_PASS_DEPTH_FAIL
#define KZS_GL_STENCIL_BACK_PASS_DEPTH_PASS   GL_STENCIL_BACK_PASS_DEPTH_PASS
#define KZS_GL_STENCIL_BACK_REF               GL_STENCIL_BACK_REF
#define KZS_GL_STENCIL_BACK_VALUE_MASK        GL_STENCIL_BACK_VALUE_MASK
#define KZS_GL_STENCIL_BACK_WRITEMASK         GL_STENCIL_BACK_WRITEMASK
#define KZS_GL_VIEWPORT                       GL_VIEWPORT
#define KZS_GL_SCISSOR_BOX                    GL_SCISSOR_BOX
#define KZS_GL_COLOR_CLEAR_VALUE              GL_COLOR_CLEAR_VALUE
#define KZS_GL_COLOR_WRITEMASK                GL_COLOR_WRITEMASK
#define KZS_GL_UNPACK_ALIGNMENT               GL_UNPACK_ALIGNMENT
#define KZS_GL_PACK_ALIGNMENT                 GL_PACK_ALIGNMENT
#define KZS_GL_MAX_TEXTURE_SIZE               GL_MAX_TEXTURE_SIZE
#define KZS_GL_MAX_VIEWPORT_DIMS              GL_MAX_VIEWPORT_DIMS
#define KZS_GL_SUBPIXEL_BITS                  GL_SUBPIXEL_BITS
#define KZS_GL_RED_BITS                       GL_RED_BITS
#define KZS_GL_GREEN_BITS                     GL_GREEN_BITS
#define KZS_GL_BLUE_BITS                      GL_BLUE_BITS
#define KZS_GL_ALPHA_BITS                     GL_ALPHA_BITS
#define KZS_GL_DEPTH_BITS                     GL_DEPTH_BITS
#define KZS_GL_STENCIL_BITS                   GL_STENCIL_BITS
#define KZS_GL_POLYGON_OFFSET_UNITS           GL_POLYGON_OFFSET_UNITS
#define KZS_GL_POLYGON_OFFSET_FACTOR          GL_POLYGON_OFFSET_FACTOR
#define KZS_GL_TEXTURE_BINDING_2D             GL_TEXTURE_BINDING_2D
#define KZS_GL_SAMPLE_BUFFERS                 GL_SAMPLE_BUFFERS
#define KZS_GL_SAMPLES                        GL_SAMPLES
#define KZS_GL_SAMPLE_COVERAGE_VALUE          GL_SAMPLE_COVERAGE_VALUE
#define KZS_GL_SAMPLE_COVERAGE_INVERT         GL_SAMPLE_COVERAGE_INVERT

#define KZS_GL_NUM_COMPRESSED_TEXTURE_FORMATS GL_NUM_COMPRESSED_TEXTURE_FORMATS
#define KZS_GL_COMPRESSED_TEXTURE_FORMATS     GL_COMPRESSED_TEXTURE_FORMATS

/* HintMode */
#define KZS_GL_DONT_CARE                      GL_DONT_CARE
#define KZS_GL_FASTEST                        GL_FASTEST
#define KZS_GL_NICEST                         GL_NICEST

/* HintTarget */
#define KZS_GL_GENERATE_MIPMAP_HINT           GL_GENERATE_MIPMAP_HINT

/* DataType */
#define KZS_GL_BYTE                           GL_BYTE
#define KZS_GL_UNSIGNED_BYTE                  GL_UNSIGNED_BYTE
#define KZS_GL_SHORT                          GL_SHORT
#define KZS_GL_UNSIGNED_SHORT                 GL_UNSIGNED_SHORT
#define KZS_GL_INT                            GL_INT
#define KZS_GL_UNSIGNED_INT                   GL_UNSIGNED_INT
#define KZS_GL_FLOAT                          GL_FLOAT
#define KZS_GL_HALF_FLOAT                     GL_HALF_FLOAT_OES 
#define KZS_GL_FIXED                          GL_FIXED

/* PixelFormat */
#define KZS_GL_DEPTH_COMPONENT                GL_DEPTH_COMPONENT
#define KZS_GL_ALPHA                          GL_ALPHA
#define KZS_GL_RGB                            GL_RGB
#define KZS_GL_RGBA                           GL_RGBA
#define KZS_GL_LUMINANCE                      GL_LUMINANCE
#define KZS_GL_LUMINANCE_ALPHA                GL_LUMINANCE_ALPHA

/* PixelType */
#define KZS_GL_UNSIGNED_SHORT_4_4_4_4         GL_UNSIGNED_SHORT_4_4_4_4
#define KZS_GL_UNSIGNED_SHORT_5_5_5_1         GL_UNSIGNED_SHORT_5_5_5_1
#define KZS_GL_UNSIGNED_SHORT_5_6_5           GL_UNSIGNED_SHORT_5_6_5

/* Shaders */
#define KZS_GL_FRAGMENT_SHADER                  GL_FRAGMENT_SHADER
#define KZS_GL_VERTEX_SHADER                    GL_VERTEX_SHADER
#define KZS_GL_MAX_VERTEX_ATTRIBS               GL_MAX_VERTEX_ATTRIBS
#define KZS_GL_MAX_VERTEX_UNIFORM_VECTORS       GL_MAX_VERTEX_UNIFORM_VECTORS
#define KZS_GL_MAX_VARYING_VECTORS              GL_MAX_VARYING_VECTORS
#define KZS_GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
#define KZS_GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS   GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
#define KZS_GL_MAX_TEXTURE_IMAGE_UNITS          GL_MAX_TEXTURE_IMAGE_UNITS
#define KZS_GL_MAX_FRAGMENT_UNIFORM_VECTORS     GL_MAX_FRAGMENT_UNIFORM_VECTORS
#define KZS_GL_SHADER_TYPE                      GL_SHADER_TYPE
#define KZS_GL_DELETE_STATUS                    GL_DELETE_STATUS
#define KZS_GL_LINK_STATUS                      GL_LINK_STATUS
#define KZS_GL_VALIDATE_STATUS                  GL_VALIDATE_STATUS
#define KZS_GL_ATTACHED_SHADERS                 GL_ATTACHED_SHADERS
#define KZS_GL_ACTIVE_UNIFORMS                  GL_ACTIVE_UNIFORMS
#define KZS_GL_ACTIVE_UNIFORM_MAX_LENGTH        GL_ACTIVE_UNIFORM_MAX_LENGTH
#define KZS_GL_ACTIVE_ATTRIBUTES                GL_ACTIVE_ATTRIBUTES
#define KZS_GL_ACTIVE_ATTRIBUTE_MAX_LENGTH      GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
#define KZS_GL_SHADING_LANGUAGE_VERSION         GL_SHADING_LANGUAGE_VERSION
#define KZS_GL_CURRENT_PROGRAM                  GL_CURRENT_PROGRAM

/* StencilFunction */
#define KZS_GL_NEVER                          GL_NEVER
#define KZS_GL_LESS                           GL_LESS
#define KZS_GL_EQUAL                          GL_EQUAL
#define KZS_GL_LEQUAL                         GL_LEQUAL
#define KZS_GL_GREATER                        GL_GREATER
#define KZS_GL_NOTEQUAL                       GL_NOTEQUAL
#define KZS_GL_GEQUAL                         GL_GEQUAL
#define KZS_GL_ALWAYS                         GL_ALWAYS

/* StencilOp */
#define KZS_GL_KEEP                           GL_KEEP
#define KZS_GL_REPLACE                        GL_REPLACE
#define KZS_GL_INCR                           GL_INCR
#define KZS_GL_DECR                           GL_DECR
#define KZS_GL_INVERT                         GL_INVERT
#define KZS_GL_INCR_WRAP                      GL_INCR_WRAP
#define KZS_GL_DECR_WRAP                      GL_DECR_WRAP

/* StringName */
#define KZS_GL_VENDOR                         GL_VENDOR
#define KZS_GL_RENDERER                       GL_RENDERER
#define KZS_GL_VERSION                        GL_VERSION
#define KZS_GL_EXTENSIONS                     GL_EXTENSIONS

/* TextureMagFilter */
#define KZS_GL_NEAREST                        GL_NEAREST
#define KZS_GL_LINEAR                         GL_LINEAR

/* TextureMinFilter */
#define KZS_GL_NEAREST_MIPMAP_NEAREST         GL_NEAREST_MIPMAP_NEAREST
#define KZS_GL_LINEAR_MIPMAP_NEAREST          GL_LINEAR_MIPMAP_NEAREST
#define KZS_GL_NEAREST_MIPMAP_LINEAR          GL_NEAREST_MIPMAP_LINEAR
#define KZS_GL_LINEAR_MIPMAP_LINEAR           GL_LINEAR_MIPMAP_LINEAR

/* TextureParameterName */
#define KZS_GL_TEXTURE_MAG_FILTER             GL_TEXTURE_MAG_FILTER
#define KZS_GL_TEXTURE_MIN_FILTER             GL_TEXTURE_MIN_FILTER
#define KZS_GL_TEXTURE_WRAP_S                 GL_TEXTURE_WRAP_S
#define KZS_GL_TEXTURE_WRAP_T                 GL_TEXTURE_WRAP_T

/* TextureTarget */
#define KZS_GL_TEXTURE                        GL_TEXTURE

#define KZS_GL_TEXTURE_CUBE_MAP               GL_TEXTURE_CUBE_MAP
#define KZS_GL_TEXTURE_BINDING_CUBE_MAP       GL_TEXTURE_BINDING_CUBE_MAP
#define KZS_GL_TEXTURE_CUBE_MAP_POSITIVE_X    GL_TEXTURE_CUBE_MAP_POSITIVE_X
#define KZS_GL_TEXTURE_CUBE_MAP_NEGATIVE_X    GL_TEXTURE_CUBE_MAP_NEGATIVE_X
#define KZS_GL_TEXTURE_CUBE_MAP_POSITIVE_Y    GL_TEXTURE_CUBE_MAP_POSITIVE_Y
#define KZS_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
#define KZS_GL_TEXTURE_CUBE_MAP_POSITIVE_Z    GL_TEXTURE_CUBE_MAP_POSITIVE_Z
#define KZS_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
#define KZS_GL_MAX_CUBE_MAP_TEXTURE_SIZE      GL_MAX_CUBE_MAP_TEXTURE_SIZE

/* TextureUnit */
#define KZS_GL_TEXTURE0                       GL_TEXTURE0
#define KZS_GL_TEXTURE1                       GL_TEXTURE1
#define KZS_GL_TEXTURE2                       GL_TEXTURE2
#define KZS_GL_TEXTURE3                       GL_TEXTURE3
#define KZS_GL_TEXTURE4                       GL_TEXTURE4
#define KZS_GL_TEXTURE5                       GL_TEXTURE5
#define KZS_GL_TEXTURE6                       GL_TEXTURE6
#define KZS_GL_TEXTURE7                       GL_TEXTURE7
#define KZS_GL_TEXTURE8                       GL_TEXTURE8
#define KZS_GL_TEXTURE9                       GL_TEXTURE9
#define KZS_GL_TEXTURE10                      GL_TEXTURE10
#define KZS_GL_TEXTURE11                      GL_TEXTURE11
#define KZS_GL_TEXTURE12                      GL_TEXTURE12
#define KZS_GL_TEXTURE13                      GL_TEXTURE13
#define KZS_GL_TEXTURE14                      GL_TEXTURE14
#define KZS_GL_TEXTURE15                      GL_TEXTURE15
#define KZS_GL_TEXTURE16                      GL_TEXTURE16
#define KZS_GL_TEXTURE17                      GL_TEXTURE17
#define KZS_GL_TEXTURE18                      GL_TEXTURE18
#define KZS_GL_TEXTURE19                      GL_TEXTURE19
#define KZS_GL_TEXTURE20                      GL_TEXTURE20
#define KZS_GL_TEXTURE21                      GL_TEXTURE21
#define KZS_GL_TEXTURE22                      GL_TEXTURE22
#define KZS_GL_TEXTURE23                      GL_TEXTURE23
#define KZS_GL_TEXTURE24                      GL_TEXTURE24
#define KZS_GL_TEXTURE25                      GL_TEXTURE25
#define KZS_GL_TEXTURE26                      GL_TEXTURE26
#define KZS_GL_TEXTURE27                      GL_TEXTURE27
#define KZS_GL_TEXTURE28                      GL_TEXTURE28
#define KZS_GL_TEXTURE29                      GL_TEXTURE29
#define KZS_GL_TEXTURE30                      GL_TEXTURE30
#define KZS_GL_TEXTURE31                      GL_TEXTURE31
#define KZS_GL_ACTIVE_TEXTURE                 GL_ACTIVE_TEXTURE

/* TextureWrapMode */
#define KZS_GL_REPEAT                         GL_REPEAT
#define KZS_GL_CLAMP_TO_EDGE                  GL_CLAMP_TO_EDGE
#define KZS_GL_MIRRORED_REPEAT                GL_MIRRORED_REPEAT

/* Uniform Types */
#define KZS_GL_FLOAT_VEC2                     GL_FLOAT_VEC2
#define KZS_GL_FLOAT_VEC3                     GL_FLOAT_VEC3
#define KZS_GL_FLOAT_VEC4                     GL_FLOAT_VEC4
#define KZS_GL_INT_VEC2                       GL_INT_VEC2
#define KZS_GL_INT_VEC3                       GL_INT_VEC3
#define KZS_GL_INT_VEC4                       GL_INT_VEC4
#define KZS_GL_BOOL                           GL_BOOL
#define KZS_GL_BOOL_VEC2                      GL_BOOL_VEC2
#define KZS_GL_BOOL_VEC3                      GL_BOOL_VEC3
#define KZS_GL_BOOL_VEC4                      GL_BOOL_VEC4
#define KZS_GL_FLOAT_MAT2                     GL_FLOAT_MAT2
#define KZS_GL_FLOAT_MAT3                     GL_FLOAT_MAT3
#define KZS_GL_FLOAT_MAT4                     GL_FLOAT_MAT4
#define KZS_GL_SAMPLER_2D                     GL_SAMPLER_2D
#define KZS_GL_SAMPLER_CUBE                   GL_SAMPLER_CUBE

/* Vertex Arrays */
#define KZS_GL_VERTEX_ATTRIB_ARRAY_ENABLED        GL_VERTEX_ATTRIB_ARRAY_ENABLED
#define KZS_GL_VERTEX_ATTRIB_ARRAY_SIZE           GL_VERTEX_ATTRIB_ARRAY_SIZE
#define KZS_GL_VERTEX_ATTRIB_ARRAY_STRIDE         GL_VERTEX_ATTRIB_ARRAY_STRIDE
#define KZS_GL_VERTEX_ATTRIB_ARRAY_TYPE           GL_VERTEX_ATTRIB_ARRAY_TYPE
#define KZS_GL_VERTEX_ATTRIB_ARRAY_NORMALIZED     GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
#define KZS_GL_VERTEX_ATTRIB_ARRAY_POINTER        GL_VERTEX_ATTRIB_ARRAY_POINTER
#define KZS_GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING

/* Read Format */
#if defined(GL_IMPLEMENTATION_COLOR_READ_FORMAT) && defined(GL_IMPLEMENTATION_COLOR_READ_TYPE)
#define KZS_GL_IMPLEMENTATION_COLOR_READ_TYPE   GL_IMPLEMENTATION_COLOR_READ_TYPE
#define KZS_GL_IMPLEMENTATION_COLOR_READ_FORMAT GL_IMPLEMENTATION_COLOR_READ_FORMAT
#endif


/* Shader Source */
#define KZS_GL_COMPILE_STATUS                 GL_COMPILE_STATUS
#define KZS_GL_INFO_LOG_LENGTH                GL_INFO_LOG_LENGTH
#define KZS_GL_SHADER_SOURCE_LENGTH           GL_SHADER_SOURCE_LENGTH
#define KZS_GL_SHADER_COMPILER                GL_SHADER_COMPILER

/* Shader Binary */
#define KZS_GL_SHADER_BINARY_FORMATS          GL_SHADER_BINARY_FORMATS
#define KZS_GL_NUM_SHADER_BINARY_FORMATS      GL_NUM_SHADER_BINARY_FORMATS

/* Shader Precision-Specified Types */
#define KZS_GL_LOW_FLOAT                      GL_LOW_FLOAT
#define KZS_GL_MEDIUM_FLOAT                   GL_MEDIUM_FLOAT
#define KZS_GL_HIGH_FLOAT                     GL_HIGH_FLOAT
#define KZS_GL_LOW_INT                        GL_LOW_INT
#define KZS_GL_MEDIUM_INT                     GL_MEDIUM_INT
#define KZS_GL_HIGH_INT                       GL_HIGH_INT

/* Framebuffer Object. */
#define KZS_GL_FRAMEBUFFER                    GL_FRAMEBUFFER
#define KZS_GL_RENDERBUFFER                   GL_RENDERBUFFER

#define KZS_GL_RGBA4                          GL_RGBA4
#define KZS_GL_RGB5_A1                        GL_RGB5_A1
#define KZS_GL_RGB565                         GL_RGB565
#define KZS_GL_DEPTH_COMPONENT16              GL_DEPTH_COMPONENT16
#if GL_OES_depth24
#define KZS_GL_DEPTH_COMPONENT24              GL_DEPTH_COMPONENT24_OES
#endif
#if GL_OES_depth32
#define KZS_GL_DEPTH_COMPONENT32              GL_DEPTH_COMPONENT32_OES
#endif
#define KZS_GL_STENCIL_INDEX                  GL_STENCIL_INDEX
#define KZS_GL_STENCIL_INDEX8                 GL_STENCIL_INDEX8

#define KZS_GL_RENDERBUFFER_WIDTH             GL_RENDERBUFFER_WIDTH
#define KZS_GL_RENDERBUFFER_HEIGHT            GL_RENDERBUFFER_HEIGHT
#define KZS_GL_RENDERBUFFER_INTERNAL_FORMAT   GL_RENDERBUFFER_INTERNAL_FORMAT
#define KZS_GL_RENDERBUFFER_RED_SIZE          GL_RENDERBUFFER_RED_SIZE
#define KZS_GL_RENDERBUFFER_GREEN_SIZE        GL_RENDERBUFFER_GREEN_SIZE
#define KZS_GL_RENDERBUFFER_BLUE_SIZE         GL_RENDERBUFFER_BLUE_SIZE
#define KZS_GL_RENDERBUFFER_ALPHA_SIZE        GL_RENDERBUFFER_ALPHA_SIZE
#define KZS_GL_RENDERBUFFER_DEPTH_SIZE        GL_RENDERBUFFER_DEPTH_SIZE
#define KZS_GL_RENDERBUFFER_STENCIL_SIZE      GL_RENDERBUFFER_STENCIL_SIZE

#define KZS_GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
#define KZS_GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
#define KZS_GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
#define KZS_GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE

#define KZS_GL_COLOR_ATTACHMENT0              GL_COLOR_ATTACHMENT0
#define KZS_GL_DEPTH_ATTACHMENT               GL_DEPTH_ATTACHMENT
#define KZS_GL_STENCIL_ATTACHMENT             GL_STENCIL_ATTACHMENT

#define KZS_GL_NONE                           GL_NONE

#define KZS_GL_FRAMEBUFFER_COMPLETE                      GL_FRAMEBUFFER_COMPLETE
#define KZS_GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT         GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
#define KZS_GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
#define KZS_GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS         GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
#define KZS_GL_FRAMEBUFFER_UNSUPPORTED GL_FRAMEBUFFER_UNSUPPORTED

#define KZS_GL_FRAMEBUFFER_BINDING            GL_FRAMEBUFFER_BINDING
#define KZS_GL_RENDERBUFFER_BINDING           GL_RENDERBUFFER_BINDING
#define KZS_GL_MAX_RENDERBUFFER_SIZE          GL_MAX_RENDERBUFFER_SIZE

#define KZS_GL_INVALID_FRAMEBUFFER_OPERATION  GL_INVALID_FRAMEBUFFER_OPERATION

/* EXT_texture_filter_anisotropic */
#define KZS_GL_MAX_ANISOTROPY             GL_TEXTURE_MAX_ANISOTROPY_EXT
#define KZS_GL_MAX_TEXTURE_MAX_ANISOTROPY GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT

/*------------------------------------------------------------------------*
* OES extension tokens
*------------------------------------------------------------------------*/

/* ETC */
#if GL_OES_compressed_ETC1_RGB8_texture
#define KZS_GL_ETC1_RGB8_OES                                        GL_ETC1_RGB8_OES
#endif
/* S3TC (DXTC, DXT1, DXT3, DXT5) */

#ifdef GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#define KZS_GL_COMPRESSED_RGB_S3TC_DXT1_EXT                         GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define KZS_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                        GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#endif

#ifdef GL_COMPRESSED_RGB_S3TC_DXT3_EXT
#define KZS_GL_COMPRESSED_RGB_S3TC_DXT3_EXT                         GL_COMPRESSED_RGB_S3TC_DXT3_EXT
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#define KZS_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                        GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#endif

#ifdef GL_DEPTH_STENCIL_OES
#define KZS_GL_DEPTH_STENCIL GL_DEPTH_STENCIL_OES
#endif

#ifdef GL_DEPTH24_STENCIL8_OES
#define KZS_GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#endif

#ifdef GL_COMPRESSED_RGB_S3TC_DXT5_EXT
#define KZS_GL_COMPRESSED_RGB_S3TC_DXT5_EXT                         GL_COMPRESSED_RGB_S3TC_DXT5_EXT
#endif

#ifdef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#define KZS_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                        GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#endif

/* ATITC */
#ifdef GL_AMD_compressed_ATC_texture
#define KZS_GL_ATC_SUPPORTED
#define KZS_GL_ATC_RGB                                              GL_ATC_RGB_AMD
#define KZS_GL_ATC_RGBA_EXPLICIT_ALPHA_AMD                          GL_ATC_RGBA_EXPLICIT_ALPHA_AMD
#define KZS_GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD                      GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD
#endif

/* PVRTC */
#ifdef GL_IMG_texture_compression_pvrtc
#define KZS_GL_PVRTC1_SUPPORTED
#define KZS_GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG      GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 
#define KZS_GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG      GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 
#define KZS_GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG     GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG   
#define KZS_GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG     GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG   
#endif

#ifdef GL_IMG_texture_compression_pvrtc2
#define KZS_GL_PVRTC2_SUPPORTED
#define KZS_GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG			GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG
#define KZS_GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG			GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG
#endif

#define KZS_GL_INVALID_INDEX 0xFFFFFFFFu
#define KZS_GL_UNIFORM_BUFFER 0x8A11
#define KZS_GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#define KZS_GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#define KZS_GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#define KZS_GL_UNIFORM_OFFSET 0x8A3B
#define KZS_GL_UNIFORM_SIZE 0x8A38
#define KZS_GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#define KZS_GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#define KZS_GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#define KZS_GL_UNIFORM_TYPE 0x8A37

/* OES_get_program_binary extension */
typedef void (*kzPFNGLGETPROGRAMBINARYOESPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, GLvoid *binary);
typedef void (*kzPFNGLPROGRAMBINARYOESPROC) (GLuint program, GLenum binaryFormat, const GLvoid *binary, GLint length);

extern kzPFNGLPROGRAMBINARYOESPROC glProgramBinaryKZEXT;
extern kzPFNGLGETPROGRAMBINARYOESPROC glGetProgramBinaryKZEXT;
#define KZS_GL_NUM_PROGRAM_BINARY_FORMATS   0x87FE
#define KZS_GL_PROGRAM_BINARY_FORMATS       0x87FF

/*lint --e{970} Use char* because GLchar is not found from all gl2.h files. */
typedef void (*kzPFNGLGETUNIFORMINDICESEXTPROC)(GLuint program, GLsizei uniformCount, const char** uniformNames, GLuint *uniformIndices);
typedef void (*kzPFNGLBINDBUFFERBASEEXTPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (*kzPFNGLGETACTIVEUNIFORMSIVEXTPROC) (GLuint program, GLsizei uniformCount, const GLuint* uniformIndices, GLenum pname, GLint* params);
typedef GLuint (*kzPFNGLGETUNIFORMBLOCKINDEXEXTPROC) (GLuint program, const char* uniformBlockName);
typedef void (*kzPFNGLGETACTIVEUNIFORMNAMEEXTPROC) (GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei* length, char* uniformName);
typedef void (*kzPFNGLGETACTIVEUNIFORMBLOCKIVEXTPROC) (GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint* params);
typedef void (*kzPFNGLGETACTIVEUNIFORMBLOCKNAMEEXTPROC) (GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei* length, char* uniformBlockName);
typedef void (*kzPFNGLUNIFORMBLOCKBINDINGEXTPROC) (GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

extern kzPFNGLGETUNIFORMINDICESEXTPROC glGetUniformIndicesKZEXT;
extern kzPFNGLBINDBUFFERBASEEXTPROC glBindBufferBaseKZEXT;
extern kzPFNGLGETACTIVEUNIFORMSIVEXTPROC glGetActiveUniformsivKZEXT;
extern kzPFNGLGETACTIVEUNIFORMNAMEEXTPROC glGetActiveUniformNameKZEXT;
extern kzPFNGLGETUNIFORMBLOCKINDEXEXTPROC glGetUniformBlockIndexKZEXT;
extern kzPFNGLGETACTIVEUNIFORMBLOCKIVEXTPROC glGetActiveUniformBlockivKZEXT;
extern kzPFNGLGETACTIVEUNIFORMBLOCKNAMEEXTPROC glGetActiveUniformBlockNameKZEXT;
extern kzPFNGLUNIFORMBLOCKBINDINGEXTPROC glUniformBlockBindingKZEXT;
#define KZS_GL_UNIFORM_BUFFER_SUPPORTED /* Enable the feature in renderer. */


/* Map buffer range extension. */
typedef void* (*kzPFNGLMAPBUFFERRANGEEXTPROC) (kzUint target, kzInt offset, kzInt length, kzUint access);
typedef void (*kzPFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (kzUint target, kzInt offset, kzInt length);

extern kzPFNGLMAPBUFFERRANGEEXTPROC glMapBufferRangeKZEXT;
extern kzPFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC glFlushMappedBufferRangeKZEXT;

#define KZS_GL_MAP_READ_BIT                0x0001
#define KZS_GL_MAP_WRITE_BIT               0x0002
#define KZS_GL_MAP_INVALIDATE_RANGE_BIT    0x0004
#define KZS_GL_MAP_INVALIDATE_BUFFER_BIT   0x0008
#define KZS_GL_MAP_FLUSH_EXPLICIT_BIT      0x0010
#define KZS_GL_MAP_UNSYNCHRONIZED_BIT      0x0020

#define KZS_GL_MAP_BUFFER_RANGE_SUPPORTED /* Enable the feature in renderer. */


/** EGL <-> GL interop extensions. */
#define KZS_GL_TEXTURE_EXTERNAL_OES 0x8D65
typedef void (*kzPFNGLEGLIMAGETARGETTEXTURE2DOESPROC)(GLuint target, void* image);
extern kzPFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DKZEXT;


/**
* GL core functions.
*/


KZ_INLINE void kzsGlActiveTexture(kzUint texture)
{
KZS_OPENGL_CALL_BEGIN
    glActiveTexture(texture);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlAttachShader(kzUint program, kzUint shader)
{
KZS_OPENGL_CALL_BEGIN
    glAttachShader(program, shader);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindAttribLocation(kzUint program, kzUint index, kzString name)
{
KZS_OPENGL_CALL_BEGIN
    glBindAttribLocation(program, index, name);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindBuffer(kzUint target, kzUint buffer)
{
KZS_OPENGL_CALL_BEGIN
    glBindBuffer(target, buffer);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindFramebuffer(kzUint target, kzUint framebuffer)
{
KZS_OPENGL_CALL_BEGIN
    glBindFramebuffer(target, framebuffer);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindRenderbuffer(kzUint target, kzUint renderbuffer)
{
KZS_OPENGL_CALL_BEGIN
    glBindRenderbuffer(target, renderbuffer);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindTexture(kzUint target, kzUint texture)
{
KZS_OPENGL_CALL_BEGIN
    glBindTexture(target, texture);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBlendColor(kzFloat red, kzFloat green, kzFloat blue, kzFloat alpha)
{
KZS_OPENGL_CALL_BEGIN
    glBlendColor(red, green, blue, alpha);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBlendEquation(kzUint mode)
{
KZS_OPENGL_CALL_BEGIN
    glBlendEquation(mode);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBlendEquationSeparate(kzUint modeRGB, kzUint modeAlpha)
{
KZS_OPENGL_CALL_BEGIN
    glBlendEquationSeparate(modeRGB, modeAlpha);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBlendFunc(kzUint sfactor, kzUint dfactor)
{
KZS_OPENGL_CALL_BEGIN
    glBlendFunc(sfactor, dfactor);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBlendFuncSeparate(kzUint srcRGB, kzUint dstRGB, kzUint srcAlpha, kzUint dstAlpha)
{
KZS_OPENGL_CALL_BEGIN
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBufferData(kzUint target, kzInt size, const void* data, kzUint usage)
{
KZS_OPENGL_CALL_BEGIN
    glBufferData(target, size, data, usage);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBufferSubData(kzUint target, kzInt offset, kzInt size, const void* data)
{
KZS_OPENGL_CALL_BEGIN
    glBufferSubData(target, offset, size, data);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzUint kzsGlCheckFramebufferStatus(kzUint target)
{
KZS_OPENGL_CALL_BEGIN
    return glCheckFramebufferStatus(target);
KZS_OPENGL_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsGlClear(GLbitfield mask)
{
KZS_OPENGL_CALL_BEGIN
    glClear(mask);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlClearColor(kzFloat red, kzFloat green, kzFloat blue, kzFloat alpha)
{
KZS_OPENGL_CALL_BEGIN
    glClearColor(red, green, blue, alpha);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlClearDepthf(kzFloat depth)
{
KZS_OPENGL_CALL_BEGIN
    glClearDepthf(depth);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlClearStencil(kzInt s)
{
KZS_OPENGL_CALL_BEGIN
    glClearStencil(s);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlColorMask(kzBool red, kzBool green, kzBool blue, kzBool alpha)
{
KZS_OPENGL_CALL_BEGIN
    glColorMask(kzsGetGLBoolean_private(red), kzsGetGLBoolean_private(green), kzsGetGLBoolean_private(blue), kzsGetGLBoolean_private(alpha));
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlCompileShader(kzUint shader)
{
KZS_OPENGL_CALL_BEGIN
    glCompileShader(shader);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlCompressedTexImage2D(kzUint target, kzInt level, kzUint internalformat, kzInt width, kzInt height, kzInt border, kzInt imageSize, const void* data)
{
KZS_OPENGL_CALL_BEGIN
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlCompressedTexSubImage2D(kzUint target, kzInt level, kzInt xoffset, kzInt yoffset, kzInt width, kzInt height, kzUint format, kzInt imageSize, const void* data)
{
KZS_OPENGL_CALL_BEGIN
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlCopyTexImage2D(kzUint target, kzInt level, kzUint internalformat, kzInt x, kzInt y, kzInt width, kzInt height, kzInt border)
{
KZS_OPENGL_CALL_BEGIN
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlCopyTexSubImage2D(kzUint target, kzInt level, kzInt xoffset, kzInt yoffset, kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENGL_CALL_BEGIN
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzUint kzsGlCreateProgram(void)
{
KZS_OPENGL_CALL_BEGIN
    return glCreateProgram();
KZS_OPENGL_CALL_END_RETURN_VALUE(1)
}

KZ_INLINE kzUint kzsGlCreateShader(kzUint type)
{
KZS_OPENGL_CALL_BEGIN
    return glCreateShader(type);
KZS_OPENGL_CALL_END_RETURN_VALUE(1)
}

KZ_INLINE void kzsGlCullFace(kzUint mode)
{
KZS_OPENGL_CALL_BEGIN
    glCullFace(mode);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteBuffers(kzInt n, const kzUint* buffers)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteBuffers(n, buffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteFramebuffers(kzInt n, const kzUint* framebuffers)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteFramebuffers(n, framebuffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteProgram(kzUint program)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteProgram(program);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteRenderbuffers(kzInt n, const kzUint* renderbuffers)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteRenderbuffers(n, renderbuffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteShader(kzUint shader)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteShader(shader);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDeleteTextures(kzInt n, const kzUint* textures)
{
KZS_OPENGL_CALL_BEGIN
    glDeleteTextures(n, textures);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDepthFunc(kzUint func)
{
KZS_OPENGL_CALL_BEGIN
    glDepthFunc(func);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDepthMask(kzBool flag)
{
KZS_OPENGL_CALL_BEGIN
    glDepthMask(kzsGetGLBoolean_private(flag));
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDepthRangef(kzFloat zNear, kzFloat zFar)
{
KZS_OPENGL_CALL_BEGIN
    glDepthRangef(zNear, zFar);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDetachShader(kzUint program, kzUint shader)
{
KZS_OPENGL_CALL_BEGIN
    glDetachShader(program, shader);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDisable(kzUint cap)
{
KZS_OPENGL_CALL_BEGIN
    glDisable(cap);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDisableVertexAttribArray(kzUint index)
{
KZS_OPENGL_CALL_BEGIN
    glDisableVertexAttribArray(index);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDrawArrays(kzUint mode, kzInt first, kzInt count)
{
KZS_OPENGL_CALL_BEGIN
    glDrawArrays(mode, first, count);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlDrawArrays");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlDrawElements(kzUint mode, kzInt count, kzUint type, const void* indices)
{
KZS_OPENGL_CALL_BEGIN
    glDrawElements(mode, count, type, indices);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlDrawElements");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlEnable(kzUint cap)
{
KZS_OPENGL_CALL_BEGIN
    glEnable(cap);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlEnableVertexAttribArray(kzUint index)
{
KZS_OPENGL_CALL_BEGIN
    glEnableVertexAttribArray(index);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlFinish(void)
{
KZS_OPENGL_CALL_BEGIN
    glFinish();
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlFlush(void)
{
KZS_OPENGL_CALL_BEGIN
    glFlush();
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlFramebufferRenderbuffer(kzUint target, kzUint attachment, kzUint renderbuffertarget, kzUint renderbuffer)
{
KZS_OPENGL_CALL_BEGIN
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlFramebufferTexture2D(kzUint target, kzUint attachment, kzUint textarget, kzUint texture, kzInt level)
{
KZS_OPENGL_CALL_BEGIN
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlFrontFace(kzUint mode)
{
KZS_OPENGL_CALL_BEGIN
    glFrontFace(mode);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGenBuffers(kzInt n, kzUint* buffers)
{
KZS_OPENGL_CALL_BEGIN
    glGenBuffers(n, buffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGenerateMipmap(kzUint target)
{
KZS_OPENGL_CALL_BEGIN
    glGenerateMipmap(target);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGenFramebuffers(kzInt n, kzUint* framebuffers)
{
KZS_OPENGL_CALL_BEGIN
    glGenFramebuffers(n, framebuffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGenRenderbuffers(kzInt n, kzUint* renderbuffers)
{
KZS_OPENGL_CALL_BEGIN
    glGenRenderbuffers(n, renderbuffers);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGenTextures(kzInt n, kzUint* textures)
{
KZS_OPENGL_CALL_BEGIN
    glGenTextures(n, textures);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetActiveAttrib(kzUint program, kzUint index, kzInt bufsize, kzInt* length, kzInt* size, kzUint* type, kzMutableString name)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveAttrib(program, index, bufsize, length, size, type, name);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetActiveUniform(kzUint program, kzUint index, kzInt bufsize, kzInt* length, kzInt* size, kzUint* type, kzMutableString name)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveUniform(program, index, bufsize, length, size, type, name);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetAttachedShaders(kzUint program, kzInt maxcount, kzInt* count, kzUint* shaders)
{
KZS_OPENGL_CALL_BEGIN
    glGetAttachedShaders(program, maxcount, count, shaders);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzInt kzsGlGetAttribLocation(kzUint program, kzString name)
{
KZS_OPENGL_CALL_BEGIN
    kzsCounterIncrease("kzsGlGetAttribLocation");
    return (kzInt)glGetAttribLocation(program, name);
KZS_OPENGL_CALL_END_RETURN_VALUE(1)
}

KZ_INLINE void kzsGlGetBooleanv(kzUint pname, GLboolean* params) /* params is of type GLboolean, because this type cannot be casted to kzBool */
{
KZS_OPENGL_CALL_BEGIN
    glGetBooleanv(pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetBufferParameteriv(kzUint target, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetBufferParameteriv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzUint kzsGlGetError(void)
{
KZS_OPENGL_CALL_BEGIN
    return glGetError();
KZS_OPENGL_CALL_END_RETURN_VALUE(KZS_GL_NO_ERROR)
}

KZ_INLINE void kzsGlGetFloatv(kzUint pname, kzFloat* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetFloatv(pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetFramebufferAttachmentParameteriv(kzUint target, kzUint attachment, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetIntegerv(kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetIntegerv(pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetProgramiv(kzUint program, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetProgramiv(program, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetProgramInfoLog(kzUint program, kzInt bufsize, kzInt* length, kzMutableString infolog)
{
KZS_OPENGL_CALL_BEGIN
    glGetProgramInfoLog(program, bufsize, length, infolog);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetRenderbufferParameteriv(kzUint target, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetRenderbufferParameteriv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetShaderiv(kzUint shader, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetShaderiv(shader, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetShaderInfoLog(kzUint shader, kzInt bufsize, kzInt* length, kzMutableString infolog)
{
KZS_OPENGL_CALL_BEGIN
    glGetShaderInfoLog(shader, bufsize, length, infolog);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetShaderPrecisionFormat(kzUint shadertype, kzUint precisiontype, kzInt* range, kzInt* precision)
{
KZS_OPENGL_CALL_BEGIN
    glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetShaderSource(kzUint shader, kzInt bufsize, kzInt* length, kzMutableString source)
{
KZS_OPENGL_CALL_BEGIN
    glGetShaderSource(shader, bufsize, length, source);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzString kzsGlGetString(kzUint name)
{
KZS_OPENGL_CALL_BEGIN
    return (kzString)glGetString(name);
KZS_OPENGL_CALL_END_RETURN_VALUE("")
}

KZ_INLINE void kzsGlGetTexParameterfv(kzUint target, kzUint pname, kzFloat* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetTexParameterfv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetTexParameteriv(kzUint target, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetTexParameteriv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetUniformfv(kzUint program, kzInt location, kzFloat* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetUniformfv(program, location, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetUniformiv(kzUint program, kzInt location, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetUniformiv(program, location, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzInt kzsGlGetUniformLocation(kzUint program, kzString name)
{
KZS_OPENGL_CALL_BEGIN
    kzsCounterIncrease("kzsGlGetUniformLocation");
    return (kzInt)glGetUniformLocation(program, name);
KZS_OPENGL_CALL_END_RETURN_VALUE(-1)
}

KZ_INLINE void kzsGlGetVertexAttribfv(kzUint index, kzUint pname, kzFloat* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetVertexAttribfv(index, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetVertexAttribiv(kzUint index, kzUint pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetVertexAttribiv(index, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetVertexAttribPointerv(kzUint index, kzUint pname, void** pointer)
{
KZS_OPENGL_CALL_BEGIN
    glGetVertexAttribPointerv(index, pname, pointer);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlHint(kzUint target, kzUint mode)
{
KZS_OPENGL_CALL_BEGIN
    glHint(target, mode);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE kzBool kzsGlIsBuffer(kzUint buffer)
{
KZS_OPENGL_CALL_BEGIN
    return glIsBuffer(buffer);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsEnabled(kzUint cap)
{
KZS_OPENGL_CALL_BEGIN
    return glIsEnabled(cap);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsFramebuffer(kzUint framebuffer)
{
KZS_OPENGL_CALL_BEGIN
    return glIsFramebuffer(framebuffer);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsProgram(kzUint program)
{
KZS_OPENGL_CALL_BEGIN
    return glIsProgram(program);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsRenderbuffer(kzUint renderbuffer)
{
KZS_OPENGL_CALL_BEGIN
    return glIsRenderbuffer(renderbuffer);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsShader(kzUint shader)
{
KZS_OPENGL_CALL_BEGIN
    return glIsShader(shader);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE kzBool kzsGlIsTexture(kzUint texture)
{
KZS_OPENGL_CALL_BEGIN
    return glIsTexture(texture);
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_FALSE)
}

KZ_INLINE void kzsGlLineWidth(kzFloat width)
{
KZS_OPENGL_CALL_BEGIN
    glLineWidth(width);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlLinkProgram(kzUint program)
{
KZS_OPENGL_CALL_BEGIN
    glLinkProgram(program);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlPixelStorei(kzUint pname, kzInt param)
{
KZS_OPENGL_CALL_BEGIN
    glPixelStorei(pname, param);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlPolygonOffset(kzFloat factor, kzFloat units)
{
KZS_OPENGL_CALL_BEGIN
    glPolygonOffset(factor, units);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlReadPixels(kzInt x, kzInt y, kzInt width, kzInt height, kzUint format, kzUint type, void* pixels)
{
KZS_OPENGL_CALL_BEGIN
    glReadPixels(x, y, width, height, format, type, pixels);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlReleaseShaderCompiler(void)
{
KZS_OPENGL_CALL_BEGIN
    glReleaseShaderCompiler();
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlRenderbufferStorage(kzUint target, kzUint internalformat, kzInt width, kzInt height)
{
KZS_OPENGL_CALL_BEGIN
    glRenderbufferStorage(target, internalformat, width, height);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlSampleCoverage(kzFloat value, kzBool invert)
{
KZS_OPENGL_CALL_BEGIN
    glSampleCoverage(value, kzsGetGLBoolean_private(invert));
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlScissor(kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENGL_CALL_BEGIN
    glScissor(x, y, width, height);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlShaderBinary(kzInt n, const kzUint* shaders, kzUint binaryformat, const void* binary, kzInt length)
{
KZS_OPENGL_CALL_BEGIN
    glShaderBinary(n, shaders, binaryformat, binary, length);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlProgramBinary(kzUint program, kzUint binaryFormat, const void *binary, kzInt length)
{
KZS_OPENGL_CALL_BEGIN
    glProgramBinaryKZEXT(program, binaryFormat, binary, length);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlProgramGetBinary(kzUint program, kzInt bufferSize, kzInt* out_length, kzUint* out_binaryFormat, void* out_binary)
{
KZS_OPENGL_CALL_BEGIN
    glGetProgramBinaryKZEXT(program, bufferSize, out_length, out_binaryFormat, out_binary);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlShaderSource(kzUint shader, kzInt count, /*lint -e{818}*/kzString* string, const kzInt* length)
{
KZS_OPENGL_CALL_BEGIN
    glShaderSource(shader, count, (kzString*)string, length);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilFunc(kzUint func, kzInt ref, kzUint mask)
{
KZS_OPENGL_CALL_BEGIN
    glStencilFunc(func, ref, mask);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilFuncSeparate(kzUint face, kzUint func, kzInt ref, kzUint mask)
{
KZS_OPENGL_CALL_BEGIN
    glStencilFuncSeparate(face, func, ref, mask);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilMask(kzUint mask)
{
KZS_OPENGL_CALL_BEGIN
    glStencilMask(mask);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilMaskSeparate(kzUint face, kzUint mask)
{
KZS_OPENGL_CALL_BEGIN
    glStencilMaskSeparate(face, mask);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilOp(kzUint fail, kzUint zfail, kzUint zpass)
{
KZS_OPENGL_CALL_BEGIN
    glStencilOp(fail, zfail, zpass);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlStencilOpSeparate(kzUint face, kzUint fail, kzUint zfail, kzUint zpass)
{
KZS_OPENGL_CALL_BEGIN
    glStencilOpSeparate(face, fail, zfail, zpass);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexImage2D(kzUint target, kzInt level, kzInt internalformat, kzInt width, kzInt height, kzInt border, kzUint format, kzUint type, const void* pixels)
{
KZS_OPENGL_CALL_BEGIN
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexParameterf(kzUint target, kzUint pname, kzFloat param)
{
KZS_OPENGL_CALL_BEGIN
    glTexParameterf(target, pname, param);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexParameterfv(kzUint target, kzUint pname, const kzFloat* params)
{
KZS_OPENGL_CALL_BEGIN
    glTexParameterfv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexParameteri(kzUint target, kzUint pname, kzInt param)
{
KZS_OPENGL_CALL_BEGIN
    glTexParameteri(target, pname, param);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexParameteriv(kzUint target, kzUint pname, const kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glTexParameteriv(target, pname, params);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlTexSubImage2D(kzUint target, kzInt level, kzInt xoffset, kzInt yoffset, kzInt width, kzInt height, kzUint format, kzUint type, const void* pixels)
{
KZS_OPENGL_CALL_BEGIN
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform1f(kzInt location, kzFloat x)
{
KZS_OPENGL_CALL_BEGIN
    glUniform1f(location, x);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform1fv(kzInt location, kzInt count, const kzFloat* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform1fv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform1i(kzInt location, kzInt x)
{
KZS_OPENGL_CALL_BEGIN
    glUniform1i(location, x);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform1iv(kzInt location, kzInt count, const kzInt* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform1iv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform2f(kzInt location, kzFloat x, kzFloat y)
{
KZS_OPENGL_CALL_BEGIN
    glUniform2f(location, x, y);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform2fv(kzInt location, kzInt count, const kzFloat* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform2fv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform2i(kzInt location, kzInt x, kzInt y)
{
KZS_OPENGL_CALL_BEGIN
    glUniform2i(location, x, y);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform2iv(kzInt location, kzInt count, const kzInt* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform2iv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform3f(kzInt location, kzFloat x, kzFloat y, kzFloat z)
{
KZS_OPENGL_CALL_BEGIN
    glUniform3f(location, x, y, z);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform3fv(kzInt location, kzInt count, const kzFloat* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform3fv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform3i(kzInt location, kzInt x, kzInt y, kzInt z)
{
KZS_OPENGL_CALL_BEGIN
    glUniform3i(location, x, y, z);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform3iv(kzInt location, kzInt count, const kzInt* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform3iv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform4f(kzInt location, kzFloat x, kzFloat y, kzFloat z, kzFloat w)
{
KZS_OPENGL_CALL_BEGIN
    glUniform4f(location, x, y, z, w);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform4fv(kzInt location, kzInt count, const kzFloat* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform4fv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform4i(kzInt location, kzInt x, kzInt y, kzInt z, kzInt w)
{
KZS_OPENGL_CALL_BEGIN
    glUniform4i(location, x, y, z, w);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniform4iv(kzInt location, kzInt count, const kzInt* v)
{
KZS_OPENGL_CALL_BEGIN
    glUniform4iv(location, count, v);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniformMatrix2fv(kzInt location, kzInt count, kzBool transpose, const kzFloat* value)
{
KZS_OPENGL_CALL_BEGIN
    glUniformMatrix2fv(location, count, kzsGetGLBoolean_private(transpose), value);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniformMatrix3fv(kzInt location, kzInt count, kzBool transpose, const kzFloat* value) 
{
KZS_OPENGL_CALL_BEGIN
    glUniformMatrix3fv(location, count, kzsGetGLBoolean_private(transpose), value);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniformMatrix4fv(kzInt location, kzInt count, kzBool transpose, const kzFloat* value) 
{
KZS_OPENGL_CALL_BEGIN
    glUniformMatrix4fv(location, count, kzsGetGLBoolean_private(transpose), value);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUniform");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUseProgram(kzUint program)
{
KZS_OPENGL_CALL_BEGIN
    glUseProgram(program);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlUseProgram");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlValidateProgram(kzUint program)
{
KZS_OPENGL_CALL_BEGIN
    glValidateProgram(program);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib1f(kzUint indx, kzFloat x)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib1f(indx, x);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib1fv(kzUint indx, const kzFloat* values)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib1fv(indx, values);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib2f(kzUint indx, kzFloat x, kzFloat y)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib2f(indx, x, y);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib2fv(kzUint indx, const kzFloat* values)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib2fv(indx, values);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib3f(kzUint indx, kzFloat x, kzFloat y, kzFloat z)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib3f(indx, x, y, z);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib3fv(kzUint indx, const kzFloat* values)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib3fv(indx, values);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib4f(kzUint indx, kzFloat x, kzFloat y, kzFloat z, kzFloat w)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib4f(indx, x, y, z, w);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttrib4fv(kzUint indx, const kzFloat* values)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttrib4fv(indx, values);
    kzsGlErrorTest();
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlVertexAttribPointer(kzUint indx, kzInt size, kzUint type, kzBool normalized, kzInt stride, const void* ptr)
{
KZS_OPENGL_CALL_BEGIN
    glVertexAttribPointer(indx, size, type, kzsGetGLBoolean_private(normalized), stride, ptr);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlVertexAttribPointer");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlViewport(kzInt x, kzInt y, kzInt width, kzInt height)
{
KZS_OPENGL_CALL_BEGIN
    glViewport(x, y, width, height);
    kzsGlErrorTest();

    kzsCounterIncrease("kzsGlViewport");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetUniformIndices(kzUint program, kzUint uniformCount, const kzChar** uniformNames, kzUint* uniformIndices)
{
KZS_OPENGL_CALL_BEGIN
    glGetUniformIndicesKZEXT(program, (GLsizei)uniformCount, uniformNames, uniformIndices);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGllGetUniformIndices");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetActiveUniformsiv(kzUint program, kzUint uniformCount, const kzUint *uniformIndices, kzInt pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveUniformsivKZEXT(program, (GLsizei)uniformCount, uniformIndices, (GLenum)pname, params);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlGetActiveUniformsiv");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetActiveUniformName(kzUint program, kzUint uniformIndex, kzUint bufSize, kzInt* length, kzChar* uniformName)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveUniformNameKZEXT(program, uniformIndex, (GLsizei)bufSize, length, uniformName);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlGetActiveUniformName");
KZS_OPENGL_CALL_END
}

KZ_INLINE kzUint kzsGlGetUniformBlockIndex(kzUint program, const kzChar* uniformBlockName)
{
KZS_OPENGL_CALL_BEGIN
    kzUint index = glGetUniformBlockIndexKZEXT(program, uniformBlockName);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlGetUniformBlockIndex");
    return index;
KZS_OPENGL_CALL_END_RETURN_VALUE(0)
}

KZ_INLINE void kzsGlGetActiveUniformBlockiv(kzUint program, kzUint uniformBlockIndex, kzInt pname, kzInt* params)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveUniformBlockivKZEXT(program, uniformBlockIndex, (GLenum)pname, params);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlGetActiveUniformBlockiv");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlGetActiveUniformBlockName(kzUint program, kzUint uniformBlockIndex, kzUint bufSize, kzInt* length, kzChar* uniformBlockName)
{
KZS_OPENGL_CALL_BEGIN
    glGetActiveUniformBlockNameKZEXT(program, uniformBlockIndex, (GLsizei)bufSize, length, uniformBlockName);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlGetActiveUniformBlockName");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlUniformBlockBinding(kzUint program, kzUint uniformBlockIndex, kzUint uniformBlockBinding)
{
KZS_OPENGL_CALL_BEGIN
    glUniformBlockBindingKZEXT(program, uniformBlockIndex, uniformBlockBinding);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlUniformBlockBinding");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlBindBufferBase(kzInt target, kzUint index, kzUint buffer)
{
KZS_OPENGL_CALL_BEGIN
    glBindBufferBaseKZEXT((GLenum)target, index, buffer);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlBindBufferBase");
KZS_OPENGL_CALL_END
}

KZ_INLINE void kzsGlEGLImageTargetTexture2D(GLuint target, void* image)
{
KZS_OPENGL_CALL_BEGIN
    glEGLImageTargetTexture2DKZEXT(target, image);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlEGLImageTargetTexture2D");
KZS_OPENGL_CALL_END
}

KZ_INLINE void* kzsGlMapBufferRange(kzUint target, kzInt offset, kzInt length, kzUint access)
{
KZS_OPENGL_CALL_BEGIN
    void* mappedData;
    mappedData = glMapBufferRangeKZEXT(target, offset, length, access);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlMapBufferRange");
    return mappedData;
KZS_OPENGL_CALL_END_RETURN_VALUE(KZ_NULL)
}

KZ_INLINE void kzsGlFlushMappedBufferRange(kzUint target, kzInt offset, kzInt length)
{
KZS_OPENGL_CALL_BEGIN
    glFlushMappedBufferRangeKZEXT(target, offset, length);
    kzsGlErrorTest();
    kzsCounterIncrease("kzsGlFlushMappedBufferRange");
KZS_OPENGL_CALL_END
}

KZ_HEADER_END


#endif
