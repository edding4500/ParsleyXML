#include "XmlWriterVisitor.h"

XmlWriterVisitor::XmlWriterVisitor(std::string outputFileName)
  : indent("")
{
  this->file = std::ofstream(outputFileName, std::ios::trunc);
  if (file.good()) {
    if (file.is_open()) {
      std::cout << "Writing to file " << outputFileName << std::endl;
    }
  }
  else {
    std::cout << "Could not open file handle for \"" << outputFileName << "\"" << std::endl;
    file.clear();
    file.close();
  }
}

XmlWriterVisitor::~XmlWriterVisitor()
{
  if (file.is_open()) {
    file.close();
  }
}

void XmlWriterVisitor::visit(AstNode& node)
{
}

void XmlWriterVisitor::visit(RootNode& node)
{
  auto children = node.getChildren();
  for (auto& child : children) {
    child->accept(*this);
  }
}

void XmlWriterVisitor::visit(ElementNode& node)
{
}

void XmlWriterVisitor::visit(TagNode& node)
{
  file << indent << "<" << node.getTagName();
  auto attributes = node.getAttributes();
  for (auto& attribute : attributes) {
    file << " ";
    attribute->accept(*this);
    file << " ";
  }
  
  if (attributes.size() <= 0) {
    file << ">" << std::endl;
  }
  else {
    file.seekp(file.tellp() - std::streamoff(1));
    file << ">";
  }
  auto children = node.getChildren();
  incIndent();
  for (auto& child : children) {
    child->accept(*this);
  }
  decIndent();
  if (attributes.size() <= 0) {
    file << indent;
  }
  file << "</" << node.getTagName() << ">" << std::endl;
}

void XmlWriterVisitor::visit(TextNode& node)
{
  file << node.getText();
}

void XmlWriterVisitor::visit(AttributeNode& node)
{
  node.getNameNode()->accept(*this);
  file << "=";
  node.getValueNode()->accept(*this);
}

void XmlWriterVisitor::visit(AttributeNameNode& node)
{
  file << node.getName();
}

void XmlWriterVisitor::visit(AttributeValueNode& node)
{
  file << "\"" << node.getValue() << "\"";
}

void XmlWriterVisitor::incIndent()
{
  indent += "  ";
}

void XmlWriterVisitor::decIndent()
{
  if(indent.size() >= 2) indent.resize(indent.size() - 2);
}
