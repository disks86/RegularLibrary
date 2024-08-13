//
// Created by disks on 8/12/2024.
//

#ifndef REGULARLIBRARY_IIOSTREAM_H
#define REGULARLIBRARY_IIOSTREAM_H

#include "Export.h"

namespace Core {

    class REGULAR_API IIOStream {
    public:
        virtual bool Write(char* buffer, Index bufferLength) noexcept = 0;
    };

} // Core

#endif //REGULARLIBRARY_IIOSTREAM_H
