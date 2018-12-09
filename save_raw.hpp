#ifndef RAW_GUARD_1212
#define RAW_GUARD_1212

#include <vector>
#include <string>

#include "ConfReader.hpp"

union union_4_byte {
    int integer;
    char byte[4];
};

/**
 * @brief  Speichert die Rohe Matrix als Binäratei.
 * ersten 4 byte -> pixel_width
 * zweiten 4 byte -> pixel_height
 * rest in 4byte schritten -> werte
 * 
 * @note   
 * @param  filename: 
 * @param  &matrix: 
 * @param  max_value: 
 * @param  &params: 
 * @retval None
 */
void dump_raw_data(std::string filename,
                   const std::vector<std::vector<int>> &matrix,
                   const conf_data &params);

void read_raw_data(std::string filename,
                   std::vector<std::vector<int>> &matrix,
                   const conf_data &params);

#endif // !RAW_GUARD_1212
