#include "Configuration.hh"

namespace MiniCompiler
{
  /*!
  ** Get the real value of a keyword.
  **
  ** @param keyword The keyword key
  **
  ** @return The value associated to the given keyword
  */
  std::string&
  Configuration:: operator[](const std::string keyword)
  {
    return _keyWords[keyword];
  }

}
