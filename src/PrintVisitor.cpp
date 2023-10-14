#include "PrintVisitor.h"

void PrintVisitor::visit(AstNode& node)
{
  std::cout << "basic AstNode" << std::endl;
}

void PrintVisitor::visit(RootNode& node)
{
  std::cout << writeIndentation() << "Xml document root, visiting children:" << std::endl;
  currentIndent++;
  for (auto child : node.getChildren()) {
    child->accept(*this);
  }
  currentIndent--;
}

void PrintVisitor::visit(ElementNode& node)
{
  std::cout << writeIndentation() << "Element Node, visiting children:" << std::endl;
  currentIndent++;
  for (auto child : node.getChildren()) {
    child->accept(*this);
  }
  currentIndent--;
}

void PrintVisitor::visit(TagNode& node)
{
  std::cout << writeIndentation() << "TagNode: " << node.getTagName() << std::endl;
  std::cout << writeIndentation() << "*Attributes:" << std::endl;
  currentIndent++;
  for (auto attribute : node.getAttributes()) {
    attribute->accept(*this);
  }
  currentIndent--;
  std::cout << writeIndentation() << "*Children:" << std::endl;
  currentIndent++;
  for (auto child : node.getChildren()) {
    child->accept(*this);
  }
  currentIndent--;
}

void PrintVisitor::visit(TextNode& node)
{
  std::cout << writeIndentation() << "TextNode: " << node.getText() << std::endl;
  //textnodes have no children.
}

void PrintVisitor::visit(AttributeNode& node)
{
  std::cout << writeIndentation() << "AttributeNode: ";
  node.getNameNode()->accept(*this);
  std::cout << " = ";
  node.getValueNode()->accept(*this);
  std::cout << std::endl;
}

void PrintVisitor::visit(AttributeNameNode& node)
{
  std::cout << node.getName();
}

void PrintVisitor::visit(AttributeValueNode& node)
{
  std::cout << node.getValue();
}

std::string PrintVisitor::writeIndentation()
{
  std::string indent = "";
  for (int i = 0; i < currentIndent; i++) {
    indent += '\t';
  }
  return indent;
}
