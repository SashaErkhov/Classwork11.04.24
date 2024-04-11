#include <iostream>
#include "formulanode.h"
#include "formulae.h"

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
    Formula c("abc+*");
    std::cout<<c.tex()<<std::endl;
    std::cout<<c.str()<<std::endl;
    try
    {
        double ans = c.calc();
        std::cout << c.str() << " = " << ans << std::endl;
    }
    catch (const char* e)
    {
        std::cout << e << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
    }
    return 0;
}
