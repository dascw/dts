#ifndef DTS_GEN_H
#define DTS_GEN_H
/**
 * @defgroup dts base_macro
 *
 * Macros for general use throughout dts library.
 *
 * @todo add license details.
**/

/**
  * Allows use of semicolon at end of macros that are not compound statements (i.e. that
  * cannot be correctly wrapped in a do {} while() loop due to lack of scope.
  */
#define dts_EAT_SEMICOLON() struct sc_required
#define dts_CPP_11 201103L

#endif 
    // DTS_GEN_H

/**************************************end of file**************************************/
