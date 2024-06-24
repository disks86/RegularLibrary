#ifndef REGULARLIBRARY_EXPECTED_H
#define REGULARLIBRARY_EXPECTED_H

namespace Core {

    class REGULAR_API Empty {

    };

    template<class ValueType, class ErrorType>
    union REGULAR_API ExpectedValue {
        ValueType ValueType;
        ErrorType ErrorType;
    };

    template<class ValueType, class ErrorType>
    class REGULAR_API Expected {
        bool mHasValue = false;
        ExpectedValue<ValueType,ErrorType> mExpectedValue;
    public:
        inline Expected(ValueType valueType) noexcept {
            mHasValue = true;
            mExpectedValue.ValueType = valueType;
        }

        inline Expected(ErrorType errorType) noexcept {
            mHasValue = false;
            mExpectedValue.ErrorType = errorType;
        }

        inline ValueType GetValueOr(ValueType valueType) const noexcept {
            if (mHasValue) {
                return mExpectedValue.ValueType;
            } else {
                return valueType;
            }
        }

        inline bool HasValue() const noexcept {
            return mHasValue;
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
