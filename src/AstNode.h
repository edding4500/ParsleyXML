#pragma once

#include <list>

#include "AstVisitor.h"

///
/// abstract base class for tree nodes
///
class AstNode
{
  public:
    virtual ~AstNode() = default;
    virtual void accept(class AstVisitor& v) = 0;

};



class ElementNode : public AstNode
{
  public:
    ElementNode();
    ~ElementNode();
    void accept(class AstVisitor& v);
    void addChild(AstNode* child);
    std::list<AstNode*> & getChildren();

  private:
    std::list<AstNode*> children;

};


class AttributeNameNode : public AstNode
{
public:
  AttributeNameNode(std::string& name);
  AttributeNameNode(const char* name);
  ~AttributeNameNode();
  void accept(class AstVisitor& v);
  std::string& getName();

private:
  std::string name;
};

class AttributeValueNode : public AstNode
{
public:
  AttributeValueNode(std::string& value);
  AttributeValueNode(const char* value);
  ~AttributeValueNode();
  void accept(class AstVisitor& v);
  std::string& getValue();

private:
  std::string value;
};

class AttributeNode : public ElementNode
{
public:
  AttributeNode();
  AttributeNode(AttributeNameNode* name, AttributeValueNode* value);
  ~AttributeNode();

  void accept(class AstVisitor& v);
  std::string & getName();
  std::string & getValue();
  AttributeNameNode* getNameNode();
  AttributeValueNode* getValueNode();
  void setAttributeNameNode(AttributeNameNode* name);
  void setAttributeValueNode(AttributeValueNode* value);

private:
  AttributeNameNode* nameNode;
  AttributeValueNode* valueNode;
};

class TagNode : public ElementNode
{
  public:
    TagNode();
    TagNode(std::string tagName);

    ~TagNode();

    void accept(class AstVisitor& v);
    std::string & getTagName();
    bool hasEqualTagName(std::string & otherTagName);
    void addAttribute(AttributeNode * attribute);
    std::list<AttributeNode*> & getAttributes();

  private:
    std::string tagName;
    std::list<AttributeNode*> attributeList;
};

class RootNode : public TagNode {
public:
  RootNode();
  ~RootNode();
  void accept(class AstVisitor& v);
 // void addChild(AstNode* child);

private:

};

class TextNode : public AstNode
{
  public:
    TextNode();
    TextNode(std::string text);
    ~TextNode();
    void accept(class AstVisitor& v);
    void addChild(AstNode* child);
    std::string & getText();
  private:
    std::string text;
};



