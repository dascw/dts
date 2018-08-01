/**
 * @brief Macros for general use throughout dts library.
 * @file base_macro.h
 * @defgroup dts base_macro
 * @author SCW
 */
#ifndef DTS_GEN_H
#define DTS_GEN_H
#include "dts/license.h"
/**
  * Allows use of semicolon at end of macros that are not compound statements (i.e. that
  * cannot be correctly wrapped in a do {} while() loop due to lack of scope.
  */
#define dts_EAT_SEMICOLON() struct sc_required
#define dts_CPP_11 201103L

#endif 
    // DTS_GEN_H

/**************************************end of file**************************************/
