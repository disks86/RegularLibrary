//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_CONSOLE_H
#define REGULARLIBRARY_CONSOLE_H

#include "Export.h"
#include "Core/Expected.h"

namespace System {

    enum class REGULAR_API ConsoleType{
        Input,
        Output,
        Error
    };

class REGULAR_API Console
{
    void* NativeHandle;
public:
    Console(ConsoleType consoleType) noexcept;
};

} // System

#endif //REGULARLIBRARY_CONSOLE_H
