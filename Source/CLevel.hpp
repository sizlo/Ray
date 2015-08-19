#ifndef __Ray__CLevel__
#define __Ray__CLevel__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "CMessageListener.hpp"
#include "CPlatform.hpp"
#include "CPlayer.hpp"
#include "CTorch.hpp"
#include "CSwitch.hpp"

class CLevel :  public CUpdateable,
                public CRenderable,
                public CGameLocation,
                public CMessageListener<CEvent>
{
public:
    CLevel();
    ~CLevel();
    
    void StartLevel();
    
    void Update (CTime elapsedTime);
    void Draw (CWindow *theWindow);
    void Enter();
    void Exit();
    bool HandleMessage(CEvent e);
    
    std::list<CConvexShape> GetOccluders();
    std::list<CPlatform *> GetPlatforms();
    
    void TurnOnLights();
    
    static CLevel * GetCurrent();
    
private:
    void HandleCollisions();
    
    std::list<CPlatform *> mPlatforms;
    CPlayer *mPlayer;
    CTorch *mTorch;
    CSwitch *mSwitch;
    
    bool mLightsOn;
    
    static CLevel *smCurrentLevel;
};

#endif // __Ray__CLevel__
