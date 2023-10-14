#include "AstNode.h"

RootNode::RootNode()
{
}

RootNode::~RootNode()
{
}

void RootNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

//void RootNode::addChild(AstNode* child)
//{
//  this->children.push_back(child);
//}

ElementNode::ElementNode()
{
}

ElementNode::~ElementNode()
{
  if (children.size() > 0) {
    for (auto child : children) {
      delete child;
    }
    children.clear();
  }
}

void ElementNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

void ElementNode::addChild(AstNode* child)
{
  this->children.push_back(child);
}

std::list<AstNode*>& ElementNode::getChildren()
{
  return this->children;
}

TextNode::TextNode()
  : text("")
{
}

TextNode::TextNode(std::string text)
{
  this->text = text;
}

TextNode::~TextNode()
{
}

void TextNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

void TextNode::addChild(AstNode* child)
{
}

std::string& TextNode::getText()
{
  return this->text;
}

TagNode::TagNode()
  : ElementNode(),
  tagName("")
{
}

TagNode::TagNode(std::string tagName)
{
  this->tagName = tagName;
}

TagNode::~TagNode()
{
  /*auto children = getChildren();
  if (children.size() > 0) {
    for (auto child : children) {
      delete child;
    }
  }*/
}

void TagNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

std::string & TagNode::getTagName()
{
  return this->tagName;
}

bool TagNode::hasEqualTagName(std::string & otherTagName)
{
  return (this->tagName == (otherTagName));
}

void TagNode::addAttribute(AttributeNode* attribute)
{
  this->attributeList.push_back(attribute);
}

std::list<AttributeNode*>& TagNode::getAttributes()
{
  return this->attributeList;
}


AttributeNode::AttributeNode()
  : nameNode(nullptr),
  valueNode(nullptr)
{
}

AttributeNode::AttributeNode(AttributeNameNode* name, AttributeValueNode* value)
{
  nameNode = name;
  valueNode= value;
}

void AttributeNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

std::string& AttributeNode::getName()
{
  //NOT CHECKING FOR NULLPTR!
  return this->nameNode->getName();
}

std::string& AttributeNode::getValue()
{
  //NOT CHECKING FOR NULLPTR!
  return this->valueNode->getValue();
}

AttributeNameNode* AttributeNode::getNameNode()
{
  return this->nameNode;
}

AttributeValueNode* AttributeNode::getValueNode()
{
  return this->valueNode;
}

void AttributeNode::setAttributeNameNode(AttributeNameNode* name)
{
  this->nameNode = name;
}

void AttributeNode::setAttributeValueNode(AttributeValueNode* value)
{
  this->valueNode = value;
}

AttributeNode::~AttributeNode()
{
  if(valueNode != nullptr) delete valueNode;
  if(nameNode != nullptr) delete nameNode;
}

AttributeNameNode::~AttributeNameNode()
{
}


void AttributeNameNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

AttributeNameNode::AttributeNameNode(std::string& name)
{
  this->name = name;
}

AttributeNameNode::AttributeNameNode(const char* name)
{
  this->name = name;
}

std::string& AttributeNameNode::getName()
{
  return this->name;
}

AttributeValueNode::~AttributeValueNode()
{
}

void AttributeValueNode::accept(AstVisitor& v)
{
  v.visit(*this);
}

AttributeValueNode::AttributeValueNode(std::string& value)
{
  this->value = value;
}

AttributeValueNode::AttributeValueNode(const char* value)
{
  this->value = value;
}

std::string& AttributeValueNode::getValue()
{
  return this->value;
}
