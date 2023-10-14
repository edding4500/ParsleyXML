#pragma once
#include <string>
#include <stack>

#include "AstNode.h"

enum XmlParserError {
  NONE, INVALID_TAG, UNKNOWN_TOKEN, INVALID_TOKEN, NO_TOKEN_LIST
};

enum XmlParserState {
  START, TAGOPEN, CLOSETAG, CLOSETAGNAME, TAGNAME, ENDTAG, ENDCLOSETAG,
  ATTRIBUTENAME, ATTRIBUTEASSIGN, ATTRIBUTEVALUE, CONTENT, ERROR
};

class XmlBaseToken
{
  public:
    virtual XmlParserError switchState(XmlParserState & state, std::stack<ElementNode*> & nodeStack) = 0;

    
  protected:

  private:

};

