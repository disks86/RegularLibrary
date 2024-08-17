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

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Write(const char message) noexcept {
    DWORD written;
    if (!WriteFile(mNativeHandle, &message, 1, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError>
System::FileIOStream::Write(const char *message, Index messageLength) noexcept {
    DWORD written;
    if (!WriteFile(mNativeHandle, message, messageLength, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Write(const Core::AsciiString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Write(const Core::AsciiStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Read(Core::AsciiString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    if (!ReadFile(mNativeHandle, mBuffer, 255, &numberOfCharsRead, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        switch (result.GetError()) {
            case Core::ListError::OutOfMemory:
                return Core::IOStreamError::OutOfMemory;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    return numberOfCharsRead;
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Write(const wchar_t message) noexcept {
    DWORD written;
    if (!WriteFile(mNativeHandle, &message, 1, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError>
System::FileIOStream::Write(const wchar_t *message, Index messageLength) noexcept {
    DWORD written;
    if (!WriteFile(mNativeHandle, message, messageLength, &written, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return written;
    }
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Write(const Core::UnicodeString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError>
System::FileIOStream::Write(const Core::UnicodeStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::FileIOStream::Read(Core::UnicodeString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    if (!ReadFile(mNativeHandle, mBuffer, 255, &numberOfCharsRead, nullptr)) {
        DWORD errorCode = GetLastError();
        switch (errorCode) {
            case ERROR_INVALID_FUNCTION:
            case ERROR_INVALID_HANDLE:
                return Core::IOStreamError::InvalidConsoleType;
            case ERROR_INVALID_PARAMETER:
                return Core::IOStreamError::InvalidArgument;
            case ERROR_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case ERROR_NOT_ENOUGH_QUOTA:
                return Core::IOStreamError::GenericError;
            case ERROR_ACCESS_DENIED:
                return Core::IOStreamError::AccessDenied;
            case ERROR_OPERATION_ABORTED:
                return Core::IOStreamError::Aborted;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    auto result = message.Clear();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    result = message.Add(mBuffer, numberOfCharsRead);
    if (!result.HasValue()) {
        switch (result.GetError()) {
            case Core::ListError::OutOfMemory:
                return Core::IOStreamError::OutOfMemory;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    return numberOfCharsRead;
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