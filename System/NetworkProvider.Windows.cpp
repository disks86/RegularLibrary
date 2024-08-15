#include "NetworkProvider.h"

#include <winsock2.h>
#include <ws2tcpip.h>

System::NetworkProvider::NetworkProvider() noexcept {
    WSADATA wsaData;
    mResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    mMaxSockets = wsaData.iMaxSockets;
    mMaxUdpMessageSize = wsaData.iMaxUdpDg;
}

System::NetworkProvider::~NetworkProvider() noexcept {
    WSACleanup();
}