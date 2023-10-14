/*
#include "DataNode.h"
#include "NodeStack.h"
#include "DataParser.h"
*/
#include "XmlReader.h"
#include "XmlTokenizer.h"
#include "XmlParser.h"
#include "AstVisitor.h"
#include "OperationsVisitor.h"
#include "AnalysisVisitor.h"
#include "XmlWriterVisitor.h"
#include "PrintVisitor.h"

#include <iostream>

int main(){
  
  XmlReader dataReader("./books.xml");

  XmlTokenizer dataTokenizer(dataReader.getData());
  if (dataTokenizer.tokenize() == XmlTokenizer::TokenizerError::NONE) {
    XmlParser dataParser;
    XmlParserError perr = dataParser.parse(dataTokenizer.getTokenList());
    if (perr != XmlParserError::NONE) {
      std::cout << "Error while parsing data.xml, aborting.";
      return 23;
    }

    PrintVisitor printer;
    dataParser.getAstRoot()->accept(printer);

    }
  else {
    std::cout << "Error while tokenizing data.xml, aborting.";
    return 23;
  }
}