//
// Created by disks on 8/14/2024.
//

#ifndef REGULARLIBRARY_TCPCLIENT_H
#define REGULARLIBRARY_TCPCLIENT_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/AsciiString.h"
#include "Core/UnicodeString.h"
#include "Core/IIOStream.h"

namespace System {

    class REGULAR_API TCPClient : public Core::IIOStream {
    private:
        unsigned long long mConnectSocket = {};
        char mBuffer[512] = {};
    public:
        TCPClient() noexcept;

        ~TCPClient() noexcept;

        Core::Expected<bool, Core::IOStreamError> Open(const char *host, const char *port) noexcept;

        Core::Expected<bool, Core::IOStreamError> Open(const wchar_t *host, const wchar_t *port) noexcept;

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

        template<typename T>
        Core::Expected<Index, Core::IOStreamError> Write(T message) noexcept {
            return Write((char *) (&message), sizeof(T));
        }

        template<typename T, Index N>
        Core::Expected<Index, Core::IOStreamError> Write(const T (&array)[N]) noexcept {
            return Write(array, N - 1);
        }

        template<typename T, Index N>
        Core::Expected<Index, Core::IOStreamError> Write(const T (&&array)[N]) noexcept {
            return Write(array, N - 1);
        }
    };

} // System

#endif //REGULARLIBRARY_TCPCLIENT_H
