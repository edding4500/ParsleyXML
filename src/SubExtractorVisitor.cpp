#include "SubExtractorVisitor.h"

SubExtractorVisitor::SubExtractorVisitor(std::string& subName)
  : subName(subName),
  extractedValue("")
{
}

void SubExtractorVisitor::visit(TagNode& node)
{
  if (node.getTagName() == (subName)) {
    auto children = node.getChildren();
    for (auto child : children) {
      child->accept(*this);
    }
  }
}

void SubExtractorVisitor::visit(TextNode& node)
{
  this->extractedValue = node.getText();
}

std::string& SubExtractorVisitor::getExtractedValue()
{
  return this->extractedValue;
}
