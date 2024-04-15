//
// Created by sasor on 11.04.2024.
//

#ifndef CALC_FORMULAE_H
#define CALC_FORMULAE_H

#include <string>
#include <cstring>
#include "formulanode.h"
#include <stack>

class Formula
{
    FormulaNode *root;
    FormulaNode* Postfix2Tree(const char *);
    void InfixFilter(const char*,char*);
    void Infix2Postfix(const char*,char*);
public:
    Formula(const char *str): root(nullptr)
    {
        size_t len = strlen(str);
        len=(len<10)? 20: 2*len;
        char *str_infix = new char[len];
        char *str_postfix = new char[len];
        try {
            InfixFilter(str, str_infix);
            Infix2Postfix(str_infix, str_postfix);
            root = Postfix2Tree(str_postfix);
        }
        catch(...)
        {
            delete[] str_infix;
            delete[] str_postfix;
            throw;
        }
        delete[] str_infix;
        delete[] str_postfix;
    }
    double calc()const
    {
        if(root)return root->calc();
        return 0;
    }
    std::string str()const
    {
        if(root)return root->str();
        return std::string("");
    }
    std::string tex()const
    {
        if(root)return root->tex();
        return std::string("");
    }
    ~Formula() {if(root)delete root;}
};

#endif //CALC_FORMULAE_H
