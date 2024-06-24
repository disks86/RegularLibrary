#include "Allocator.h"

#include <windows.h>

System::Allocator::Allocator() {

}

Core::Expected<void *, System::AllocationError> System::Allocator::Allocate(size_t size, bool initialize) {
    HANDLE heap = GetProcessHeap();
    if (heap == NULL) {
        return AllocationError::GenericFailure;
    }

    LPVOID memory = HeapAlloc(heap, initialize ? HEAP_ZERO_MEMORY : 0, size);
    if (heap == NULL) {
        return AllocationError::OutOfMemory;
    }

    return memory;
}

Core::Expected<Core::Empty, System::AllocationError> System::Allocator::Deallocate(void *ptr) {
    HANDLE heap = GetProcessHeap();
    if (heap == NULL) {
        return AllocationError::GenericFailure;
    }

    if (!HeapFree(heap, 0, ptr)) {
        return AllocationError::GenericFailure;
    } else {
        return Core::Empty();
    }
}