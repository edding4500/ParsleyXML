#pragma once

#include <string>
#include <list>
#include <iostream>

#include "XmlBaseToken.h"
#include "XmlTokens.h"


static char ValidTagNameChars[] = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";



class XmlTokenizer
{
  public:
   XmlTokenizer();
   XmlTokenizer(std::string rawInput);
   ~XmlTokenizer();

   void setRawInput(std::string rawInput);
   
   enum TokenizerError {
     NONE, NO_CLOSING_TAG, NO_OPENING_TAG, INVALID_CHAR, NO_INPUT_DATA,
     WHITESPACE, UNANDLED_STATE
   };

   TokenizerError tokenize();

   std::list<XmlBaseToken*>& getTokenList();

  protected:

  private:
    enum TokenizerState {
      START, OPENTAG, OPENTAGNAME, ENDTAG, CLOSETAG, CLOSETAGNAME, ATTRIBUTENAME, ATTRIBUTEASSIGN,
      ATTRIBUTEVAL, CONTENT, OPENCLOSETAG, TAGWHITESPACE, ERROR
    };
    
    void handleError(TokenizerError error, char input);

    std::string rawInput;

    std::list<XmlBaseToken*> tokenList;
    size_t rawInputIndex = 0;

    TokenizerState state = TokenizerState::START;

    TokenizerError switchState(char input);

    bool isValidTageNameChar(char input);

    std::string currentDataString = "";
    

};

