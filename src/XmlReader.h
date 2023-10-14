#pragma once
#include <fstream>
#include <string>
#include <iostream>

/// <summary>
/// Base class for XML parsers.
/// Offers file access / data stream operations.
/// DataParser and OperationsParser inherit from this to generate individual ASTs
/// </summary>
class XmlReader
{
  public:
    XmlReader();
    XmlReader(std::string filePath);

    std::string & getData();

  protected:

  private:
    std::ifstream file;
    std::string rawData;
    std::string cleanData;

    void readRawData();
    std::string cleanRawData();
    void removeComments(std::string &data);
    void removeLineBreaks(std::string& data);
    void removeDosLineBreaks(std::string& data);
    void removeUnixLineBreaks(std::string& data);

};

