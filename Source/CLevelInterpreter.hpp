#ifndef __Ray__CLevelInterpreter__
#define __Ray__CLevelInterpreter__

#include "CXMLInterpreter.hpp"
#include "CLevel.hpp"

class CLevelInterpreter : public CXMLInterpreter
{
public:
    CLevelInterpreter(std::string filename);
    ~CLevelInterpreter();
    
    void Parse(CLevel *theLevel);
    std::string GetLevelName();
    
private:
    CPlatform * GetPlatform(pugi::xml_node theRoot);
};

#endif // __Ray__CLevelInterpreter__
