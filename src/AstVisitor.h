#pragma once

#include <iostream>

#include "AstNode.h"

///
/// abstract visitor class
///
class AstVisitor
{
  public:
    virtual void visit(class AstNode & node) = 0;
    virtual void visit(class RootNode & node) = 0;
    virtual void visit(class ElementNode & node) = 0;
    virtual void visit(class TagNode & node) = 0;
    virtual void visit(class TextNode & node) = 0;
    virtual void visit(class AttributeNode & node) = 0;
    virtual void visit(class AttributeNameNode& node) = 0;
    virtual void visit(class AttributeValueNode& node) = 0;

};


