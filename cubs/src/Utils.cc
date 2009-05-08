#include <cassert>
#include "Utils.hh"
#include "Configuration.hh"

namespace MiniCompiler
{
  /*!
  ** Convert a char to a string.
  **
  ** @param c The char to convert
  **
  ** @return A string from the given char
  */
  std::string
  Utils::charToString(char c)
  {
    char tab[2] = { 0, 0};

    tab[0] = c;

    return tab;
  }

  /*!
  ** Convert a string to an enum operation type.
  **
  ** @param s The string representing the operation type
  **
  ** @return The enum operation type
  */
  AST::Operator::type
  Utils::StringToOp(const std::string& s)
  {
    Configuration& cfg = Configuration::getInstance();
    if (s == cfg["+"])
      return AST::Operator::PLUS;
    if (s == cfg["-"])
      return AST::Operator::MINUS;
    if (s == cfg["*"])
      return AST::Operator::MUL;
    if (s == cfg["/"])
      return AST::Operator::DIV;
    if (s == cfg["%"])
      return AST::Operator::MODULO;
    if (s == cfg[">"])
      return AST::Operator::SUP;
    if (s == cfg["<"])
      return AST::Operator::INF;
    if (s == cfg[">="])
      return AST::Operator::SUPEQUAL;
    if (s == cfg["<="])
      return AST::Operator::INFEQUAL;
    if (s == cfg["!="])
      return AST::Operator::DIFF;
    if (s == cfg["=="])
      return AST::Operator::EQUAL;
    assert(false);
    return AST::Operator::PLUS;
  }

  /*!
  ** Convert an enum operation type to a string.
  **
  ** @param t The operation type
  **
  ** @return The string corresponding to the given enum operation type
  */
  const std::string&
  Utils::OpToString(AST::Operator::type t)
  {
    Configuration& cfg = Configuration::getInstance();
    if (t == AST::Operator::PLUS)
      return cfg["+"];
    if (t == AST::Operator::MINUS)
      return cfg["-"];
    if (t == AST::Operator::MUL)
      return cfg["*"];
    if (t == AST::Operator::DIV)
      return cfg["/"];
    if (t == AST::Operator::MODULO)
      return cfg["%"];
    if (t == AST::Operator::SUP)
      return cfg[">"];
    if (t == AST::Operator::INF)
      return cfg["<"];
    if (t == AST::Operator::SUPEQUAL)
      return cfg[">="];
    if (t == AST::Operator::INFEQUAL)
      return cfg["<="];
    if (t == AST::Operator::DIFF)
      return cfg["!="];
    if (t == AST::Operator::EQUAL)
      return cfg["=="];
    assert(false);
    return cfg["=="];
  }

  /*!
  ** Create a string of given size constitued by the given character.
  **
  ** @param c The character use to fill the string
  ** @param size The size the string will have
  **
  ** @return A string constituted with given arguments
  */
  const std::string
  Utils::stringFill(const char c, const unsigned int size)
  {
    const std::string fill(size, c);
    return fill;
  }

  /*!
  ** Convert a boolean to string.
  **
  ** @param t The boolean
  **
  ** @return A string corresponding to boolean
  */
  const std::string&
  Utils::boolToString(const bool t)
  {
    Configuration& cfg = Configuration::getInstance();
    if (t)
      return cfg["true"];
    return cfg["false"];
  }

  /*!
  ** Convert a string to a boolean.
  **
  ** @param t The string
  **
  ** @return True if "true", and "false" if false.
  */
  bool
  Utils::stringToBool(const std::string& t)
  {
    Configuration& cfg = Configuration::getInstance();
    if (t == cfg["true"])
      return true;
    if (t == cfg["false"])
      return false;

    assert(false);
    return false;
  }

  /*!
  ** Convert an int to a string.
  **
  ** @param i The argument
  **
  ** @return A string corresponding to the given integer
  */
  const std::string
  Utils::intToString(const int i)
  {
    std::ostringstream out;
    out << i;
    return out.str();
  }

  /*!
  ** Convert a string to an enum ast type.
  **
  ** @param t The string representing a type
  **
  ** @return An enum ast type
  */
  AST::Type::type
  Utils::stringToType(const std::string& t)
  {
    Configuration& cfg = Configuration::getInstance();

    if (t == cfg["int"])
      return AST::Type::INTEGER;
    else
      if (t == cfg["string"])
	return AST::Type::STRING;
      else
	if (t == cfg["bool"])
	  return AST::Type::BOOLEAN;

    return AST::Type::UNDEFINED;
  }

  /*!
  ** Convert a type to a string.
  **
  ** @param t The type to convert
  **
  ** @return A string corresponding to the given type
  */
  const std::string&
  Utils::typeToString(const AST::Type::type t)
  {
    Configuration& cfg = Configuration::getInstance();

    if (t == AST::Type::INTEGER)
      return cfg["int"];
    else
      if (t == AST::Type::STRING)
	return cfg["string"];
      else
	if (t == AST::Type::BOOLEAN)
	  return cfg["bool"];

    return cfg["undefined"];
  }
}
