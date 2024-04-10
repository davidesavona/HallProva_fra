
//#include <QCoreApplication>
#include <signal.h>
#include <wiringPi.h>
#include "hallsensor.h"
#include <thread>
#include <pthread.h>
#include <numeric>
#include <iostream>
using namespace std;
hallsensor Hallsensor;
bool running = 1;
bool oldstate=0;
long int TIME=0;
long int OLD_TIME=-1;
int elapsed;
double w;
double seconds;
double cfr = 2.096; // m
double km = 0;
double m = 0;
bool firstPulse=0;
double w_vect[5];
double w_mean;
double v;
int i=0;


#define DEFAULT_LOOP_TIME_NS 1000000L
#define TH1_PERIOD 5
#define TH2_PERIOD 20

timespec addition(timespec a, timespec b) {
    timespec r;

    if(a.tv_nsec + b.tv_nsec <= 999999999) {
        r.tv_nsec = a.tv_nsec + b.tv_nsec;
        r.tv_sec = a.tv_sec + b.tv_sec;
    }
    else {
        int c = (a.tv_nsec + b.tv_nsec)/1000000000;
        r.tv_nsec = a.tv_nsec + b.tv_nsec - 1000000000*c;
        r.tv_sec = a.tv_sec + b.tv_sec + c;
    }

    return r;
}


void *threadFunction(void* a) {

    //signal(SIGINT, myInterruptHandler);

    //readfromSM();

    struct timespec t_now;
    struct timespec t_next;
    struct timespec t_period;
    struct timespec t_wait;
    struct timespec pause_duration;

    //unsigned long int t_overflow = 0;   // measure the overflowed time for each cycle
    unsigned long int loop_count = 0;

    // t_period defines duration of one "running" cycle (1 ms in this case)
    t_period.tv_sec = 0;
    t_period.tv_nsec = DEFAULT_LOOP_TIME_NS;

    // pause_duration defines duration of pause considered when a buttton is pressed (1 s in this case)

    clock_gettime( CLOCK_MONOTONIC, &t_next);

    // Save into variables the first input variables from GUI
    // TODO: save user variables


   while(running) {

       // chartclass.readButton();
        t_next = addition(t_next, t_period); // update t_next (needed for usleep at the end)clock_gettime ( CLOCK_MONOTONIC, &t_now);

        if(loop_count%1 == 0) {
        // cout<< "1000hz\n";
            TIME++;
            if(Hallsensor.triggerHall()){
                    if(oldstate==0){
                        if(firstPulse){
                        //rpm=(60.0/(TIME/1000.0))/20;
                        //w = (0.314159 / (TIME / 1000.0)); // angular velocity 1/20*2pi (20 buds)
//                        w = ((2*3.14) / (TIME / 1000.0));
//                        if(i==4)i=0;
//                        w_vect[i]=w;
//                        i++;
//                        for(int j=0; j<5; j++){
//                            w_mean+=w_vect[j];
//                        }
//                        w_mean=w_mean/5;

//                        v = w * 0.35;

                        v = (cfr / (TIME / 1000.0)) * 3.6;
                        km += cfr / 1000.0; // conta km
                                

//                        cout<<w_mean<< "[rad/s]"<< endl;
                        cout<<v<<" [km/h] | "<<km<<" [km]\n";
                        } else firstPulse=1;

                        TIME=0;
                        oldstate=1;

                    }




            }else {
                if(oldstate==1){

                //cout<<"0"<<endl;
                oldstate=0;}
             }




        }
        if(loop_count%100==0){

        }




        loop_count++;

        clock_nanosleep ( CLOCK_MONOTONIC, TIMER_ABSTIME, &t_next, nullptr ); // waits until time t_next is reached

        // print t_now (just to check "running" cycle repeats with desired frequency)
        clock_gettime ( CLOCK_MONOTONIC, &t_now);
        //cout << "\nT running = " << t_now.tv_sec*1000 + t_now.tv_nsec/1000000 << "\n";
    }

}


int main (void)
{
    Hallsensor.initHall();

//    while (1) {

//}
    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, nullptr);
    pthread_join(thread, NULL);



return 0;

}
