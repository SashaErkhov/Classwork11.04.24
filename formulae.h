//
// Created by sasor on 11.04.2024.
//

#ifndef CALC_FORMULAE_H
#define CALC_FORMULAE_H

#include <string>
#include "formulanode.h"

class Formula
{
    FormulaNode *root;
    FormulaNode* Postfix2Tree(const char *);
public:
    Formula(const char *str)
    {
        root = Postfix2Tree(str);
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

FormulaNode* Formula::Postfix2Tree(const char * str)
{
    return nullptr;
}

#endif //CALC_FORMULAE_H
