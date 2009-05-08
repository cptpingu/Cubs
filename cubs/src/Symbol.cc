#include "Symbol.hh"
#include "Utils.hh"

namespace MiniCompiler
{
  /*!
  ** Construct a symbol with a string, and a line number.
  ** The type is guessed automatically.
  **
  ** @param token The string expression
  ** @param line The line number
  */
  Symbol::Symbol(const std::string& token, const int line)
    : _text(token), _line(line), _type(findType(token))
  {
  }

  /*!
  ** Construct a symbol with a string, a line number and a type.
  **
  ** @param token The string expression
  ** @param line The line number
  ** @param type The symbol's type
  */
  Symbol::Symbol(const std::string& token, const int line,
		 const Symbol::type type)
    : _text(token), _line(line), _type(type)
  {
  }

  /*!
  ** Construct a symbol using another one.
  ** Use to copy symbol.
  **
  ** @param symb The symbol to copy
  */
  Symbol::Symbol(const Symbol& symb)
    : _text(symb._text), _line(symb._line),
      _type(symb._type)
  {
  }

  /*!
  ** Destroy the symbol
  */
  Symbol::~Symbol()
  {
  }

  /*!
  ** Check if the symbol is correct, ie
  ** symbol is a valid ID : [a-zA-Z][a-zA-Z0-9_]*
  **
  ** @return If symbol valid
  */
  bool
  Symbol::check() const
  {
    // First, check if it was an ID
    if (_type != ID)
      return true;

    // Check if first character is valid
    if (!(_text[0] >= 'a' && _text[0] <= 'z') &&
	!(_text[0] >= 'A' && _text[0] <= 'Z'))
      return false;

    // Check if remaining characters are valid
    for (unsigned int j = 1; j < _text.length(); j++)
    {
      if (!(_text[j] >= 'a' && _text[j] <= 'z') &&
	  !(_text[j] >= 'A' && _text[j] <= 'Z') &&
	  !(_text[j] >= '0' && _text[j] <= '9') &&
	  _text[j] != '_')
	return false;
    }

    return true;
  }

  /*!
  ** Copy token, line and type.
  **
  ** @param symb The symb to copy.
  */
  void
  Symbol::operator=(const Symbol& symb)
  {
    _text = symb._text;
    _line = symb._line;
    _type = symb._type;
  }

  /*!
  ** Find the token type.
  **
  ** @param token The token
  **
  ** @return Type of the given token
  */
  Symbol::type
  Symbol::findType(const std::string& token) const
  {
    Configuration& cfg = Configuration::getInstance();

    if (token == cfg["function"] ||
	token == cfg["return"] ||
	token == cfg["exit"] ||
	token == cfg["var"] ||
	token == cfg["if"] ||
	token == cfg["then"] ||
	token == cfg["else"] ||
	token == cfg["while"] ||
	token == cfg["do"] ||
	token == cfg["begin"] ||
	token == cfg["end"])
      return KEYWORD;
    if (token == cfg["int"] ||
	token == cfg["string"] ||
	token == cfg["bool"])
      return TYPE;
    if (token == cfg["+"] ||
	token == cfg["/"] ||
	token == cfg["-"] ||
	token == cfg["*"] ||
	token == cfg["%"])
      return OPERATOR;
    if (token == cfg["("])
      return LEFT_BRACKET;
    if (token == cfg[")"])
      return RIGHT_BRACKET;
    if (token == cfg[","])
      return COMA;
    if (token == cfg[";"])
      return SEMI_COLON;
    if (token == cfg[":"])
      return COLON;
    if (token == cfg["="])
      return ALLOCATION;
    if (token == cfg["=="] ||
	token == cfg[">="] ||
	token == cfg["<="] ||
	token == cfg[">"] ||
	token == cfg["<"] ||
	token == cfg["!="])
      return COMPARATOR;
    if (token == cfg["true"] ||
	token == cfg["false"])
      return BOOLEAN;
    for (unsigned int i = 0; i < token.length(); i++)
      if (token[i] != '0' &&
	  token[i] != '1' &&
	  token[i] != '2' &&
	  token[i] != '3' &&
	  token[i] != '4' &&
	  token[i] != '5' &&
	  token[i] != '6' &&
	  token[i] != '7' &&
	  token[i] != '8' &&
	  token[i] != '9')
	return ID;

    return VALUE;
  }

  /*!
  ** Convert a type to a string.
  **
  ** @param symbolType The type of the symbol
  **
  ** @return The string corresponding to the type
  */
  std::string
  Symbol::typeToString(const Symbol::type symbolType)
  {
    switch (symbolType)
    {
      case TYPE:
	return "Type";
      case KEYWORD:
	return "Keyword";
      case LEFT_BRACKET:
	return "Left bracket";
      case RIGHT_BRACKET:
	return "Right bracket";
      case SEMI_COLON:
	return "Semi colon";
      case OPERATOR:
	return "Operator";
      case SEPARATOR:
	return "Separator";
      case VALUE:
	return "Value";
      case ID:
	return "Id";
      case COMA:
	return "Coma";
      case ALLOCATION:
	return "Allocation";
      case COMPARATOR:
	return "Comparator";
      case STRING_EXPR:
	return "String expression";
      case BOOLEAN:
	return "Boolean";
      case COLON:
	return "Colon";
      default:
	return "Unknow";
    }
  }

  /*!
  ** Force a string to have a certain size. If the string is too small,
  ** it was filled with spaces.
  **
  ** @param s The string to format
  ** @param size The size the string must reach
  **
  ** @return The formatted string
  */
  const std::string
  Symbol::stringSizeFormatter(const std::string& s, const unsigned int size)
  {
    if (s.length() < size)
    {
      std::string fill(size - s.length(), ' ');
      return s + fill;
    }
    return s;
  }

  /*!
  ** Display a symbol, ie the type, the text and the type of this symbol.
  **
  ** @param o The stream where to display it
  ** @param symbol The symbol to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const Symbol& symbol)
  {
    return o << Symbol::stringSizeFormatter(Symbol::typeToString(symbol._type), 20)
	     << "(At line "
	     << symbol._line
	     << "): \t"
	     << symbol._text << std::nl;
  }
}
