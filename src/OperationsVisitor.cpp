#include "OperationsVisitor.h"

void OperationsVisitor::visit(AstNode& node)
{
}

void OperationsVisitor::visit(RootNode& node)
{
  for (auto child : node.getChildren()) {
    child->accept(*this);
  }
}

void OperationsVisitor::visit(ElementNode& node)
{
}

void OperationsVisitor::visit(TagNode& node)
{
  auto tagName = node.getTagName();
  if (tagName == ("operations")) {
    for (auto child : node.getChildren()) {
      child->accept(*this);
    }
  }
  else if (tagName == ("operation")) {
    operations.push_back(new Operation);
    auto attributes = node.getAttributes();
    if (attributes.size() < 5) {
      std::cout << "\"operation\"-tag with insufficient attributes found!";
      return;
    }
    for (auto attribute : node.getAttributes()) {
      attribute->accept(*this);
    }
    if (operations.back()->getSetAttributesCount() < 5) {
      std::cout << "Invalid \"operation\"-tag found, deleting." << std::endl;
      operations.pop_back();
    }
  }
}

void OperationsVisitor::visit(TextNode& node)
{

}

void OperationsVisitor::visit(AttributeNode& node)
{
  std::string nodeName = node.getNameNode()->getName();
  if (nodeName == ("name")) {
    operations.back()->setName(node.getValueNode()->getValue());
  }
  else if (nodeName == ("type")) {
    std::string type = node.getValueNode()->getValue();
    if (type == ("sub")) {
      operations.back()->setType(SUB);
    }
    else if (type == ("attrib")) {
      operations.back()->setType(ATTRIB);
    }
  }
  else if (nodeName == ("func")) {
    std::string function = node.getValueNode()->getValue();
    if (function == ("average")) {
      operations.back()->setFunction(AVERAGE);
    }
    else if (function == ("sum")) {
      operations.back()->setFunction(SUM);
    }
    else if (function == ("min")) {
      operations.back()->setFunction(MIN);
    }
    else if (function == ("max")) {
      operations.back()->setFunction(MAX);
    }
  }
  else if (nodeName == ("attrib")) {
    operations.back()->setAttribute(node.getValueNode()->getValue());
  }
  else if (nodeName == ("filter")) {
    if (operations.back() != nullptr) {
      operations.back()->setFilter(node.getValueNode()->getValue());
    }
  }
}

void OperationsVisitor::visit(AttributeNameNode& node)
{
}

void OperationsVisitor::visit(AttributeValueNode& node)
{
}

std::list<Operation*>& OperationsVisitor::getOperations()
{
  return this->operations;
}

