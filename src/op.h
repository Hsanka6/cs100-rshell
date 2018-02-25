#ifndef __OP_H__
#define __OP_H__
#include <iostream>
#include <string>
#include <vector>
#include "base.h"
using namespace std;

class Op: public Base{
    //private:
        //string val;
    public:
        // Base * lhs;
        // Base * rhs;
        string val;
        Op(){}
        Op(string value){
            val = value;
        }
        string eVal(){
            return val;
        }
        bool execute(){
            return true;
        }
};
#endif //__OP_H__