//
// Created by disks on 8/10/2024.
//

#ifndef REGULARLIBRARY_FILEIOSTREAM_H
#define REGULARLIBRARY_FILEIOSTREAM_H

#include "Export.h"
#include "Core/List.h"
#include "Core/IIOStream.h"

namespace System {

    using UnicodeFilePath = Core::List<wchar_t>;
    using FilePath = Core::List<char>;
    using FileBuffer = Core::List<char>;

    class REGULAR_API FileIOStream : public Core::IIOStream {
        void *mNativeHandle = {};
        char mBuffer[255] = {};
    public:
        ~FileIOStream() noexcept;

        bool Open(const char *filePath, Index filePathLength) noexcept;

        bool Open(const wchar_t *filePath, Index filePathLength) noexcept;

        bool Open(const FilePath &filePath) noexcept;

        bool Open(const UnicodeFilePath &filePath) noexcept;

        template<typename T, Index N>
        bool Open(const T (&array)[N]) noexcept {
            return Open(array, N);
        }

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

        static bool Copy(const FilePath &source, const FilePath &target) noexcept;
    };

} // System

#endif //REGULARLIBRARY_FILEIOSTREAM_H
