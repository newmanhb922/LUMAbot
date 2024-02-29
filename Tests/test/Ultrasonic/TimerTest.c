#include <signal.h>
#include <stdio.h>
#include <wiringPi.h>

void TimerInterrupt();

unsigned int startTime;

int main()
{
    unsigned int timerSet; // microseconds to set the timer
    printf("Enter number of microseconds to trigger the timer.\n");
    scanf("%d", &timerSet);
    signal(SIGALRM, TimerInterrupt);
    startTime = micros();
    ualarm(timerSet, timerSet);
    while(1);
}

void TimerInterrupt()
{
    unsigned int endTime = micros();
    printf("Elapsed microseconds: %d\n", endTime - startTime);
    startTime = micros();
}
