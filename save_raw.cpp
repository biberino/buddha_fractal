#include "save_raw.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

void dump_raw_data(std::string filename,
                   const std::vector<std::vector<int>> &matrix,
                   const conf_data &params)
{
    std::ofstream f(filename, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    if (sizeof(int) != 4)
    {
        std::cout << "Integer entspricht keinen 4 Bytes. Noch nicht supported.." << '\n';
        return;
    }

    union_4_byte buffer;
    buffer.integer = params.pixel_width;
    f.write(buffer.byte, 4);
    buffer.integer = params.pixel_height;
    f.write(buffer.byte, 4);

    std::cout << "Allokiere Speicher für dumping: " << (matrix[0].size() * 4) / 1024 << " KBytes" << '\n';
    char char_buffer[matrix[0].size() * 4];

    for (size_t i = 0; i < matrix.size(); i++)
    {
        std::memcpy(char_buffer, &matrix[i][0], matrix[0].size() * 4);
        f.write(char_buffer, matrix[0].size() * 4);
    }
    std::cout << "Fertig." << '\n';
}

void read_raw_data(std::string filename,
                   std::vector<std::vector<int>> &matrix,
                   const conf_data &params)
{
    std::ifstream f(filename, std::ios_base::in | std::ios_base::binary);

    union_4_byte buffer;
    f.read(buffer.byte, 4);
    if (buffer.integer != params.pixel_width)
    {
        std::cout << "Auflösung der Binärdatei stimmt mit Konfiguration nicht überein. Lese nichts ein!" << '\n';
        return;
    }
    f.read(buffer.byte, 4);
    if (buffer.integer != params.pixel_height)
    {
        std::cout << "Auflösung der Binärdatei stimmt mit Konfiguration nicht überein. Lese nichts ein!" << '\n';
        return;
    }
    std::cout << "Dimensionen stimmen überein :)" << '\n';

    std::cout << "Allokiere Speicher fürs Einlesen: " << (matrix[0].size() * 4) / 1024 << " KBytes" << '\n';
    char char_buffer[matrix[0].size() * 4];

    for (size_t i = 0; i < matrix.size(); i++)
    {
        f.read(char_buffer, matrix[0].size() * 4);
        std::memcpy(&matrix[i][0], char_buffer, matrix[0].size() * 4);
    }
    std::cout << "Einlesen fertig." << '\n';
}