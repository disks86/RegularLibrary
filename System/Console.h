//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_CONSOLE_H
#define REGULARLIBRARY_CONSOLE_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/AsciiString.h"
#include "Core/UnicodeString.h"

namespace System {

    enum class ConsoleType{
        Input,
        Output,
        Error
    };

    enum class ConsoleError {
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
    Core::Expected<unsigned long , System::ConsoleError> Write(char message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const char* message, unsigned long messageLength) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const Core::AsciiString& message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Read(Core::AsciiString& message) noexcept;

    Core::Expected<unsigned long , System::ConsoleError> Write(wchar_t message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const wchar_t* message, unsigned long messageLength) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Write(const Core::UnicodeString& message) noexcept;
    Core::Expected<unsigned long , System::ConsoleError> Read(Core::UnicodeString& message) noexcept;

    template <typename T, unsigned long N>
    Core::Expected<unsigned long , System::ConsoleError> Write(const T (&array)[N]) noexcept {
        return Write(array,N-1);
    }
};

} // System

#endif //REGULARLIBRARY_CONSOLE_H
