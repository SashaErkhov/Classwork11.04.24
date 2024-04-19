//
// Created by sasor on 15.04.2024.
//
#include "formulae.h"

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
                case '=':
                    if(S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new AssignmentNode(left, right);
                    break;
                default:
                    if (ch >= '0' && ch <= '9') { result = new NumNode(ch - '0'); }
                    else if ((ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z'))
                    { result = new ParamNode(ch); }
                    else {
                        if(S.empty()) throw 1;
                        left = S.top();
                        S.pop();
                        result =  new FuncNode(ch,left);
                    }
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
    int i=0;//индекс во входной строке
    int j=0;//индекс в выходной строке
    char ch;
    char buf[256];
    int bufLen=0;
    char prev=0;//предыдущий символ во входной строке

    while((ch=instr[i++])!='\0')
    {
        if(ch==' ' or ch=='\t') continue;
        if((ch>='a' and ch<='z') or (ch>='A' and ch<='Z')or(ch>='0' and ch<='9'))
            buf[bufLen++]=ch;
        else {
            //Унарный минус в 0-
            if(ch=='-' and (prev==0 or prev=='(' or bufLen==0))
            {
                outstr[j++]='0';
            }
            else
            {
                //Посмотреть что в буфере и если ф-ия, то преобр. в короткое имя
                if(bufLen==1)
                {
                    outstr[j++]=buf[0];
                    bufLen=0;
                }
                else if(bufLen>1)
                {
                    buf[bufLen]='\0';
                    outstr[j++]=FunctionsTable::get(
                            FunctionsTable::funcNumberByLongName(buf)).shortName;
                    bufLen=0;
                }
            }

            outstr[j++]=ch;
        }
        prev=ch;
    }
    if(bufLen>1) throw "Function without arguments";
    if(bufLen>0) outstr[j++]=buf[0];
    outstr[j]='\0';
}

int actionsRowNumber(char ch)
{
    switch(ch)
    {
        case 0:return 0;
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
        case '^':return 5;
        case '(':return 6;
        case '=':return 8;
    }
    return 7;
}

int actionsColNumber(char ch)
{
    switch(ch)
    {
        case 0:return 0;
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
        case '^':return 5;
        case '(':return 6;
        case ')':return 7;
        case '=':return 10;
    }
    if(ch>='a' and ch<='z')return 8;
    if(ch>='A' and ch<='Z')return 8;
    if(ch>='0' and ch<='9')return 8;
    return 9;
}

const unsigned char ActionsTable[][11] = {
        //       0      +      -      *      /      ^      (      )      P      F      =
        {7, 2, 2, 2, 2, 2, 2, 6, 1, 2,2},//empty
        {3, 3, 3, 2, 2, 2, 2, 3, 1, 2,9},// +
        {3, 3, 3, 2, 2, 2, 2, 3, 1, 2,9},// -
        {3, 3, 3, 3, 3, 2, 2, 3, 1, 2,9},// *
        {3, 3, 3, 3, 3, 2, 2, 3, 1, 2,9},// /
        {3, 3, 3, 3, 3, 2, 2, 3, 1, 2,9},// ^
        {5, 2, 2, 2, 2, 2, 2, 4, 1, 2,2},// (
        {3, 3, 3, 3, 3, 3, 2, 3, 1, 8,9},// F
        {3, 2, 2, 2, 2, 2, 2, 3, 1, 2,2} // =
};
//1. Переместить из instr в outstr
//2. из вх перем в стек
//3. из стека в outstr
//4. удалить из стека и перем на один символ во вх строке
//5. Ошибка: нет закр скобки

void Formula::Infix2Postfix(const char* instr,char* outstr)
{
    int i=0;//идекс во входной строке
    int j=0;//индекс во выходной строке
    int row,col;
    unsigned char action;
    std::stack<char> S;
    do
    {
        col=actionsColNumber(instr[i]);
        row=S.empty()?0:actionsRowNumber(S.top());
        action=ActionsTable[row][col];
        switch(action)
        {
            case 1:
                outstr[j++]=instr[i];
                ++i;
                break;
            case 2:
                S.push(instr[i]);
                ++i;
                break;
            case 3:
                outstr[j++]=S.top();
                S.pop();
                break;
            case 4:
                S.pop();
                ++i;
                break;
            case 5:
                throw ErrorBracetsClose(instr,i); break;
            case 6:
                throw ErrorBracetsOpen(instr,i); break;
            case 7:
                outstr[j]='\0';
                break;
            case 8:
                throw ErrorFunctionBrakets(instr,i); break;
            case 9:
                throw ErrorRValue(); break;
        }
    }while(action!=7);
}
