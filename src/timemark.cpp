//---------------------------------------------------------------------------
#include "timemark.h"
#include <cassert>
using namespace std;
unsigned int TimeMark::endMilliseconds() throw(VException)
        {
         if (!isInit) throw VException(" TimeMark::endMilliseconds no call to init()");
         ftime(&endTime);
         int seconds,milliseconds;
         if (endTime.time==initTime.time)
                 return endTime.millitm-initTime.millitm ;
                else{
                  seconds=endTime.time-initTime.time-1;
                  milliseconds=(1000-initTime.millitm)+endTime.millitm;
                 return (milliseconds+seconds*1000);
            }
}

/*
*
*/
unsigned int TimeMark::end(TimeScale ts) throw(VException)
{
 assert(ts== Milliseconds);
 return endMilliseconds();
}

