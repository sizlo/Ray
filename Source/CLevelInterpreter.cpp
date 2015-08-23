#include "CLevelInterpreter.hpp"

CLevelInterpreter::CLevelInterpreter(std::string filename)
: CXMLInterpreter(filename)
{
    
}

CLevelInterpreter::~CLevelInterpreter()
{
    
}

void CLevelInterpreter::Parse(CLevel *theLevel)
{
    // Begin processing
    pugi::xml_node theRoot = mDocument.document_element();
    
    CHECK_CHILD(theRoot, "playerStartPos");
    CHECK_CHILD(theRoot, "switchPos");
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "playerStartPos") == 0)
        {
            theLevel->SetPlayerStartPosition(GetVector2f(theNode));
        }
        else if (strcmp(theNode.name(), "switchPos") == 0)
        {
            theLevel->SetSwitchPosition(GetVector2f(theNode));
        }
        else if (strcmp(theNode.name(), "platform") == 0)
        {
            theLevel->AddPlatform(GetPlatform(theNode));
        }
        else if (strcmp(theNode.name(), "hazard") == 0)
        {
            theLevel->AddHazard(GetHazard(theNode));
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
}

std::string CLevelInterpreter::GetLevelName()
{
    // Get the name and ID from the root element
    pugi::xml_node theRoot = mDocument.document_element();
    CHECK_ATTRIBUTE(theRoot, "name");
    std::string theName = theRoot.attribute("name").as_string();
    
    return theName;
}

CPlatform * CLevelInterpreter::GetPlatform(pugi::xml_node theRoot)
{
    SLevelBlockInfo s = GetLevelBlockInfo(theRoot);
    return new CPlatform(s.topLeft, s.width, s.height);
}

CHazard * CLevelInterpreter::GetHazard(pugi::xml_node theRoot)
{
    SLevelBlockInfo s = GetLevelBlockInfo(theRoot);
    return new CHazard(s.topLeft, s.width, s.height);
}

SLevelBlockInfo CLevelInterpreter::GetLevelBlockInfo(pugi::xml_node theRoot)
{
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "width");
    CHECK_CHILD(theRoot, "height");
    
    SLevelBlockInfo s;
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            s.topLeft = GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "width") == 0)
        {
            s.width = GetFloat(theNode);
        }
        else if (strcmp(theNode.name(), "height") == 0)
        {
            s.height = GetFloat(theNode);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
    
    return s;
}