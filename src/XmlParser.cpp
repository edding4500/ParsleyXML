#include "XmlParser.h"

XmlParser::XmlParser()
  : tokenList(),
  state(START)
{
  //nodeStack.push(new RootNode());
}

XmlParser::XmlParser(std::list<XmlBaseToken*>& tokenList)
  : XmlParser()
{
  this->tokenList = tokenList;
}

XmlParser::~XmlParser()
{
  if (tokenList.size() > 0) {
    for (auto token : tokenList) {
      delete token;
    }
    tokenList.clear();
  }
  while (nodeStack.size() > 0) {
    delete nodeStack.top();
    nodeStack.pop();
  }
}

XmlParserError XmlParser::parse()
{
  if (this->tokenList.size() > 0) {
    return parse(this->tokenList);
  }
  else {
    return XmlParserError::NO_TOKEN_LIST;
  }
}

XmlParserError XmlParser::parse(std::list<XmlBaseToken*>& tokenList)
{
  //we need a document root on the stack, will be the AST root
  nodeStack.push(new RootNode());

  XmlParserError lastError = XmlParserError::NONE;
  int tokenCount = 0;
  for (auto token : tokenList) {
    tokenCount++;
    lastError = token->switchState(this->state, nodeStack); //switchState(token);
    switch (lastError)
    {
      case XmlParserError::INVALID_TOKEN: {
        std::cout <<"Invalid token type, token #"<< tokenCount << std::endl;
        return lastError;
      }
      case XmlParserError::UNKNOWN_TOKEN: {
        std::cout << "Unknown token type, token #" << tokenCount << std::endl;
        return lastError;
      }
      default: continue;
    }
  }
  return lastError;
}

ElementNode* XmlParser::getAstRoot()
{
  return nodeStack.top();
}

std::stack<ElementNode*>& XmlParser::getNodeStack()
{
  return this->nodeStack;
}
