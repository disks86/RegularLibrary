//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_LIST_H
#define REGULARLIBRARY_LIST_H

#include "System/Allocator.h"
#include "Core/Math.h"
#include "Core/MemoryConsumer.h"
#include "Core/Pair.h"

namespace Core {

    template <typename T>
    struct IsCharacterType {
        static constexpr bool value = false;
    };

    template <>
    struct IsCharacterType<char> {
        static constexpr bool value = true;
    };

    enum class REGULAR_API ListError {
        IndexOutOfRange,
        OutOfMemory,
        ElementNotFound
    };

    template<typename ValueType>
    class List : public MemoryConsumer {
        ValueType *mArray = {};
        unsigned long mSize = {};
        unsigned long mCapacity = {};

        Core::Expected<Core::Empty, System::AllocationError> Grow() noexcept {
            mCapacity *= 2;
            if (mArray == nullptr) {
                auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
                if (!allocationResult.HasValue()) {
                    return System::AllocationError::OutOfMemory;
                }
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                return Core::Empty();
            } else {
                auto allocationResult = mAllocator->Resize(mArray, mCapacity * sizeof(ValueType), true);
                if (!allocationResult.HasValue()) {
                    return System::AllocationError::OutOfMemory;
                }
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                return Core::Empty();
            }
        }

    public:

        template<typename T, unsigned long N>
        List(const T (&array)[N]) noexcept: mSize(0), mCapacity(N + 1) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                auto copyResult = mAllocator->Copy(array, mArray, (N * sizeof(ValueType)));
                if (copyResult.HasValue()) {
                    mSize = (mCapacity - (IsCharacterType<T>::value ? 2 : 1));
                }
            }
        }

        template<typename T, unsigned long N>
        List(System::IAllocator &allocator, const T (&array)[N]) noexcept: MemoryConsumer(allocator), mSize(0),
                                                                           mCapacity(N + 1) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                auto copyResult = mAllocator->Copy(array, mArray, (N * sizeof(ValueType)));
                if (copyResult.HasValue()) {
                    mSize = (mCapacity - (IsCharacterType<T>::value ? 2 : 1));
                }
            }
        }

        template<typename T, unsigned long N>
        List(System::IAllocator *allocator, const T (&array)[N]) noexcept: MemoryConsumer(allocator), mSize(0),
                                                                           mCapacity(N + 1) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                auto copyResult = mAllocator->Copy(array, mArray, (N * sizeof(ValueType)));
                if (copyResult.HasValue()) {
                    mSize = (mCapacity - (IsCharacterType<T>::value ? 2 : 1));
                }
            }
        }

        List(unsigned long capacity = 2) noexcept: mSize(0), mCapacity(capacity) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
            }
        }

        List(System::IAllocator &allocator, unsigned long capacity = 2) noexcept: MemoryConsumer(allocator), mSize(0),
                                                                                  mCapacity(capacity) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
            }
        }

        List(System::IAllocator *allocator, unsigned long capacity = 2) noexcept: MemoryConsumer(allocator), mSize(0),
                                                                                  mCapacity(capacity) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
            }
        }

        ~List() noexcept {
            Clear();

            auto allocationResult = mAllocator->Deallocate(mArray);
            if (!allocationResult.HasValue()) {

            }
        }

        // Copy constructor
        List(const List &other) noexcept: mSize(other.mSize), mCapacity(other.mCapacity) {
            if (mAllocator == nullptr) {
                mAllocator = other.mAllocator;
            }

            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                mAllocator->Copy(other.mArray, mArray, mSize);
            }
        }

        // Copy assignment operator
        List &operator=(const List &other) noexcept {
            if (this != &other) {
                if (mAllocator == nullptr) {
                    mAllocator = other.mAllocator;
                }

                auto deallocationResult = mAllocator->Deallocate(mArray);
                if (deallocationResult.HasValue()) {
                    mSize = other.mSize;
                    mCapacity = other.mCapacity;
                    auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
                    if (allocationResult.HasValue()) {
                        mArray = static_cast<ValueType *>(allocationResult.GetValue());
                        mAllocator->Copy(other.mArray, mArray, mSize);
                    }
                }
            }
            return *this;
        }

        // Move constructor
        List(List &&other) noexcept: mSize(other.mSize), mCapacity(other.mCapacity), mArray(other.mArray) {
            if (mAllocator == nullptr) {
                mAllocator = other.mAllocator;
            }

            other.mSize = 0;
            other.mCapacity = 0;
            other.mArray = nullptr;
        }

        // Move assignment operator
        List &operator=(List &&other) noexcept {
            if (this != &other) {
                if (mAllocator == nullptr) {
                    mAllocator = other.mAllocator;
                }

                auto allocationResult = mAllocator->Deallocate(mArray);
                if (allocationResult.HasValue()) {
                    mSize = other.mSize;
                    mCapacity = other.mCapacity;
                    mArray = other.mArray;
                    other.mSize = 0;
                    other.mCapacity = 0;
                    other.mArray = nullptr;
                }
            }
            return *this;
        }

        List &operator=(const ValueType &value) noexcept {
            auto result = this->Clear();
            if (result.HasValue()) {
                this->Add(value);
            }
            return *this;
        }

        List &operator+=(const ValueType &value) noexcept {
            this->Add(value);
            return *this;
        }

        List &operator+=(const List &other) noexcept {
            this->Add(other);
            return *this;
        }

        unsigned long GetSize() const noexcept {
            return mSize;
        }

        unsigned long GetLength() const noexcept {
            return mSize;
        }

        unsigned long GetUpperBound() const noexcept {
            return (mSize - 1);
        }

        unsigned long GetCapacity() const noexcept {
            return mCapacity;
        }

        bool IsEmpty() const noexcept {
            return !mSize;
        }

        template<typename T, unsigned long N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N]) noexcept {
            for (unsigned long i = 0; i < N; ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()) {
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        template<typename T, unsigned long N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N], unsigned long count) noexcept {
            for (unsigned long i = 0; i < Core::Math::Min(N, count); ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()) {
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        Core::Expected<Core::Empty, Core::ListError> Add(const List &other) noexcept {
            for (unsigned long i = 0; i < other.mSize; ++i) {
                auto result = Add(other.mArray[i]);
                if (!result.HasValue()) {
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        Core::Expected<ValueType *, Core::ListError> Add(ValueType value) noexcept {
            if (mSize == mCapacity || mArray == nullptr) {
                auto allocationResult = Grow();
                if (!allocationResult.HasValue()) {
                    return ListError::OutOfMemory;
                }
            }

            auto index = mSize++;
            mArray[index] = value;

            return &mArray[index];
        }

        Core::Expected<Core::Empty, Core::ListError> Remove(unsigned long index) noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            for (unsigned long i = index; i < mSize - 1; ++i) {
                mArray[i] = mArray[i + 1];
            }
            --mSize;

            return Empty();
        }

        Core::Expected<Core::Empty, Core::ListError> Remove(ValueType value) noexcept {
            unsigned long i;
            for (i = 0; i < mSize; ++i) {
                if (mArray[i] == value) {
                    mArray[i].~ValueType();
                    break;
                }
            }

            if (i < mSize) {
                for (int j = i; j < mSize - 1; ++j) {
                    mArray[j] = mArray[j + 1];
                }
                --mSize;
            } else {
                return ListError::ElementNotFound;
            }

            return Empty();
        }

        Core::Expected<Core::Empty, Core::ListError> Clear() noexcept {
            if (!IsEmpty()) {
                for (unsigned long i = 0; i < mSize; ++i) {
                    mArray[i].~ValueType();
                }
                mSize = 0;
            }

            return Core::Empty();
        }

        Core::Expected<ValueType *, Core::ListError> Get() const noexcept {
            if (!mSize) {
                return ListError::IndexOutOfRange;
            }
            return mArray;
        }

        Core::Expected<ValueType *, Core::ListError> Get(int index) const noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            return mArray[index];
        }

        Core::Expected<ValueType *, Core::ListError> Get(const ValueType &value) const noexcept {
            for (unsigned long i = 0; i < mSize; ++i) {
                if (mArray[i] == value) {
                    return mArray[i];
                }
            }

            return ListError::ElementNotFound;
        }

        Core::Expected<Core::Empty, Core::ListError> Set(int index, ValueType value) noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            mArray[index] = value;

            return Empty();
        }

        template<typename Func>
        void ForEach(Func func) {
            for (int i = 0; i < mSize; ++i) {
                func(mArray[i]);
            }
        }
    };

    template<typename T>
    using Optional = Core::List<T>;

    template<typename KeyType, typename ValueType>
    using Dictionary = Core::List<Core::Pair<KeyType, ValueType>>;

    template<typename KeyType, typename ValueType>
    using Map = Core::List<Core::Pair<KeyType, ValueType>>;

} // Core

#endif //REGULARLIBRARY_LIST_H
