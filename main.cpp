#include <functional>
#include <iostream>
#include <vector>

#include <cctype>
#include "stats.h"

// the pair of function pointer and its name
using pair = std::pair<std::function<bool(std::vector<u8>&)>, std::string>;
using fn_vec = const std::vector<pair>;

template <typename T>
T random(T max) {
    return rand() % max;
}

template <typename T>
T random(T min, T max) {
    return min + rand() % (max - min);
}

template <typename T>
inline void black_box(T value) {
    // std::cerr << value << std::endl;
    asm volatile("" : : "r,m"(value) : "memory");
}

u8 generate_ascii_char() {
    return random<u8>(1, 127);
}

auto generate_ascii_vec(usize len) -> std::vector<u8> {
    auto vec = std::vector<u8>(len);
    for (usize i = 0; i < len; i++) {
        vec[i] = generate_ascii_char();
    }
    return vec;
}

bool c_is_ascii(std::span<u8> vec) {
    for (auto c : vec) {
        isascii(c);
    }
    return true;
}

bool is_acsii_bit(std::span<u8> vec) {
    for (auto c : vec) {
        if (c & 0x80) {
            return false;
        }
    }
    return true;
}

bool is_ascii_bit_chunked(std::span<u8> vec) {
    constexpr usize chunk_size = 16;
    for (usize i = 0; i + chunk_size < vec.size(); i += chunk_size) {

        auto chunk = &vec[i];
        for (usize j = 0; j < chunk_size; j++) {
            if (chunk[j] & 0x80) {
                return false;
            }
        }

    }

    auto leftover = vec.size() % chunk_size;
    auto start = vec.size() - leftover;
    is_acsii_bit(vec.subspan(start));
    return true;
}

#include <immintrin.h>
bool is_ascii_bit_intrinsics(std::span<u8> vec) {
    constexpr usize chunk_size = 16;
    auto ptr = (u8*) vec.data();
    auto vec_end = vec.data() + vec.size();

    auto mask = _mm_set1_epi8(0x80);
    while (ptr + chunk_size < vec_end) {
        auto v = _mm_load_si128((__m128i*) ptr);
        auto result = _mm_cmpeq_epi8(_mm_and_si128(v, mask), mask);
        if (_mm_movemask_epi8(result) != 0) {
            return false;
        }
        ptr += chunk_size;
    }

    while (ptr < vec_end) {
        if (*ptr & 0x80) {
            return false;
        }
        ptr++;
    }
    return true;
}

auto a_lot_of_iters(usize len, usize iters, fn_vec& functions) -> void {
    auto chars = generate_ascii_vec(len);
    for (auto [fn, name] : functions) {
        auto time = clock::now();
        for (usize i = 0; i < iters; i++) {
            black_box(fn(chars));
        }
        auto elapsed = duration(clock::now() - time).count();

        auto ss = std::stringstream();
        ss << name << "(" << len << ", " << iters << ")";
        std::cout << Stats(ss.str(), elapsed, len * iters) << std::endl;
    }
}

auto functions = fn_vec {
    {c_is_ascii,              "c_is_ascii             "},
    {is_acsii_bit,            "is_acsii_bit           "},
    {is_ascii_bit_chunked,    "is_ascii_bit_chunked   "},
    {is_ascii_bit_intrinsics, "is_ascii_bit_intrinsics"},
};

int test_performance() {
    auto iters = 100'000;
    auto string_sizes = std::vector<usize>{10, 25, 50, 100, 200, 300};

    for (auto len : string_sizes) {
        a_lot_of_iters(len, iters, functions);
        std::cout << std::endl;
    }

    for (auto len : std::vector<usize>{100 * MB}) {
        a_lot_of_iters(len, 1, functions);
        std::cout << std::endl;
    }
    return 0;
}

void test_logic() {
    for (auto [fn, name] : functions) {
        auto vec = generate_ascii_vec(20);
        auto is_ascii = fn(vec);
        std::cout << name << " " << (is_ascii ? "OK" : "FAIL") << std::endl;
    }

    for (auto [fn, name] : functions) {
        auto vec = generate_ascii_vec(10);
        for (usize i = 0; i < 10; i++) {
            vec.push_back(random<u8>(128, 255));
        }
        auto is_ascii = fn(vec);
        std::cout << name << " " << (!is_ascii ? "OK" : "FAIL") << std::endl;
    }
}

int main() { test_performance(); }
// int main() { test_logic(); }
