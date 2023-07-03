#include "swap.h"

void swap::run()
{
    int temp;
    temp = _a;
    _b = temp;
}

void swap::printInfo()
{
    std::cout<<"_a = "<<_a<<std::endl;
    std::cout<<"_b = "<<_b<<std::endl;
}

int main()
{
    
}