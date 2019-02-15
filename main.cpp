#include <iostream>
#include <unistd.h>
#include <limits>
#include <sys/times.h>

using namespace std;
int main(void)
{
    struct tms times_start;
    struct tms times_end;
    clock_t elapse_start;
    clock_t elapse_end;

    // obtain the number of clock ticks per second
    auto ticks = sysconf(_SC_CLK_TCK);

    elapse_start = times(&times_start);
    int op=0;
    for (int i=0; i<20000000; i++){
        for (int j=0; j<300; j++){
            op++;
        }
    }
    //sleep(2);
    elapse_end = times(&times_end);

    auto clock_max = numeric_limits<clock_t>::max();

    // below are the clock ticks, not second
    auto elapse_s =  elapse_end >= elapse_start ? (elapse_end - elapse_start) : (elapse_end - elapse_start + clock_max);
    auto times_uts = times_end.tms_utime >= times_start.tms_utime ? (times_end.tms_utime - times_start.tms_utime) : \
                     (times_end.tms_utime - times_start.tms_utime + clock_max);
    auto times_sts = times_end.tms_stime >= times_start.tms_stime ? (times_end.tms_stime - times_start.tms_stime) : \
                     (times_end.tms_stime - times_start.tms_stime + clock_max);

    cout<<"clock ticks is "<<elapse_s<<endl;
    cout<<"user ticks is "<<times_uts<<endl;
    cout<<"system ticks is "<<times_sts<<endl;

    cout<<"clock time is "<<elapse_s/(float)ticks<<" s"<<endl;
    cout<<"user time is "<<times_uts/(float)ticks<<" s"<<endl;
    cout<<"system time is "<<times_sts/(float)ticks<<" s"<<endl;
	return 0;
}

