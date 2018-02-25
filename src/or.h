#ifndef __OR_H__
#define __OR_H__
#include "connector.h"


class Or : public Connector {
    public:
        bool execute();
};

#endif //__OR_H__