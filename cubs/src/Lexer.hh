#ifndef LEXER_HH_
# define LEXER_HH_

# include <vector>
# include <string>
# include <sstream>
# include <fstream>
# include <iostream>
# include "Configuration.hh"
# include "Utils.hh"
# include "Symbol.hh"
# include "ErrorHandler.hh"

namespace MiniCompiler
{
  class Lexer
  {
  public:
    Lexer(std::stringstream& file);
    ~Lexer();

  public:
    bool hasErrors() const;
    void displayErrors() const;
    std::ostream& displaySymbols(std::ostream& o) const;
    const Symbol& operator[](const unsigned int i) const;
    unsigned int length() const;

  private:
    bool charInTab(const char c, const char* tab);
    bool isSpace(const char c);
    void extractTokenFromLine(const std::string& line, const int lineNumber);
    bool isAtomicSymbol(const char c);
    bool isValidChar(const char c);
    void checkCharValidity(const char c, const int lineNumber);
    void storeSymbol(const char c, const int line);
    void mergeAndStoreSymbol(const char cl, const char cr,
			     const int line);
    void storeStringExpr(const std::string& stringExpr,
			 const int line);
    void storeExpr(const std::string& Expr,
		   const int line);
    unsigned int handleTwoCharsSymbol(unsigned int i, const unsigned int size,
			      const std::string& line,
			      const int lineNumber);
    unsigned int handleStringExpr(unsigned int i, const unsigned int size, const std::string& line,
			  const int lineNumber);
    unsigned int handleExpr(unsigned int i, const unsigned int size, const std::string& line,
		    const int lineNumber);

  private:
    std::vector<Symbol*>	_symbols;
    ErrorHandler		_errors;
  };

  std::ostream&
  operator<<(std::ostream& o, const Lexer& lexer);
}
#endif /* !LEXER_HH_ */
