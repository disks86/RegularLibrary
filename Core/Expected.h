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
    union ExpectedValue {
        ValueType ValueType;
        ErrorType ErrorType;
    };

    template<typename ValueType, typename ErrorType>
    class Expected : public ExpectedBase {
        ExpectedValue<ValueType, ErrorType> mExpectedValue;
    public:
        Expected(ValueType valueType) noexcept {
            mHasValue = true;
            mExpectedValue.ValueType = valueType;
        }

        Expected(ErrorType errorType) noexcept {
            mHasValue = false;
            mExpectedValue.ErrorType = errorType;
        }

        Expected(Expected const &other) noexcept {
            mHasValue = other.mHasValue;
            if (other.mHasValue) {
                mExpectedValue.ValueType = other.mExpectedValue.ValueType;
            } else {
                mExpectedValue.ErrorType = other.mExpectedValue.ErrorType;
            }
        }

        ValueType GetValueOr(ValueType valueType) const noexcept {
            if (mHasValue) {
                return mExpectedValue.ValueType;
            } else {
                return valueType;
            }
        }

        ValueType GetValue() const noexcept {
            return mExpectedValue.ValueType;
        }

        ErrorType GetError() const noexcept {
            return mExpectedValue.ErrorType;
        }

        operator ValueType() const noexcept {
            return mExpectedValue.ValueType;
        }

        operator ErrorType() const noexcept {
            return mExpectedValue.ErrorType;
        }
    };
}

#endif //REGULARLIBRARY_EXPECTED_H
