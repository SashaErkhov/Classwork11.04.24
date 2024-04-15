#ifndef ERRORS_PVM_2024
#define ERRORS_PVM_2024

#include <string>

class Error
{
public:
    virtual std::string what() const{return std::string("Unknown error");}
};

class ErrorDivideByZero : public Error
{
public:
    std::string what() const{return std::string("Division by zero");}
};

class ErrorPostfix : public Error
{
    std::string str;
    int index;
public:
    ErrorPostfix(const char *s,int position):str(s),index(position){}
    std::string what() const
    { return std::string("Error in postfix string '"
    + str + "' at position "
    + std::to_string(index+1));}
};

class ErrorBracetsClose : public Error
{
    std::string str;
    int index;
public:
    ErrorBracetsClose(const char *s,int position):str(s),index(position){}
    std::string what() const
    { return std::string("Error with brackets. There are no '(' for ')' in '"
                         + str + "' at position "
                         + std::to_string(index+1));}
};

class ErrorBracetsOpen : public Error
{
    std::string str;
    int index;
public:
    ErrorBracetsOpen(const char *s,int position):str(s),index(position){}
    std::string what() const
    { return std::string("Error with brackets. There are no ')' for '(' in '"
                         + str + "' at position "
                         + std::to_string(index+1));}
};

class ErrorUnknownFunction: public Error
{
    std::string str;
public:
    ErrorUnknownFunction(const char *s):str(s){}
    ErrorUnknownFunction(char s):str(1,s){}
    std::string what() const
    { return std::string("Unknow function name '"
                         + str
                         + "'");}
};

class ErrorFunctionBrakets : public Error
{
    std::string str;
    int index;
public:
    ErrorFunctionBrakets(const char *s,int position):str(s),index(position){}
    std::string what() const
    { return std::string("Error with brackets after function in '"
                         + str + "' at position "
                         + std::to_string(index+1));}
};


#endif // !ERRORS_PVM_2024