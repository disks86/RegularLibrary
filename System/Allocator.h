#ifndef REGULARLIBRARY_ALLOCATOR_H
#define REGULARLIBRARY_ALLOCATOR_H

#include "Export.h"
#include "Core/Expected.h"

namespace System {

    enum class REGULAR_API AllocationError {
        GenericFailure,
        OutOfMemory
    };

    class REGULAR_API IAllocator {
    public:
        virtual Core::Expected<void *, System::AllocationError> Allocate(size_t size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) = 0;
    };

    class REGULAR_API Allocator : public IAllocator {
    public:
        Allocator();

        Core::Expected<void *, System::AllocationError> Allocate(size_t size, bool initialize);

        Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr);
    };

} // System

#endif //REGULARLIBRARY_ALLOCATOR_H
