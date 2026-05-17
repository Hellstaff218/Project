#include "parse_fonts.h"

#include "verdana_8_font.h"

#include <cstdint>
#include <iostream>

void parse_font(char symbol, char fill, char background)
{
    constexpr unsigned int kBytesPerRow = 2;
    constexpr unsigned int kBytesPerChar = FONT_VERDANA_8_CHAR_HEIGHT * kBytesPerRow;
    const unsigned int code = static_cast<unsigned char>(symbol);

    if (code < FONT_VERDANA_8_START_CHAR ||
        code >= FONT_VERDANA_8_START_CHAR + FONT_VERDANA_8_LENGTH)
    {
        std::cerr << "unsupported symbol: " << symbol << std::endl;
        return;
    }

    const unsigned int symbolIndex = code - FONT_VERDANA_8_START_CHAR;
    const unsigned int offset = symbolIndex * kBytesPerChar;

    for (unsigned int row = 0; row < FONT_VERDANA_8_CHAR_HEIGHT; row++)
    {
        const unsigned int rowOffset = offset + row * kBytesPerRow;
        const std::uint16_t rowBits =
            static_cast<std::uint16_t>(font_verdana_8[rowOffset]) |
            (static_cast<std::uint16_t>(font_verdana_8[rowOffset + 1]) << 8);

        for (unsigned int col = 0; col < FONT_VERDANA_8_CHAR_WIDTH; col++)
        {
            const bool pixelOn = ((rowBits >> col) & 0x1U) != 0;
            std::cout << (pixelOn ? fill : background);
        }

        std::cout << '\n';
    }
}
