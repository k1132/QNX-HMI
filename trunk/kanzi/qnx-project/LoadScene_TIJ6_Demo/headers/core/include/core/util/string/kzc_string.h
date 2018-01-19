/**
 * \file
 * String utilities.
 * 
 * Copyright 2008-2014 by Rightware. All rights reserved.
 */
#ifndef KZC_STRING_H
#define KZC_STRING_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/wrappers/kzs_arg.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/* Forward declarations */
struct KzcMemoryManager;


/** Constant for string termination character. */
#define KZC_STRING_TERMINATION_SYMBOL '\0'
/** Constant for unicode replacement character. */
#define KZC_STRING_UNICODE_REPLACEMENT_CHARACTER (kzUnicodeChar)0xFFFD


/** String iterator for unicode characters. */
struct KzcStringIterator
{
    kzString tail_private; /**< Tail of the string being iterated in UTF-8 format. */
    kzUnicodeChar codePoint_private; /**< Codepoint of the current string position. */
};


/**
 * Creates a new mutable string of given size and terminates it with '\0' from the start.
 * The string can contain size - 1 characters in addition to the terminating character.
 */
kzsError kzcStringCreate(const struct KzcMemoryManager* memoryManager, kzUint size, kzMutableString* out_string);

/**
 * Creates a new string of given length. Terminating '\0' is not counted in the length.
 * The resulting string is not initialized and does not have terminating '\0'.
 */
kzsError kzcStringAllocate(const struct KzcMemoryManager* memoryManager, kzUint length, kzMutableString* out_string);

/** Creates a new empty string. The resulting zero-length string is '\0' terminated. */
kzsError kzcStringCreateEmpty(const struct KzcMemoryManager* memoryManager, kzMutableString* out_string);

/** Deletes a string. */
kzsError kzcStringDelete(kzMutableString string);


/**
 * Returns the length of a string. Terminating '\0' is not counted.
 * Note that this function returns the number of UTF-8 bytes, not the number of unicode code points in it.
 */
kzUint kzcStringLength(kzString string);

/** Returns KZ_TRUE if the string is empty. */
kzBool kzcStringIsEmpty(kzString string);

/** Creates a copy of the given source string. */
kzsError kzcStringCopy(const struct KzcMemoryManager* memoryManager, kzString source, kzMutableString* out_target);

/** Concatenates two strings. */
kzsError kzcStringConcatenate(const struct KzcMemoryManager* memoryManager, kzString front, kzString back,
                              kzMutableString* out_string);

/** Concatenates arbitrary number of strings. */
kzsError kzcStringConcatenateMultiple(const struct KzcMemoryManager* memoryManager, kzUint numStrings,
                                      kzMutableString* out_string, ...);

/**
 * Returns a substring of the given string starting from the given index and length characters long.
 * If length would go out of bounds of the string it is silently clamped to the end of the string. 
 */
kzsError kzcStringSubstring(const struct KzcMemoryManager* memoryManager, kzString string, kzUint start, kzUint length,
                            kzMutableString* out_string);

/**
 * Finds the first position where given sub string is located in the given string.
 * Returns the index of the first letter which is part of the search string
 * Returns false if the pattern is not found.
 * \param out_index Index from the beginning of the string, KZ_NULL if not used.
 */
kzBool kzcStringFindSubstring(kzString string, kzString subString, kzUint* out_index);

/**
 * Finds the next position where given sub string is located in the given string. Search is started from the given index,
 * which must be smaller than the length of the string. Returns false if the pattern is not found.
 * \param out_index Index from the beginning of the string, KZ_NULL if not used.
 */
kzBool kzcStringFindNextSubstring(kzString string, kzString subString, kzUint startIndex, kzUint* out_index);

/** Returns the number of how many times given pattern exists as a substring in given string without overlapping. */
kzUint kzcStringGetSubstringCount(kzString string, kzString pattern);

/**
 * Finds the first position where given character is located in the given string.
 * Returns false if the character is not found.
 */
kzBool kzcStringFindCharacter(kzString string, kzChar ch, kzUint* out_index);

/**
 * Finds the next position where given character is located in the given string. Search is started from the given index,
 * which must be smaller than the length of the string. Returns false if the character is not found.
 */
kzBool kzcStringFindNextCharacter(kzString string, kzChar ch, kzUint startIndex, kzUint* out_index);

/** Checks if the given string starts with the given pattern. */
kzBool kzcStringStartsWith(kzString string, kzString pattern);

/** Checks if the given string ends with the given pattern. */
kzBool kzcStringEndsWith(kzString string, kzString pattern);

/** Replace instances of pattern in base. Return resulting string in out_string. 'out_string' is assigned new memory from heap. */
kzsError kzcStringReplace(const struct KzcMemoryManager* memoryManager, kzString originalString, kzString pattern,
                          kzString patternReplacement, kzMutableString* out_string);
/** Remove a substring from a string in-place. */
void kzcStringRemoveSubstringInPlace(kzMutableString string, kzString substring);

/**
* Parse input string to a boolean value.
* String literals "true" and "false" are accepted. Integer values that are not 1 or 0 will be interpreted as KZ_TRUE.
* \param string String to parse.
* \return Boolean value parsed from string or KZ_FALSE if the string contains an invalid boolean value. */
kzBool kzcStringToBool(kzString string);

/**
* Parse input string to an integer value.
* \param string String to parse.
* \return Integer value parsed from string or 0 if the string contains an invalid number. */
kzInt kzcStringToInt(kzString string);

/**
* Parse input string to a floating point value.
* \param string String to parse.
* \return Floating-point value parsed from string or 0.0f if the string contains an invalid number. */
kzFloat kzcStringToFloat(kzString string);

/** Returns a string representation of integer. */
kzsError kzcIntToString(const struct KzcMemoryManager* memoryManager, kzInt value, kzMutableString* out_string);

/** Returns an approximate string representation of a floating point value. */
kzsError kzcFloatToString(const struct KzcMemoryManager* memoryManager, kzFloat value, kzMutableString* out_string);

/**
 * Splits the string by the given separator into an array of strings.
 * The separator symbol is not included in the output string.
 */
kzsError kzcStringSplit(const struct KzcMemoryManager* memoryManager, kzString string, kzString separator,
                        kzUint* out_stringCount, kzMutableString** out_strings);

/** Joins the given string array with a given delimiter to a single string. */
kzsError kzcStringJoin(const struct KzcMemoryManager* memoryManager, kzUint stringCount, const kzString* strings,
                       kzString delimiter, kzMutableString* out_string);

/**
 * Creates string that contains lower case letters from source string.
 * This function only modifies characters in the range A-Z.
 */
kzsError kzcStringAsciiToLowerCase(const struct KzcMemoryManager* memoryManager, kzString sourceString,
                                   kzMutableString* out_string);

/** Get the formatted length of the string. */
kzsError kzcStringFormatGetLength(kzString format, KZ_CONST_ARGLIST kzArgList* arguments, kzUint* out_length);

/**
 * vsnprintf()-like string formatter.
 * Format parameter specifies how the resulting string is formatted.
 * Arguments parameter provides the formatting arguments as variable arguments list.
 * \param out_string Newly allocated, formatted string. Free with kzcStringDelete().
 * \see kzcStringFormat for format information.
 */
kzsError kzcStringFormatList(const struct KzcMemoryManager* memoryManager, kzString format, KZ_CONST_ARGLIST kzArgList* arguments, kzMutableString* out_string);

/**
 * Formats the given string with given parameters.
 * Format parameter specifies how the resulting string is formatted.
 * Formatting arguments are given as variable arguments.
 *
 * Format flags:
 *
 * %[flags][width][.precision]type
 * Alternatively %% produces a single % character.
 *
 * flags:  - Use left alignment for output
 *         + Use sign for non-negative numbers also
 *         0 Use leading zeros for padding, when width is specified
 *
 *         Flags must appear in the order listed above.
 *
 * width: Any positive number. Output will be padded with spaces until it is at least this number of characters wide.
 *        Output will then be right-aligned by default.
 *
 * precision: Precision is available only for floating point types.
 *            Exactly this number of decimal digits will be outputted.
 *
 * Type char  Actual type     Format
 *   i/d        kzInt           Signed integer
 *   u          kzUint          Unsigned integer
 *   f          kzFloat         printed in scientific notation if not enough space for decimal notation
 *   x          kzUint          Lowercase hexadecimal integer (badf00d)
 *   X          kzUint          Uppercase hexadecimal integer (BADF00D)
 *   s          kzString        String
 *   c          kzChar          ASCII character
 *   C          kzUnicodeChar   Unicode character
 *   b          kzBool          Lowercase boolean string (true or false)
 *   B          kzBool          Boolean string with first letter uppercase (True or False)
 *   p          void*           Memory pointer
 *
 * An error is thrown, if the format is not meaningful (eg. %+b, %5.5i or %-i).
 */
kzsError kzcStringFormat(const struct KzcMemoryManager* memoryManager, kzString format, kzMutableString* out_string, ...);

/** Compare two strings. Return -1 if first < second, 0 if first == second and 1 if first > second. */ 
kzInt kzcStringCompare(kzString first, kzString second);
/**
 * Compare two strings but only look at most length characters.
 * Return -1 if first < second, 0 if first == second and 1 if first > second.
 */
kzInt kzcStringCompareWithLength(kzString first, kzString second, kzUint length);
/**
 * Compare two strings ignoring case for characters in the range A-Z and a-z.
 * Returns negative number if first < second, 0 if first == second, poisitive number if first > second.
 */
kzInt kzcStringCompareIgnoreAsciiCase(kzString first, kzString second);
/**
 * Compare two strings ignoring case for characters in the range A-Z and a-z, but only look at most length characters.
 * Returns negative number if first < second, 0 if first == second, poisitive number if first > second.
 */
kzInt kzcStringCompareIgnoreAsciiCaseWithLength(kzString first, kzString second, kzUint length);

/** Compare two strings. Return KZ_TRUE if the strings are equal. */ 
kzBool kzcStringIsEqual(kzString first, kzString second);

/** Compare two strings. Return KZ_TRUE if the strings are equal. It is safe to pass KZ_NULL arguments to this function. KZ_NULL is equal only to KZ_NULL. */
kzBool kzcStringIsEqualNullSafe(kzString first, kzString second);


/** Returns the number of unicode characters in given UTF-8 encoded string. */
kzUint kzcStringGetUnicodeLength(kzString string);

/**
 * Returns the unicode code point at the beginning of given string in UTF-8 format.
 * Number of bytes read for the unicode code point is stored in out_byteReadCount.
 */
kzUnicodeChar kzcStringGetUnicodeCharacter(kzString string, kzUint* out_byteReadCount);

/**
 * Encodes the given unicode character in UTF-8 format to the given string. Number of bytes written is returned.
 * 0 is returned, if the given character is invalid unicode code point.
 * The string must be preallocated and have enough space for the necessary UTF-8 bytes of the unicode character.
 */
kzUint kzcStringWriteUnicodeCharacter(kzMutableString string, kzUnicodeChar character);

/**
 * Decodes the given UTF-8 encoded string to an array of unicode code points.
 * New memory is allocated for out_unicodeArray, which must be manually freed.
 */
kzsError kzcStringToUnicodeArray(const struct KzcMemoryManager* memoryManager, kzString string,
                                 kzUint* out_characterCount, kzUnicodeChar** out_unicodeCharacters);

/**
 * Encodes the given array of unicode code points to UTF-8 string.
 * New string is allocated for out_string, which must be manually deleted with kzcStringDelete().
 */
kzsError kzcStringFromUnicodeArray(const struct KzcMemoryManager* memoryManager, kzUint arrayLength,
                                   const kzUnicodeChar* unicodeArray, kzMutableString* out_string);


/** Get unicode iterator for given UTF-8 string. */
struct KzcStringIterator kzcStringGetIterator(kzString string);

/** Finds the next entry in the attached hash map. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzcStringIterate(iterator_param) kzcStringIterate_private(&iterator_param)

/** Returns the value of the hash map entry pointed by the iterator. */
#define kzcStringIteratorGetValue(iterator_param) kzcStringIteratorGetValue_private(&iterator_param)


/** \see kzcStringIterate */
kzBool kzcStringIterate_private(struct KzcStringIterator* iterator);
/** \see kzcStringIteratorGetValue */
kzUnicodeChar kzcStringIteratorGetValue_private(const struct KzcStringIterator* iterator);

/** Test whether or not a certain character is whitespace. */
kzBool kzcStringAsciiCharIsSpace(kzChar character);

/** In-place string trim. Modifies the source string. */
kzMutableString kzcStringTrim(kzMutableString input);


KZ_HEADER_END


#endif
