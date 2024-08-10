//
// Created by disks on 8/10/2024.
//

#ifndef REGULARLIBRARY_FILE_H
#define REGULARLIBRARY_FILE_H

#include "Export.h"
#include "Core/List.h"

namespace System {

    typedef Core::List<char> FilePath;
    typedef Core::List<wchar_t> UnicodeFilePath;
    typedef Core::List<char> FileBuffer;

    class REGULAR_API File {
        void *mNativeHandle = nullptr;
    public:

        File() noexcept;
        ~File() noexcept;

        bool Open(const char *filePath, Index filePathLength) noexcept;

        bool Open(const wchar_t *filePath, Index filePathLength) noexcept;

        bool Open(const FilePath &filePath) noexcept;

        bool Open(const UnicodeFilePath &filePath) noexcept;

//        template<typename T, Index N>
//        bool Open(const T (&array)[N]) noexcept {
//            return Open(array, N);
//        }
        //static bool Copy(const FilePath &source, const FilePath &target) noexcept;
    };

} // System

#endif //REGULARLIBRARY_FILE_H
