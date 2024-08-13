//
// Created by disks on 8/12/2024.
//

#ifndef REGULARLIBRARY_ISTREAM_H
#define REGULARLIBRARY_ISTREAM_H

#include "Export.h"

namespace Core {

    class REGULAR_API IStream {
    public:
        virtual bool Write(char* buffer, Index bufferLength) noexcept = 0;
    };

} // Core

#endif //REGULARLIBRARY_ISTREAM_H
