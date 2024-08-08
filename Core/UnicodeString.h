//
// Created by disks on 7/24/2024.
//

#ifndef REGULARLIBRARY_UNICODESTRING_H
#define REGULARLIBRARY_UNICODESTRING_H

#include "Export.h"
#include "List.h"

namespace Core {

    typedef List<wchar_t> UnicodeString;
    typedef ListView<wchar_t> UnicodeStringView;

} // Core

#endif //REGULARLIBRARY_UNICODESTRING_H
