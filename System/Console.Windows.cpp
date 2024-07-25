#include "Console.h"

#include <windows.h>

System::Console::Console()
{
    AllocConsole();
}

Core::Expected<unsigned long , System::ConsoleError> System::Console::Write(const char message) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return ConsoleError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, &message, 1, &written, NULL)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_HANDLE:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return ConsoleError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return ConsoleError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return ConsoleError::GenericError;
            case ERROR_ACCESS_DENIED:
                return ConsoleError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return ConsoleError::Aborted;
            default:
                return ConsoleError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<unsigned long, System::ConsoleError>
System::Console::Write(const char *message, unsigned long messageLength) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return ConsoleError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, message, messageLength, &written, NULL)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_HANDLE:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return ConsoleError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return ConsoleError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return ConsoleError::GenericError;
            case ERROR_ACCESS_DENIED:
                return ConsoleError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return ConsoleError::Aborted;
            default:
                return ConsoleError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<unsigned long, System::ConsoleError> System::Console::Write(const Core::AsciiString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return ConsoleError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<unsigned long, System::ConsoleError> System::Console::Read(Core::AsciiString &message) noexcept {
    DWORD numberOfCharsRead=0;
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return ConsoleError::InvalidConsoleType;
    }

    if (!ReadFile(hConsole, mBuffer, 255, &numberOfCharsRead, NULL)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_HANDLE:
                return ConsoleError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return ConsoleError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return ConsoleError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return ConsoleError::GenericError;
            case ERROR_ACCESS_DENIED:
                return ConsoleError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return ConsoleError::Aborted;
            default:
                return ConsoleError::GenericError;
        }
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return ConsoleError::GenericError;
    }

    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        switch (result.GetError()) {
            case Core::ListError::OutOfMemory:
                return ConsoleError::OutOfMemory;
            default:
                return ConsoleError::GenericError;
        }
    }

    return numberOfCharsRead;
}