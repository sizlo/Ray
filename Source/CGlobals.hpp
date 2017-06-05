#ifndef __Ray__CGlobals__
#define __Ray__CGlobals__

#include "SFMLIntegration/SFMLIntegration.hpp"
#include "CInput.hpp"

class CGlobals
{
public:
    static float playerSize;
    static float switchSize;
    static CVector2f gravity;
	static float torchRadius;
	
    static CInput leftInput;
    static CInput rightInput;
    static CInput jumpInput;
    static CInput resetInput;
};

#endif // __Ray__CGlobals__
