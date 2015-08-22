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
    CHECK_CHILD(theRoot, "position");
    CHECK_CHILD(theRoot, "width");
    CHECK_CHILD(theRoot, "height");
    
    CVector2f position(-10.0f, -10.0f);
    float width = 0.0f;
    float height = 0.0f;
    
    // Go through all children of the root and process each in turn
    for (pugi::xml_node theNode = theRoot.first_child();
         theNode;
         theNode = theNode.next_sibling())
    {
        if (strcmp(theNode.name(), "position") == 0)
        {
            position = GetVector2f(theNode);
        }
        else if (strcmp(theNode.name(), "width") == 0)
        {
            width = GetFloat(theNode);
        }
        else if (strcmp(theNode.name(), "height") == 0)
        {
            height = GetFloat(theNode);
        }
        else
        {
            DEBUG_LOG("Unknown xml node: %s", theNode.name());
        }
    }
    
    return new CPlatform(position, width, height);
}