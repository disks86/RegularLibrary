#include "Allocator.h"

#include <windows.h>

System::Allocator::Allocator() {
    NativeHandle = GetProcessHeap();
}

Core::Expected<void *, System::AllocationError> System::Allocator::Allocate(size_t size, bool initialize) noexcept {
    if (NativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    LPVOID memory = HeapAlloc(NativeHandle, initialize ? HEAP_ZERO_MEMORY : 0, size);
    if (memory == NULL) {
        return AllocationError::OutOfMemory;
    }

    return memory;
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Deallocate(void *ptr) noexcept {
    if (NativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    if (!HeapFree(NativeHandle, 0, ptr)) {
        return AllocationError::GenericFailure;
    } else {
        return Core::Empty();
    }
}

Core::Expected<void *, System::AllocationError> System::Allocator::Resize(void *ptr, size_t size, bool initialize) noexcept {
    if (NativeHandle == NULL) {
        return AllocationError::GenericFailure;
    }

    void* resizedBlock = HeapReAlloc(NativeHandle, initialize ? HEAP_ZERO_MEMORY : 0, ptr, size);
    if (resizedBlock == NULL) {
        return AllocationError::OutOfMemory;
    }

    return resizedBlock;
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Copy(void *sourcePointer, void *targetPointer, size_t size) noexcept {
    CopyMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Move(void *sourcePointer, void *targetPointer, size_t size) noexcept {
    MoveMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Zero(void *ptr, size_t size) noexcept {
    SecureZeroMemory(ptr, size);
    return Core::Empty();
}