#include "XmlReader.h"

XmlReader::XmlReader()
  : rawData("")
{
}

XmlReader::XmlReader(std::string filePath)
  : rawData("")
{
  this->file = std::ifstream(filePath, std::ios::in);
  if (file.good()) {
    if (file.is_open()) {
      std::cout << "Reading file " << filePath << std::endl;
      readRawData();
      file.close();
    }
  }
  else {
    std::cout << "Could not open file \"" << filePath << "\"" << std::endl;
    file.clear();
    file.close();
  }
}

std::string & XmlReader::getData()
{
  return cleanData;
}

/// Read all data without any processing into rawData string.
/// Assumes that the file handle is set up correctly and filestream is good&open
void XmlReader::readRawData()
{
  //reading the whole block at once would be faster... maybe change that later
  std::string line;
  while (std::getline(file, line)) {
    rawData.append(line + '\n');
  }
  cleanData = cleanRawData();
}

/// Helper method to remove XML code that is unneccessary for AST creation
std::string XmlReader::cleanRawData()
{
  std::string copy = rawData;
  removeComments(copy);
  removeLineBreaks(copy);
  return copy;
}

/// crude removal of XML comments, not checking for validity
void XmlReader::removeComments(std::string &data)
{
  bool commentFound = false;

  do {
    size_t commentStart = data.find("<!--");
    if (commentStart != std::string::npos) {
      size_t commentEnd = data.find("-->");
      if (commentEnd != std::string::npos) {
        commentFound = true;
        data.erase(commentStart, (commentEnd - commentStart + 3) );
      } 
      else {
        commentFound = false;
      }
    }
    else {
      commentFound = false;
    }
  } while (commentFound);
}

void XmlReader::removeLineBreaks(std::string& data)
{
  //DOS linebreaks"\r\n" have to be removed before unix line break "\n" for obvious reason
  removeDosLineBreaks(data);
  removeUnixLineBreaks(data);
}

void XmlReader::removeDosLineBreaks(std::string& data)
{
  bool lineBreakFound = false;
  do {
    //search DOS line endings
    size_t lineBreakStart = data.find('\r\n');
    if (lineBreakStart != std::string::npos) {
      lineBreakFound = true;
      data.erase(lineBreakStart, 2);
    }
    else {
      lineBreakFound = false;
    }
  } while (lineBreakFound);
}

void XmlReader::removeUnixLineBreaks(std::string& data)
{
  bool lineBreakFound = false;
  do {
    //search DOS line endings
    size_t lineBreakStart = data.find('\n');
    if (lineBreakStart != std::string::npos) {
      lineBreakFound = true;
      data.erase(lineBreakStart, 1);
    }
    else {
      lineBreakFound = false;
    }
  } while (lineBreakFound);
}
