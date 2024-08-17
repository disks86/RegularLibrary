#include "TCPClient.h"

#include <winsock2.h>
#include <ws2tcpip.h>

System::TCPClient::TCPClient() noexcept {

}

System::TCPClient::~TCPClient() noexcept {

}

Core::Expected<bool, Core::IOStreamError> System::TCPClient::Open(const char *host, const char *port) noexcept {
    if (!mConnectSocket) {
        mConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == mConnectSocket) {
            switch (WSAGetLastError()) {
                case WSA_NOT_ENOUGH_MEMORY:
                    return Core::IOStreamError::OutOfMemory;
                case WSAEACCES:
                    return Core::IOStreamError::AccessDenied;
                default:
                    return Core::IOStreamError::GenericError;
            }
        }
    }

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    auto iResult = getaddrinfo(host, port, &hints, &result);
    if (iResult != 0) {
        switch (iResult) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    ptr = result;
    iResult = connect(mConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        mConnectSocket = INVALID_SOCKET;
        return Core::IOStreamError::GenericError;
    }

    return true;
}

Core::Expected<bool, Core::IOStreamError> System::TCPClient::Open(const wchar_t *host, const wchar_t *port) noexcept {
    if (!mConnectSocket) {
        mConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == mConnectSocket) {
            switch (WSAGetLastError()) {
                case WSA_NOT_ENOUGH_MEMORY:
                    return Core::IOStreamError::OutOfMemory;
                case WSAEACCES:
                    return Core::IOStreamError::AccessDenied;
                default:
                    return Core::IOStreamError::GenericError;
            }
        }
    }

    ADDRINFOW *result = NULL, *ptr = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    auto iResult = GetAddrInfoW(host, port, &hints, &result);
    if (iResult != 0) {
        switch (iResult) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    }

    ptr = result;
    iResult = connect(mConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        mConnectSocket = INVALID_SOCKET;
        return Core::IOStreamError::GenericError;
    }

    return true;
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Write(const char message) noexcept {
    auto iResult = send(mConnectSocket, &message, 1, 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return 1;
    }
}

Core::Expected<Index, Core::IOStreamError>
System::TCPClient::Write(const char *message, Index messageLength) noexcept {
    auto iResult = send(mConnectSocket, message, (int)messageLength, 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return messageLength;
    }
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Write(const Core::AsciiString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Write(const Core::AsciiStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Read(Core::AsciiString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    auto iResult = recv(mConnectSocket, mBuffer, 512, 0);
    if (iResult > 0) {
        numberOfCharsRead = iResult;
    } else if (iResult == 0) {
        return Core::IOStreamError::AlreadyClosed;
    } else {
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
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

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Write(const wchar_t message) noexcept {
    auto iResult = send(mConnectSocket, (const char*)&message, (int)sizeof(wchar_t), 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return sizeof(wchar_t);
    }
}

Core::Expected<Index, Core::IOStreamError>
System::TCPClient::Write(const wchar_t *message, Index messageLength) noexcept {
    DWORD written;
    auto iResult = send(mConnectSocket, (const char*)message, (int)(messageLength*sizeof(wchar_t)), 0);
    if (iResult == SOCKET_ERROR) {
        closesocket(mConnectSocket);
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
            default:
                return Core::IOStreamError::GenericError;
        }
    } else {
        return (messageLength*sizeof(wchar_t));
    }
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Write(const Core::UnicodeString &message) noexcept {
    auto result = message.Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    return Write(result.GetValue(), message.GetLength());
}

Core::Expected<Index, Core::IOStreamError>
System::TCPClient::Write(const Core::UnicodeStringView &message) noexcept {
    auto result = message.GetList().Get();
    if (!result.HasValue()) {
        return Core::IOStreamError::GenericError;
    }

    auto array = result.GetValue();
    array += message.GetIndex();

    return Write(array, message.GetLength());
}

Core::Expected<Index, Core::IOStreamError> System::TCPClient::Read(Core::UnicodeString &message) noexcept {
    DWORD numberOfCharsRead = 0;
    auto iResult = recv(mConnectSocket, mBuffer, 512, 0);
    if (iResult > 0) {
        numberOfCharsRead = iResult;
    } else if (iResult == 0) {
        return Core::IOStreamError::AlreadyClosed;
    } else {
        switch (WSAGetLastError()) {
            case WSA_NOT_ENOUGH_MEMORY:
                return Core::IOStreamError::OutOfMemory;
            case WSAEACCES:
                return Core::IOStreamError::AccessDenied;
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