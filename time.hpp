#ifndef TIME_GUARD
#define TIME_GUARD
#include <chrono>

class time_meassure
{
  private:
    std::chrono::system_clock::time_point _start;
    std::chrono::system_clock::time_point _stop;
  public:
    time_meassure();
    ~time_meassure();

    void start();
    int stop();
};

#endif // !TIME_GUARD