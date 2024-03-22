#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cmath>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;

using f32 = _Float32;
using f64 = _Float64;

constexpr usize B = 1;
constexpr usize KB = 1024 * B;
constexpr usize MB = 1024 * KB;
constexpr usize GB = 1024 * MB;

constexpr usize NS = 1;
constexpr usize US = 1000 * NS;
constexpr usize MS = 1000 * US;
constexpr usize S = 1000 * MS;
constexpr usize M = 60 * S;

namespace {
    using clock = std::chrono::high_resolution_clock;

    constexpr std::chrono::nanoseconds (*duration) (
        const std::chrono::duration<
            std::chrono::high_resolution_clock::rep,
            std::chrono::high_resolution_clock::period
        >&
    ) = std::chrono::duration_cast<std::chrono::nanoseconds>;

}

struct Stats {
    Stats(std::string name, usize time, usize size)
        : name(name), time(time), size(size) {
        rate = (f32) size / time;
    }

    std::string name;
    usize time;
    usize size;
    f32 rate;
};

auto fmt(f32 value, usize precision = 0) -> std::string {
    auto stream = std::stringstream();
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

auto fmt_size(usize size) -> std::string {
    if (false);
    else if (size < KB) return fmt(size / B)  + " b";
    else if (size < MB) return fmt(size / KB) + " kb";
    else if (size < GB) return fmt(size / MB) + " mb";
    else                return fmt(size / GB) + " gb";
}

auto fmt_time(usize time) -> std::string {
    if (false);
    else if (time < US) return fmt((f32) time / NS, 2) + " ns";
    else if (time < MS) return fmt((f32) time / US, 2) + " us";
    else if (time < S)  return fmt((f32) time / MS, 2) + " ms";
    else                return fmt((f32) time / S,  2)  + " s";
}

auto fmt_rate(f32 rate) -> std::string {
    auto rate_in_bps = rate * S;
    if (false);
    else if (rate_in_bps < KB) return fmt((f32) rate_in_bps / B,  2)  + " b/s";
    else if (rate_in_bps < MB) return fmt((f32) rate_in_bps / KB, 2) + " kb/s";
    else if (rate_in_bps < GB) return fmt((f32) rate_in_bps / MB, 2) + " mb/s";
    else                       return fmt((f32) rate_in_bps / GB, 2) + " gb/s";
}

std::ostream& operator<<(std::ostream& os, const Stats& stats) {
    os << "'" << stats.name << "':";
    os << " processed " << fmt_size(stats.size);
    os << " in " << fmt_time(stats.time);
    os << " at " << fmt_rate(stats.rate);
    return os;
}
