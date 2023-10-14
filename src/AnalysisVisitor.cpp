#include "AnalysisVisitor.h"


AnalysisVisitor::AnalysisVisitor(ElementNode* operationsTree, ElementNode* dataTree)
  : dataTree(dataTree),
  operationsTree(operationsTree),
  resultAST(nullptr)
{
  if (operationsTree != nullptr && dataTree != nullptr) {
    //create the operations list
    operationsTree->accept(this->opVis);
    //now visit the dataTree and collect the data values that match the rules of the operations
    dataTree->accept(*this);
    //the AnalysisVisitor enriches the Operations of the OperationsVisitor with the matching data
    //stored in Operation.valueList. Thus we can issue the 
    auto operations = opVis.getOperations();
    for (auto operation : operations) {
      std::cout << std::fixed << "Operation result: " << operation->executeFunction() << std::endl;
    }

    //manually create the result AST :)
    this->resultAST = new RootNode();
    auto resultsNode = new TagNode("results");
    resultAST->addChild(resultsNode);
    for (auto operation : operations) {
      auto singleResultNode = new TagNode("result");
      singleResultNode->addAttribute(new AttributeNode(
            new AttributeNameNode("name"), new AttributeValueNode(operation->getName()) ));
      
      std::stringstream value;
      value << std::fixed << std::setprecision(2) << operation->getResult();
      auto valueNode = new TextNode(value.str());
      singleResultNode->addChild(valueNode);
      resultsNode->addChild(singleResultNode);
    }

  }
  else {
    std::cout << "No valid data tree or operations tree handed to the AnalasysVisitor!" << std::endl;
  }
}

AnalysisVisitor::~AnalysisVisitor()
{
  //operationsTree and dataTree are actually deleted by the parsers dtor!
  if(resultAST != nullptr) delete resultAST;
}

void AnalysisVisitor::visit(AstNode& node)
{
}

void AnalysisVisitor::visit(RootNode& node)
{
  auto children = node.getChildren();
  for (auto & child : children) {
    child->accept(*this);
  }
}

void AnalysisVisitor::visit(ElementNode& node)
{
}


AttributeNode* AnalysisVisitor::extractAttribute(std::string& attributeName, std::list<AttributeNode*>& attributeList)
{
  for (auto attribute : attributeList) {
    if (attribute->getName() == (attributeName)) {
      return attribute;
    }
  }
  std::cout << "No attribute with name=\"" << attributeName << "\" found, returning nullptr!" << std::endl;
  return nullptr;
}

AttributeNode* AnalysisVisitor::extractAttribute(const char* attributeName, std::list<AttributeNode*>& attributeList)
{
  std::string str(attributeName);
  return extractAttribute(str, attributeList);
}

void AnalysisVisitor::visit(TagNode& node)
{
  //just deal with city tags. We could have defined special node types for city tags
  //but that is not quite flexible, thus we do it the "static way"
  if (node.getTagName() == ("city")) {
    auto operations = opVis.getOperations();
    for (auto operation : operations) {
      switch (operation->getType())
      {
        case OperationType::ATTRIB: {
          auto attributes = node.getAttributes();
          //apply filter on city name
          auto nameAttribute = extractAttribute("name", attributes);
          if (nameAttribute != nullptr && operation->passesFilter(nameAttribute->getValue())) {
            auto attributeValue = extractAttribute(operation->getAttribute(), attributes);
            if (attributeValue != nullptr) {
              operation->addToValueList(attributeValue->getValue());
              //attributeValue->accept(*this);
            }
          }
          break;
        }
        case OperationType::SUB: {
          auto attributes = node.getAttributes();
          //apply filter on city name
          auto nameAttribute = extractAttribute("name", attributes);
          if (nameAttribute != nullptr && operation->passesFilter(nameAttribute->getValue())) {
            //manually search the nodes children for one whose name matches the attrib-value 
            auto &children = node.getChildren();
            for (auto& child : children) {
              SubExtractorVisitor SEV(operation->getAttribute());
              child->accept(SEV);
              operation->addToValueList(SEV.getExtractedValue());
            }
          }
          break;
        }
        default: {
          std::cout << "Unhandled operation type: " << operation->getType() << std::endl;
          break;
        }
      }
    }
  }
  else {
    for (auto child : node.getChildren()) {
      child->accept(*this);
    }
  }
}

void AnalysisVisitor::visit(TextNode& node)
{
  
}

void AnalysisVisitor::visit(AttributeNode& node)
{

  node.getNameNode()->accept(*this);
  node.getValueNode()->accept(*this);
}

void AnalysisVisitor::visit(AttributeNameNode& node)
{
}

void AnalysisVisitor::visit(AttributeValueNode& node)
{
}

RootNode* AnalysisVisitor::getResultAst()
{
  return this->resultAST;
}
