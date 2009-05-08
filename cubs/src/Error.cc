#include "Error.hh"

namespace MiniCompiler
{
  /*!
  ** Construct an error with a type, a message and a line number.
  **
  ** @param type The type of the error
  ** @param msg The error message
  ** @param line The line where the error was
  */
  Error::Error(const Error::type type,
	       const std::string msg, const int line)
    : _type(type), _msg(msg), _line(line)
  {
  }

  /*!
  ** Destruct the error.
   */
  Error::~Error()
  {
  }

  /*!
  ** Get the type of the error.
  **
  ** @return The type of the error
  */
  Error::type
  Error::getType()
  {
    return _type;
  }

  /*!
  ** Get the line of the error.
  **
  ** @return The line of the error
  */
  int
  Error::getLine()
  {
    return _line;
  }

  /*!
  ** Get the error message.
  **
  ** @return The error message
  */
  std::string
  Error::getMsg()
  {
    return _msg;
  }
}
