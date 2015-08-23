#ifndef __Ray__CLevel__
#define __Ray__CLevel__

#include "CUpdateable.hpp"
#include "CRenderable.hpp"
#include "CGameLocation.hpp"
#include "CMessageListener.hpp"
#include "CPlatform.hpp"
#include "CHazard.hpp"
#include "CPlayer.hpp"
#include "CTorch.hpp"
#include "CSwitch.hpp"
#include "CToolTip.hpp"

class CLevel :  public CUpdateable,
                public CRenderable,
                public CGameLocation,
                public CMessageListener<CEvent>
{
public:
    CLevel();
    CLevel(std::string filename);
    ~CLevel();
    
    virtual void StartLevel();
    
    virtual void Update (CTime elapsedTime);
    virtual void Draw (CWindow *theWindow);
    
    void Enter();
    void Exit();
    bool HandleMessage(CEvent e);
    
    void AddPlatform(CPlatform *p);
    void AddHazard(CHazard *h);
    std::list<CConvexShape> GetOccluders();
    std::list<CPlatform *> GetPlatforms();
    
    void SetPlayerStartPosition(CVector2f pos);
    void SetSwitchPosition(CVector2f pos);
    
    void TurnOnLights();
    
    static CLevel * GetCurrent();
    
private:
    void HandleCollisions();
    bool PlayerIsDead();
    bool PlayerIsOutOfBounds();
    
    std::list<CPlatform *> mPlatforms;
    std::list<CHazard *> mHazards;
    CPlayer *mPlayer;
    CVector2f mPlayerStartPos;
    CTorch *mTorch;
    CSwitch *mSwitch;
    CVector2f mSwitchPos;
    bool mLightsOn;
    bool mDebugLightsOn;
    CToolTip mResetTooltip;
    CToolTip mLevelWinToolTip;
    
    static CLevel *smCurrentLevel;
};

#endif // __Ray__CLevel__
