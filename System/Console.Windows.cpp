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

Core::Expected<unsigned long , System::ConsoleError> System::Console::Write(const Core::AsciiString& message) noexcept {
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return ConsoleError::GenericError;
    }

    const char* text = message.Get();
    DWORD textLength = message.GetLength();
    DWORD written;
    if (!WriteConsoleA(mNativeHandle, text, textLength, &written, NULL)) {
        return ConsoleError::GenericError;
    } else {
        return written;
    }
}

Core::Expected<unsigned long , System::ConsoleError> System::Console::Read(Core::AsciiString& message) noexcept {
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return ConsoleError::GenericError;
    }

    DWORD numberOfCharsRead;
    if (!ReadConsoleA(mNativeHandle,mBuffer,255, &numberOfCharsRead, NULL))
    {
        return ConsoleError::GenericError;
    }

    //TODO: clear out message object.
    auto result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        return ConsoleError::GenericError;
    }

    return numberOfCharsRead;
}