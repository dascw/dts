// enum_extend.h
#ifndef ENUM_EXTEND_H
#define ENUM_EXTEND_H
/**
 * @defgroup utilities Utilities
 *
 * Components deemed generally useful. Includes pair, tuple,
 * forward/move helpers, ratio, function object, metaprogramming and
 * type traits, time, date, and memory functions.
 *
 * @todo add details on the enumeration method.
 * @todo list caveats of use (e.g. inefficient resizing of vectors etc.)
 * @todo add details on how to use.
 * @todo add details 
**/
#include "base_macro.h"

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
    __ENUM_GREATER_THAN(__enum_type, __enum_base) \
    __ENUM_LESS_THAN(__enum_type, __enum_base) \
    __ENUM_EQUAL_TO(__enum_type, __enum_base) \
    __ENUM_NOT_EQUAL_TO(__enum_type, __enum_base) \
    def_EAT_SEMICOLON()


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
  // ENUM_EXTEND_H

/************************************end of file************************************/
