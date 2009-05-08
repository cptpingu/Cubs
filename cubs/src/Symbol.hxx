
namespace MiniCompiler
{
  /*!
  ** Get the text from the symbol.
  **
  ** @return The symbol text
  */
  inline const std::string&
  Symbol::getText() const
  {
    return _text;
  }

  /*!
  ** Get the line from the symbol.
  **
  ** @return The symbol line
  */
  inline int
  Symbol::getLine() const
  {
    return _line;
  }

  /*!
  ** Get the type from the symbol.
  **
  ** @return The symbol type
  */
  inline Symbol::type
  Symbol::getType() const
  {
    return _type;
  }
}
