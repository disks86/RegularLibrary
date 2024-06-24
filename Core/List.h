//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_LIST_H
#define REGULARLIBRARY_LIST_H

#include "System/Allocator.h"

namespace Core {

    template<class ValueType>
    class List {
        ValueType* mArray={};
        System::IAllocator* mAllocator={};
        size_t mSize={};
        size_t mCapacity={};
    public:
    };

} // Core

#endif //REGULARLIBRARY_LIST_H
