#ifndef __Ray__CLevel__
#define __Ray__CLevel__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "CPlatform.hpp"
#include "CPlayer.hpp"
#include "CTorch.hpp"

class CLevel : public CUpdateable, public CRenderable, public CGameLocation
{
public:
    CLevel();
    ~CLevel();
    
    void StartLevel();
    
    void Update (CTime elapsedTime);
    void Draw (CWindow *theWindow);
    void Enter();
    void Exit();
    
private:
    void HandleCollisions();
    
    std::list<CPlatform *> mPlatforms;
    CPlayer *mPlayer;
    CTorch *mTorch;
};

#endif // __Ray__CLevel__
