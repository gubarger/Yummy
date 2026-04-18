// clang-format off
/**
 * @file memo_hash.h
 * @brief Custom hash functionality for rule identification (for std::unordered_map).
 * @license MIT
 * @author Gubarger
 *
 * @see https://en.cppreference.com/cpp/utility/hash
 */
// clang-format on

#pragma once

#include <functional>

namespace yummy::utils {
struct MemoKey {
  int rule;
  size_t position;

  bool operator==(const MemoKey& key) const = default;
};

/**
 * @brief Implements the classic hash_combine
 */
struct MemoKeyHash {
  size_t operator()(const MemoKey& key) const noexcept {
    size_t seed = 0;
    seed ^= std::hash<int>{}(key.rule) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= std::hash<size_t>{}(key.position) + 0x9e3779b9 + (seed << 6) +
            (seed >> 2);
    return seed;
  }
};
}  // namespace yummy::utils