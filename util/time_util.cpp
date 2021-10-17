#include "time_util.h"
#include <time.h>
#include <ctime>

using namespace std;

namespace slow_logger{

string TimeUtil::GetTimeHourStr()
{
    string s;
    char stime[128] = { 0 };
    time_t now_time;
    time(&now_time);
    strftime(stime, sizeof(stime), "%Y-%m-%d_%H", localtime(&now_time));
    s = stime;
    return s;
};

}
