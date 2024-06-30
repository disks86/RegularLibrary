#include "Console.h"

#include <windows.h>

System::Console::Console(ConsoleType consoleType) noexcept {
    switch (consoleType) {
        case ConsoleType::Input:
            mNativeHandle = GetStdHandle(STD_INPUT_HANDLE);
            break;
        case ConsoleType::Output:
            mNativeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            break;
        default:
            mNativeHandle = GetStdHandle(STD_ERROR_HANDLE);
            break;
    }
}

Core::Expected<unsigned long, System::ConsoleError>
System::Console::Write(const char *message, unsigned long messageLength) noexcept {
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return ConsoleError::InvalidConsoleType;
    }

    DWORD written;
    if (!WriteConsoleA(mNativeHandle, message, messageLength, &written, NULL)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
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
    return Write(message.Get(), message.GetLength());
}

Core::Expected<unsigned long, System::ConsoleError> System::Console::Read(Core::AsciiString &message) noexcept {
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return ConsoleError::InvalidConsoleType;
    }

    DWORD numberOfCharsRead;
    if (!ReadConsoleA(mNativeHandle, mBuffer, 255, &numberOfCharsRead, NULL)) {
        return ConsoleError::GenericError;
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return ConsoleError::GenericError;
    }
    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        return ConsoleError::GenericError;
    }

    return numberOfCharsRead;
}