#pragma once
#include <string>
#include <regex>
#include <list>
#include <algorithm>
#include <iostream>

enum OperationType {
  SUB, ATTRIB, UNINITIALIZED
};

enum OperationFunction {
  AVERAGE, SUM, MIN, MAX, NOP
};

class Operation
{
public:
  Operation();

  void setName(std::string& name);
  void setType(OperationType type);
  void setFilter(std::string& regEx);
  void setFunction(OperationFunction function);
  void setAttribute(std::string& attribute);

  std::string & getName();
  OperationType getType();
  std::string & getAttribute();
  int getSetAttributesCount();
  double getResult();

  void addToValueList(std::string & value);
  bool passesFilter(std::string & input);
  float executeFunction();

private:
  std::string name;
  std::regex filter;
  OperationType type;
  OperationFunction function;
  std::string attribute;
  int attributesSet;

  double result;

  std::list<std::string> valueList;

};
