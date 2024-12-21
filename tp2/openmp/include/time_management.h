#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
 
void timeval_subtract (struct timeval*, struct timeval*, struct timeval*);
double joinTimes (time_t, suseconds_t);

#endif