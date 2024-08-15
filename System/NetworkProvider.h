//
// Created by disks on 8/14/2024.
//

#ifndef REGULARLIBRARY_NETWORKPROVIDER_H
#define REGULARLIBRARY_NETWORKPROVIDER_H

#include "Export.h"
#include "Core/Expected.h"
#include "Core/AsciiString.h"
#include "Core/UnicodeString.h"
#include "Core/IIOStream.h"

namespace System {

    class REGULAR_API NetworkProvider {
    private:
        int mResult = 0;
        int mMaxSockets = 0;
        int mMaxUdpMessageSize = 0;
    public:
        NetworkProvider() noexcept;
        ~NetworkProvider() noexcept;
        inline int GetMaxSockets() const noexcept {return mMaxSockets;}
        inline int GetMaxUdpMessageSize() const noexcept {return mMaxUdpMessageSize;}
    };

} // System

#endif //REGULARLIBRARY_NETWORKPROVIDER_H
