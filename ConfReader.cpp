#include <iostream>
#include <fstream>
#include "ConfReader.hpp"

#include "lib/json.hpp"

// for convenience
using json = nlohmann::json;

ConfReader::ConfReader()
{
}

ConfReader::~ConfReader()
{
}

conf_data ConfReader::readConf(std::string path)
{
    conf_data retVal;

    std::ifstream cfg_file(path);

    if (!cfg_file.is_open())
    {
        std::cout << "Keine Konfig gefunden, nehme defaults" << '\n';
        return retVal;
    }

    try
    {
        json cfg = json::parse(cfg_file);

        retVal.pixel_width = cfg["pixel_width"];
        retVal.pixel_height = cfg["pixel_height"];
        retVal.x_axis_min = cfg["x_axis_min"];
        retVal.x_axis_max = cfg["x_axis_max"];
        retVal.y_axis_min = cfg["y_axis_min"];
        retVal.y_axis_max = cfg["y_axis_max"];
        retVal.real_min = cfg["real_min"];
        retVal.real_max = cfg["real_max"];
        retVal.im_min = cfg["im_min"];
        retVal.im_max = cfg["im_max"];
        retVal.max_iter = cfg["max_iter"];
        retVal.func_indentifier = cfg["func_indentifier"];
        retVal.zwilling = cfg["zwilling"];
        retVal.koppl = cfg["koppl"];
        retVal.chunck_min_points = cfg["chunck_min_points"];
        retVal.chunck_time_seconds = cfg["chunck_time_seconds"];
        retVal.seconds = cfg["seconds"];
        retVal.num_threads = cfg["num_threads"];
        retVal.save_raw_result = cfg["save_raw_result"];
        retVal.anti = cfg["anti"];

        return retVal;
    }
    catch (const std::exception &e)
    {
        std::cout << "Fehler beim Parsen der Json Conf..." << '\n';
        return retVal;
    }
}