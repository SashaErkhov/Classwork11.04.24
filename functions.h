//
// Created by sasor on 15.04.2024.
//

#ifndef CALC_FUNCTIONS_H
#define CALC_FUNCTIONS_H

#include <cmath>
#include "errors.h"
#include <cstring>

typedef double (*pfun)(double);

double sign(double x);

class FunctionsTable {
    struct FuncInfo {
        char shortName;
        const char *longName;
        pfun fun;
    };
    static const FuncInfo FTable[];
    static const int sizeFTable;
public:
    static int funcNumberByLongName(const char* s);
    static int funcNumberByShortName(char s);
    static const FuncInfo & get(int i)
    {
        if(i<sizeFTable and i>=0) return FTable[i];
        throw ErrorFunctionsTable();
    }
};

#endif //CALC_FUNCTIONS_H
