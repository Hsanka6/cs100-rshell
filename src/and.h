#ifndef __AND_H__
#define __AND_H__
#include "connector.h"


class And : public Connector
{
    public:
    bool execute();
};

#endif //__AND_H__