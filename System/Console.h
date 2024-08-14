//
// Created by disks on 6/23/2024.
//

#ifndef REGULARLIBRARY_CONSOLE_H
#define REGULARLIBRARY_CONSOLE_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/AsciiString.h"
#include "Core/UnicodeString.h"
#include "Core/IIOStream.h"

namespace System {

    enum class ConsoleType {
        Input,
        Output,
        Error
    };

    class REGULAR_API Console : public Core::IIOStream {
        char mBuffer[255] = {};
    public:
        Console() noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(char message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const char *message, Index messageLength) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const Core::AsciiString &message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const Core::AsciiStringView &message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Read(Core::AsciiString &message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(wchar_t message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const wchar_t *message, Index messageLength) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const Core::UnicodeString &message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Write(const Core::UnicodeStringView &message) noexcept;

        Core::Expected<Index, Core::IOStreamError> Read(Core::UnicodeString &message) noexcept;
    };

} // System

#endif //REGULARLIBRARY_CONSOLE_H
