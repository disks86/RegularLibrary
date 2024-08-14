#include "Console.h"

#include <windows.h>

System::Console::Console() noexcept {
    AllocConsole();
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const char message) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, &message, 1, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError>
System::Console::Write(const char *message, Index messageLength) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, message, messageLength, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const Core::AsciiString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const Core::AsciiStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::Console::Read(Core::AsciiString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!ReadFile(hConsole, mBuffer, 255, &numberOfCharsRead, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        switch (result.GetError()) {
            case Core::ListError::OutOfMemory:
                return Core::IOStreamError::OutOfMemory;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    return numberOfCharsRead;
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const wchar_t message) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, &message, 1, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError>
System::Console::Write(const wchar_t *message, Index messageLength) noexcept {
    DWORD written;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!WriteFile(hConsole, message, messageLength, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const Core::UnicodeString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::Console::Write(const Core::UnicodeStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::Console::Read(Core::UnicodeString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Core::IOStreamError::InvalidConsoleType;
    }

    if (!ReadFile(hConsole, mBuffer, 255, &numberOfCharsRead, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        switch (result.GetError()) {
            case Core::ListError::OutOfMemory:
                return Core::IOStreamError::OutOfMemory;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    return numberOfCharsRead;
}