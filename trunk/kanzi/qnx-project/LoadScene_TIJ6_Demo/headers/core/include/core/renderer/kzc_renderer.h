/**
* \file
* Core renderer. Contains the graphics state machine.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZC_RENDERER_H
#define KZC_RENDERER_H


#include <core/util/color/kzc_color.h>
#include <core/util/math/kzc_matrix4x4.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_math.h>
#include <system/wrappers/kzs_opengl_base.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/** Size of the uniform cache. */
#define KZC_RENDERER_UNIFORM_CACHE_SIZE     150000
/** Size of the per frame memory manager. */
#define KZC_RENDERER_PER_FRAME_MEMORY_MANAGER_SIZE     20000

/** Maximum number of supported texture units. */
#if KZ_OPENGL_VERSION == KZ_OPENGL_LATEST
#define KZC_RENDERER_MAX_TEXTURE_UNITS      17
#else
#define KZC_RENDERER_MAX_TEXTURE_UNITS      5
#endif

#define KZC_RENDERER_MAX_VERTEX_ATTRIBUTES 16 /**< Maximum amount of shader vertex attributes. */

/** Clear target options for renderer. */
enum KzcRendererClearTarget
{
    KZC_RENDERER_CLEAR_TARGET_COLOR,    /**< Clear target color. */
    KZC_RENDERER_CLEAR_TARGET_DEPTH,    /**< Clear target depth. */
    KZC_RENDERER_CLEAR_TARGET_STENCIL,   /**< Clear target stencil. */
    KZC_RENDERER_CLEAR_TARGET_COVERAGE_BUFFER /**< Clear target coverage buffer. */
};

/** Renderer state enumerations. */
enum KzcRendererState
{
    KZC_RENDERER_STATE_DEPTH_TEST,      /**< Renderer state for depth testing. */
    KZC_RENDERER_STATE_CULL_FACE,       /**< Renderer state for cull face. */
    KZC_RENDERER_STATE_BLEND,           /**< Renderer state for blending. */
    KZC_RENDERER_STATE_DEPTH_WRITE,     /**< Renderer state for depth write. */
    KZC_RENDERER_STATE_STENCIL_TEST,   /**< Renderer state for stencil test. */
    KZC_RENDERER_STATE_STENCIL_WRITE,   /**< Renderer state for stencil write. */
    KZC_RENDERER_STATE_MULTISAMPLE,     /**< Renderer state for multi-sampling. */
    KZC_RENDERER_STATE_SCISSOR_TEST,     /**< Renderer state for scissor test. */
    KZC_RENDERER_STATE_COVERAGE_WRITE,     /**< Renderer state for coverage write. */

    KZC_RENDERER_MAX_STATES             /**< Maximum count of renderer states. */
};

/** List of available cull modes. */
enum KzcRendererCullMode
{
    KZC_RENDERER_CULL_MODE_NONE,    /**< No culling. */
    KZC_RENDERER_CULL_MODE_BACK,    /**< Backface culling. */
    KZC_RENDERER_CULL_MODE_FRONT    /**< Frontface culling. */
};

/** List of active renderer scalars for fixed functionality. */
enum KzcRendererScalar
{
    KZC_RENDERER_SCALAR_CLEAR_DEPTH,    /**< Clear depth value. */
    KZC_RENDERER_SCALAR_CAMERA_NEAR_PLANE,    /**< Camera near plane distance. */
    KZC_RENDERER_SCALAR_CAMERA_FAR_PLANE,    /**< Camera far plane distance. */
    
    KZC_RENDERER_MAX_SCALARS            /**< Maximum amount of scalars. */
};

/** Renderer stencil modes. */
enum KzcRendererStencilFunction
{
    KZC_RENDERER_STENCIL_MODE_NEVER, /**< Always fails. */
    KZC_RENDERER_STENCIL_MODE_LESS, /**< (Ref & mask) < (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_LEQUAL, /**< (Ref & mask) <= (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_GREATER, /**< (Ref & mask) > (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_GEQUAL, /**< (Ref & mask) >= (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_EQUAL, /**< (Ref & mask) = (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_NOT_EQUAL,/**< (Ref & mask) != (stencil & mask). */
    KZC_RENDERER_STENCIL_MODE_ALWAYS /**< Always passes. */
};

/** Renderer stencil operations. */
enum KzcRendererStencilOperation
{
    KZC_RENDERER_STENCIL_OPERATION_KEEP, /**< Keeps the current stencil buffer value. */
    KZC_RENDERER_STENCIL_OPERATION_ZERO, /**< Sets stencil buffer value to zero. */
    KZC_RENDERER_STENCIL_OPERATION_REPLACE, /**< Set stencil buffer value to reference value, specified by StencilFunction. */
    KZC_RENDERER_STENCIL_OPERATION_INCREASE_WRAP, /**< Increases stencil buffer value, wraps to zero when reaching maximum. */
    KZC_RENDERER_STENCIL_OPERATION_DECREASE_WRAP, /**< Decreases stencil buffer value, wraps to maximum - 1 when below 0. */
    KZC_RENDERER_STENCIL_OPERATION_INCREASE, /**< Increases current stencil buffer value. */
    KZC_RENDERER_STENCIL_OPERATION_DECREASE, /**< Decreases current stencil buffer value. */
    KZC_RENDERER_STENCIL_OPERATION_INVERT /**< Inverts current stencil buffer value. */
};

#define KZC_RENDERER_BUFFER_VALUE_NONE 0    /**< Null value for buffers, that is, vertex & index buffer. */

/** List of active matrices renderer keeps track of. */
enum KzcRendererMatrix
{
    KZC_RENDERER_MATRIX_PROJECTION,                 /**< Projection matrix. */
    KZC_RENDERER_MATRIX_CAMERA,                     /**< Camera matrix. */
    KZC_RENDERER_MATRIX_WORLD,                      /**< Current world matrix. */
    KZC_RENDERER_MATRIX_CAMERA_WORLD,               /**< Current camera x world matrix. */
    KZC_RENDERER_MATRIX_PROJECTION_CAMERA_WORLD,   /**< Current projection x camera x world matrix. */

    KZC_RENDERER_MAX_MATRICES                       /**< Maximum amount of matrices. */
};

/** List of color write modes. */
enum KzcRendererColorWriteMode
{
    KZC_RENDERER_COLOR_WRITE_INVALID,   /**< Invalid color write mode, initial value when nothing is specified. */
    KZC_RENDERER_COLOR_WRITE_NONE,      /**< No color write. */
    KZC_RENDERER_COLOR_WRITE_RGB,       /**< Color write for RGB channels. */
    KZC_RENDERER_COLOR_WRITE_RGBA,      /**< Color write for RGBA channels. */
    KZC_RENDERER_COLOR_WRITE_RED,       /**< Color write for red channel. */
    KZC_RENDERER_COLOR_WRITE_GREEN,     /**< Color write for green channel. */
    KZC_RENDERER_COLOR_WRITE_BLUE,      /**< Color write for blue channel. */
    KZC_RENDERER_COLOR_WRITE_CYAN,      /**< Color write for cyan (green+blue). */
    KZC_RENDERER_COLOR_WRITE_ALPHA      /**< Color write for alpha channel. */
};

/** List of renderer blend modes. */
enum KzcRendererBlendMode
{
    KZC_RENDERER_BLEND_MODE_OPAQUE,              /**< Opaque blend mode. */
    KZC_RENDERER_BLEND_MODE_ALPHA,               /**< Regular alpha blend. */
    KZC_RENDERER_BLEND_MODE_ADDITIVE,            /**< Additive blend mode. */
    KZC_RENDERER_BLEND_MODE_PREMULTIPLIED_ALPHA, /**< Alpha blend of target, but source color has already been processed. */
    KZC_RENDERER_BLEND_MODE_MIXED_ALPHA          /**< Takes regular alpha input, but produces premultiplied output. */
};

/** List of renderer depth modes. */
enum KzcRendererDepthTest
{
    KZC_RENDERER_DEPTH_TEST_DISABLED,      /**< Depth test disabled completely. */
    KZC_RENDERER_DEPTH_TEST_ALWAYS,        /**< Always pass. Akin to disabled, but allows writing depth. */
    KZC_RENDERER_DEPTH_TEST_EQUAL,         /**< Pass on exact same depth as in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_NOT_EQUAL,     /**< Pass on depth anything else than depth as in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_LESS,          /**< Pass on depth less than depth in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_LESS_EQUAL,    /**< Pass on depth less or equal to depth in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_GREATER,       /**< Pass on depth greater than depth in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_GREATER_EQUAL, /**< Pass on depth greater or equal to depth in framebuffer. */
    KZC_RENDERER_DEPTH_TEST_NEVER          /**< Never pass. Of dubious applicability.*/
};

/** List of color formats.. */
enum KzcRendererColorFormat
{
    KZC_RENDERER_COLOR_FORMAT_UNSIGNED_SHORT_RGB_5_6_5,        /**< 16 bit RGB565 color. */
    KZC_RENDERER_COLOR_FORMAT_UNSIGNED_BYTE_RGB_8_8_8,        /**< 24 bit RGB color. */
    KZC_RENDERER_COLOR_FORMAT_UNSIGNED_BYTE_RGBA_8_8_8_8        /**< 32 bit RGBA color. */
};

/** List of texture types. */
enum KzcRendererTextureType
{
    KZC_RENDERER_TEXTURE_TYPE_INVALID, /**< Invalid type. */
    KZC_RENDERER_TEXTURE_TYPE_2D, /**< 2D Texture. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP, /**< Cubemap texture. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_NEG_X, /**< Cubemap texture side negative X. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_POS_X, /**< Cubemap texture side positive X. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_NEG_Y, /**< Cubemap texture side negative Y. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_POS_Y, /**< Cubemap texture side positive Y. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_NEG_Z, /**< Cubemap texture side negative Z. */
    KZC_RENDERER_TEXTURE_TYPE_CUBEMAP_POS_Z, /**< Cubemap texture side positive Z. */
    KZC_RENDERER_TEXTURE_TYPE_EXTERNAL /**< External 2D Texture. */
};

/** List of texture wrap modes. */
enum KzcRendererTextureWrapMode
{
    KZC_RENDERER_TEXTURE_WRAP_MODE_CLAMP_TO_EDGE, /**< Clamp to edge. */
    KZC_RENDERER_TEXTURE_WRAP_MODE_REPEAT /**< Repeat. */
};

/** List of texture filters. */
enum KzcRendererTextureFilter
{
    KZC_RENDERER_TEXTURE_FILTER_POINT_SAMPLE, /**< Point sample (direct detch from texel) */
    KZC_RENDERER_TEXTURE_FILTER_LINEAR, /**< Linear sampling from 4 texels. */
    KZC_RENDERER_TEXTURE_FILTER_MIPMAP, /**< Mipmap */
    KZC_RENDERER_TEXTURE_FILTER_TRILINEAR /**< Trilinear. */
};

/** Specifies list of available texture formats. */
enum KzcRendererTextureFormat
{
    KZC_RENDERER_TEXTURE_FORMAT_RGB,            /**< RGB texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGBA,           /**< RGBA texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ALPHA,          /**< Alpha texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGB565,         /**< RGB565 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ETC,            /**< ETC compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_LUMINANCE,      /**< Luminance texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_LUMINANCE_ALPHA, /**< Luminance alpha texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DXT3_RGBA,      /**< DXT3 RGBA compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DXT5_RGBA,      /**< DXT5 RGBA compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ATC, /**< ATC compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ATC_EXPLICIT_ALPHA, /**< ATC explicit alpha compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ATC_INTERPOLATED_ALPHA, /**< ATC explicit alpha compressed texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC1_RGB_2BPP,     /**< RGB PVRTC1 2 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC1_RGB_4BPP,     /**< RGB PVRTC1 4 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC1_RGBA_2BPP,    /**< RGBA PVRTC1 2 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC1_RGBA_4BPP,    /**< RGBA PVRTC1 4 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC2_RGBA_2BPP,    /**< RGBA PVRTC2 2 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_PVRTC2_RGBA_4BPP,    /**< RGBA PVRTC2 4 bits per pixel texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGB_FLOAT_16,   /** RGB float 16 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGB_FLOAT_32,   /** RGB float 32 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGBA_FLOAT_16,  /** RGBA float 16 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_RGBA_FLOAT_32,  /** RGBA float 32 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ALPHA_FLOAT_16, /** Alpha float 16 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_ALPHA_FLOAT_32,  /** Alpha float 32 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DEPTH_TEXTURE_FORMAT_16,    /**< Depth 16 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DEPTH_TEXTURE_FORMAT_24,    /**< Depth 24 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DEPTH_TEXTURE_FORMAT_32,    /**< Depth 32 texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_DEPTH_TEXTURE_FORMAT_32F,   /**< Depth 32 float texture format. */
    KZC_RENDERER_TEXTURE_FORMAT_AUTOMATIC /**< Texture format is automatically detected from image format. This texture format is valid only during loading. */
};

/** Texture target type. */
enum KzcRendererTextureTargetType
{
    KZC_RENDERER_TEXTURE_TARGET_TYPE_INVALID, /**< Invalid texture target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_2D, /**< 2D texture target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_POSITIVE_X, /**< Cube map positive x target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_NEGATIVE_X, /**< Cube map negative x target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_POSITIVE_Y, /**< Cube map positive y target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_NEGATIVE_Y, /**< Cube map negative y target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_POSITIVE_Z, /**< Cube map positive z target type. */
    KZC_RENDERER_TEXTURE_TARGET_TYPE_CUBEMAP_NEGATIVE_Z /**< Cube map negative z target type. */
};

/** List of shader types. */
enum KzcRendererShaderType
{
    KZC_RENDERER_SHADER_TYPE_VERTEX, /**< Vertex shader. */
    KZC_RENDERER_SHADER_TYPE_FRAGMENT /**< Fragment shader. */
};

/** Enumeration for index buffer primitive type. */
enum KzcPrimitiveType
{
    KZC_PRIMITIVE_TYPE_POINTS,         /**< Point primitive type. */
    KZC_PRIMITIVE_TYPE_LINES,          /**< Line primitive type. */
    KZC_PRIMITIVE_TYPE_LINE_LOOP,      /**< Line loop primitive type. */
    KZC_PRIMITIVE_TYPE_LINE_STRIP,     /**< Line strip primitive type. */
    KZC_PRIMITIVE_TYPE_TRIANGLES,      /**< Triangle primitive type. */
    KZC_PRIMITIVE_TYPE_TRIANGLE_STRIP, /**< Triangle strip primitive type. */
    KZC_PRIMITIVE_TYPE_TRIANGLE_FAN    /**< Triangle fan primitive type. */
};

/** Type of vertex attribute. */
enum KzcVertexAttributeSemantic
{
    /* Fixed function attributes. */
    KZC_VERTEX_ATTRIBUTE_POSITION,              /**< Vertex attribute for position. */
    KZC_VERTEX_ATTRIBUTE_COLOR,                 /**< Vertex attribute for color. */
    KZC_VERTEX_ATTRIBUTE_NORMAL,                /**< Vertex attribute for normal. */
    KZC_VERTEX_ATTRIBUTE_TANGENT,               /**< Vertex attribute for tangent. */
    KZC_VERTEX_ATTRIBUTE_TEXTURE_COORDINATE,    /**< Vertex attribute for texture coordinate. */
    KZC_VERTEX_ATTRIBUTE_WEIGHT,                /**< Vertex attribute for weight. */
    KZC_VERTEX_ATTRIBUTE_MATRIX_INDEX,          /**< Vertex attribute for matrix indices used in skinning. */

    KZC_VERTEX_ATTRIBUTE_CUSTOM                 /**< Custom vertex attribute (can be used on programmable pipeline). */
};

/** Vertex attribute data type. */
enum KzcVertexAttributeDataType
{
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_S8,          /**< Signed 8bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_U8,          /**< Unsigned 8bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_S16,         /**< Signed 16bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_U16,         /**< Unsigned 16bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_S32,         /**< Signed 32bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_U32,         /**< Unsigned 32bit integer. */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT16,     /**< 16 bit floating point (half float). */
    KZC_VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT32      /**< 32 bit floating point. */
};

/** Vertex list format. */
enum KzcVertexListFormat
{
    KZC_VERTEX_LIST_FORMAT_LIST_OF_ARRAYS,      /**< List of arrays. A1_0,A1_1,A1_2...A2_0,A2_1,A2_2... */
    KZC_VERTEX_LIST_FORMAT_LIST_OF_ATTRIBUTES   /**< List of attributes. A1_0,A2_0,A1_1,A2_1...A1_N,A2_N. */
};

/** Supported texture compressions. */
enum KzcRendererTextureCompression
{
    KZC_RENDERER_TEXTURE_COMPRESSION_NONE, /**< No texture compression. */
    KZC_RENDERER_TEXTURE_COMPRESSION_ETC, /**< Ericsson texture compression (ETC1_RGB8_OES). */
    KZC_RENDERER_TEXTURE_COMPRESSION_DXT3_RGBA, /**< DXT3 texture compression (COMPRESSED_RGBA_S3TC_DXT3_EXT). */
    KZC_RENDERER_TEXTURE_COMPRESSION_DXT5_RGBA, /**< DXT5 texture compression (COMPRESSED_RGBA_S3TC_DXT5_EXT). */
    KZC_RENDERER_TEXTURE_COMPRESSION_ATC, /**< ATC texture compression (ATC_RGB_AMD). */
    KZC_RENDERER_TEXTURE_COMPRESSION_ATC_EXPLICIT_ALPHA, /**< ATC texture compression (ATC_RGBA_EXPLICIT_ALPHA_AMD). */
    KZC_RENDERER_TEXTURE_COMPRESSION_ATC_INTERPOLATED_ALPHA, /**< ATC texture compression (ATC_RGBA_INTERPOLATED_ALPHA_AMD). */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC1_RGB_2BPP, /**< PVRTC1 2 bpp compression */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC1_RGBA_2BPP, /**< PVRTC1 2 bpp compression */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC1_RGB_4BPP, /**< PVRTC1 4 bpp compression */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC1_RGBA_4BPP, /**< PVRTC1 4 bpp compression */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC2_RGBA_2BPP, /**< PVRTC2 2 bpp compression */
    KZC_RENDERER_TEXTURE_COMPRESSION_PVRTC2_RGBA_4BPP  /**< PVRTC2 4 bpp compression */
};
#define KZC_RENDERER_TEXTURE_COMPRESSION_COUNT 13 /**< Number of texture compression modes. */

/** Type of the FBO target */
enum KzcRendererFBOTarget
{
    KZC_RENDERER_FBO_TARGET_INVALID, /**< Invalid frame buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR2, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR3, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR4, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR5, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR6, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR7, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_COLOR8, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_DEPTH, /**< Color buffer target. */
    KZC_RENDERER_FBO_TARGET_STENCIL /**< Stencil target. */
};

/** FBO render buffer format */
enum KzcRendererFBORenderBufferFormat
{
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_INVALID, /**< Invalid render buffer format. */
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_RGBA, /**< 32 or 16 bit color buffer. */
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_DEPTH_16, /**< 16 bit depth buffer. */
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_DEPTH_24, /**< 24 bit depth buffer. */
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_DEPTH_STENCIL, /**< Combined depth and stencil buffer. */
    KZC_RENDERER_FBO_RENDER_BUFFER_FORMAT_STENCIL /**< Stencil 8bit format. */
};

/** Fixed uniform locations of the shader. */
enum KzcRendererFixedUniform
{
    KZC_RENDERER_FIXED_UNIFORM_WORLD_MATRIX = 0, /**< World matrix. */
    KZC_RENDERER_FIXED_UNIFORM_CAMERA_MATRIX,/**< Camera matrix. */
    KZC_RENDERER_FIXED_UNIFORM_CAMERA_POSITION, /**< Camera position. */
    KZC_RENDERER_FIXED_UNIFORM_VIEWPORT, /**< Viewport area. */
    KZC_RENDERER_FIXED_UNIFORM_NORMAL_MATRIX, /**< Normal matrix. */
    KZC_RENDERER_FIXED_UNIFORM_CAMERA_NORMAL_MATRIX, /**< Camera* normal matrix (screenspace normal). */
    KZC_RENDERER_FIXED_UNIFORM_PROJECTION_CAMERA_WORLD_MATRIX, /**< Projection * camera * world matrix. */
    KZC_RENDERER_FIXED_UNIFORM_PROJECTION_MATRIX, /**< Projection matrix. */
    KZC_RENDERER_FIXED_UNIFORM_CAMERA_WORLD_MATRIX, /**< Camera * world matrix. */
    KZC_RENDERER_FIXED_UNIFORM_NEAR_FAR_PLANE, /**< Vec2 containing near and far plane. */
    KZC_RENDERER_FIXED_UNIFORM_TIME, /**< Debug timer. */

    KZC_RENDERER_FIXED_UNIFORM_COUNT /**< Number of fixed uniforms. */
};

/** FrameBuffer depth bits */
enum KzcRendererFrameBufferDepthStencilFormat
{
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_DEPTH_16, /**< 16 bit frame buffer. */
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_DEPTH_24, /**< 24 bit frame buffer. */
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_DEPTH_STENCIL, /**< Depth stencil format. */
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_DEPTH_24_STENCIL_8, /**< Depth + stencil combined format. */
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_STENCIL_8, /**< Stencil 8bit format. */
    KZC_RENDERER_FRAME_BUFFER_DEPTH_STENCIL_FORMAT_NONE /**< No depth / stencil. */
};

/** Specifies uniform names of the fixed uniforms. */
extern const kzString KzcRendererFixedUniformNames[KZC_RENDERER_FIXED_UNIFORM_COUNT];


/* Vertex array types for vertex array usage. */
#define KZC_VERTEX_ARRAY_POSITION               (1 << 0)        /**< Positions for vertex array. */
#define KZC_VERTEX_ARRAY_NORMAL                 (1 << 1)        /**< Normals for vertex array. */
#define KZC_VERTEX_ARRAY_COLOR                  (1 << 2)        /**< Colors for vertex array. */
#define KZC_VERTEX_ARRAY_TEXTURE_COORDINATE     (1 << 3)        /**< UVs for vertex array. */


/** Vertex attribute enumeration for engine. */
enum KzcRendererVertexAttribute
{
    KZC_RENDERER_VERTEX_ATTRIBUTE_POSITION = 0, /**< Position. */
    KZC_RENDERER_VERTEX_ATTRIBUTE_TEXTURE_COORDINATE, /**< Texture coordinate. */
    KZC_RENDERER_VERTEX_ATTRIBUTE_NORMAL, /**< Normal. */
    KZC_RENDERER_VERTEX_ATTRIBUTE_COLOR, /**< Color. */
    KZC_RENDERER_VERTEX_ARRAY_ATTRIBUTE_COUNT /**< Number of vertex attributes. */
};

#define KZC_RENDERER_UNIFORM_BUFFER_DEFAULT "kzUniforms" /**< Default uniform buffer, that contains all the uniforms in the shader. */

/* Fixed shader attribute names. */
extern const kzString KZC_RENDERER_ATTRIBUTE_POSITION;        /**< Attribute string for vertex positions. */
extern const kzString KZC_RENDERER_ATTRIBUTE_NORMAL;          /**< Attribute string for vertex normals. */
extern const kzString KZC_RENDERER_ATTRIBUTE_TANGENT;         /**< Attribute string for vertex tangents. */
extern const kzString KZC_RENDERER_ATTRIBUTE_WEIGHT;          /**< Attribute string for vertex weight (skinning). */
extern const kzString KZC_RENDERER_ATTRIBUTE_MATRIX_PALETTE;  /**< Attribute string for matrix palette (skinning). */
extern const kzString KZC_RENDERER_ATTRIBUTE_TEXTURE_COORDINATE[];  /**< List of attribute strings for texture coordinates. */
extern const kzString KZC_RENDERER_ATTRIBUTE_COLOR[];       /**< List of attribute strings for vertex colors. */


/** Specifies single uniform buffer uniform. */
struct KzcRendererUniformBufferUniform
{
    kzInt index; /**< Index, i.e. uniform location inside block. */
    kzInt offset; /**< Offset. */
    kzMutableString name; /**< Name of the uniform. */
};

/** Structure for uniform buffer block. */
struct KzcRendererUniformBufferBlock
{
    kzBool containsBlock; /**< Returns if shader has the block. */
    kzUint uniformBlockHandle; /**< Shader default uniform block handle. */
    kzUint uniformBufferHandle; /**< Uniform buffer handle. */

    kzByte* data; /**< Byte data of the block. */
    struct KzcHashMap* uniforms; /**< Uniforms inside block, <string(uniformName), struct KzcRendererUniformBufferUniform(data)>. */
};


/* Forward declaration structures. */
struct KzuScreen;
struct KzcMemoryManager;
struct KzcHashMap;
struct KzcVector2;
struct KzcVector3;
struct KzcVector4;
struct KzcMatrix2x2;
struct KzcMatrix3x3;
struct KzcMatrix4x4;
struct KzsSurface;


/**
 * \struct KzcRenderer
 * Structure for core layer renderer, that is a low level wrapper for GPU with state tracking and caching.
 */
struct KzcRenderer;


/** Creates a new renderer object. */
kzsError kzcRendererCreate(const struct KzcMemoryManager* memoryManager, struct KzcRenderer** out_renderer);
/** Deletes a renderer object. */
kzsError kzcRendererDelete(struct KzcRenderer* renderer);
/** Resets frame for core renderer, that is, counters for logging rendering infos (triangle count etc.). */
kzsError kzcRendererResetFrame(struct KzcRenderer* renderer);
/** Resets renderer, e.g. resets its caches and states and syncs renderer variables with actual GL states. */
kzsError kzcRendererReset(struct KzcRenderer* renderer);
/** Initializes renderer object. Requires graphics context. */
kzsError kzcRendererInitialize(struct KzcRenderer* renderer, kzUint vertexBufferPoolSize, kzUint indexBufferPoolSize);
/** Uninitializes renderer object. */
kzsError kzcRendererUninitialize(struct KzcRenderer* renderer);

/** Sets active surface context for renderer. */
void kzcRendererSetActiveSurface(struct KzcRenderer* renderer, struct KzsSurface* surface);
/** Gets active surface context from renderer. */
struct KzsSurface* kzcRendererGetActiveSurface(const struct KzcRenderer* renderer);

/** Enables a specific renderer state. */
void kzcRendererEnableState(struct KzcRenderer* renderer, enum KzcRendererState state);
/** Disables a specific renderer state. */
void kzcRendererDisableState(struct KzcRenderer* renderer, enum KzcRendererState state);
/** Enables or disables the state of a specific renderer state. */
void kzcRendererSetState(struct KzcRenderer* renderer, enum KzcRendererState state, kzBool enable);
/** Returns state of a specific renderer state. */
kzBool kzcRendererGetState(const struct KzcRenderer* renderer, enum KzcRendererState state);

/** Clears a context using specified flags. */
void kzcRendererClear(struct KzcRenderer* renderer);
/** Resets a clear target for renderer. */
void kzcRendererResetClearTarget(struct KzcRenderer* renderer);
/** Sets a clearing target for renderer. */
void kzcRendererAddClearTarget(struct KzcRenderer* renderer, enum KzcRendererClearTarget target);
/** Removes a clearing target for renderer. */
void kzcRendererRemoveClearTarget(struct KzcRenderer* renderer, enum KzcRendererClearTarget target);
/** Sees if renderer has specific clear target. */
kzBool kzcRendererHasClearTarget(const struct KzcRenderer* renderer, enum KzcRendererClearTarget target);
/** See if clear is enabled. */
kzBool kzcRendererIsClearEnabled(const struct KzcRenderer* renderer);
/** Set clear color for renderer. */
void kzcRendererSetClearColor(struct KzcRenderer* renderer, struct KzcColorRGBA colorRGBA);
/** Set a color write mode for renderer. */
void kzcRendererSetColorWriteMode(struct KzcRenderer* renderer, enum KzcRendererColorWriteMode colorWriteMode);
/** Gets current color write mode from renderer. */
enum KzcRendererColorWriteMode kzcRendererGetColorWriteMode(const struct KzcRenderer* renderer);
/** Sets scissor test for renderer. */
void kzcRendererSetScissorTest(struct KzcRenderer* renderer, kzBool enabled, kzInt x, kzInt y, kzInt width, kzInt height);
/** Gets scissor specific values from renderer. KZ_NULL if not requiring some specific value. */
void kzcRendererGetScissorTest(const struct KzcRenderer* renderer, kzInt* out_x, kzInt* out_y, kzInt* out_width, kzInt* out_height);


/** Set clear depth for renderer. */
void kzcRendererSetClearDepthValue(struct KzcRenderer* renderer, kzFloat clearDepthValue);
/** Set clear stencil for renderer. */
void kzcRendererSetClearStencil(struct KzcRenderer* renderer, kzInt stencilClearValue);


/** Sets an active view port for renderer. */
void kzcRendererSetViewport(struct KzcRenderer* renderer, kzInt x, kzInt y, kzInt width, kzInt height);


/** Sets a vertex buffer for renderer. */
void kzcRendererSetVertexBuffer(struct KzcRenderer* renderer, kzUint value);
/** Sets an index buffer for renderer. */
void kzcRendererSetIndexBuffer(struct KzcRenderer* renderer, kzUint value);
/** Render buffers that are currently bound. */
void kzcRendererDrawBuffers(struct KzcRenderer* renderer);
/** Sets vertex count for renderer. */
void kzcRendererSetVertexCount(struct KzcRenderer* renderer, kzUint vertexCount);
/** Sets the index count for renderer. */
void kzcRendererSetIndexCount(struct KzcRenderer* renderer, kzUint indexCount);
/** Sets index data for renderer. */
void kzcRendererSetIndexData(struct KzcRenderer* renderer, void* indexData);
/** Sets the index type for renderer. */
void kzcRendererSetIndexType(struct KzcRenderer* renderer, enum KzcPrimitiveType indexType);


/** Finds uniform location for given uniform from active shader. The data will be stored to uniform cache and fetched from in subsequent calls. */
kzsError kzcRendererGetUniformLocation(const struct KzcRenderer* renderer, kzString uniformName, kzInt* out_uniformLocation);
/** Returns array uniform length for given uniform. If uniform with given name is not found, returns 0. If uniform is not an array, returns 1. */
kzsError kzcRendererGetUniformArrayLength(const struct KzcRenderer* renderer, kzString uniformName, kzUint* out_arrayLength);
/** Sets integer uniform for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformInteger(struct KzcRenderer* renderer, kzInt value, kzInt uniformLocation);
/** Sets float uniform for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformFloat(struct KzcRenderer* renderer, kzFloat value, kzInt uniformLocation);
/** Sets uniform float array for renderer. */
kzsError kzcRendererSetUniformFloatArray(struct KzcRenderer* renderer, kzInt uniformLocation, kzUint count, const kzFloat* value);
/** Sets uniform vec2 for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformVec2(struct KzcRenderer* renderer, const struct KzcVector2* value, kzInt uniformLocation);
/** Sets uniform vec3 for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformVec3(struct KzcRenderer* renderer, const struct KzcVector3* value, kzInt uniformLocation);
/** Sets uniform vec3 array for renderer. */
kzsError kzcRendererSetUniformVec3Array(struct KzcRenderer* renderer, kzInt uniformLocation, kzUint count, const struct KzcVector3* value);
/** Sets uniform vec4 for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformVec4(struct KzcRenderer* renderer, const struct KzcVector4* value, kzInt uniformLocation);
/** Sets arbitrary vector array with dimension to renderer, using currently bound shader. */
kzsError kzcRendererSetUniformVecArray(struct KzcRenderer* renderer, kzInt uniformLocation, kzUint count, kzUint dimension, const kzFloat* values);
/** Sets uniform colorRGBA for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformColorRGBA(struct KzcRenderer* renderer, const struct KzcColorRGBA* value, kzInt uniformLocation);
/** Sets uniform vec4 array for renderer. */
kzsError kzcRendererSetUniformVec4Array(struct KzcRenderer* renderer, kzInt uniformLocation, kzUint count, const struct KzcVector4* value);
/** Sets matrix2x2 uniform for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformMatrix2x2(struct KzcRenderer* renderer, const struct KzcMatrix2x2* value, kzInt uniformLocation);
/** Sets matrix3x3 uniform for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformMatrix3x3(struct KzcRenderer* renderer, const struct KzcMatrix3x3* value, kzInt uniformLocation);
/** Sets matrix4x4 uniform for renderer, using currently bound shader. */
kzsError kzcRendererSetUniformMatrix4x4(struct KzcRenderer* renderer, const struct KzcMatrix4x4* value, kzInt uniformLocation);


/** Switches an scalar value for renderer if necessary, e.g. depth clear value. */
void kzcRendererSetActiveScalar(struct KzcRenderer* renderer, enum KzcRendererScalar scalar, kzFloat value);
/** Returns a current scalar value from renderer. */
kzFloat kzcRendererGetActiveScalar(const struct KzcRenderer* renderer, enum KzcRendererScalar scalar);


/** Sets a blend mode for renderer. */
void kzcRendererSetBlendMode(struct KzcRenderer* renderer, enum KzcRendererBlendMode blendMode);
/** Gets a blend mode for renderer. */
enum KzcRendererBlendMode kzcRendererGetBlendMode(const struct KzcRenderer* renderer);
/** Sets a cull mode for renderer. */
void kzcRendererSetCullMode(struct KzcRenderer* renderer, enum KzcRendererCullMode cullMode);
/** Gets a cull mode for renderer. */
enum KzcRendererCullMode kzcRendererGetCullMode(const struct KzcRenderer* renderer);
/** Sets a depth pass mode for renderer. */
void kzcRendererSetDepthTest(struct KzcRenderer* renderer, enum KzcRendererDepthTest depthMode);
/** Gets a depth pass mode for renderer. */
enum KzcRendererDepthTest kzcRendererGetDepthTest(const struct KzcRenderer* renderer);
/** Sets a stencil function for renderer. */
void kzcRendererSetStencilFunction(struct KzcRenderer* renderer, enum KzcRendererStencilFunction stencilFunction,
                                   kzUint referenceValue, kzUint maskValue);
/** Sets a stencil operation for renderer. */
void kzcRendererSetStencilOperation(struct KzcRenderer* renderer, enum KzcRendererStencilOperation stencilFailOperation,
                                    enum KzcRendererStencilOperation stencilPassDepthFailOperation,
                                    enum KzcRendererStencilOperation stencilPassDepthPassOperation);
/** Gets stencil function from renderer. */
void kzcRendererGetStencilFunction(const struct KzcRenderer* renderer, enum KzcRendererStencilFunction* out_stencilFunction,
                                   kzUint* out_referenceValue, kzUint* out_maskValue);
/** Gets a stencil operation from renderer. */
void kzcRendererGetStencilOperation(const struct KzcRenderer* renderer, enum KzcRendererStencilOperation* out_stencilFailOperation,
                                    enum KzcRendererStencilOperation* out_stencilPassDepthFailOperation,
                                    enum KzcRendererStencilOperation* out_stencilPassDepthPassOperation);


/** Sets matrix for a renderer. */
void kzcRendererSetMatrix(struct KzcRenderer* renderer, enum KzcRendererMatrix matrixType, const struct KzcMatrix4x4* matrix);
/** Gets a matrix from renderer. */
struct KzcMatrix4x4 kzcRendererGetMatrix(const struct KzcRenderer* renderer, enum KzcRendererMatrix matrixType);
/** Calculates projection * camera * world matrix. */
void kzcRendererCalculateProjectionCameraWorldMatrix(struct KzcRenderer* renderer);
/** Applies transformations from renderer to GPU. */
kzsError kzcRendererApplyTransformation(struct KzcRenderer* renderer);


/** Sets texture unit active. */
kzsError kzcRendererSetActiveTextureUnit(struct KzcRenderer* renderer, kzUint textureUnit);
/** Gets texture uniform locations from renderer. */
kzsError kzcRendererGetTextureSizeUniformLocations(const struct KzcRenderer* renderer, kzInt* out_textureWidthUniformLocation, kzInt* out_textureHeightUniformLocation);
/** Applies texture uniforms for the renderer. */
kzsError kzcRendererApplyTextureSizeUniforms(struct KzcRenderer* renderer, kzInt textureWidthUniformLocation, kzInt textureHeightUniformLocation, kzUint textureWidth, kzUint textureHeight);
/** Applies texture for renderer using currently bound shader (required) and texture uniform (required). */
kzsError kzcRendererApplyTexture(struct KzcRenderer* renderer, kzInt textureUniformLocation, kzUint textureHandle, enum KzcRendererTextureType textureType);
/** Sets texture uniform location for renderer, effectively used for storing the integer in renderer to retrieve it when binding textures. */
void kzcRendererSetUniformTexture(struct KzcRenderer* renderer, kzInt uniformLocation);
/** Gets texture uniform location from renderer. */
kzInt kzcRendererGetUniformTexture(const struct KzcRenderer* renderer);



/** Detaches texture handle from all texture units it has been applied for. */
kzsError kzcRendererDetachTextureHandle(struct KzcRenderer* renderer, kzUint textureHandle);
/** Detaches texture from rendering. */
void kzcRendererDetachTexture(struct KzcRenderer* renderer);

/** Invalidates texture handle from renderer without affecting GL state. */
kzsError kzcRendererInvalidateTextureHandle(struct KzcRenderer* renderer, kzUint textureHandle);

/** Binds texture for renderer. */
void kzcRendererBindTexture(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType, kzUint textureHandle);
/** Generates new texture for renderer. */
kzsError kzcRendererGenerateTexture(struct KzcRenderer* renderer, kzUint* out_textureHandle);
/** Uploads texture data to GPU. */
void kzcRendererSetTextureImage2D(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType, kzUint mipmapLevel,
                                  enum KzcRendererTextureFormat textureFormat, kzUint width, kzUint height, const void* data);
/** Uploads texture subimage data to GPU. */
void kzcRendererSetTextureSubImage2D(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType, kzUint mipmapLevel,
                                     enum KzcRendererTextureFormat textureFormat, kzUint x, kzUint y, kzUint width, kzUint height, const void* data);
/** Uploads compressed texture data to GPU. */
kzsError kzcRendererSetCompressedTextureImage2D(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType,
                                                kzUint mipmapLevel, enum KzcRendererTextureCompression compression,
                                                kzUint width, kzUint height, const void* data);
/** Deletes texture via renderer. */
kzsError kzcRendererDeleteTexture(struct KzcRenderer* renderer, kzUint textureHandle);
/** Sets wrap mode for currently bound texture in current texture unit. */
void kzcRendererSetTextureWrapMode(struct KzcRenderer* renderer,enum KzcRendererTextureType textureType, enum KzcRendererTextureWrapMode wrapMode);
/**
 * Sets texture filter for currently bound texture in current texture unit.
 *
 * @param anisotropy Set anisotropic filtering level of texture. Values <= 1.0f disable the feature.
 */
void kzcRendererSetTextureFilter(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType, enum KzcRendererTextureFilter filter,
                                 kzFloat anisotropy);
/** Sets pack storage for renderer. Specifies how the pixel data is aligned. */
void kzcRendererSetPixelStorePack(struct KzcRenderer* renderer, kzUint packBytes);
/** Sets unpack storage for renderer. Specifies how the pixel data is aligned. */
void kzcRendererSetPixelStoreUnpack(struct KzcRenderer* renderer, kzUint unpackBytes);

/** Creates shader. */
kzsError kzcRendererCreateShader(const struct KzcRenderer* renderer, enum KzcRendererShaderType type, kzUint* out_shaderHandle);
/** Creates shader program. Returns the handle to the program. */
kzsError kzcRendererCreateShaderProgram(struct KzcRenderer* renderer, kzUint* out_programHandle);
/** Refreshes render context to contain all proper states. */
void kzcRendererRefreshRenderContext(struct KzcRenderer* renderer, kzBool geometryRendering);
/** Attaches shader to program. */
kzsError kzcRendererAttachShaderToProgram(struct KzcRenderer* renderer, kzUint programHandle, kzUint shaderHandle);
/** Binds attribute to given location index, for example "kzPosition" to 0. */
kzsError kzcRendererBindAttributeToLocation(struct KzcRenderer* renderer, kzUint programHandle, kzUint locationIndex, kzString attributeName);
/** Links shader program with given handle. */
kzsError kzcRendererLinkShader(struct KzcRenderer* renderer, const struct KzcMemoryManager* memoryManager, kzUint programHandle, kzString shaderName, kzBool* out_success);
/** Compiles source shader and deploys it to GPU. */
kzsError kzcRendererCompileSourceShader(struct KzcRenderer* renderer, const struct KzcMemoryManager* memoryManager,
                                        enum KzcRendererShaderType shaderType, kzUint shaderHandle, kzString shaderCode,
                                        kzString shaderName, kzBool* out_compileSuccess);
/** Deploys binary shaders. */
kzsError kzcRendererDeployBinaryShader(struct KzcRenderer* renderer, kzUint count, const kzUint* shaders, kzUint formatConstant, const void* data, kzUint dataSize);
/** Loads a program binary. Uses a different OpenGL extension depending on the platform. */
kzsError kzcRendererProgramBinary(struct KzcRenderer* renderer, const struct KzcMemoryManager* memoryManager, kzUint program, kzUint formatConstant, const void* data, kzInt dataSize, kzBool* out_success);
/** Deletes shader. */
kzsError kzcRendererDeleteShader(struct KzcRenderer* renderer, kzUint programHandle, kzUint vertexShaderHandle, kzUint fragmentShaderHandle);
/** Helper function for removing fixed uniform mapping for given shader handle. */
kzsError kzcRendererDeleteFixedUniformMapping(const struct KzcRenderer* renderer, kzUint handle);
/** Returns fixed shader uniform location of given fixed uniform. */
kzInt kzcRendererGetFixedShaderUniformLocation(const struct KzcRenderer* renderer, enum KzcRendererFixedUniform fixedUniform);

/** Generates new texture for renderer. */
kzsError kzcRendererGenerateFrameBuffer(const struct KzcRenderer* renderer, kzUint* out_framebufferHandle);
/** Deletes framebuffer. */
kzsError kzcRendererDeleteFrameBuffer(struct KzcRenderer* renderer, kzUint frameBufferHandle);
/** Binds framebuffer. */
void kzcRendererBindFrameBuffer(struct KzcRenderer* renderer, kzUint frameBufferHandle);
/** Checks if the framebuffer is complete. */
kzBool kzcRendererIsFrameBufferComplete(struct KzcRenderer* renderer);
/** Check framebuffer completeness and log possible errors . */
kzsException kzcRendererFrameBufferCheckErrors(struct KzcRenderer* renderer);
/** Attaches texture to frame buffer. */
kzsError kzcRendererFrameBufferTexture2D(struct KzcRenderer* renderer, enum KzcRendererTextureTargetType textureTarget,
                                         enum KzcRendererFBOTarget frameBufferTarget, kzUint textureHandle, kzUint mipmapLevel);
/** Gets compressed texture data size in bytes. */
kzUint kzcRendererGetCompressedTextureDataSizeBytes(kzUint width, kzUint height, enum KzcRendererTextureCompression compressionFormat);
/** Attaches renderbuffer to framebuffer. */
kzsError kzcRendererFrameBufferRenderBuffer(struct KzcRenderer* renderer, enum KzcRendererFBOTarget frameBufferTarget, kzUint renderBufferHandle);
/** Generates new texture for renderer. */
kzsError kzcRendererGenerateRenderBuffer(const struct KzcRenderer* renderer, kzUint* out_renderbufferHandle);
/** Deletes framebuffer. */
kzsError kzcRendererDeleteRenderBuffer(const struct KzcRenderer* renderer, kzUint renderBufferHandle);
/** Binds framebuffer. */
void kzcRendererBindRenderBuffer(struct KzcRenderer* renderer, kzUint renderBufferHandle);

/** Sets storage for render buffer. */
kzsException kzcRendererRenderBufferStorage(const struct KzcRenderer* renderer, enum KzcRendererFBORenderBufferFormat format, kzUint width, kzUint height, kzUint multisamples);

#if KZ_OPENGL_VERSION == KZ_OPENGL_LATEST
/** Blits framebuffer to depth and color. */
void kzcRendererBlitFramebuffer(struct KzcRenderer* renderer, kzUint readBufferHandle, kzUint drawBufferHandle, kzUint sourceX, kzUint sourceY, kzUint sourceWidth, kzUint sourceHeight,
                                kzUint destX, kzUint destY, kzUint destWidth, kzUint destHeight);
/** Draws framebuffer to number of targets. */
void kzcRendererDrawFrameBuffers(struct KzcRenderer* renderer, kzUint targetCount);
#endif

/** Generates new index or vertex buffer or uniform buffer handle.*/
kzsError kzcRendererGenerateBuffer(const struct KzcRenderer* renderer, kzUint* out_handle);
/** Sets static vertex buffer data. */
void kzcRendererSetVertexBufferData(struct KzcRenderer* renderer, kzUint dataSize, const void* data);
/** Sets static index buffer data. */
void kzcRendererSetIndexBufferData(struct KzcRenderer* renderer, kzUint dataSize, const void* data);
/** Uploads vertex buffer subdata with given offset and size. */
void kzcRendererSetVertexBufferSubData(struct KzcRenderer* renderer, kzUint offset, kzUint size, const void* data);
/** Uploads index buffer subdata with given offset and size. */
void kzcRendererSetIndexBufferSubData(struct KzcRenderer* renderer, kzUint offset, kzUint size, const void* data);
/** Deletes vertex or index buffer. */
kzsError kzcRendererDeleteBuffer(struct KzcRenderer* renderer, kzUint handle);
/** Enables vertex attribute array. */
kzsError kzcRendererEnableVertexAttributeArray(struct KzcRenderer* renderer, kzUint attributeHandle);
/** Disables vertex attribute array. */
kzsError kzcRendererDisableVertexAttributeArray(struct KzcRenderer* renderer, kzUint attributeHandle);
/** Sets vertex buffer object pointer for currently enabled vertex attribute array. */
void kzcRendererSetVertexBufferPointer(struct KzcRenderer* renderer, kzUint attributeHandle, kzUint dimension, enum KzcVertexAttributeDataType attributeDataType, kzUint stride, const void* pointer);


/** Sets active shader for renderer. */
kzsError kzcRendererSetActiveShaderHandle(struct KzcRenderer* renderer, kzUint activeShaderHandle);
/** Gets active shader handle from renderer. */
kzUint kzcRendererGetActiveShaderHandle(const struct KzcRenderer* coreRenderer);
/** Sets active vertex attribute map for renderer. */
void kzcRendererSetActiveVertexAttributeMap(struct KzcRenderer* renderer, struct KzcHashMap* vertexAttributeMap);
/** Gets active vertex attribute map from renderer. */
struct KzcHashMap* kzcRendererGetActiveShaderAttributeMap(const struct KzcRenderer* renderer);


/** Specifies default frame buffer (screen) for renderer. */
void kzcRendererSetDefaultFrameBuffer(struct KzcRenderer* renderer, kzUint frameBufferHandle);
/** Sets active frame buffer for renderer. */
void kzcRendererSetActiveFrameBuffer(struct KzcRenderer* renderer, kzUint frameBufferHandle);
/** Resets active frame buffer for renderer to default (screen). */
void kzcRendererResetActiveFrameBuffer(struct KzcRenderer* renderer);
/** Callback prototype for setActiveFrameBuffer. */
typedef void (*KzcRendererFrameBufferCallback)(kzUint frameBufferHandle);
/** Sets callback function that is called after setActiveFrameBuffer. */
void kzcRendererSetActiveFrameBufferCallback(struct KzcRenderer* renderer, KzcRendererFrameBufferCallback callbackFunction);
/** Gets active frame buffer handle from. */
kzUint kzcRendererGetActiveFrameBuffer(const struct KzcRenderer* renderer);

/** Reads the pixels from the current frame buffer. */
void kzcRendererReadPixels(struct KzcRenderer* renderer, kzInt x, kzInt y, kzInt width, kzInt height,
                           enum KzcRendererColorFormat format, void* pixels);
/** Returns native pixel read format from renderer. */
enum KzcRendererColorFormat kzcRendererGetNativePixelReadFormat(struct KzcRenderer* renderer);

/** Begins a material for renderer. */
void kzcRendererBeginMaterialSetup(struct KzcRenderer* renderer);
/** Ends a material for renderer. */
kzsError kzcRendererEndMaterialSetup(struct KzcRenderer* renderer);

/** 
* Begins set of vertex arrays.
* \param renderer Core renderer object.
* \param vertexArrayFlags Set of vertex arrays to be applied. Options: KZC_VERTEX_ARRAY_POSITION, KZC_VERTEX_ARRAY_NORMAL,
* KZC_VERTEX_ARRAY_TEXTURE_COORDINATE and KZC_VERTEX_ARRAY_COLOR.
*/
void kzcRendererBeginVertexArray(struct KzcRenderer* renderer, kzUint vertexArrayFlags);
/** Sets vertex array data. */
void kzcRendererSetVertexArrayData(struct KzcRenderer* renderer, kzUint vertexArrayFlag, const void* data);
/** Ends vertex array. Renders the specified vertex lists and finishes the usage. */
kzsError kzcRendererEndVertexArray(struct KzcRenderer* renderer, enum KzcPrimitiveType primitiveType, kzUint count);

/** Gets current vertex array data from renderer. Reset when switching the shader. */
const void* kzcRendererGetCurrentVertexArrayAttributeData(const struct KzcRenderer* renderer, enum KzcRendererVertexAttribute attribute);

/** Prints info about renderer capabilities. */
kzsError kzcRendererPrintInfo(const struct KzcRenderer* renderer);


/** Sets line rendering width for renderer. */
void kzcRendererSetLineWidth(struct KzcRenderer* renderer, kzFloat lineWidth);

/** Gets view port from renderer. If out_x, out_y, out_width or out_height are specified as KZ_NULL, they're not used. */
void kzcRendererGetViewport(const struct KzcRenderer* renderer, kzFloat* out_x, kzFloat* out_y, kzFloat* out_width, kzFloat* out_height);

/** Flushes the GPU pipeline, forces all commands to be executed in finite time. */
void kzcRendererFlush(const struct KzcRenderer* renderer);

/** Sets debug logging state for renderer. */
void kzcRendererSetCollectingStatisticsEnabled(struct KzcRenderer* renderer, kzBool collectingStatisticsEnabled);
/** Gets triangle count from renderer. */
kzUint kzcRendererGetTriangleCount(const struct KzcRenderer* renderer);
/** Gets shader switches. */
kzUint kzcRendererGetShaderSwitchCount(const struct KzcRenderer* renderer);
/** Gets uniform sending count from renderer. */
kzUint kzcRendererGetUniformSendCount(const struct KzcRenderer* renderer);
/** Gets number of texture switches from renderer. */
kzUint kzcRendererGetTextureSwitchCount(const struct KzcRenderer* renderer);
/** Gets number of framebuffer switches from renderer. */
kzUint kzcRendererGetFrameBufferSwitchCount(const struct KzcRenderer* renderer);
/** Gets number of buffer switches (VBO + IBO) from renderer. */
kzUint kzcRendererGetBufferSwitchCount(const struct KzcRenderer* renderer);
/** Gets batch count from renderer (number of draw calls, such as drawElements and drawArrays). */
kzUint kzcRendererGetBatchCount(const struct KzcRenderer* renderer);
/** Returns potential heavyweight calls such as buffer or texture updates and glFinish from renderer. Potential due to GPU implementation may decide when heavyweight occurs (e.g. reading cannot be performed before write operation finishes). */
kzUint kzcRendererGetHeavyweightCallCount(const struct KzcRenderer* renderer);

/** Sets binary shader format identifier for renderer. This is used to detect corresponding binary shader from list of compiled binaries. KZ_NULL to none, i.e. using platform-specific string. 
 * \param binaryFormatIdentifier GPU identifier of the binary shader (GL constant for glShaderBinary function).
 */
kzsError kzcRendererSetBinaryShaderFormatIdentifier(struct KzcRenderer* renderer, kzString binaryShaderID, kzUint binaryFormatGPUConstant);
/** Gets binary shader format identifier from renderer. KZ_NULL if nothing is set. */
kzString kzcRendererGetBinaryShaderFormatIdentifier(const struct KzcRenderer* renderer);
/** Gets the GPU identifier of the binary shader format. */
kzUint kzcRendererGetBinaryShaderGPUFormatIdentifier(const struct KzcRenderer* renderer);

/** Sets the usage of the GL_OES_get_program_binary extension when loading binary shaders. */
void kzcRendererSetProgramBinaryExtensionEnabled(struct KzcRenderer* renderer, kzBool enabled);
/** Checks if the use of GL_OES_get_program_binary extension is enabled. */
kzBool kzcRendererProgramBinaryExtensionIsEnabled(const struct KzcRenderer* renderer);

/** Sets GPU calls enabled / disabled. */
void kzcRendererSetGPUCallsEnabled(struct KzcRenderer* renderer, kzBool enabled);
/** Checks if GPU calls are enabled. */
kzBool kzcRendererGPUCallsIsEnabled(const struct KzcRenderer* renderer);


/** Prints raw list of extensions supported. */
kzsError kzcRendererPrintExtensionInfo(const struct KzcRenderer* renderer);
/** Checks if combined depth+stencil render buffer format is supported. */
kzBool kzcRendererIsDepthStencilSupported(struct KzcRenderer* renderer);
/** Is coverage buffer supported or not. */
kzBool kzcRendererIsCoverageBufferSupported(struct KzcRenderer* renderer);
/** Is half float supported. */
kzBool kzcRendererIsHalfFloatSupported(struct KzcRenderer* renderer);
/** Is frame buffer supported. */
kzBool kzcRendererIsFrameBufferSupported(struct KzcRenderer* renderer);
/** Is frame buffer depth 24 supported. */
kzBool kzcRendererIsFrameBufferDepth24Supported(struct KzcRenderer* renderer);
/** Returns if uniform buffer is supported. */
kzBool kzcRendererIsUniformBufferSupported(struct KzcRenderer* renderer);
/** Returns if external texture extension is supported. */
kzBool kzcRendererIsExternalTextureSupported(struct KzcRenderer* renderer);
/** Returns if map buffer range extension is supported. */
kzBool kzcRendererIsMapBufferRangeSupported(struct KzcRenderer* renderer);

/** Gets location of the uniform buffer. */
kzBool kzcRendererGetUniformBufferBlockLocation(struct KzcRenderer* renderer, kzUint shaderHandle, kzString uniformBufferBlock, kzUint* out_location);
/** Binds uniform block to buffer. */
kzInt kzcRendererBindUniformBlockToBuffer(struct KzcRenderer* renderer, kzString uniformBufferBlock);
/** Sets dynamic uniform buffer data. */
void kzcRendererSetUniformBufferData(struct KzcRenderer* renderer, kzUint dataSize, const void* data);
/** Sets a uniform buffer for renderer. */
void kzcRendererSetUniformBuffer(struct KzcRenderer* renderer, kzUint value);

/** Gets specific uniform block uniform count. */
kzUint kzcRendererGetUniformBlockUniformCount(struct KzcRenderer* renderer, kzUint shaderHandle, kzUint uniformBufferBlock);
/** Gets specific uniform block size. */
kzUint kzcRendererGetUniformBlockSize(struct KzcRenderer* renderer, kzUint shaderHandle, kzUint uniformBufferBlock);
/** Gets uniform names, locations and offsets from given shader and uniform block. */
kzsError kzcRendererGetUniformIndices(struct KzcRenderer* renderer, kzUint shaderHandle, kzUint uniformBufferBlock, kzUint uniformCount, kzMutableString** out_uniformNames,
                                      kzInt** out_uniformLocations, kzInt** out_uniformOffsets);
/** Binds uniform buffer base to binding point. */
void kzcRendererBindBufferBase(struct KzcRenderer* renderer, kzUint uniformBufferHandle, kzUint bindingPoint);
/** Uploads sub data for uniform buffer. */
void kzcRendererSetUniformBufferSubData(struct KzcRenderer* renderer, kzUint offset, kzUint dataSize, const void* data);

/** Creates image object, returns KZ_NULL if no hardware support. Image object can be bound as texture input. 
    Requires surface to be set for renderer via kzcRendererSetSurface, otherwise throws an error. */
kzsError kzcRendererCreateImageObject(struct KzcRenderer* renderer, void* dataPointer, kzInt target, kzInt* attributes, void** out_imageObject);
/** Deletes image object created with kzcRendererCreateImageObject. */
kzsError kzcRendererDeleteImageObject(struct KzcRenderer* renderer, void* imageObject);
/** Sets image object bound to currently bound texture (type). */
kzsError kzcRendererSetImageTargetTexture(struct KzcRenderer* renderer, enum KzcRendererTextureType textureType, void* imageObject);


/** Begins active uniform block uniform deployment. */
void kzcRendererBeginActiveUniformBlockUniform(struct KzcRenderer* renderer, kzByte* data, kzInt offset, kzUint uniformBlockUniformBufferHandle);
/** Ends active uniform block uniform deployment. */
void kzcRendererEndActiveUniformBlockUniform(struct KzcRenderer* renderer);
/** Initializes a new uniform block. */
kzsError kzcRendererInitializeUniformBufferBlock(struct KzcRenderer* renderer, const struct KzcMemoryManager* memoryManager, kzUint programHandle, kzString blockName);
/** Gets uniform buffer location from renderer. */
kzBool kzcRendererGetUniformBufferLocation(struct KzcRenderer* coreRenderer, kzUint programHandle, kzString uniformName, kzInt* out_offset, kzByte** out_data, kzUint* out_uniformBufferHandle);

/** Returns if specific texture compression format is supported. */
kzBool kzcRendererIsCompressionFormatSupported(struct KzcRenderer* renderer, enum KzcRendererTextureCompression compression);

/** Gets maximum anisotropy. */
kzFloat kzcRendererGetMaximumAnisotropy(struct KzcRenderer* renderer);
/** Gets maximum texture side size. */
kzUint kzcRendererGetMaximumTextureSize(struct KzcRenderer* renderer);
/** Gets maximum cubemap side size. */
kzUint kzcRendererGetMaximumCubemapSize(struct KzcRenderer* renderer);
/** Returns number of stencil buffer bits in main GL context. */
kzUint kzcRendererGetStencilBufferBits(struct KzcRenderer* renderer);
/** Returns GL constant for the color read format used in reading back data form framebuffer (kzcRendererReadPixels). */
kzInt kzcRendererGetColorReadFormat(struct KzcRenderer* renderer);
/** Returns GL constant for the color read type used in reading back data form framebuffer (kzcRendererReadPixels). */
kzInt kzcRendererGetColorReadType(struct KzcRenderer* renderer);


/** Invalidates all handles from renderer without affecting GL state. */
kzsError kzcRendererInvalidateAllocations(struct KzcRenderer* renderer);
/** Gets GPU buffer manager from renderer. */
struct KzcGPUBufferManager* kzcRendererGetGPUBufferManager(const struct KzcRenderer* renderer);


KZ_HEADER_END



#endif
