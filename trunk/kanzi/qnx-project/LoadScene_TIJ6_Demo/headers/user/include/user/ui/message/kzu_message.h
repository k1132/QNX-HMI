/**
* \file
* Message object.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_H
#define KZU_MESSAGE_H


#include <user/properties/kzu_property_common.h>

#include <core/util/math/kzc_vector2.h>
#include <core/util/math/kzc_vector3.h>
#include <core/util/math/kzc_vector4.h>
#include <core/util/math/kzc_matrix2x2.h>
#include <core/util/math/kzc_matrix3x3.h>
#include <core/util/math/kzc_matrix4x4.h>
#include <core/util/color/kzc_color.h>
#include <core/util/string/kzc_string.h>

#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations. */
struct KzuMessageDispatcher;
struct KzuMessageType;
struct KzuVariant;
struct KzuObjectNode;
struct KzcMemoryManager;
struct KzuPropertyType;


/**
 * \struct KzuMessage
 * Message object.
 */
struct KzuMessage;


/** Gets the relative timestamp of a message. */
kzUint kzuMessageGetTimestamp(const struct KzuMessage* message);

/** Returns the dispatcher of a message. */
struct KzuMessageDispatcher* kzuMessageGetDispatcher(const struct KzuMessage* message);

/** Returns the type of a message. */
const struct KzuMessageType* kzuMessageGetType(const struct KzuMessage* message);

/** Get the source of the message. */
struct KzuObjectNode* kzuMessageGetSource(const struct KzuMessage* message);

/** Sets the handled state of a message. */
void kzuMessageSetHandled(struct KzuMessage* message, kzBool handled);

/** Gets the handled state of a message. */
kzBool kzuMessageIsHandled(const struct KzuMessage* message);

/** Sets the valid state of a message. */
void kzuMessageSetValid(struct KzuMessage* message, kzBool valid);

/** Gets the valid state of the message. The message becomes invalid after sending or if the source of the message is destroyed. */
kzBool kzuMessageIsValid(const struct KzuMessage* message);

/** Get an argument as a variant. Writes KZ_TRUE to out_found if the argument is found, KZ_FALSE otherwise. */
kzsError kzuMessageGetArgumentAsVariant(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, enum KzuPropertyField field, struct KzuVariant* variant, kzBool* out_found);
/** Sets a variant argument. */
kzsError kzuMessageSetVariantArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, enum KzuPropertyField field, const struct KzuVariant* variant);

/** Gets a float argument and returns the default value from the type if the argument is not found. */
kzFloat kzuMessageGetFloatArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a float argument. */
kzsError kzuMessageSetFloatArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, kzFloat value);

/** Gets a int argument and returns the default value from the type if the argument is not found. */
kzInt kzuMessageGetIntArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a int argument. */
kzsError kzuMessageSetIntArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, kzInt value);

/** Gets a bool argument and returns the default value from the type if the argument is not found. */
kzBool kzuMessageGetBoolArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a bool argument. */
kzsError kzuMessageSetBoolArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, kzBool value);

/** Gets a color argument and returns the default value from the type if the argument is not found. */
struct KzcColorRGBA kzuMessageGetColorArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a color argument. */
kzsError kzuMessageSetColorArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcColorRGBA value);

/** Gets a vector2 argument and returns the default value from the type if the argument is not found. */
struct KzcVector2 kzuMessageGetVector2ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a vector2 argument. */
kzsError kzuMessageSetVector2Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcVector2 value);

/** Gets a vector3 argument and returns the default value from the type if the argument is not found. */
struct KzcVector3 kzuMessageGetVector3ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a vector3 argument. */
kzsError kzuMessageSetVector3Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcVector3 value);

/** Gets a vector4 argument and returns the default value from the type if the argument is not found. */
struct KzcVector4 kzuMessageGetVector4ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a vector4 argument. */
kzsError kzuMessageSetVector4Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcVector4 value);

/** Gets a matrix2x2 argument and returns the default value from the type if the argument is not found. */
struct KzcMatrix2x2 kzuMessageGetMatrix2x2ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a matrix2x2 argument. */
kzsError kzuMessageSetMatrix2x2Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcMatrix2x2 value);

/** Gets a matrix3x3 argument and returns the default value from the type if the argument is not found. */
struct KzcMatrix3x3 kzuMessageGetMatrix3x3ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a matrix3x3 argument. */
kzsError kzuMessageSetMatrix3x3Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcMatrix3x3 value);

/** Gets a matrix4x4 argument and returns the default value from the type if the argument is not found. */
struct KzcMatrix4x4 kzuMessageGetMatrix4x4ArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a matrix4x4 argument. */
kzsError kzuMessageSetMatrix4x4Argument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, struct KzcMatrix4x4 value);

/** Gets a pointer argument and returns the default value from the type if the argument is not found. */
void* kzuMessageGetPointerArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a pointer argument. */
kzsError kzuMessageSetPointerArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, void* value);

/** Gets a string argument and returns the default value from the type if the argument is not found. */
kzString kzuMessageGetStringArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a string argument. */
kzsError kzuMessageSetStringArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, kzString value);

/** Gets a resourceID argument and returns the default value from the type if the argument is not found. */
kzString kzuMessageGetResourceIDArgumentDefault(const struct KzuMessage* message, const struct KzuPropertyType* argumentType);
/** Sets a string argument. */
kzsError kzuMessageSetResourceIDArgument(const struct KzuMessage* message, const struct KzuPropertyType* argumentType, kzString resourceID);


KZ_HEADER_END


#endif
