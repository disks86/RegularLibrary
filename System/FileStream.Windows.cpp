#include "System/FileIOStream.h"

#include <windows.h>

System::FileIOStream::~FileIOStream() noexcept {
    if (mNativeHandle && mNativeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(mNativeHandle);
    }
}

bool System::FileIOStream::Open(const char *filePath, Index filePathLength) noexcept {
    mNativeHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return false;
    } else {
        return true;
    }
}

bool System::FileIOStream::Open(const wchar_t *filePath, Index filePathLength) noexcept {
    mNativeHandle = CreateFileW(filePath, GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (mNativeHandle == INVALID_HANDLE_VALUE) {
        return false;
    } else {
        return true;
    }
}

bool System::FileIOStream::Open(const System::FilePath &filePath) noexcept {
    if (filePath.GetLength() > MAX_PATH) {
        return false;
    }

    auto filePathResult = filePath.Get();

    if (filePathResult.HasValue()) {
        mNativeHandle = CreateFileA(filePathResult.GetValue(), GENERIC_READ | GENERIC_WRITE,
                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (mNativeHandle == INVALID_HANDLE_VALUE) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool System::FileIOStream::Open(const System::UnicodeFilePath &filePath) noexcept {
    if (filePath.GetLength() > MAX_PATH) {
        return false;
    }

    auto filePathResult = filePath.Get();

    if (filePathResult.HasValue()) {
        mNativeHandle = CreateFileW(filePathResult.GetValue(), GENERIC_READ | GENERIC_WRITE,
                                    FILE_SHARE_READ | FILE_SHARE_WRITE,
                                    nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (mNativeHandle == INVALID_HANDLE_VALUE) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

bool System::FileIOStream::Write(char *buffer, Index bufferLength) noexcept {
    //TODO: implement write.
    return true;
}

REGULAR_API bool System::FileIOStream::Copy(const System::FilePath &source, const System::FilePath &target) noexcept {
    if (source.GetLength() > MAX_PATH || target.GetLength() > MAX_PATH) {
        return false;
    }

    auto sourceResult = source.Get();
    auto targetResult = target.Get();

    if (sourceResult.HasValue() && targetResult.HasValue()) {
        return CopyFile(sourceResult.GetValue(), targetResult.GetValue(), false);
    } else {
        return false;
    }
}