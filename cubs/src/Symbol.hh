#ifndef SYMBOL_HH_
# define SYMBOL_HH_

# include <iostream>
# include "Configuration.hh"
# include "SharedString.hh"

namespace MiniCompiler
{
  class Symbol
  {
    friend std::ostream& operator<<(std::ostream& o, const Symbol& symbol);

  public:
    enum type
      {
	TYPE,
	KEYWORD,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	SEMI_COLON,
	OPERATOR,
	SEPARATOR,
	VALUE,
	ID,
	COMA,
	ALLOCATION,
	COMPARATOR,
	STRING_EXPR,
	BOOLEAN,
	COLON
      };

  public:
    Symbol(const std::string& token, const int line);
    Symbol(const std::string& token, const int line,
	   const type type);
    Symbol(const Symbol& symb);
    void operator=(const Symbol& symb);
    ~Symbol();

  private:
    type findType(const std::string& token) const;
    static std::string typeToString(const type symbolType);
    static const std::string stringSizeFormatter(const std::string& s,
						 const unsigned int size);

  public:
    bool check() const;
    const std::string& getText() const;
    int	getLine() const;
    type getType() const;

  private:
    mystd::SharedString		_text;
    int				_line;
    type			_type;

  };

  std::ostream&
  operator<<(std::ostream& o, const Symbol& symbol);
}

#include "Symbol.hxx"

#endif /* !SYMBOL_HH_ */
