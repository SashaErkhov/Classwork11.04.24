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

FormulaNode* Formula::Postfix2Tree(const char * str)
{
    int index=0;//индекс элемента во входной строке
    std::stack<FormulaNode*> S;
    char ch;
    FormulaNode *result,*right,*left;
    try {
        while ((ch = str[index]) != '\0') {
            left = right = nullptr;
            switch (ch) {
                case '+':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new PlusNode(left, right);
                    break;
                case '-':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new MinusNode(left, right);
                    break;
                case '*':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new MultNode(left, right);
                    break;
                case '/':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new DivNode(left, right);
                    break;
                case '^':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new PowNode(left, right);
                    break;
                default:
                    if (ch >= '0' && ch <= '9') { result = new NumNode(ch - '0'); }
                    else if ((ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z'))
                    { result = new ParamNode(ch); }
                    else throw "Unknow character";//TODO
            }
            S.push(result);
            ++index;
        }
        if(S.size()!=1)
        {
            left=right=nullptr;
            throw 2;
        }
        return S.top();
    }
    catch (...)
    {
        if(left) delete left;
        if(right) delete right;
        while(!S.empty()) {left=S.top();S.pop();delete left;}
        throw ErrorPostfix(str,index);
    }
}

void Formula::InfixFilter(const char* instr,char* outstr)
{
    int index=0;
    while((outstr[index]=instr[index])!='\0')++index;
}

void Formula::Infix2Postfix(const char* instr,char* outstr)
{
    int index=0;
    while((outstr[index]=instr[index])!='\0')++index;
}

#endif //CALC_FORMULAE_H
