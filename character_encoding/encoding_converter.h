#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>

namespace encoding_converter {

int GetU8ByteCount(char ch);
bool IsU8LaterByte(char ch);
std::optional<char32_t> ConvChU8ToU32(const std::array<char, 4>& u8Ch);
std::optional<std::array<char16_t, 2>> ConvChU32ToU16(const char32_t u32Ch);
std::optional<std::array<char16_t, 2>> ConvChU8ToU16(
    const std::array<char, 4>& u8Ch);
std::optional<std::u16string> ConvU8ToU16(const std::string& u8Str);

}  // namespace encoding_converter
