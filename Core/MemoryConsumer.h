#ifndef REGULARLIBRARY_MEMORYCONSUMER_H
#define REGULARLIBRARY_MEMORYCONSUMER_H

#include "Allocator.h"

namespace Core {

    class REGULAR_API MemoryConsumer {
    protected:
        System::IAllocator *mAllocator = {};
    public:
        MemoryConsumer() noexcept;
        MemoryConsumer(System::IAllocator& allocator) noexcept;
        MemoryConsumer(System::IAllocator* allocator) noexcept;
    };

} // Core

#endif //REGULARLIBRARY_MEMORYCONSUMER_H
