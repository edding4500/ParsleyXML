#pragma once
#include "AstVisitor.h"
#include "OperationsVisitor.h"
#include "SubExtractorVisitor.h"
#include <stack>
#include <sstream>
#include <iomanip>

class AnalysisVisitor :
  public AstVisitor
{
  public:
    AnalysisVisitor(ElementNode * operationsTree, ElementNode * dataTree);
    ~AnalysisVisitor();
    void visit(AstNode& node);
    void visit(RootNode& node);
    void visit(ElementNode& node);
    void visit(TagNode& node);
    void visit(TextNode& node);
    void visit(AttributeNode& node);
    void visit(AttributeNameNode& node);
    void visit(AttributeValueNode& node);

    RootNode * getResultAst();

  private:
    OperationsVisitor opVis;
    ElementNode * operationsTree;
    ElementNode * dataTree;

    AttributeNode* extractAttribute(std::string& attributeName, std::list<AttributeNode*>& attributeList);
    AttributeNode* extractAttribute(const char* attributeName, std::list<AttributeNode*>& attributeList);


    std::list<TagNode*> resultNodes;
    RootNode * resultAST;

};

