#include "Allocator.h"

#include <windows.h>

System::Allocator::Allocator() {
    mNativeHandle = GetProcessHeap();
}

Core::Expected<void *, System::AllocationError> System::Allocator::Allocate(unsigned long size, bool initialize) noexcept {
    if (mNativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    LPVOID memory = HeapAlloc(mNativeHandle, initialize ? HEAP_ZERO_MEMORY : 0, size);
    if (memory == NULL) {
        return AllocationError::OutOfMemory;
    }

    return memory;
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Deallocate(void *ptr) noexcept {
    if (mNativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    if (!HeapFree(mNativeHandle, 0, ptr)) {
        return AllocationError::GenericFailure;
    } else {
        return Core::Empty();
    }
}

Core::Expected<void *, System::AllocationError> System::Allocator::Resize(void *ptr, unsigned long size, bool initialize) noexcept {
    if (mNativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    void* resizedBlock = HeapReAlloc(mNativeHandle, initialize ? HEAP_ZERO_MEMORY : 0, ptr, size);
    if (resizedBlock == NULL) {
        return AllocationError::OutOfMemory;
    }

    return resizedBlock;
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Copy(void *sourcePointer, void *targetPointer, unsigned long size) noexcept {
    CopyMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Move(void *sourcePointer, void *targetPointer, unsigned long size) noexcept {
    MoveMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Zero(void *ptr, unsigned long size) noexcept {
    SecureZeroMemory(ptr, size);
    return Core::Empty();
}