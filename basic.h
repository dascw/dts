// dts_basic.h
#ifndef DTS_BASIC_H
#define DTS_BASIC_H

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
     *
     * constexpr significance: declaration indicating it is possible to evaluate
     * the result of the function or variable at compile time, which allows the
     * result of the function to be used where only compile time expressions
     * are usually allowed.
     * @todo noexcept presumably blocks exceptions
     */
    template <typename _Tp, std::size_t _Sz>
    inline constexpr std::size_t 
    array_size(_Tp (&)[_Sz]) noexcept {
        return _Sz;
    }

    /**
     * Function template that takes an arbitrary enumerator and can return its value as
     * a compile time constant.
     *
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
      * @brief dts_BUILD_GET_TYPE() : creates get_tuple method for simple enumeration
      * access of tuple members (removes requirement to constantly cast to accessable
      * value.
      *
      * @details to use:
      *
      * 1. add dts_BUILD_GET_TUPLE(enum_class) below your enum declaration.
      *
      * 2. const auto& val = get_tuple<enum_class::enum_member>(tuple_object);
      */
    #define dts_BUILD_GET_TUPLE(_Enum_t) \
        template <_Enum_t key, typename Tuple> \
        decltype(auto) 
        get_tuple(Tuple &&tuple) { \
            return std::get<static_cast<std::underlying_type_t<_Enum_t>>(key)>(tuple); \
        } dts_EAT_SEMICOLON() 
} 

#endif 
    // DTS_BASIC_H

/****************************************end of file****************************************/