#pragma once
#include "XmlBaseToken.h"


///
/// Placeholder for "<" followed by a tag name
///
class OpenTagToken :
  public XmlBaseToken
{
public:
  OpenTagToken();
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

};

///
/// Placeholder for ">"
///
class EndTagToken :
  public XmlBaseToken
{
public:
  EndTagToken();
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

};

///
/// Placeholder for "/" after a "<", followed by a tag name
///
class CloseTagToken :
  public XmlBaseToken
{
public:
  CloseTagToken();
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

  private:
    
};

///
/// Placeholder for "/" after a token name or attribute, followed by a EndTagToken ">"
///
class EndCloseTagToken :
  public XmlBaseToken
{
public:
  EndCloseTagToken();
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*>& nodeStack);

private:

};

///
/// placeholder for a tagname consisting of valid chars.
/// followed by EndTagToken OR AttibuteNameToken
///
class TagNameToken :
  public XmlBaseToken
{
public:
  TagNameToken(std::string tagName);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  std::string tagName;
};

///
/// placeholder for a tagname of a closing tag, consisting of valid chars.
/// followed by EndTagToken
///
class CloseTagNameToken :
  public XmlBaseToken
{
public:
  CloseTagNameToken(std::string tagName);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  std::string tagName;
};

///
/// placeholder for an attribute name consisting fo valid chars.
/// followed by an AttributeAssignToken "="
///
class AttributeNameToken :
  public XmlBaseToken
{
public:
  AttributeNameToken(std::string attributeName);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  
  std::string attributeName;
};


///
/// Placeholder for "=" after an AttributeNameToken, followed by an 
/// AttributeValueToken
///
class AttributeAssignToken :
  public XmlBaseToken
{
public:
  AttributeAssignToken();
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

  private:
    
};

///
/// Placeholder for an AttributeValue
///
class AttributeValueToken :
  public XmlBaseToken
{
public:
  AttributeValueToken(std::string value);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  
  std::string value;
};


///
/// Placeholder for an expression like attributeName="attributeValue"
/// in case we want only one token for this kind of expression
///
class AttributeToken :
  public XmlBaseToken
{
public:
  AttributeToken(std::string attributeName, std::string attributeValue);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  std::string attributeValue;
  std::string attributeName;
};


///
/// Represents text content inbetween tags
///
class ContentToken :
  public XmlBaseToken
{
public:
  ContentToken(std::string content);
  XmlParserError switchState(XmlParserState& state, std::stack<ElementNode*> & nodeStack);

private:
  std::string content;
};