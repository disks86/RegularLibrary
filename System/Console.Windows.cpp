#include "Console.h"

#include <windows.h>

System::Console::Console(ConsoleType consoleType) noexcept {
    switch (consoleType) {
        case ConsoleType::Input:
            NativeHandle = GetStdHandle(STD_INPUT_HANDLE);
            break;
        case ConsoleType::Output:
            NativeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
            break;
        default:
            NativeHandle = GetStdHandle(STD_ERROR_HANDLE);
            break;
    }
}

Core::Expected<unsigned long , System::ConsoleError> System::Console::Write(const Core::AsciiString& message) noexcept {
    if (NativeHandle == INVALID_HANDLE_VALUE) {
        return ConsoleError::GenericError;
    }

    const char* text = message.Get();
    DWORD textLength = message.GetLength();
    DWORD written;
    if (!WriteConsoleA(NativeHandle, text, textLength, &written, NULL)) {
        return ConsoleError::GenericError;
    } else {
        return written;
    }
}