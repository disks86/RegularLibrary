//
// Created by disks on 8/10/2024.
//

#ifndef REGULARLIBRARY_FILESTREAM_H
#define REGULARLIBRARY_FILESTREAM_H

#include "Export.h"
#include "Core/List.h"
#include "Core/IStream.h"

namespace System {

    typedef Core::List<char> FilePath;
    typedef Core::List<wchar_t> UnicodeFilePath;
    typedef Core::List<char> FileBuffer;

    class REGULAR_API FileStream : public Core::IStream {
        void *mNativeHandle = nullptr;
    public:
        ~FileStream() noexcept;

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

#endif //REGULARLIBRARY_FILESTREAM_H
