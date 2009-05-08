#include <cassert>
#include "Lexer.hh"

namespace MiniCompiler
{
  namespace
  {
    const char _Spaces[]  =
      {
	' ', '\n', '\f', '\v', '\r', '\t',
	0
      };
    const char _AtomicSymbol[] =
      {
	'-','*','+','/',',',';','(',')','=','<','>','!', '"', ':', '#', '%',
	0
      };
    const char _ValidChars[] =
      {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
	's','t','u','v','w','x','y','z',
	'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
	'S','T','U','V','W','X','Y','Z',
	'0','1','2','3','4','5','6','7','8','9', '_',
	0
      };
  }

  /*!
  ** This function is used to compare a real character
  ** with a string character.
  **
  ** @param c Char to compare
  ** @param str String expression as char
  **
  ** @return If char equal to string expression
  */
  bool
  operator==(const char c, const std::string& str)
  {
    if (str == "")
      return false;

    return  c == str[0];
  }

  /*!
  ** Browse the file line by line,
  ** and extract tokens.
  **
  ** @param file The stream to lex
  */
  Lexer::Lexer(std::stringstream& file)
  {
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line))
      extractTokenFromLine(line, ++lineNumber);
  }

  /*!
  ** Delete all symbol contains in the lexer.
  */
  Lexer::~Lexer()
  {
    typedef std::vector<Symbol*>::iterator iter;

    for (iter symbol = _symbols.begin();
	 symbol != _symbols.end(); ++symbol)
      delete *symbol;
  }

  /*!
  ** Check if a character is present in the given table.
  **
  ** @param c The char to check presence
  ** @param tab The table
  **
  ** @return If character is in the table
  */
  bool
  Lexer::charInTab(const char c, const char* tab)
  {
    while (*tab)
    {
      if (c == *tab)
	return true;
      tab++;
    }

    return false;
  }

  /*!
  ** Check if the character is a space.
  **
  ** @param c The char to test
  **
  ** @return If the char is a space char
  */
  bool
  Lexer::isSpace(const char c)
  {
    return charInTab(c, _Spaces);
  }

  /*!
  ** Check if char is an atomic symbol,
  ** ie if char is a space or a single special char.
  **
  ** @param c The char to test
  **
  ** @return If char is an atomic symbol
  */
  bool
  Lexer::isAtomicSymbol(const char c)
  {
    return isSpace(c) || charInTab(c, _AtomicSymbol);
  }

  /*!
  ** Test if the char is valid.
  **
  ** @param c The char to test
  **
  ** @return If the char is valid
  */
  bool
  Lexer::isValidChar(const char c)
  {
    return isAtomicSymbol(c) || charInTab(c, _ValidChars);
  }

  /*!
  ** Test if the given character is valid.
  **
  ** @param c The char to test
  ** @param lineNumber The line where the character is
  */
  void
  Lexer::checkCharValidity(const char c, const int lineNumber)
  {
    if (!isValidChar(c))
    {
      std::string err = "Invalid char \"";
      err += c;
      err += "\"";
      _errors.addError(Error::LEXER, err, lineNumber);
    }
  }

  /*!
  ** Add a new symbol in the lexer.
  **
  ** @param c The character to add
  ** @param line The line where the character is
  */
  void
  Lexer::storeSymbol(const char c, const int line)
  {
    _symbols.push_back(new Symbol(Utils::charToString(c), line));
  }

  /*!
  ** Merge two tokens in one, and add it into a single symbol.
  **
  ** @param cl The first character
  ** @param cr The second character
  ** @param line The line where the character was
  */
  void
  Lexer::mergeAndStoreSymbol(const char cl, const char cr,
			     const int line)
  {
    _symbols.push_back(new Symbol(Utils::charToString(cl) +
				  Utils::charToString(cr), line));
  }

  /*!
  ** Add a string expression into a symbol and add it to the lexer.
  **
  ** @param stringExpr The string expression to add
  ** @param line The line where the string expression is
  */
  void
  Lexer::storeStringExpr(const std::string& stringExpr,
			 const int line)
  {
    _symbols.push_back(new Symbol(stringExpr,
				  line, Symbol::STRING_EXPR));
  }

  /*!
  ** Store a classic token into a symbol. If symbol is an ID,
  ** then check if it's a valid one.
  **
  ** @param Expr The expression to store
  ** @param line The line where the expression is
  */
  void
  Lexer::storeExpr(const std::string& Expr, const int line)
  {
    Symbol* symb = new Symbol(Expr, line);
    _symbols.push_back(symb);
    if (!symb->check())
      _errors.addError(Error::LEXER, "\"" + Expr + "\" is invalid : an ID must have a valid name, ie [a-zA-Z][a-zA-Z0-9_]* and no builtin name", line);
  }

  /*!
  ** Handle a two char symbol, checking if there is a two symbol token
  **
  ** @param i The current position in the line
  ** @param size The size of the line
  ** @param line The line expression
  ** @param lineNumber The line number
  **
  ** @return New position in the line
  */
  unsigned int
  Lexer::handleTwoCharsSymbol(unsigned int i, const unsigned int size,
			      const std::string& line,
			      const int lineNumber)
  {
    Configuration& cfg = Configuration::getInstance();

    if (i + 1 < size && line[i + 1] == cfg["="])
    {
      mergeAndStoreSymbol(line[i], line[i + 1], lineNumber);
      i += 2;
    }

    return i;
  }

  /*!
  ** Handle string expression. Check if the string is correctly
  ** closed. Escape all special characters.
  **
  ** @param i The current position in the line
  ** @param size The size of the line
  ** @param line The line expression
  ** @param lineNumber The line number
  **
  ** @return New position in the line
  */
  unsigned int
  Lexer::handleStringExpr(unsigned int i, const unsigned int size,
			  const std::string& line, const int lineNumber)
  {
    std::string stringExpr = "";

    i++;
    while (i < size && line[i] != '"')
    {
      if (line[i] == '\\' && i + 1 < size && line[i + 1] == '"')
      {
	stringExpr += "\\\"";
	i++;
      }
      else
	stringExpr += line[i];
      i++;
    }

    if (i >= size)
      _errors.addError(Error::LEXER,
		       "Non terminated string", lineNumber);
    else
    {
      storeStringExpr(stringExpr, lineNumber);
      i++;
    }

    return i;
  }

  /*!
  ** Handle classic expression. Browse the line from position "i",
  ** until reach an atomic symbol, or a space.
  ** Check each characters and buffered them. Then, store bufferd
  ** expression.
  **
  ** @param i The current position in the line
  ** @param size The size of the line
  ** @param line The line expression
  ** @param lineNumber The line number
  **
  ** @return New position in the line
  */
  unsigned int
  Lexer::handleExpr(unsigned int i, const unsigned int size, const std::string& line,
		    const int lineNumber)
  {
    std::string stringExpr = "";

    while (i < size && !isAtomicSymbol(line[i]))
    {
      checkCharValidity(line[i], lineNumber);
      stringExpr += line[i];
      i++;
    }
    if (stringExpr != "")
      storeExpr(stringExpr, lineNumber);

    return i;
  }

  /*!
  ** Extract all token in a line. Check each chararacters validity.
  **
  ** @param line The line
  ** @param lineNumber The line number
  */
  void
  Lexer::extractTokenFromLine(const std::string& line,
			      const int lineNumber)
  {
    Configuration& cfg = Configuration::getInstance();
    const unsigned int size = line.length();

    for (unsigned int i = 0; i < size; i++)
    {
      checkCharValidity(line[i], lineNumber);
      // Handle comments
      if (line[i] == cfg["#"] ||
	  (line[i] == cfg["/"] && i + 1 < size && line[i + 1] == cfg["/"]))
	return;
      // Store 2 chars symbol
      if (line[i] == cfg["="] || line[i] == cfg[">"] ||
	  line[i] == cfg["<"] || line[i] == cfg["!"])
	i = handleTwoCharsSymbol(i, size, line, lineNumber);
      else
	// Extract string expression
	if (line[i] == cfg["str"])
	  i = handleStringExpr(i, size, line, lineNumber);
	else
	  // Here is the text
	  i = handleExpr(i, size, line, lineNumber);
      // Handle unary symbol
      if (i < size && isAtomicSymbol(line[i]) && !isSpace(line[i]))
	storeSymbol(line[i], lineNumber);
    }
  }

  /*!
  ** Get if errors occured.
  **
  ** @return If errors occured
  */
  bool
  Lexer::hasErrors() const
  {
    return _errors.hasErrors();
  }

  /*!
  ** Display all errors.
  */
  void
  Lexer::displayErrors() const
  {
    std::cerr << _errors;
  }

  /*!
  ** Display all lexed symbols.
  **
  ** @param o The stream where to display it
  **
  ** @return The modified stream
  */
  std::ostream&
  Lexer::displaySymbols(std::ostream& o) const
  {
    typedef std::vector<Symbol*>::const_iterator iter;

    for (iter symbol = _symbols.begin();
	 symbol != _symbols.end(); ++symbol)
      o << **symbol;

    return o;
  }

  /*!
  ** Get the wanted symbol.
  **
  ** @param i The lexer to get
  **
  ** @return Wanted symbols
  */
  const Symbol&
  Lexer::operator[](const unsigned int i) const
  {
    assert(i <= length());
    return *_symbols[i];
  }

  /*!
  ** Get the number of symbol store.
  **
  ** @return The number of symbol
  */
  unsigned int
  Lexer::length() const
  {
    return _symbols.size();
  }

  /*!
  ** Display all symbols in the given stream.
  **
  ** @param o The stream to display it
  ** @param lexer The lexer
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const Lexer& lexer)
  {
    return lexer.displaySymbols(o);
  }
}
