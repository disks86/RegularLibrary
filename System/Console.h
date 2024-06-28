//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_CONSOLE_H
#define REGULARLIBRARY_CONSOLE_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/AsciiString.h"

namespace System {

    enum class REGULAR_API ConsoleType{
        Input,
        Output,
        Error
    };

    enum class REGULAR_API ConsoleError{
        GenericError
    };

class REGULAR_API Console
{
    void* mNativeHandle;
    char mBuffer[255] = {};
public:
    Console(ConsoleType consoleType) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const Core::AsciiString& message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Read(Core::AsciiString& message) noexcept;
};

} // System

#endif //REGULARLIBRARY_CONSOLE_H
