#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__
#include "base.h"
#include "op.h"
class Connector: public Op
{
    public:
        Op * lhs;
        Op * rhs;
        string val;
        vector<string> cmds;
        /* Constructor */
        Connector() {
            lhs = NULL;
            rhs = NULL;
            val = "";
        }
        Connector(string value){
            val = value;
        }
        
        string eVal()
        {
            return val;
        }

        /*Bool function */
        bool execute()
        {
            return true;
        }
};

#endif //__BASE_H__
