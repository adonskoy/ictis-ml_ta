//
// Created by Антон Донской on 13.04.2018.
//

#include <iostream>

struct test{
    int a=1,b=2,c=3;
};

int main(){
    test aa;
    std::cout<<aa[0]<<std::endl;
    std::cout<<aa[1]<<std::endl;
    std::cout<<aa[2]<<std::endl;
}