//
// Created by disks on 8/12/2024.
//

#ifndef REGULARLIBRARY_IIOSTREAM_H
#define REGULARLIBRARY_IIOSTREAM_H

#include "Export.h"
#include "Core/AsciiString.h"
#include "Core/UnicodeString.h"

namespace Core {

    enum class IOStreamError {
        GenericError,
        OutOfMemory,
        OutOfBuffer,
        Aborted,
        AccessDenied,
        InvalidArgument,
        InvalidConsoleType
    };

    class REGULAR_API IIOStream {
    public:
        virtual Core::Expected<Index, Core::IOStreamError> Write(char message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(const char *message, Index messageLength) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(const Core::AsciiString &message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(const Core::AsciiStringView &message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Read(Core::AsciiString &message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(wchar_t message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError>
        Write(const wchar_t *message, Index messageLength) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(const Core::UnicodeString &message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Write(const Core::UnicodeStringView &message) noexcept = 0;

        virtual Core::Expected<Index, Core::IOStreamError> Read(Core::UnicodeString &message) noexcept = 0;
    };

} // Core

#endif //REGULARLIBRARY_IIOSTREAM_H
