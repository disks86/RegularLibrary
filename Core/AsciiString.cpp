
#include "AsciiString.h"

Core::AsciiString::AsciiString() noexcept: List() {

}

Core::AsciiString::AsciiString(System::Allocator &allocator) noexcept: List(allocator) {

}

Core::AsciiString::AsciiString(System::IAllocator *allocator) noexcept: List(allocator) {

}