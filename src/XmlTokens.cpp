#include "XmlTokens.h"


EndTagToken::EndTagToken()
  : XmlBaseToken()
{
}

XmlParserError EndTagToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::TAGNAME:
    case XmlParserState::CLOSETAGNAME:
    case XmlParserState::ATTRIBUTEVALUE: 
    case XmlParserState::ENDCLOSETAG: {
      state = XmlParserState::ENDTAG;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}


OpenTagToken::OpenTagToken()
{
}

XmlParserError OpenTagToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::START:
    case XmlParserState::ENDTAG:
    case XmlParserState::CONTENT: {
      state = XmlParserState::TAGOPEN;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}


CloseTagToken::CloseTagToken()
{
}

XmlParserError CloseTagToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::TAGOPEN: {
      state = XmlParserState::CLOSETAG;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}



TagNameToken::TagNameToken(std::string tagName)
  : XmlBaseToken()
{
  this->tagName = tagName;
}

XmlParserError TagNameToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::TAGOPEN: {
      //add TagNode to the stack
      nodeStack.push(new TagNode(this->tagName));

      state = XmlParserState::TAGNAME;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}

AttributeNameToken::AttributeNameToken(std::string attributeName)
  : XmlBaseToken()
{
  this->attributeName = attributeName;
}

XmlParserError AttributeNameToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::TAGNAME:
    case XmlParserState::ATTRIBUTEVALUE: {
      auto attributeNode = new AttributeNode();
      attributeNode->setAttributeNameNode(new AttributeNameNode(this->attributeName));
      nodeStack.push(attributeNode);
      state = XmlParserState::ATTRIBUTENAME;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}



AttributeValueToken::AttributeValueToken(std::string value)
  : XmlBaseToken()
{
  this->value = value;
}

XmlParserError AttributeValueToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::ATTRIBUTEASSIGN: {
      //assuming an AttributeNode on top of the stack! Otherwise the stack
      //is corrupted which can only happen if the token stream is corrupted
      auto attributeNode = (AttributeNode*)nodeStack.top();
      attributeNode->setAttributeValueNode(new AttributeValueNode(this->value));
      //now pop the stack. next node MUST be a TagName token where we can add the attribute
      nodeStack.pop();
      ((TagNode*)nodeStack.top())->addAttribute(attributeNode);

      state = XmlParserState::ATTRIBUTEVALUE;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}



AttributeToken::AttributeToken(std::string attributeName, std::string attributeValue)
  : XmlBaseToken()
{
  this->attributeName = attributeName;
  this->attributeValue = attributeValue;
}

XmlParserError AttributeToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  return XmlParserError::UNKNOWN_TOKEN;
}


AttributeAssignToken::AttributeAssignToken()
  : XmlBaseToken()
{
}

XmlParserError AttributeAssignToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::ATTRIBUTENAME: {
      state = XmlParserState::ATTRIBUTEASSIGN;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}



ContentToken::ContentToken(std::string content)
  : XmlBaseToken()
{
  this->content = content;
}

XmlParserError ContentToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::ENDTAG: {
      //create a TextNode content node
      auto contentNode = new TextNode(this->content);
      //add the content to the children of the current stack head
      nodeStack.top()->addChild(contentNode);
      state = XmlParserState::CONTENT;
      return XmlParserError::NONE;
    }
    default: {
      state = XmlParserState::ERROR;
      return XmlParserError::INVALID_TOKEN;
    }
  }
}

CloseTagNameToken::CloseTagNameToken(std::string tagName)
  : XmlBaseToken()
{
  this->tagName = tagName;
}

XmlParserError CloseTagNameToken::switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack)
{
  switch (state)
  {
    case XmlParserState::CLOSETAG: {
      //tagname on the nodestack must match current tagname
      if (((TagNode*)nodeStack.top())->hasEqualTagName(this->tagName)) {
        //pop node from the stack
        auto oldNode = nodeStack.top();
        nodeStack.pop();
        //add old stack head to new stack heads children
        nodeStack.top()->addChild(oldNode);
      }
      state = XmlParserState::CLOSETAGNAME;
      return NONE;
    }
    default: {
      state = ERROR;
      return INVALID_TOKEN;
    }
  }
}

EndCloseTagToken::EndCloseTagToken()
{
}

XmlParserError EndCloseTagToken::switchState(XmlParserState& state, std::stack<ElementNode*>& nodeStack)
{
  switch (state)
  {
    case TAGNAME:
    case ATTRIBUTEVALUE: {
      //tag is closing early, thus pop the current stack head
      auto topNode = nodeStack.top();
      nodeStack.pop();
      nodeStack.top()->addChild(topNode);
      state = ENDCLOSETAG;
      return NONE;
    }
    default: {
      state = ERROR;
      return INVALID_TOKEN;
    }
  }
}
