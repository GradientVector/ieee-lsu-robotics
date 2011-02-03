#ifndef SERIAL_EXCEPTION
#define SERIAL_EXCEPTION
class serial_exception {
    public:
        serial_exception(const char *str = "An exception has occured.\n") : msg(str) {};
        const char *what() const { return msg; };
    private:
        const char *msg;
};

#endif
