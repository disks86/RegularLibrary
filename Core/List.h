//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_LIST_H
#define REGULARLIBRARY_LIST_H

#include "System/Allocator.h"
#include "Core/Math.h"

namespace Core {

    enum class REGULAR_API ListError {
        IndexOutOfRange,
        OutOfMemory
    };

    template<class ValueType>
    class REGULAR_API List {
        ValueType *mArray = {};
        System::IAllocator *mAllocator = {};
        unsigned long mSize = {};
        unsigned long mCapacity = {};

        Core::Expected<Core::Empty, System::AllocationError> Grow() noexcept {
            mCapacity *= 2;
            auto allocationResult = mAllocator->Resize(mArray, mCapacity* sizeof(ValueType), false);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                return Core::Empty();
            } else {
                return System::AllocationError::OutOfMemory;
            }
        }

    public:
        List() noexcept: mSize(0), mCapacity(2) {
            auto allocationResult = mAllocator->Allocate(mCapacity* sizeof(ValueType), false);
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
            auto allocationResult = mAllocator->Allocate(mCapacity* sizeof(ValueType), false);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
                mAllocator->Copy(other.mArray, mArray, mSize);
            }
        }

        // Copy assignment operator
        List &operator=(const List &other) noexcept {
            if (this != &other) {
                auto deallocationResult = mAllocator->Deallocate(mArray);
                if (deallocationResult.HasValue()) {
                    mSize = other.mSize;
                    mCapacity = other.mCapacity;
                    auto allocationResult = mAllocator->Allocate(mCapacity* sizeof(ValueType), false);
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
            other.mSize = 0;
            other.mCapacity = 0;
            other.mArray = nullptr;
        }

        // Move assignment operator
        List &operator=(List &&other) noexcept {
            if (this != &other) {
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

        template <typename T, unsigned long N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N]) noexcept {
            for (unsigned long i = 0; i < N; ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()){
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        template <typename T, unsigned long N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N], unsigned long count) noexcept {
            for (unsigned long i = 0; i < Core::Math::Min(N,count); ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()){
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        Core::Expected<ValueType*, Core::ListError> Add(ValueType value) noexcept {
            if (mSize == mCapacity) {
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

        Core::Expected<Core::Empty, Core::ListError> Clear() noexcept {
            for (unsigned long i = 0; i < mSize; ++i) {
                mArray[i].~ValueType();
            }
            mSize = 0;

            return Core::Empty();
        }

        Core::Expected<ValueType*, Core::ListError> Get() const noexcept {
            if (!mSize) {
                return ListError::IndexOutOfRange;
            }
            return mArray;
        }

        Core::Expected<ValueType*, Core::ListError> Get(int index) const noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            return mArray[index];
        }

        Core::Expected<Core::Empty, Core::ListError> Set(int index, ValueType value) noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            mArray[index] = value;

            return Empty();
        }
    };

} // Core

#endif //REGULARLIBRARY_LIST_H
