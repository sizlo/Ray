#ifndef __Ray__CPlatform__
#define __Ray__CPlatform__

#include "CLevelBlock.hpp"

class CPlatform : public CLevelBlock
{
public:
    CPlatform(CVector2f topLeft, float width, float height);
    ~CPlatform();
};

#endif // __Ray__CPlatform__
