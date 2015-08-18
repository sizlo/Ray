#ifndef __Ray__CTorch__
#define __Ray__CTorch__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"

class CPlayer;

class CTorch: public CUpdateable, public CRenderable
{
public:
    CTorch(CPlayer *theHolder);
    ~CTorch();
    
    void Update(CTime elapsedTime);
    void Draw(CWindow *theWindow);
    
private:
    CConvexShape mShape;
    CPlayer *mHolder;
};

#endif // __Ray__CTorch__
