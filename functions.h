//
// Created by sasor on 15.04.2024.
//

#ifndef CALC_FUNCTIONS_H
#define CALC_FUNCTIONS_H

#include <cmath>
#include "errors.h"

typedef double (*pfun)(double);

struct FuncInfo{
    char shortName;
    const char *longName;
    pfun fun;
};

double sign(double x){
    return x==0? 0: (x>0? 1.0:-1.0);
}

const FuncInfo FTable[] = {
        {char(128),"arcsin",std::asin},
        {char(129),"arccos",std::acos},
        {char(130),"sin",std::sin},
        {char(131),"cos",std::cos},
        {char(132),"arctg",std::atan},
        {char(133),"tg",std::tan},
        {char(134),"ln",std::log},
        {char(135),"exp",std::exp},
        {char(136),"abs",std::fabs},
        {char(137),"sh",std::sinh},
        {char(138),"ch",std::cosh},
        {char(139),"sqrt",std::sqrt},
        {char(140),"sign",sign}
};

const int sizeFTable = sizeof(FTable)/sizeof(FTable[0]);

int funcNumberByShortName(char s)
{
    for(int i=0;i<sizeFTable;++i){
        if(FTable[i].shortName == s) return i;
    }
    throw ErrorUnknownFunction(s);
}

#include <cstring>
int funcNumberByLongName(const char* s)
{
    for(int i=0;i<sizeFTable;++i){
        if(strcmp(s,FTable[i].longName)==0) return i;
    }
    throw ErrorUnknownFunction(s);
}

#endif //CALC_FUNCTIONS_H
