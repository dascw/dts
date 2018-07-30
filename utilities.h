#ifndef DTS_UTILITIES_H
#define DTS_UTILITIES_H
#include "dts/license.h" // see for license details
/**
 * @defgroup dts utilities
 *
 * Components deemend generally useful for everyday programming.
 *
**/
#include <utility>
#include <functional>  // required  for std::ref
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <typeinfo>
#include "dts/base_macro.h"

namespace dts {
    /**
     * @brief returns universal reference to container at requested index, type
     * deduced.
     */
    template<typename _Container, typename _Index>
    inline auto 
    uni_access(_Container&& __cntr, _Index __idx) -> 
            decltype(std::forward<_Container>(__cntr)[__idx]) {
        return std::forward<_Container>(__cntr)[__idx];
    }

    /**
     * @brief return size of an array as a compile-time constant. (The
     * array parameter has no name, because we care only abou the number of elements
     * it contains.)
     */
    template <typename _Tp, std::size_t _Sz>
    inline constexpr std::size_t 
    array_size(_Tp (&)[_Sz]) noexcept {
        return _Sz;
    }

    /**
     * Function template that takes an arbitrary enumerator and can return its value as
     * a compile time constant.
     * @note should in principle provide simplistic conversion of ENUM to size_t etc?
     * 
     * @todo Read through example for tuple access with scoped enumeration.
     */
    template<typename _Enum>
    constexpr typename std::underlying_type<_Enum>::type
    to_idx(_Enum __enum) noexcept {
        return static_cast<typename std::underlying_type<_Enum>::type>(__enum);
    }

    /**
     * @brief prevents rvalue delete.
     * @details "if you consider zeroing out pointers important, consider using destroy."
     *          http://www.stroustrup.com/bs_faq2.html @ why doesn't delete zero out its operand?
     * @example
     *        if we have: `delete (int*)10;`, the compiler will NOT catch this and will successfully compile.
     *        if we pass an rvalue to destroy, a compile time error will be generated by the asignment
     *        to nullptr.
     *                    destroy( (int*)10); // prevents rvalue delete when cast.
     * @note it's obvious when casting directly that this has the potential to crash a system, 
     *       and should not be carried out.
     */
    template<class _Tp>
    inline void
    destroy(_Tp*& __p) { delete __p; __p = nullptr; }

    /**
     * @brief provides compile time check that object of type _T1 can
     * @details http://www.stroustrup.com/bs_faq2.html#constraints
     * be assigned to object of type _T2.
     * @example has_value<deduced_type, actual_type>(); // generates error on false.
     * @note constraints and concepts are standard in C++20.
     */
    template <class _Tp1, class _Tp2>
    struct is_type {
        static void constraints(_Tp1 __a, _Tp2 __b) {
            _Tp2 c = __a; __b = __a; (void)c;
        }
        is_type() { void(*ptr)(_Tp1, _Tp2) = constraints; (void)ptr; }
    };

#if __cplusplus >= dts_CPP_11
    /**
     * @brief returns underlying type of enuemration.
     */
    template<typename _Enum>
    constexpr auto
    utype(_Enum __enum) noexcept {
        return static_cast<std::underlying_type_t<_Enum>>(__enum);
    }
#endif

    /**
     * @brief should privde on the fly access to tuples through meaningful
     * name (enum created locally if required).
     * @details provides simple container creation/access; reduces use of
     * wrapper classes; more pythonic.
     * @note currently doesn't work due to const expr restrictions; could potentially
     * work with macro handling.
     * @todo look at deriving from tuple class, creating custom class with
     * accessible members.
     */
#if 0
    template <typename _Tuple, typename _Enum>
    decltype(auto)
    get(_Tuple& __tuple, const _Enum& __key) {
        // code..
    }
#endif // 0
} 

#endif 
    // DTS_UTILITIES_H

/****************************************end of file****************************************/
