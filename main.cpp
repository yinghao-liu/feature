#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

using namespace std;

/*hander when timer expired*/
void timer_handle(union sigval)
{
    cout<<"in timer_handle"<<endl;
}

int main(void)
{
    timer_t timer_id;
    struct sigevent sev;
    
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = timer_handle;
    sev.sigev_notify_attributes = nullptr;
    if (-1 == timer_create(CLOCK_REALTIME, &sev, &timer_id)){
        perror("timer_create");
    }

    struct itimerspec timer_value;
    memset(&timer_value, 0, sizeof (timer_value));
    timer_value.it_value.tv_sec = 5;
    if (-1 == timer_settime(timer_id, 0, &timer_value, nullptr)){
        perror("timer_settime");
    }

    /*here disarm the timer*/
    struct itimerspec timer_zero;
    struct itimerspec timer_old;
    memset(&timer_zero, 0, sizeof (timer_zero));
    memset(&timer_old, 0, sizeof (timer_old));
    if (-1 == timer_settime(timer_id, 0, &timer_zero, &timer_old)){
        perror("timer_settime");
    }
    /*sleep more than the timer's seconds*/
    sleep(6);

    /*continue the timer*/
    if (-1 == timer_settime(timer_id, 0, &timer_old, nullptr)){
        perror("timer_settime");
    }

    while (true){
        sleep(1);
        cout<<"------------"<<endl;
    }
    /*though will never reach*/
    timer_delete(timer_id);
	return 0;
}

