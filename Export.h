#ifndef EXPORT_H
#define EXPORT_H

#if defined(_WIN32) || defined(_WIN64)
    #ifdef BUILD_REGULARLIBRARY
        #define REGULAR_API __declspec(dllexport)
    #else
        #define REGULAR_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) && __GNUC__ >= 4
    #define REGULAR_API __attribute__((visibility("default")))
#else
    #define REGULAR_API
#endif

using Index = long;

#endif // EXPORT_H
