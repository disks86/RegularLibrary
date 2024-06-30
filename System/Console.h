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

    enum class REGULAR_API ConsoleError {
        GenericError,
        OutOfMemory,
        OutOfBuffer,
        Aborted,
        AccessDenied,
        InvalidArgument,
        InvalidConsoleType
    };

class REGULAR_API Console
{
    char mBuffer[255] = {};
public:
    Console();
    Core::Expected<unsigned long , System::ConsoleError> Write(const char* message, unsigned long messageLength) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const Core::AsciiString& message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Read(Core::AsciiString& message) noexcept;

    template <typename T, unsigned long N>
    Core::Expected<unsigned long , System::ConsoleError> Write(const T (&array)[N]) noexcept {
        return Write(array,N-1);
    }
};

} // System

#endif //REGULARLIBRARY_CONSOLE_H
