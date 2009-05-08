#include "ErrorHandler.hh"
#include "Utils.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the error handler
   */
  ErrorHandler::ErrorHandler()
  {
  }

  /*!
  ** Destruct the error handler, deleting all errors.
   */
  ErrorHandler::~ErrorHandler()
  {
    typedef std::vector<Error*>::iterator iter;

    for (iter i = _errors.begin(); i != _errors.end(); ++i)
      delete *i;
  }

  /*!
  ** Check if error handler contains errors.
  **
  ** @return If error handler own errors
  */
  bool
  ErrorHandler::hasErrors() const
  {
    return _errors.size() > 0;
  }

  /*!
  ** Get the min error type
  **
  ** @return The min error type
  */
  char
  ErrorHandler::getErrorType()
  {
    typedef std::vector<Error*>::iterator iter;
    char minErr = 0;

    for (iter i = _errors.begin(); i != _errors.end(); ++i)
      if ((*i)->getType() < minErr)
	minErr = (*i)->getType();

    return minErr;
  }

  /*!
  ** Add an error into the error handler.
  **
  ** @param type The type of the error
  ** @param msg The error message
  ** @param line The line of the error
  */
  void
  ErrorHandler::addError(const Error::type type, const std::string msg, const int line)
  {
    _errors.push_back(new Error(type, msg, line));
  }

  /*!
  ** Display all errors into the given stream.
  **
  ** @param o The stream where to display error
  **
  ** @return The modified stream
  */
  std::ostream&
  ErrorHandler::displayErrors(std::ostream& o) const
  {
    typedef std::vector<Error*>::const_iterator iter;

    for (iter i = _errors.begin(); i != _errors.end(); ++i)
      o << "Line " << (*i)->getLine() << ": " << (*i)->getMsg() << std::nl;

    return o;
  }

  /*!
  ** Display all errors into the given stream.
  **
  ** @param o The stream where to display error
  ** @param errors The error object to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const ErrorHandler& errors)
  {
    return errors.displayErrors(o);
  }
}
