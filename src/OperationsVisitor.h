#pragma once
#include "AstVisitor.h"
#include "Operation.h"
#include <regex>



class OperationsVisitor :
  public AstVisitor
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

    std::list<Operation*> & getOperations();

  private:
    std::list<Operation*> operations;
    
};

