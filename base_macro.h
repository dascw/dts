#ifndef DTS_GEN_H
#define DTS_GEN_H

/**
  * Allows use of semicolon at end of macros that are not compound statements (i.e. that
  * cannot be correctly wrapped in a do {} while() loop due to their lack of scope.
  */
#define dts_EAT_SEMICOLON() struct sc_required

#endif 
    // DTS_GEN_H

/**************************************end of file**************************************/