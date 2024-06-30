//
// Created by disks on 6/30/2024.
//

#include "MemoryConsumer.h"

Core::MemoryConsumer::MemoryConsumer() noexcept : mAllocator(&System::Allocator::Default) {

}

Core::MemoryConsumer::MemoryConsumer(System::Allocator& allocator) noexcept : mAllocator(&allocator) {

}

Core::MemoryConsumer::MemoryConsumer(System::IAllocator* allocator) noexcept : mAllocator(allocator) {

}