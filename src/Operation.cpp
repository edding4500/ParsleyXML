#include "Operation.h"


Operation::Operation()
  : name(""), type(UNINITIALIZED), attribute(""), attributesSet(0),
  function(NOP), result(0.0)
{
}

void Operation::setName(std::string& name)
{
  this->name = name;
  attributesSet++;
}

void Operation::setType(OperationType type)
{
  this->type = type;
  attributesSet++;
}

std::string& Operation::getName()
{
  return this->name;
}

OperationType Operation::getType()
{
  return this->type;
}

void Operation::setFunction(OperationFunction function)
{
  this->function = function;
  attributesSet++;
}

void Operation::setAttribute(std::string& attribute)
{
  this->attribute = attribute;
  attributesSet++;
}

std::string& Operation::getAttribute()
{
  return this->attribute;
}

void Operation::setFilter(std::string& regEx)
{
  this->filter = std::regex(regEx);
  attributesSet++;
}

bool Operation::passesFilter(std::string & input)
{
  return std::regex_match(input, this->filter);
}

float Operation::executeFunction()
{
  switch (function)
  {
    case AVERAGE: {
      double val = 0.0;
      for (auto& value : valueList) {
        val += std::strtod(value.c_str(), NULL);
      }
      this->result = (val/valueList.size());
      return result;
    }
    case SUM: {
      double val = 0.0f;
      for (auto& value : valueList) {
        val += std::strtod(value.c_str(), NULL);
      }
      this->result = val;
      return result;
    }
    case MIN: {
      double min = (valueList.size() > 0) ?
         std::strtod(valueList.front().c_str(), NULL)
        : 0.0;
      for (auto& value : valueList) {
        double comp = std::strtod(value.c_str(), NULL);
        if (comp < min) {
          min = comp;
        }
      }
      this->result = min;
      return result;
    }
    case MAX: {
      double max = (valueList.size() > 0) ?
        std::strtod(valueList.front().c_str(), NULL)
        : 0.0;
      for (auto& value : valueList) {
        double comp = std::strtod(value.c_str(), NULL);
        if (comp > max) {
          max = comp;
        }
      }
      this->result = max;
      return result;
    }
    default: {
      std::cout << "Unknown operation function: " << function << std::endl;
      return 0.0;
    }
  }
}

double Operation::getResult()
{
  return this->result;
}

int Operation::getSetAttributesCount()
{
  return this->attributesSet;
}

void Operation::addToValueList(std::string& value)
{
  this->valueList.push_back(value);
}
