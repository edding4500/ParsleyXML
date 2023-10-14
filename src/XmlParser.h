#pragma once

#include <list>
#include <typeinfo>
#include <iostream>
#include <stack>

#include "XmlTokens.h"
#include "AstNode.h"




class XmlParser
{
  public:
    XmlParser();
    XmlParser(std::list<XmlBaseToken*> &tokenList);

    ~XmlParser();

    XmlParserError parse();
    XmlParserError parse(std::list<XmlBaseToken*>& tokenList);

    ElementNode* getAstRoot();

    std::stack<ElementNode*> & getNodeStack();

  private:
    std::list<XmlBaseToken*> tokenList;
    std::stack<ElementNode*> nodeStack;

    XmlParserState state;

};