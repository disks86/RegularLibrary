//
// Created by disks on 6/24/2024.
//

#ifndef REGULARLIBRARY_ASCIISTRING_H
#define REGULARLIBRARY_ASCIISTRING_H

#include "Export.h"
#include "List.h"

namespace Core {

    class REGULAR_API AsciiString : public List<char> {
    public:
        AsciiString() noexcept;

        AsciiString(System::Allocator &allocator) noexcept;

        AsciiString(System::IAllocator *allocator) noexcept;
    };

} // Core

#endif //REGULARLIBRARY_ASCIISTRING_H
