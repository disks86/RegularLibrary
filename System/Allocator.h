#ifndef REGULARLIBRARY_ALLOCATOR_H
#define REGULARLIBRARY_ALLOCATOR_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/Math.h"

namespace System {

    enum class REGULAR_API AllocationError {
        GenericFailure,
        OutOfMemory
    };

    class REGULAR_API IAllocator {
    public:
        virtual Core::Expected<void *, System::AllocationError> Allocate(unsigned long size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) = 0;

        virtual Core::Expected<void *, System::AllocationError>
        Resize(void *ptr, unsigned long size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError>
        Copy(void *sourcePointer, void *targetPointer, unsigned long size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError>
        Move(void *sourcePointer, void *targetPointer, unsigned long size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, unsigned long size) = 0;

        template<typename SourceType, unsigned long SourceSize, typename TargetType, unsigned long TargetSize>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType (&source)[SourceSize], TargetType (&target)[TargetSize]) {
            void* sourcePointer = (void*)&source;
            void* targetPointer = (void*)&target;
            unsigned long size = Core::Math::Min(SourceSize * sizeof(SourceType), TargetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }

        template<typename SourceType, typename TargetType, unsigned long TargetSize>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType *source, unsigned long sourceSize, TargetType (&target)[TargetSize]) {
            void* sourcePointer = (void*)source;
            void* targetPointer = (void*)&target;
            unsigned long size = Core::Math::Min(sourceSize * sizeof(SourceType), TargetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }

        template<typename SourceType, unsigned long SourceSize, typename TargetType>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType (&source)[SourceSize], TargetType *target, unsigned long targetSize) {
            void* sourcePointer = (void*)&source;
            void* targetPointer = (void*)target;
            unsigned long size = Core::Math::Min(SourceSize * sizeof(SourceType), targetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }
    };

    class REGULAR_API Allocator : public IAllocator {
    public:
        Allocator();

        Core::Expected<void *, System::AllocationError> Allocate(unsigned long size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) noexcept;

        Core::Expected<void *, System::AllocationError> Resize(void *ptr, unsigned long size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError>
        Copy(void *sourcePointer, void *targetPointer, unsigned long size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError>
        Move(void *sourcePointer, void *targetPointer, unsigned long size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, unsigned long size) noexcept;

        static Allocator Default;
    };

} // System

#endif //REGULARLIBRARY_ALLOCATOR_H
