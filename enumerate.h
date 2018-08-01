#ifndef DTS_ENUMERATE_H
#define DTS_ENUMERATE_H
#include "dts/license.h"
/**
 * @defgroup dts enumerate
 * @brief Provides an experimental version of Python's enumerate in range functionality.
 * @example
 *      for (auto& a : dts::enumerate(std::vector<uint8_t>(5, 0xDE))) {
 *           // a.index contains current point inside vector.
 *           // a.value contains rvalue reference to current point.
 *      }
 * @details the underlying mechanism in Python's enumerate method is its tuple return
 * capability. In C++, this can be emulated through both std::tuple and std::pair. 
 * For the enumerate method, only two return values are required, index and value at index. 
 * 
 * enum_pair class is used to provide descriptive members than (not .first / .second.)
 * 
 * @caveats effiency: current implementation is inefficient due to vector resizing. 
 *          overheads: this isn't intended to be used for large vector objects, as results
 *                  in additional memory allocations for vector<pair> objects.
 *
 * @supported containers: tested with {map, forward_list, vector}.
**/
#include <utility>
#include <functional>  
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <stdint.h>

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
        using _T1_ref_t     = enum_type::_ref<_T1_t>;
        using _T2_ref_t     = enum_type::_ref<_T2_t>;

        enum_pair() = delete;
        enum_pair(enum_pair<_T1, _T2>&& __in) 
            : std::pair<_T1, _T2>(static_cast<std::pair<_T1, _T2>>(__in)), index(this->first), value(this->second) { }
        enum_pair(const enum_pair<_T1, _T2>& __in)  
            : std::pair<_T1, _T2>(static_cast<std::pair<_T1, _T2>>(__in)), index(this->first), value(this->second) { }
        enum_pair(_T1 __idx, _T2 __val)  
            : std::pair<_T1, _T2>(__idx, __val), index(_T1_ref_t(this->first)), value(_T2_ref_t(this->second)) { }

        typename std::pair<_T1, _T2>::first_type&   index;
        typename std::pair<_T1, _T2>::second_type&  value;
        ~enum_pair() = default;
    };

    /**
     * @brief enumerate() : returns immutable rvalue object.
     * @tparam _Tp 
     * @param obj 
     * @return const std::vector<enum_pair<int, _Tp>> 
     */
    template <typename _Container>
    const std::vector<enum_pair<enum_type::index_t, typename _Container::value_type>>
    enumerate(const _Container& __obj) {
        using _Tp = typename _Container::value_type;

        std::vector<enum_pair<enum_type::index_t, _Tp>> ret_val; // resize only once
        ret_val.reserve(std::distance(__obj.begin(), __obj.end()));
        enum_type::index_t index = 0;

        for (auto it = __obj.begin(); it != __obj.end(); ++it)
            ret_val.push_back(enum_pair<enum_type::index_t, _Tp>(index++, *it));

        return ret_val;
    }

    /**
     * @brief enumerate() : returns lvalue object containing references to vector object members.
     * @tparam _Tp 
     * @param obj 
     * @return const std::vector<enum_pair<int, std::reference_wrapper<_Tp>>> 
     */
    template <typename _Container>
    std::vector<enum_pair<enum_type::index_t, enum_type::_ref<typename _Container::value_type>>>
    enumerate(_Container& __obj) {
        using _Tp = typename _Container::value_type;

        std::vector<enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>> ret_val;
        ret_val.reserve(std::distance(__obj.begin(), __obj.end()));
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
        ret_val.reserve(std::distance(__obj.begin(), __obj.end()));

        std::for_each(__first, __last, [&](_Tp& val)->void {
            ret_val.push_back(enum_pair<enum_type::index_t, enum_type::_ref<_Tp>>(index++, std::ref(val)));
        });
        return ret_val;
    } 
}

#endif 
    // DTS_ENUMERATE_H

/**********************************************end of file**********************************************/
