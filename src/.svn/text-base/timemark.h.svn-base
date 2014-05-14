//---------------------------------------------------------------------------

#ifndef _VIRTUA_TIMEMARK_
#define _VIRTUA_TIMEMARK_
#include <sys/timeb.h>
#include "vexception.h"
#include <string>
using  namespace std;
/**
*  This class allow to capture the time instant in two differents moments
* and to check how much time has past
*/
class TimeMark
{
public:	
	/**Possible ways of measuring time
	 */
	enum TimeScale{Milliseconds=0};
        /** Empty constructor
        */
        TimeMark(){
                isInit=false;
                }
        /** Copy constructor
        */
        TimeMark(const TimeMark &GT){
         isInit=GT.isInit;
         initTime=GT.initTime;
         endTime=GT.endTime;
        }
        /** Memorize this moment call
         */
        void init()
        {
                ftime(&initTime);
                isInit=true;
        }
        /** return the time past in milliseconds since last call to init()
        *@see init
        */
        unsigned int endMilliseconds() throw(VException);
        /** return the time past in milliseconds since last call to init()
        *@see init
        */
        unsigned int end(TimeScale ts=Milliseconds) throw(VException);
private:
        bool isInit;
        struct timeb initTime,endTime;
};
//---------------------------------------------------------------------------
#endif
