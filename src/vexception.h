#ifndef _VException_
#define _VException_
#include <string>

using namespace std;
/**This is the base class for all the exceptions of the Virtua Library
*/

class VException: public std::exception
{
public :
/**Empty Constructor
*/
VException (){}
/**Constructor
*@param _message error message
*/
VException (string _message){message=_message;}

/**Copy constructor
*/
VException (const VException &VE):std::exception(VE)
{
message=VE.message;
}
/**Destructor
*/
virtual ~VException()throw(){}
/**Message function
*/
virtual const char *what()const throw(){return message.c_str();}
protected:
string message;
};

#endif
