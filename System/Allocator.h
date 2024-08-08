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
        virtual Core::Expected<void *, System::AllocationError> Allocate(Index size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) = 0;

        virtual Core::Expected<void *, System::AllocationError>
        Resize(void *ptr, Index size, bool initialize) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError>
        Copy(void *sourcePointer, void *targetPointer, Index size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError>
        Move(void *sourcePointer, void *targetPointer, Index size) = 0;

        virtual Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, Index size) = 0;

        template<typename SourceType, Index SourceSize, typename TargetType, Index TargetSize>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType (&source)[SourceSize], TargetType (&target)[TargetSize]) {
            void* sourcePointer = (void*)&source;
            void* targetPointer = (void*)&target;
            Index size = Core::Math::Min(SourceSize * sizeof(SourceType), TargetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }

        template<typename SourceType, typename TargetType, Index TargetSize>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType *source, Index sourceSize, TargetType (&target)[TargetSize]) {
            void* sourcePointer = (void*)source;
            void* targetPointer = (void*)&target;
            Index size = Core::Math::Min(sourceSize * sizeof(SourceType), TargetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }

        template<typename SourceType, Index SourceSize, typename TargetType>
        Core::Expected<Core::Empty, System::AllocationError>
        Copy(const SourceType (&source)[SourceSize], TargetType *target, Index targetSize) {
            void* sourcePointer = (void*)&source;
            void* targetPointer = (void*)target;
            Index size = Core::Math::Min(SourceSize * sizeof(SourceType), targetSize * sizeof(TargetType));
            return Copy(sourcePointer, targetPointer, size);
        }
    };

    class REGULAR_API Allocator : public IAllocator {
    public:
        Allocator();

        Core::Expected<void *, System::AllocationError> Allocate(Index size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Deallocate(void *ptr) noexcept;

        Core::Expected<void *, System::AllocationError> Resize(void *ptr, Index size, bool initialize) noexcept;

        Core::Expected<Core::Empty, System::AllocationError>
        Copy(void *sourcePointer, void *targetPointer, Index size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError>
        Move(void *sourcePointer, void *targetPointer, Index size) noexcept;

        Core::Expected<Core::Empty, System::AllocationError> Zero(void *ptr, Index size) noexcept;

        static Allocator Default;
    };

} // System

#endif //REGULARLIBRARY_ALLOCATOR_H
