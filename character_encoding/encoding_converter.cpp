#include "encoding_converter.h"

namespace encoding_converter {

int GetU8ByteCount(char ch) {
  if (0 <= uint8_t(ch) && uint8_t(ch) < 0x80) {
    return 1;
  }
  if (0xC2 <= uint8_t(ch) && uint8_t(ch) < 0xE0) {
    return 2;
  }
  if (0xE0 <= uint8_t(ch) && uint8_t(ch) < 0xF0) {
    return 3;
  }
  if (0xF0 <= uint8_t(ch) && uint8_t(ch) < 0xF8) {
    return 4;
  }
  return 0;
}

bool IsU8LaterByte(char ch) {
  return 0x80 <= uint8_t(ch) && uint8_t(ch) < 0xC0;
}

std::optional<char32_t> ConvChU8ToU32(const std::array<char, 4>& u8Ch) {
  char32_t u32Ch;
  int numBytes = GetU8ByteCount(u8Ch[0]);
  if (numBytes == 0) {
    return std::nullopt;
  }
  switch (numBytes) {
    case 1:
      u32Ch = char32_t(uint8_t(u8Ch[0]));
      break;
    case 2:
      if (!IsU8LaterByte(u8Ch[1])) {
        return std::nullopt;
      }
      if ((uint8_t(u8Ch[0]) & 0x1E) == 0) {
        return std::nullopt;
      }

      u32Ch = char32_t(u8Ch[0] & 0x1F) << 6;
      u32Ch |= char32_t(u8Ch[1] & 0x3F);
      break;
    case 3:
      if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2])) {
        return std::nullopt;
      }
      if ((uint8_t(u8Ch[0]) & 0x0F) == 0 && (uint8_t(u8Ch[1]) & 0x20) == 0) {
        return std::nullopt;
      }

      u32Ch = char32_t(u8Ch[0] & 0x0F) << 12;
      u32Ch |= char32_t(u8Ch[1] & 0x3F) << 6;
      u32Ch |= char32_t(u8Ch[2] & 0x3F);
      break;
    case 4:
      if (!IsU8LaterByte(u8Ch[1]) || !IsU8LaterByte(u8Ch[2]) ||
          !IsU8LaterByte(u8Ch[3])) {
        return std::nullopt;
      }
      if ((uint8_t(u8Ch[0]) & 0x07) == 0 && (uint8_t(u8Ch[1]) & 0x30) == 0) {
        return std::nullopt;
      }

      u32Ch = char32_t(u8Ch[0] & 0x07) << 18;
      u32Ch |= char32_t(u8Ch[1] & 0x3F) << 12;
      u32Ch |= char32_t(u8Ch[2] & 0x3F) << 6;
      u32Ch |= char32_t(u8Ch[3] & 0x3F);
      break;
    default:
      return std::nullopt;
  }

  return u32Ch;
}

std::optional<std::array<char16_t, 2>> ConvChU32ToU16(const char32_t u32Ch) {
  std::array<char16_t, 2> u16Ch;
  if (u32Ch < 0 || u32Ch > 0x10FFFF) {
    return std::nullopt;
  }

  if (u32Ch < 0x10000) {
    u16Ch[0] = char16_t(u32Ch);
    u16Ch[1] = 0;
  } else {
    u16Ch[0] = char16_t((u32Ch - 0x10000) / 0x400 + 0xD800);
    u16Ch[1] = char16_t((u32Ch - 0x10000) % 0x400 + 0xDC00);
  }

  return u16Ch;
}

std::optional<std::array<char16_t, 2>> ConvChU8ToU16(
    const std::array<char, 4>& u8Ch) {
  auto u32Ch = ConvChU8ToU32(u8Ch);
  if (!u32Ch) {
    return std::nullopt;
  }
  auto u16Ch = ConvChU32ToU16(*u32Ch);
  if (!u16Ch) {
    return std::nullopt;
  }
  return *u16Ch;
}

std::optional<std::u16string> ConvU8ToU16(const std::string& u8Str) {
  std::u16string u16Str;
  for (auto u8It = u8Str.begin(); u8It != u8Str.end(); ++u8It) {
    auto numBytes = GetU8ByteCount((*u8It));
    if (numBytes == 0) {
      return std::nullopt;
    }

    std::array<char, 4> u8Ch;
    u8Ch[0] = (*u8It);
    for (int i = 1; i < numBytes; i++) {
      ++u8It;
      if (u8It == u8Str.end()) {
        return std::nullopt;
      }
      u8Ch[i] = (*u8It);
    }

    auto u16Ch = ConvChU8ToU16(u8Ch);
    if (!u16Ch) {
      return std::nullopt;
    }

    u16Str.push_back((*u16Ch)[0]);
    if ((*u16Ch)[1] != 0) {
      u16Str.push_back((*u16Ch)[1]);
    }
  }
  return u16Str;
}

}  // namespace encoding_converter
