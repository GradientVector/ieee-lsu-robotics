/**
[TODO: documentation goes here]

author - Del Spangler

TODO: rename this with the naming convention "serialException.h", which we decided on at the Feb 15 meeting
NOPE: This is the normal naming convention for exceptions.
*/

#ifndef _SERIAL_EXCEPTION_H_
#define _SERIAL_EXCEPTION_H_
class serial_exception {
    public:
        serial_exception(const char *str = "An exception has occured.\n") : msg(str) {};
        const char *what() const { return msg; };
    private:
        const char *msg;
};

#endif
