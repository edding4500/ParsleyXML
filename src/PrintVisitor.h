#pragma once
#include "AstVisitor.h"

class PrintVisitor : public AstVisitor
{
public:
  void visit(AstNode& node);
  void visit(RootNode& node);
  void visit(ElementNode& node);
  void visit(TagNode& node);
  void visit(TextNode& node);
  void visit(AttributeNode& node);
  void visit(AttributeNameNode& node);
  void visit(AttributeValueNode& node);

private:
  int currentIndent = 0;
  std::string writeIndentation();
};