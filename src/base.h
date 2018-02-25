#ifndef __BASE_H__
#define __BASE_H__
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Base
{
    
    public:
        /*Constructor */
        
        Base(){}
       
        /* Pure virtual function */
        virtual bool execute() = 0;
        virtual string eVal() = 0;
};

#endif //__BASE_H__