#pragma once
#include "AstVisitor.h"
#include <fstream>

class XmlWriterVisitor :
  public AstVisitor
{
  public:
    XmlWriterVisitor(std::string outputFileName);
    ~XmlWriterVisitor();
    void visit(class AstNode& node);
    void visit(class RootNode& node);
    void visit(class ElementNode& node);
    void visit(class TagNode& node);
    void visit(class TextNode& node);
    void visit(class AttributeNode& node);
    void visit(class AttributeNameNode& node);
    void visit(class AttributeValueNode& node);

  private:
    std::ofstream file;

    std::string indent;

    void incIndent();
    void decIndent();
};

