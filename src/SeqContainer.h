#pragma once

/*****************************************************************************************/
//
//                           Copyright(C) 2024 Max J Martin
//
//                            This file is part of Oliver.
//                      Oliver is program language interpreter. 
//    
//        This program is free software : you can redistribute it and /or modify
//        it under the terms of the GNU Affero General Public License as published by
//        the Free Software Foundation, either version 3 of the License, or
//        (at your option) any later version.
//    
//        This program is distributed in the hope that it will be useful,
//        but WITHOUT ANY WARRANTY; without even the implied warranty of
//        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//        GNU Affero General Public License for more details.
//    
//        You should have received a copy of the GNU Affero General Public License
//        along with this program.If not, see <https://www.gnu.org/licenses/>.
//    
//        The author can be reached at: maxjmartin@gmail.com
//
/*****************************************************************************************/

#include <algorithm>
#include <array>
#include <bit>
#include <compare>
#include <cstdint>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <iostream>
#include <functional>
#include <limits>
#include <list>
#include <type_traits>

#include "Expression_Template.h"

namespace Oliver {

    /********************************************************************************************/
    //
    //                                    'SeqContainer' class
    //          
    //          The SeqContainer, is an expression templated wrapper class intended 
    //          to be usable with the std::vector, and std::deque.  A specialized 
    //          class is available for the std::array.
    // 
    //          The original inspiration for the class was an from the book "C++ Templates:
    //          The Complete Guide" by David Vandevoorde, Nicolai M. and Douglas Gregor.
    //
    //          The material was supplemented by the Stack Overflow link: 
    //          https://stackoverflow.com/questions/11809052/expression-templates-and-c11.
    //          which heavily influenced the design of the class due to the readability
    //          of the solutions defined within the post.  
    //
    /********************************************************************************************/

    template <typename Object >
    concept HasReserveMethod = requires(Object) {
        { std::is_member_function_pointer<decltype(&Object::reserve)>::value };
    };

    template<typename VALUE = intmax_t, typename IMPL = std::vector<VALUE>>
    class SeqContainer {

    public:
        using impl_type              = IMPL;
        using value_type             = impl_type::value_type;
        using iterator               = impl_type::iterator;
        using const_iterator         = impl_type::const_iterator;
        using reverse_iterator       = impl_type::reverse_iterator;
        using const_reverse_iterator = impl_type::const_reverse_iterator;

        constexpr SeqContainer();
        constexpr SeqContainer(value_type value);
        constexpr SeqContainer(std::initializer_list<value_type> list);

        template <typename LE, typename Op, typename RE>
        constexpr SeqContainer(ExprTemplate<LE, Op, RE>&& expr);

        constexpr ~SeqContainer() = default;

        constexpr SeqContainer(SeqContainer&& arr)                  noexcept = default;
        constexpr SeqContainer(const SeqContainer& arr)             noexcept = default;
        constexpr SeqContainer& operator =(SeqContainer&& arr)      noexcept = default;
        constexpr SeqContainer& operator =(const SeqContainer& arr) noexcept = default;

        friend constexpr void swap(SeqContainer& first, SeqContainer& second);

        operator bool() const;

        auto  begin()       noexcept;
        auto  begin() const noexcept;
        auto cbegin() const noexcept;

        auto  end()       noexcept;
        auto  end() const noexcept;
        auto cend() const noexcept;

        auto  rbegin()       noexcept;
        auto  rbegin() const noexcept;
        auto crbegin() const noexcept;

        auto  rend()       noexcept;
        auto  rend() const noexcept;
        auto crend() const noexcept;

        constexpr std::size_t     size() const;
        constexpr std::size_t max_size() const;
        constexpr std::size_t capacity() const;

        constexpr SeqContainer&  resize(std::size_t size);
        constexpr SeqContainer&  resize(std::size_t size, value_type value);
        constexpr SeqContainer& reserve(std::size_t size);

        constexpr SeqContainer&  pop_back();
        constexpr SeqContainer& push_back(value_type value);

        constexpr SeqContainer& insert(std::size_t at, const auto& range);
        constexpr SeqContainer& insert(std::size_t at, std::ranges::sized_range auto&& range);

        constexpr SeqContainer&  shift(int index);
        constexpr SeqContainer& cshift(int index);

        constexpr SeqContainer& apply(value_type func(value_type));
        constexpr SeqContainer& apply(value_type func(const value_type&));

        constexpr SeqContainer& apply(const SeqContainer& b, value_type func(value_type, value_type));
        constexpr SeqContainer& apply(const SeqContainer& b, value_type func(const value_type&, const value_type&));

        constexpr bool                  operator ==(const SeqContainer& b) const;
        constexpr std::partial_ordering operator<=>(const SeqContainer& b) const;

        constexpr const value_type& operator [](std::size_t index) const;
        constexpr       value_type& operator [](std::size_t index);

        constexpr SeqContainer operator +();
        constexpr SeqContainer operator -();
        constexpr SeqContainer operator ~();

        constexpr SeqContainer& operator  +=(const SeqContainer& b);
        constexpr SeqContainer& operator  -=(const SeqContainer& b);
        constexpr SeqContainer& operator  *=(const SeqContainer& b);
        constexpr SeqContainer& operator  /=(const SeqContainer& b);
        constexpr SeqContainer& operator  %=(const SeqContainer& b);
        constexpr SeqContainer& operator  &=(const SeqContainer& b);
        constexpr SeqContainer& operator  |=(const SeqContainer& b);
        constexpr SeqContainer& operator  ^=(const SeqContainer& b);
        constexpr SeqContainer& operator <<=(const SeqContainer& b);
        constexpr SeqContainer& operator >>=(const SeqContainer& b);

        template <typename RightExpr> SeqContainer& operator   =(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  +=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  -=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  *=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  /=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  %=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  &=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  |=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator  ^=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator <<=(RightExpr&& re);
        template <typename RightExpr> SeqContainer& operator >>=(RightExpr&& re);
        template <typename RightExpr> SeqContainer&        apply(RightExpr&& re);

        template <typename RightExpr> auto operator  +(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Add_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  -(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Sub_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  *(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Mul_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  /(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Div_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  %(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Mod_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  &(RightExpr&& re) const->ExprTemplate<const SeqContainer&, And_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  |(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Or_Op<value_type>,                  decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator  ^(RightExpr&& re) const->ExprTemplate<const SeqContainer&, Xor_Op<value_type>,                 decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator <<(RightExpr&& re) const->ExprTemplate<const SeqContainer&, LeftShift_Op<value_type>,           decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto operator >>(RightExpr&& re) const->ExprTemplate<const SeqContainer&, RightShift_Op<value_type>,          decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto       apply(RightExpr&& re) const->ExprTemplate<const SeqContainer&, std::function<VALUE(VALUE)>,        decltype(std::forward<RightExpr>(re))>;
        template <typename RightExpr> auto       apply(RightExpr&& re) const->ExprTemplate<const SeqContainer&, std::function<VALUE(VALUE, VALUE)>, decltype(std::forward<RightExpr>(re))>;

    protected:
        static const value_type def_value;
        impl_type _sequence;

        constexpr SeqContainer& rotate_left          (std::size_t shift);
        constexpr SeqContainer& rotate_left_and_drop (std::size_t shift);
        constexpr SeqContainer& rotate_right         (std::size_t shift);
        constexpr SeqContainer& rotate_right_and_drop(std::size_t shift);
    };

    /*****************************************************************************************/
    //
    //                         Default Initialization & TypeDefines
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    const IMPL::value_type SeqContainer<VALUE, IMPL>::def_value = VALUE{};

    /*****************************************************************************************/
    //
    //                                     IO Stream Overload
    //
    /*****************************************************************************************/

    template <typename VALUE, typename IMPL>
    std::ostream& operator <<(std::ostream& os, SeqContainer<VALUE, IMPL> const& a) {
        if (a.size() > 0) {
            os << "(";
            for (std::size_t i = 0; i < a.size(); ++i) {
                os << a[i] << ((i + VALUE{ 1 } != a.size()) ? ',' : ')');
            }
        }
        return os;
    }

    /*****************************************************************************************/
    //
    //                                    Constructors & Swap
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>::SeqContainer() : _sequence() {
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>::SeqContainer(value_type value) : _sequence(1, value) {
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>::SeqContainer(std::initializer_list<value_type> list) : _sequence(list) {
        std::cout << "value = " << std::is_same<decltype(&IMPL::size), void>::value << std::endl;
    }

    template<typename VALUE, typename IMPL>
    template<typename LE, typename Op, typename RE>
    inline constexpr SeqContainer<VALUE, IMPL>::SeqContainer(ExprTemplate<LE, Op, RE>&& expr) : _sequence(expr.size(), value_type{}) {
        const auto limit = _sequence.size();
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = expr[i];
        }
    }

    template<typename VALUE, typename IMPL>
    constexpr void swap(SeqContainer<VALUE, IMPL>& first, SeqContainer<VALUE, IMPL>& second) {
        std::swap(first, second);
    }

    /*****************************************************************************************/
    //
    //                                      Boolean Operation
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline SeqContainer<VALUE, IMPL>::operator bool() const {
        const auto limit = _sequence.size();
        for (std::size_t i = 0; i < limit; ++i) {
            if (static_cast<bool>(operator[](i))) {
                return true;
            }
        }
        return false;
    }

    /*****************************************************************************************/
    //
    //                                      Iterators
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::begin() noexcept {
        return _sequence.begin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::begin() const noexcept {
        return _sequence.begin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::cbegin() const noexcept {
        return _sequence.cbegin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::end() noexcept {
        return _sequence.end();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::end() const noexcept {
        return _sequence.end();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::cend() const noexcept {
        return _sequence.cend();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::rbegin() noexcept {
        return _sequence.rbegin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::rbegin() const noexcept {
        return _sequence.rbegin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::crbegin() const noexcept {
        return _sequence.crbegin();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::rend() noexcept {
        return _sequence.rend();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::rend() const noexcept {
        return _sequence.rend();
    }

    template<typename VALUE, typename IMPL>
    inline auto SeqContainer<VALUE, IMPL>::crend() const noexcept {
        return _sequence.crend();
    }

    /*****************************************************************************************/
    //
    //                                 Size & Capacity Methods
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline constexpr std::size_t SeqContainer<VALUE, IMPL>::size() const {
        return _sequence.size();
    }

    template<typename VALUE, typename IMPL>
    inline constexpr std::size_t SeqContainer<VALUE, IMPL>::max_size() const {
        return _sequence.max_size();
    }

    template<typename VALUE, typename IMPL>
    inline constexpr std::size_t SeqContainer<VALUE, IMPL>::capacity() const {
        return _sequence.capacity();
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::resize(std::size_t size) {
        resize(size, value_type{});
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::resize(std::size_t size, value_type value) {
        if (size >= _sequence.size()) {
            if constexpr (HasReserveMethod<impl_type>) {
                _sequence.reserve(size);
            }
            _sequence.resize(size, value);
        }
        else if (size > 0) {
            _sequence.resize(size);
        }
        else {
            _sequence = impl_type{};
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::reserve(std::size_t size) {
        if (size > _sequence.size()) {
            _sequence.reserve(size);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::pop_back() {
        if (_sequence.size() > 0) {
            _sequence.pop_back();
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::push_back(value_type value) {
        _sequence.push_back(value);
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::insert(std::size_t at, const auto& range) {
        return insert(at, SeqContainer( std::initializer_list<value_type>{range} ));
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::insert(std::size_t at, std::ranges::sized_range auto&& range) {
        // TODO add insert at begining, ending, and in the middle algorithms.
        if (at > _sequence.size()) {
            resize(at);
        }
        _sequence.insert(std::next(_sequence.begin(), at), range._sequence.begin(), range._sequence.end());
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::shift(int index) {
        if (index > 0) {
            rotate_left_and_drop(index);
        }
        else {
            rotate_right_and_drop(std::abs(index));
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::cshift(int index) {
        if (index > 0) {
            rotate_left(index);
        }
        else {
            rotate_right(std::abs(index));
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::apply(SeqContainer<VALUE, IMPL>::value_type func(SeqContainer<VALUE, IMPL>::value_type)) {
        const auto limit = _sequence.size(); 
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = func(_sequence[i]);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::apply(SeqContainer<VALUE, IMPL>::value_type func(const SeqContainer<VALUE, IMPL>::value_type&)) {
        const auto limit = _sequence.size();
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = func(_sequence[i]);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::apply(const SeqContainer<VALUE, IMPL>& b, SeqContainer<VALUE, IMPL>::value_type func(SeqContainer<VALUE, IMPL>::value_type, SeqContainer<VALUE, IMPL>::value_type)) {
        const auto limit = max_val(_sequence.size(), b._sequence.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = func(_sequence[i], b._sequence[i]);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::apply(const SeqContainer<VALUE, IMPL>& b, SeqContainer<VALUE, IMPL>::value_type func(const SeqContainer<VALUE, IMPL>::value_type& , const SeqContainer<VALUE, IMPL>::value_type&)) {
        const auto limit = max_val(_sequence.size(), b._sequence.size()); 
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = func(_sequence[i], b._sequence[i]);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr bool SeqContainer<VALUE, IMPL>::operator==(const SeqContainer& b) const {
        return operator<=>(b) == std::partial_ordering::equivalent;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr std::partial_ordering SeqContainer<VALUE, IMPL>::operator<=>(const SeqContainer& b) const {
        if (size() > b.size()) {
            return std::partial_ordering::greater;
        }
        if (size() < b.size()) {
            return std::partial_ordering::less;
        }
        return std::partial_ordering::equivalent;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr const SeqContainer<VALUE, IMPL>::value_type& SeqContainer<VALUE, IMPL>::operator[](std::size_t index) const {
        if (index < _sequence.size()) {
            return _sequence[index];
        }
        return def_value;
    }    

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>::value_type& SeqContainer<VALUE, IMPL>::operator[](std::size_t index) {
        if (index >= _sequence.size()) {
            resize(index + 1);
        }
        return _sequence[index];
    }

    /*****************************************************************************************/
    //
    //                                  Unary Math Operations
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL> SeqContainer<VALUE, IMPL>::operator+() {
        SeqContainer<VALUE, IMPL> a = *this;
        const auto limit = a._sequence.size(); 
        for (std::size_t i = 0; i < limit; ++i) {
            a._sequence[i] = +a._sequence[i];
        }
        return a;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL> SeqContainer<VALUE, IMPL>::operator-() {
        SeqContainer<VALUE, IMPL> a = *this;
        const auto limit = a._sequence.size(); 
        for (std::size_t i = 0; i < limit; ++i) {
            a._sequence[i] = -a._sequence[i];
        }
        return a;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL> SeqContainer<VALUE, IMPL>::operator~() {
        const auto limit = _sequence.size(); 
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = ~_sequence[i];
        }
        return *this;
    }

    /*****************************************************************************************/
    //
    //                             Self Assigning Math Operations
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator+=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] += b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator-=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] -= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator*=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] *= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator/=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] /= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator%=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] %= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator&=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] &= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator|=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] |= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator^=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] ^= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator<<=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] <<= b[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    inline constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator>>=(const SeqContainer& b) {
        const auto limit = max_val(_sequence.size(), b.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] >>= b[i];
        }
        return *this;
    }

    /*****************************************************************************************/
    //
    //                    Expression Templated Self Assigning Math Operations
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator+=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] += re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator-=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] -= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator*=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] *= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator/=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] /= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator%=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] %= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator&=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] &= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator|=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] |= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator^=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] ^= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator<<=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] <<= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::operator>>=(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] >>= re[i];
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::apply(RightExpr&& re) {
        const auto limit = max_val(_sequence.size(), re.size());
        if (_sequence.size() < limit) {
            resize(limit + 1);
        }
        for (std::size_t i = 0; i < limit; ++i) {
            _sequence[i] = std::function<VALUE(VALUE, VALUE)>(_sequence[i], re[i]);
        }
        return *this;
    }

    /*****************************************************************************************/
    //
    //                                 Binary Expression Templates
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator+(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Add_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Add_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator-(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Sub_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Sub_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator*(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Mul_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Mul_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator/(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Div_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Div_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator%(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Mod_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Mod_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator&(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, And_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, And_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator|(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Or_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Or_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator^(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, Xor_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, Xor_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator<<(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, LeftShift_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, LeftShift_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::operator>>(RightExpr&& re) const -> ExprTemplate<const SeqContainer&, RightShift_Op<value_type>, decltype(std::forward<RightExpr>(re))> {
        return ExprTemplate<const SeqContainer&, RightShift_Op<value_type>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    template<typename VALUE, typename IMPL>
    template<typename RightExpr>
    inline auto SeqContainer<VALUE, IMPL>::apply(RightExpr&& re) const->ExprTemplate<const SeqContainer&, std::function<VALUE(VALUE, VALUE)>, decltype(std::forward<RightExpr>(re)) > {
        return ExprTemplate<const SeqContainer&, std::function<VALUE(VALUE, VALUE)>, decltype(std::forward<RightExpr>(re))>(*this, std::forward<RightExpr>(re));
    }

    /*****************************************************************************************/
    //
    //                                     Private Methods
    //
    /*****************************************************************************************/

    template<typename VALUE, typename IMPL>
    constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::rotate_left(std::size_t shift) {
        //shift = _sequence.size() - shift;
        //while (shift-- > 0) {
        //    value_type last = _sequence[0];
        //    const auto limit = _sequence.size() - 1;
        //    for (std::size_t i = 0; i < limit; ++i) {
        //        _sequence[i] = _sequence[i + 1];
        //    }
        //    _sequence[_sequence.size() - 1] = last;
        //}
        if (_sequence.size() > 0) {
            shift %= _sequence.size();
            std::ranges::rotate(_sequence, _sequence.end() - shift);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::rotate_left_and_drop(std::size_t shift) {
        rotate_left(shift);
        if (_sequence.size() > 0) {
            shift %= _sequence.size();
            for (std::size_t i = 0; i < shift; ++i) {
                _sequence[i] = value_type{ 0 };
            }
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::rotate_right(std::size_t shift) {
        //while (shift-- > 0) {
        //    value_type last = _sequence[0];
        //    const auto limit = _sequence.size() - 1;
        //    for (std::size_t i = 0; i < limit; ++i) {
        //        _sequence[i] = _sequence[i + 1];
        //    }
        //    _sequence[_sequence.size() - 1] = last;
        //}
        if (_sequence.size() > 0) {
            shift %= _sequence.size();
            std::ranges::rotate(_sequence, _sequence.begin() + shift);
        }
        return *this;
    }

    template<typename VALUE, typename IMPL>
    constexpr SeqContainer<VALUE, IMPL>& SeqContainer<VALUE, IMPL>::rotate_right_and_drop(std::size_t shift) {
        rotate_right(shift);
        if (_sequence.size() > 0) {
            shift %= _sequence.size();
            const auto limit = _sequence.size() - shift;
            auto i = _sequence.size();
            while (i-- > limit) {
                _sequence[i] = 0;
            }
        }
        return *this;
    }
}
