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