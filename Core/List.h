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

    template<typename T>
    struct IsCharacterType {
        static constexpr bool value = false;
    };

    template<>
    struct IsCharacterType<char> {
        static constexpr bool value = true;
    };

    template<>
    struct IsCharacterType<wchar_t> {
        static constexpr bool value = true;
    };

    enum class REGULAR_API ListError {
        IndexOutOfRange,
        OutOfMemory,
        ElementNotFound
    };

    template<typename ValueType>
    class List;

    template<typename ValueType>
    class ListView {
        const List<ValueType> *mList;
        Index mIndex;
        Index mLength;
    public:
        ListView(const List<ValueType> *list, Index index, Index length)
        noexcept: mList(list), mIndex(index), mLength(length) {

        }

        // Copy constructor
        ListView(const ListView<ValueType> &other) noexcept: mList(other.mList), mIndex(other.mIndex),
                                                             mLength(other.mLength) {

        }

        // Copy assignment operator
        ListView &operator=(const ListView &other) noexcept {
            mList = other.mList;
            mIndex = other.mIndex;
            mLength = other.mLength;

            return *this;
        }

        // Move constructor
        ListView(const ListView<ValueType> &&other) noexcept: mList(other.mList), mIndex(other.mIndex),
                                                              mLength(other.mLength) {

        }

        const List<ValueType> &GetList() const noexcept {
            return (*mList);
        }

        Index GetIndex() const noexcept {
            return mIndex;
        }

        Index GetLength() const noexcept {
            return mLength;
        }
    };

    template<typename ValueType>
    class List : public MemoryConsumer {
        ValueType *mArray = {};
        Index mSize = {};
        Index mCapacity = {};

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

        template<typename T, Index N>
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

        template<typename T, Index N>
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

        template<typename T, Index N>
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

        List(Index capacity = 2) noexcept: mSize(0), mCapacity(capacity) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
            }
        }

        List(System::IAllocator &allocator, Index capacity = 2) noexcept: MemoryConsumer(allocator), mSize(0),
                                                                          mCapacity(capacity) {
            auto allocationResult = mAllocator->Allocate(mCapacity * sizeof(ValueType), true);
            if (allocationResult.HasValue()) {
                mArray = static_cast<ValueType *>(allocationResult.GetValue());
            }
        }

        List(System::IAllocator *allocator, Index capacity = 2) noexcept: MemoryConsumer(allocator), mSize(0),
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

        Index GetSize() const noexcept {
            return mSize;
        }

        Index GetLength() const noexcept {
            return mSize;
        }

        Index GetUpperBound() const noexcept {
            return (mSize - 1);
        }

        Index GetCapacity() const noexcept {
            return mCapacity;
        }

        bool IsEmpty() const noexcept {
            return !mSize;
        }

        template<typename T, Index N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N]) noexcept {
            for (Index i = 0; i < N; ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()) {
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        template<typename T, Index N>
        Core::Expected<Core::Empty, Core::ListError> Add(const T (&array)[N], Index count) noexcept {
            for (Index i = 0; i < Core::Math::Min(N, count); ++i) {
                auto result = Add(array[i]);
                if (!result.HasValue()) {
                    return result.GetError();
                }
            }

            return Core::Empty();
        }

        Core::Expected<Core::Empty, Core::ListError> Add(const List &other) noexcept {
            for (Index i = 0; i < other.mSize; ++i) {
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

        Core::Expected<Core::Empty, Core::ListError> Remove(Index index) noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            for (Index i = index; i < mSize - 1; ++i) {
                mArray[i] = mArray[i + 1];
            }
            --mSize;

            return Empty();
        }

        Core::Expected<Core::Empty, Core::ListError> Remove(ValueType value) noexcept {
            Index i;
            for (i = 0; i < mSize; ++i) {
                if (mArray[i] == value) {
                    mArray[i].~ValueType();
                    break;
                }
            }

            if (i < mSize) {
                for (Index j = i; j < mSize - 1; ++j) {
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
                for (Index i = 0; i < mSize; ++i) {
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

        Core::Expected<ValueType *, Core::ListError> Get(Index index) const noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            return mArray[index];
        }

        Core::Expected<ValueType *, Core::ListError> Get(const ValueType &value) const noexcept {
            for (Index i = 0; i < mSize; ++i) {
                if (mArray[i] == value) {
                    return mArray[i];
                }
            }

            return ListError::ElementNotFound;
        }

        Core::Expected<Core::Empty, Core::ListError> Set(Index index, ValueType value) noexcept {
            if (index < 0 || index >= mSize) {
                return ListError::IndexOutOfRange;
            }
            mArray[index] = value;

            return Empty();
        }

        template<typename Func>
        void ForEach(Func func) noexcept {
            for (Index i = 0; i < mSize; ++i) {
                func(mArray[i]);
            }
        }

        ListView<ValueType> Slice(Index index, Index length) const noexcept {
            Index safeIndex = Core::Math::Min(index, mSize);
            Index safeLength = Core::Math::Min(length, index + mSize);
            ListView<ValueType> view(this, safeIndex, safeLength);
            return view;
        }

        bool StartsWith(const ValueType &value) const noexcept {
            return mSize && (mArray[0] == value);
        }

        bool EndsWith(const ValueType &value) const noexcept {
            return mSize && (mArray[(mSize-1)] == value);
        }

        bool Split(const ValueType &value, List<ListView<ValueType>> &pieces) {
            Index start = -1;
            Index length = -1;

            for (Index i = 0; i < mSize; ++i) {
                if (mArray[i] == value) {
                    if (start > -1) {
                        length = (i - start) + 1;
                        pieces.Add(ListView<ValueType>(this, start, length));
                        start = -1;
                    } else {
                        pieces.Add(ListView<ValueType>(this, 0, i + 1));
                        start = i + 1;
                    }
                }
            }

            if (start > -1) {
                length = ((mSize - 1) - start) + 1;
                pieces.Add(ListView<ValueType>(this, start, length));
            }

            return pieces.GetLength();
        }

        void Replace(const ValueType &from, const ValueType &to) {
            for (Index i = 0; i < mSize; ++i) {
                if (mArray[i] == from) {
                    mArray[i] = to;
                }
            }
        }

        void Replace(const List<ValueType> &from, const List<ValueType> &to) {
            for (int i = 0; i <= mSize - from.mSize; i++) {
                bool match = true;
                for (int j = 0; j < from.mSize; j++) {
                    if (mArray[i + j] != from.mArray[j]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    if (to.mSize != from.mSize) {
                        int shift = to.mSize - from.mSize;
                        if (shift > 0) { // Insert space
                            for (int k = mSize - 1; k >= i + from.mSize; k--) {
                                mArray[k + shift] = mArray[k];
                            }
                        } else { // Remove space
                            for (int k = i + from.mSize; k < mSize; k++) {
                                mArray[k + shift] = mArray[k];
                            }
                        }
                        mSize += shift;
                    }

                    for (int j = 0; j < to.mSize; j++) {
                        mArray[i + j] = to.mArray[j];
                    }
                }
            }
        }

        void TrimStart(const ValueType &value) {
            int index = 0;

            while (index < mSize && mArray[index] == value) {
                index++;
            }

            for (int i = index; i < mSize; i++) {
                mArray[i - index] = mArray[i];
            }

            mSize -= index;
        }

        void TrimEnd(const ValueType &value) {
            int index = mSize - 1;

            while (index >= 0 && mArray[index] == value) {
                index--;
            }

            mSize = index + 1;
        }

        void Trim(const ValueType &value) {
            TrimStart(value);
            TrimEnd(value);
        }

        void Sort() {
            for (int i = 0; i < mSize - 1; i++) {
                for (int j = 0; j < mSize - i - 1; j++) {
                    if (mArray[j] > mArray[j + 1]) {
                        int temp = mArray[j];
                        mArray[j] = mArray[j + 1];
                        mArray[j + 1] = temp;
                    }
                }
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
