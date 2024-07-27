#ifndef REGULARLIBRARY_EXPECTED_H
#define REGULARLIBRARY_EXPECTED_H

#include "Export.h"

namespace Core {

    class REGULAR_API Empty {

    };

    class REGULAR_API ExpectedBase {
    protected:
        bool mHasValue = false;
    public:
        bool HasValue() const noexcept;
    };

    template<typename ValueType, typename ErrorType>
    union REGULAR_API ExpectedValue {
        ValueType ValueType;
        ErrorType ErrorType;
    };

    template<typename ValueType, typename ErrorType>
    class REGULAR_API Expected : public ExpectedBase {
        ExpectedValue<ValueType, ErrorType> mExpectedValue;
    public:
        inline Expected(ValueType valueType) noexcept {
            mHasValue = true;
            mExpectedValue.ValueType = valueType;
        }

        inline Expected(ErrorType errorType) noexcept {
            mHasValue = false;
            mExpectedValue.ErrorType = errorType;
        }

        inline Expected(Expected const &other) noexcept {
            mHasValue = other.mHasValue;
            if (other.mHasValue) {
                mExpectedValue.ValueType = other.mExpectedValue.ValueType;
            } else {
                mExpectedValue.ErrorType = other.mExpectedValue.ErrorType;
            }
        }

        inline ValueType GetValueOr(ValueType valueType) const noexcept {
            if (mHasValue) {
                return mExpectedValue.ValueType;
            } else {
                return valueType;
            }
        }

        inline ValueType GetValue() const noexcept {
            return mExpectedValue.ValueType;
        }

        inline ErrorType GetError() const noexcept {
            return mExpectedValue.ErrorType;
        }

        inline operator ValueType() const noexcept {
            return mExpectedValue.ValueType;
        }

        inline operator ErrorType() const noexcept {
            return mExpectedValue.ErrorType;
        }
    };
}

#endif //REGULARLIBRARY_EXPECTED_H
