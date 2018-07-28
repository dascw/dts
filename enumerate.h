/**
  @todo add details on the enumeration method.
  @todo list caveats of use (e.g. inefficient resizing of vectors etc.)
  @todo add details on how to use.
  @todo add details on supported container classes.
**/
#ifndef DTS_ENUMERATE_H
#define DTS_ENUMERATE_H

#include <utility>
#include <functional>  // required  for std::ref
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <typeinfo>

namespace dts {
    // @note unable to access members of enum_pair through forward deduction  when creating object of type enum_pair,
    // @solution shifted enum_pair index_t to enum_type struct. (not pretty.)
    struct enum_type {
        using index_t = int;

        template <typename _R>
        using _ref  = std::reference_wrapper<_R>;
    };

    template <typename _T1, typename _T2>
    struct enum_pair final : private std::pair<_T1, _T2> {
        using _T1_t         = typename std::pair<_T1, _T2>::first_type;
        using _T2_t         = typename std::pair<_T1, _T2>::second_type;
        using _T1_ref_t     = std::reference_wrapper<_T1_t>;
        using _T2_ref_t     = std::reference_wrapper<_T2_t>;

        // @todo implement - copy ctors
//        enum_pair(enum_pair<_T1, _T2>&& __in) {}
        enum_pair() = delete;
        enum_pair(const enum_pair<_T1, _T2>& __in)  : std::pair<_T1, _T2>(static_cast<std::pair<_T1, _T2>>(__in)), index(this->first), value(this->second)  { }
        enum_pair(_T1 index_in, _T2 value_in)       : std::pair<_T1, _T2>(index_in, value_in), index(_T1_ref_t(this->first)), value(_T2_ref_t(this->second))    { }

        typename std::pair<_T1, _T2>::first_type&   index;
        typename std::pair<_T1, _T2>::second_type&  value;
        ~enum_pair() = default;
    };


    /**
     * @brief enumerate() : returns immutable rvalue object.
     * 
     * @tparam _Tp 
     * @param obj 
     * @return const std::vector<enum_pair<int, _Tp>> 
     */
    template <typename _Container>
    const std::vector<enum_pair<enum_type::index_t, typename _Container::value_type>>
    enumerate(const _Container& __obj) {
        using _Tp = typename _Container::value_type;

        std::vector<enum_pair<enum_type::index_t, _Tp>> ret_val; // resize only once
        enum_type::index_t index = 0;

        for (auto it = __obj.begin(); it != __obj.end(); ++it)
            ret_val.push_back(enum_pair<enum_type::index_t, _Tp>(index++, *it));

        return ret_val;
    }

    /**
     * @brief enumerate() : returns lvalue object containing references to vector object members.
     * 
     * @tparam _Tp 
     * @param obj 
     * @return const std::vector<enum_pair<int, std::reference_wrapper<_Tp>>> 
     */
    template <typename _Container>
    std::vector<enum_pair<enum_type::index_t, enum_type::_ref<typename _Container::value_type>>>
    enumerate(_Container& __obj) {
        using _Tp = typename _Container::value_type;

        std::vector<enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>> ret_val;
        enum_type::index_t index = 0;

        std::for_each(__obj.begin(), __obj.end(), [&](_Tp& val)->void {
            ret_val.push_back(enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>(index++, std::ref(val)));
        });
        return ret_val;
    }

    /**
     * @brief enumerate() : returns lvalue object containing references to _Container object's members
     *                      within specified range.
     * @details works only for container classes whose underlying type is deduceable through ::value_type.
     * @tparam _Container
     * @tparam _Iter
     * @param __obj
     * @param __first
     * @param __last
     * @return std::vector<enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>>
     */
    template <typename _Container, typename _Iter>
    std::vector<enum_pair<enum_type::index_t, enum_type::_ref<typename _Container::value_type>>>
    enumerate(_Container& __obj,
                     _Iter __first,
                     _Iter __last) {
        using _Tp = typename _Container::value_type;

        std::vector<enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>> ret_val;
        enum_type::index_t index = std::distance(__obj.begin(), __first);

        std::for_each(__first, __last, [&](_Tp& val)->void {
            ret_val.push_back(enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>(index++, std::ref(val)));
        });

        return ret_val;
    } 
}

#endif 
    // DTS_ENUMERATE_H

/**********************************************end of file**********************************************/
