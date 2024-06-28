//
// Created by disks on 6/27/2024.
//

#ifndef REGULARLIBRARY_MATH_H
#define REGULARLIBRARY_MATH_H

namespace Core {
    class Math {
    public:
        template <typename T>
        constexpr static T Min(T a,T b) noexcept {
            if (a<b){
                return a;
            } else {
                return b;
            }
        }

        template <typename T>
        constexpr static T Max(T a,T b) noexcept {
            if (a>b){
                return a;
            } else {
                return b;
            }
        }
    };

} // Core

#endif //REGULARLIBRARY_MATH_H
