#include <iostream>
#include "formulae.h"
#include <cstring>
#include "errors.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    /*FormulaNode *a=new ParamNode('a');
    FormulaNode *b=new ParamNode('b');
    FormulaNode *c=new PlusNode(a,b);
    b=new MinusNode(new ParamNode('c'),c);
    a=new MinusNode(new NumNode(2),new ParamNode('x'));
    c=new MultNode(a,b);
    b=new DivNode(new NumNode(1),c);
    c=new PowNode(b,new ParamNode('y'));*/
/*    Formula c("abc+*");
    std::cout<<c.tex()<<std::endl;
    std::cout<<c.str()<<std::endl;*/
    char str[1024];
    try
    {
        while(true) {
            std::cout << "> ";
            std::cin.getline(str, 1024);
            if(strlen(str)==0) continue;
            if (strcmp(str, "quit") == 0) break;
            if(strcmp(str, "clear")==0)
            {
                global::Workspace.clear();
                continue;
            }
            try {
                Formula c(str);
                std::cout << c.str() << std::endl;
                double ans = c.calc();
                std::cout << c.str() << " = " << ans << std::endl;
            }
            catch (const Error&e) {
                std::cout <<"Error: "<< e.what() << std::endl;
            }
        }
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
    }
    return 0;
}
