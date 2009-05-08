#ifndef ERRORHANDLER_HH_
# define ERRORHANDLER_HH_

# include <vector>
# include <iostream>
# include "Error.hh"

namespace MiniCompiler
{
  class ErrorHandler
  {
  public:
    ErrorHandler();
    ~ErrorHandler();

  public:
    bool hasErrors() const;
    void addError(const Error::type type, const std::string msg, const int line);
    std::ostream& displayErrors(std::ostream& o) const;
    char getErrorType();

  private:
    std::vector<Error*>		_errors;
  };

  std::ostream&
  operator<<(std::ostream& o, const ErrorHandler& errors);
}

#endif /* !ERRORHANDLER_HH_ */
