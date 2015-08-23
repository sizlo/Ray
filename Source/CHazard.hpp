#ifndef __Ray__CHazard__
#define __Ray__CHazard__

#include "CLevelBlock.hpp"

class CHazard : public CLevelBlock
{
public:
    CHazard(CVector2f topLeft, float width, float height);
    ~CHazard();
};

#endif // __Ray__CHazard__
