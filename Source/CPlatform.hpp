#ifndef __Ray__CPlatform__
#define __Ray__CPlatform__

#include "CUpdateable.hpp"
#include "CLevelBlock.hpp"

class CPlatform : public CLevelBlock, public CUpdateable
{
public:
    CPlatform(CVector2f topLeft, float width, float height);
    ~CPlatform();
    
    virtual void Update(CTime elapsedTime);
};

#endif // __Ray__CPlatform__
