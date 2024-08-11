#include "Allocator.h"

#include <windows.h>

System::Allocator System::Allocator::Default;

System::Allocator::Allocator() {
}

Core::Expected<void *, System::AllocationError> System::Allocator::Allocate(Index size, bool initialize) noexcept {
    LPVOID memory = HeapAlloc(GetProcessHeap(), initialize ? HEAP_ZERO_MEMORY : 0, size);
    if (memory == NULL) {
        return AllocationError::OutOfMemory;
    }

    return memory;
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Deallocate(void *ptr) noexcept {
    if (!HeapFree(GetProcessHeap(), 0, ptr)) {
        return AllocationError::GenericFailure;
    } else {
        return Core::Empty();
    }
}

Core::Expected<void *, System::AllocationError>
System::Allocator::Resize(void *ptr, Index size, bool initialize) noexcept {
    void *resizedBlock = HeapReAlloc(GetProcessHeap(), initialize ? HEAP_ZERO_MEMORY : 0, ptr, size);
    if (resizedBlock == NULL) {
        return AllocationError::OutOfMemory;
    }

    return resizedBlock;
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Copy(void *sourcePointer, void *targetPointer, Index size) noexcept {
    CopyMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError>
System::Allocator::Move(void *sourcePointer, void *targetPointer, Index size) noexcept {
    MoveMemory(targetPointer, sourcePointer, size);
    return Core::Empty();
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Zero(void *ptr, Index size) noexcept {
    SecureZeroMemory(ptr, size);
    return Core::Empty();
}