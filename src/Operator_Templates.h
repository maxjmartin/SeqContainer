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

namespace Oliver {

    /********************************************************************************************/
    //
    //                                Expression Template Structs
    //
    //        The following structs define a series of operations, utilized by the
    //        expression template class 'ExprTemplate' class.  The definition of 
    //        the structs are very straight forward and simple.
    //
    /********************************************************************************************/

    template <typename T>
    struct Add_Op {

        static T apply(T const& a, T const& b) {
            return a + b;
        }

        static T apply(T&& a, T const& b) {
            a += b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            b += a;
            return std::move(b);
        }

        static T apply(T&& a, T&& b) {
            a += b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Sub_Op {

        static T apply(T const& a, T const& b) {
            return a - b;
        }

        static T apply(T&& a, T const& b) {
            a -= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            return a - b;
        }

        static T apply(T&& a, T&& b) {
            a -= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Mul_Op {

        static T apply(T const& a, T const& b) {
            return a * b;
        }

        static T apply(T&& a, T const& b) {
            a *= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            b *= a;
            return std::move(b);
        }

        static T apply(T&& a, T&& b) {
            a *= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Div_Op {

        static T apply(T const& a, T const& b) {
            return a / b;
        }

        static T apply(T&& a, T const& b) {
            a /= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            return a / b;
        }

        static T apply(T&& a, T&& b) {
            a /= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Mod_Op {

        static T apply(T const& a, T const& b) {
            if (b) {
                return a % b;
            }
            return 0;
        }

        static T apply(T&& a, T const& b) {
            a %= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            return a % b;
        }

        static T apply(T&& a, T&& b) {
            a %= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct And_Op{

        static T apply(T const& a, T const& b) {
            return a & b;
        }

        static T apply(T && a, T const& b) {
            a &= b;
            return std::move(a);
        }

        static T apply(T const& a, T && b) {
            b &= a;
            return std::move(b);
        }

        static T apply(T && a, T && b) {
            a &= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Or_Op{

        static T apply(T const& a, T const& b) {
            return a | b;
        }

        static T apply(T && a, T const& b) {
            a |= b;
            return std::move(a);
        }

        static T apply(T const& a, T && b) {
            b |= a;
            return std::move(b);
        }

        static T apply(T && a, T && b) {
            a |= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct Xor_Op{

        static T apply(T const& a, T const& b) {
            return a ^ b;
        }

        static T apply(T && a, T const& b) {
            a ^= b;
            return std::move(a);
        }

        static T apply(T const& a, T && b) {
            b ^= a;
            return std::move(b);
        }

        static T apply(T && a, T && b) {
            a ^= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct LeftShift_Op {

        static T apply(T const& a, T const& b) {
            return a << b;
        }

        static T apply(T&& a, T const& b) {
            a <<= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            a >>= b;
            return std::move(a);
        }

        static T apply(T&& a, T&& b) {
            a <<= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct RightShift_Op {

        static T apply(T const& a, T const& b) {
            return a >> b;
        }

        static T apply(T&& a, T const& b) {
            a >>= b;
            return std::move(a);
        }

        static T apply(T const& a, T&& b) {
            a >>= b;
            return std::move(a);
        }

        static T apply(T&& a, T&& b) {
            a >>= b;
            return std::move(a);
        }
    };

    template <typename T>
    struct SubScript_Op {

        static T apply(T const& a, T const& b) {
            if (b) {
                return a[b];
            }
            return T{};
        }

        static T apply(T&& a, T const& b) {
            if (b) {
                return a[b];
            }
            return T{};
        }

        static T apply(T const& a, T&& b) {
            if (b) {
                return a[b];
            }
            return T{};
        }

        static T apply(T&& a, T&& b) {
            if (b) {
                return a[b];
            }
            return T{};
        }
    };
}
