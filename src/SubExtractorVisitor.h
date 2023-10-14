#pragma once
#include "AstVisitor.h"

class SubExtractorVisitor :
  public AstVisitor
{
  public:
    
    SubExtractorVisitor(std::string & subName);
    void visit(class AstNode& node){}
    void visit(class RootNode& node){}
    void visit(class ElementNode& node){}
    void visit(class TagNode& node);
    void visit(class TextNode& node);
    void visit(class AttributeNode& node){}
    void visit(class AttributeNameNode& node){}
    void visit(class AttributeValueNode& node){}

    std::string & getExtractedValue();

  private:
    std::string subName;
    std::string extractedValue;
};

