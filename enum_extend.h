#ifndef DTS_ENUM_EXTEND_H
#define DTS_ENUM_EXTEND_H
#include "dts/license.h"
/**
 * @defgroup dts enum_extend
 *
 * @brief Provides overloading for strongly typed enumerations through macros.
 * @details
 *      class enum [typename] : [base} { [members...] };
 *      __ENUM_OPERATOR_OVERLOAD([typename]);
 * ...
 *      [typename]++; // compiler's alright.
 * @note individual overloads are available through relevant macros.
**/
#include "dts/base_macro.h"

/**
  * @brief provides weak comparison ability but retains
  * strong typing functionality desired of enum class.
  * @note implicitly declares namespace __enum.
  * 
  * @note DOES NOT ALLOW ASSIGNMENT WITHOUT CAST.
*/
#define __ENUM_OPERATOR_OVERLOAD(__enum_type, __enum_base) \
    __ENUM_PREFIX_INCREMENT(__enum_type, __enum_base) \
    __ENUM_POSTFIX_INCREMENT(__enum_type, __enum_base) \
    __ENUM_POSTFIX_DECREMENT(__enum_type, __enum_base) \
    __ENUM_PREFIX_DECREMENT(__enum_type, __enum_base) \
    __ENUM_GREATER_THAN(__enum_type, __enum_base) \
    __ENUM_LESS_THAN(__enum_type, __enum_base) \
    __ENUM_EQUAL_TO(__enum_type, __enum_base) \
    __ENUM_NOT_EQUAL_TO(__enum_type, __enum_base) \
    dts_EAT_SEMICOLON()

#define __ENUM_POSTFIX_INCREMENT(__enum_type, __enum_base) \
    inline __enum_type operator++ (__enum_type& in, int) { \
        in = static_cast<__enum_type>((__enum_base)in + 1); \
        return in; \
    } \

#define __ENUM_PREFIX_INCREMENT(__enum_type, __enum_base) \
    inline __enum_type& operator++ (__enum_type& in) { \
        in = static_cast<__enum_type>((__enum_base)in + 1); \
        return in; \
    } \

#define __ENUM_POSTFIX_DECREMENT(__enum_type, __enum_base) \
    inline __enum_type operator-- (__enum_type& in, int) { \
        in = static_cast<__enum_type>((__enum_base)in - 1); \
        return in; \
    } \

#define __ENUM_PREFIX_DECREMENT(__enum_type, __enum_base) \
    inline __enum_type& operator-- (__enum_type& in) { \
        in = static_cast<__enum_type>((__enum_base)in - 1); \
        return in; \
    } \

#define __ENUM_GREATER_THAN(__enum_type, __enum_base) \
    inline bool operator > (const __enum_type& in, const __enum_base& val) { \
        return static_cast<__enum_base>(in) > val; \
    } \

#define __ENUM_LESS_THAN(__enum_type, __enum_base) \
    inline bool operator < (const __enum_type& in, const __enum_base& val) { \
        return static_cast<__enum_base>(in) < val; \
    } \

#define __ENUM_EQUAL_TO(__enum_type, __enum_base) \
    inline bool operator == (const __enum_type& in, const __enum_base& val) { \
        return static_cast<__enum_base>(in) == val; \
    } \

#define __ENUM_NOT_EQUAL_TO(__enum_type, __enum_base) \
    inline bool operator != (const __enum_type& in, const __enum_base& val) { \
        return (in != val); \
    } \

#endif
  // DTS_ENUM_EXTEND_H

/************************************end of file************************************/
