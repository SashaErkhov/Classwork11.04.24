//
// Created by sasor on 18.04.2024.
//
#include "functions.h"

const FunctionsTable::FuncInfo FunctionsTable::FTable[] = {
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

const int FunctionsTable::sizeFTable =
        sizeof(FunctionsTable::FTable)/sizeof(FunctionsTable::FTable[0]);

double sign(double x){
    return x==0? 0: (x>0? 1.0:-1.0);
}

int FunctionsTable::funcNumberByShortName(char s)
{
    for(int i=0;i<sizeFTable;++i){
        if(FTable[i].shortName == s) return i;
    }
    throw ErrorUnknownFunction(s);
}

#include <cstring>
int FunctionsTable::funcNumberByLongName(const char* s)
{
    for(int i=0;i<sizeFTable;++i){
        if(strcmp(s,FTable[i].longName)==0) return i;
    }
    throw ErrorUnknownFunction(s);
}