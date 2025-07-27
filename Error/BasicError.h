#ifndef BASICERROR_H
#define BASICERROR_H
#include <exception>
#include <iostream>

#define ERROR_HEAD std::cout<<"SakoraErrorCatcher: An exception is thrown when the program is running:"<<std::endl;

class SakoraError: public std::exception {
protected:
    int line;
    int column;
    std::string src;
public:
    SakoraError(std::string s, int ln, int col);

    std::string what();
    virtual void print();
};

#endif