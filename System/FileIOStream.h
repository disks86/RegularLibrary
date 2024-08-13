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

        bool Write(char *buffer, Index bufferLength) noexcept;

        static bool Copy(const FilePath &source, const FilePath &target) noexcept;
    };

} // System

#endif //REGULARLIBRARY_FILEIOSTREAM_H
