#include "XmlTokenizer.h"

XmlTokenizer::XmlTokenizer()
  : rawInput(""),
  tokenList()
{
}

XmlTokenizer::XmlTokenizer(std::string rawInput)
  : XmlTokenizer()
{
  this->rawInput = rawInput;
}

XmlTokenizer::~XmlTokenizer()
{
  for (auto token : tokenList) {
    delete token;
  }
  tokenList.clear();
}

void XmlTokenizer::setRawInput(std::string rawInput)
{
  this->rawInput = rawInput;
}

XmlTokenizer::TokenizerError XmlTokenizer::tokenize()
{
  if (rawInput == "") { return TokenizerError::NO_INPUT_DATA; }

  TokenizerError lastError = NONE;
  char lastChar = ' ';
  while(state != ERROR && rawInputIndex < rawInput.length())
  { 
    lastChar = rawInput[rawInputIndex];
    lastError = switchState(lastChar);
    rawInputIndex++;
  }
  handleError(lastError, lastChar);
  return lastError;
}

std::list<XmlBaseToken*>& XmlTokenizer::getTokenList()
{
  return this->tokenList;
}

void XmlTokenizer::handleError(TokenizerError error, char input)
{
  switch (error)
  {
  case XmlTokenizer::NONE: {
    std::cout << "No errors found during tokenizing." << std::endl;
    break;
  }
  case XmlTokenizer::NO_CLOSING_TAG: {
    std::cout << "Missing closing tag, at position " << rawInputIndex-1 << std::endl;
    break;
  }
  case XmlTokenizer::NO_OPENING_TAG: {
    std::cout << "Missing opening tag, at position " << rawInputIndex - 1 << std::endl;
    break;
  }
  case XmlTokenizer::INVALID_CHAR: {
    std::cout << "Invalid character"
    << 
    ", at position " << rawInputIndex - 1 << std::endl;
    break;
  }
  case XmlTokenizer::NO_INPUT_DATA: {
    std::cout << "No input data for tokenizer." << std::endl;
    break;
  }
  case XmlTokenizer::WHITESPACE:
    break;
  default:
    break;
  }
}

XmlTokenizer::TokenizerError XmlTokenizer::switchState(char input)
{
  
  switch (state) {
    case START: {
      if(input == '<') {
        state = OPENTAG;
        return NONE;
      }
      else if (input == ' ') {
        //ignore whitespace, dont change state
        return WHITESPACE;
      }
      else {
        state = ERROR;
        return NO_OPENING_TAG;
      }
    }
    case OPENTAG: {
      //push < to token list
      tokenList.push_back(new OpenTagToken());

      if (isValidTageNameChar(input)) {
        currentDataString.append(1, input);
        state = OPENTAGNAME;
        return NONE;
      }
      else if (input == '/') {
        state = CLOSETAG;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case OPENTAGNAME: {
      if (isValidTageNameChar(input)) {
        //dont change state
        //append character to current tag name
        currentDataString.append(1, input);
        return NONE;
      }
      else if (input == '>') {
        //first of all we add a TagNameToken to the token list
        tokenList.push_back(new TagNameToken(currentDataString));
        //delete data string
        currentDataString = "";
        //change state
        state = ENDTAG;
        return NONE;
      }
      else if (input == ' ') {
        //first of all we add a TagNameToken to the token list
        tokenList.push_back(new TagNameToken(currentDataString));
        //delete data string
        currentDataString = "";
        //ignore whitespace after a tags name
        state = TAGWHITESPACE;
        return WHITESPACE;
      }
      else if (input == '/') {
        tokenList.push_back(new TagNameToken(currentDataString));
        currentDataString = "";
        state = OPENCLOSETAG;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case ENDTAG: {
      if (input == ' ') {
        //ignore Whitespace, dont change state
        return WHITESPACE;
      }
      else if (input == '<') {
        //add trailing > to token list
        tokenList.push_back(new EndTagToken());
        state = OPENTAG;
        return NONE;
      }
      else {
        //add trailing > to token list
        tokenList.push_back(new EndTagToken());
        //all of the following text must be content
        //inbetween tags
        currentDataString.append(1, input);
        state = CONTENT;
        return NONE;
      }
    }
    case TAGWHITESPACE: {
      if (input == '>') {
        state = ENDTAG;
        return NONE;
      }
      else if (input == ' ') {
        //ignore whitespace
        return WHITESPACE;
      }
      else if (isValidTageNameChar(input)) {
        //expecting attribute name
        currentDataString.append(1, input);
        state = ATTRIBUTENAME;
        return NONE;
      }
      else if (input == '/') {
        state = OPENCLOSETAG;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case ATTRIBUTENAME: {
      if (isValidTageNameChar(input)) {
        currentDataString.append(1, input);
        return NONE;
      }
      else if (input == '=') {
        tokenList.push_back(new AttributeNameToken(currentDataString));
        currentDataString = "";
        state = ATTRIBUTEASSIGN;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case ATTRIBUTEASSIGN: {
      tokenList.push_back(new AttributeAssignToken());

      if (input == '\"') {
        state = ATTRIBUTEVAL;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case ATTRIBUTEVAL: {
      if (input == '\"') {
        tokenList.push_back(new AttributeValueToken(currentDataString));
        currentDataString = "";
        state = TAGWHITESPACE;
        return NONE;
      }
      else {
        //accepted alphabet is everything except "\""
        currentDataString.append(1, input);
        return NONE;
      }
    }
    case CONTENT: {
      if (input == '<') {
        tokenList.push_back(new ContentToken(currentDataString));
        currentDataString = "";
        state = OPENTAG;
        return NONE;
      }
      else {
        currentDataString.append(1, input);
        return NONE;
      }
    }
    case CLOSETAG: {
      tokenList.push_back(new CloseTagToken());

      if (isValidTageNameChar(input)) {
        currentDataString.append(1, input);
        state = CLOSETAGNAME;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case CLOSETAGNAME: {
      if (input == '>') {
        tokenList.push_back(new CloseTagNameToken(currentDataString));
        currentDataString = "";
        state = ENDTAG;
        return NONE;
      }
      else if (isValidTageNameChar(input)) {
        currentDataString.append(1, input);
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    case OPENCLOSETAG: {
      if (input == '>') {
        tokenList.push_back(new EndCloseTagToken());
        state = ENDTAG;
        return NONE;
      }
      else {
        state = ERROR;
        return INVALID_CHAR;
      }
    }
    default: {
      std::cout << "Unhandled Tokenizer State \"" << state << "\"" << std::endl;
      state = ERROR;
      return UNANDLED_STATE;
    }
  }
  
}

bool XmlTokenizer::isValidTageNameChar(char input)
{
  //use indexing instead of linear searching.
  if (((int)input > 64 && (int)input < 91)
    || ((int)input > 96 && (int)input < 123))
  {
    if (input == ValidTagNameChars[0] ||
      input == ValidTagNameChars[(int)input - 70] || input == ValidTagNameChars[(int)input - 96])
    {
      return true;
    }
  }
  
  return false;
}
