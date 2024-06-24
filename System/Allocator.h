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

        virtual Core::Expected<void *, System::AllocationError> Resize(void *ptr, size_t size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Copy(void *sourcePointer, void *targetPointer, size_t size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Move(void *sourcePointer, void *targetPointer, size_t size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, size_t size) = 0;


    };

    class REGULAR_API Allocator : public IAllocator {
        void* NativeHandle;
    public:
        Allocator();

        Core::Expected<void *, System::AllocationError> Allocate(size_t size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) noexcept;

        Core::Expected<void *, System::AllocationError> Resize(void *ptr, size_t size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Copy(void *sourcePointer, void *targetPointer, size_t size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Move(void *sourcePointer, void *targetPointer, size_t size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, size_t size) noexcept;
    };

} // System

#endif //REGULARLIBRARY_ALLOCATOR_H
