#ifndef REGULARLIBRARY_PAIR_H
#define REGULARLIBRARY_PAIR_H

namespace Core {

    template<typename KeyType, typename ValueType>
    struct Pair {
        KeyType Key;
        ValueType Value;

        auto operator<=>(const Pair& other) const {
            return (Key <=> other.Key);
        }

        Pair(KeyType key) : Key(key),Value({}) {}

        operator ValueType() const {
            return Value;
        }
    };

} // Core

#endif //REGULARLIBRARY_PAIR_H
