#ifndef UTILS_HH_
# define UTILS_HH_

# include <string>
# include <vector>
# include <sstream>
# include <fstream>
# include <iostream>

namespace MiniCompiler
{
  namespace AST
  {
    namespace Operator
    {
      enum type
	{
	  NONE = 0,
	  PLUS,
	  MINUS,
	  MUL,
	  DIV,
	  MODULO,
	  EQUAL,
	  SUP,
	  SUPEQUAL,
	  INF,
	  INFEQUAL,
	  DIFF
	};
    }
    namespace Type
    {
      enum type
	{
	  UNDEFINED,
	  BOOLEAN,
	  INTEGER,
	  STRING
	};
    }
  }

  class Utils
  {
  public:
    template <typename C1, typename C2>
    static std::pair<C1, C2>* makePair(C1 elt1, C2 elt2);
    template <typename T>
    static T getEltFromArray(const T elt, const std::vector<T> tab);
    template <typename T>
    static T getEltFromArray(const T elt,  const T* const tab);
    template <typename T>
    static bool isInArray(const T elt, const std::vector<T> tab);
    template <typename T>
    static bool isInArray(const T elt, const T* const tab);


  public:
    static std::string charToString(char c);
    template <typename T>
    static bool
    fromString(T& t,
	       const std::string& s,
	       std::ios_base& (*f)(std::ios_base&) = std::dec);
    static AST::Operator::type
    StringToOp(const std::string& s);
    static const std::string&
    OpToString(AST::Operator::type t);
    static const std::string
    stringFill(const char c, const unsigned int size);
    static const std::string&
    boolToString(const bool t);
    static bool
    stringToBool(const std::string& t);
    static const std::string
    intToString(const int i);
    static AST::Type::type
    stringToType(const std::string& t);
    static const std::string&
    typeToString(const AST::Type::type t);
    static const std::string
    activeSpecialChar(const std::string& s);
  };
}

namespace std
{
  template <class charT, class traits>
  basic_ostream<charT, traits>&
  nl(basic_ostream<charT, traits>& os);
}

# include "Utils.hxx"

#endif /* !UTILS_HH_ */
