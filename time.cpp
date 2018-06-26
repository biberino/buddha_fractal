#include "time.hpp"


time_meassure::time_meassure(/* args */)
{
}

time_meassure::~time_meassure()
{
}

void time_meassure::start()
{
    _start = std::chrono::system_clock::now();
}

int time_meassure::stop()
{
    _stop = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(_stop - _start).count();
}
