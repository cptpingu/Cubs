#ifndef ERROR_HH_
# define ERROR_HH_

# include <string>

namespace MiniCompiler
{
  class Error
  {
  public:
    enum type
      {
	NONE,
	INVALID_OPTION,
	FILE_NOT_FOUND,
	LEXER,
	PARSER,
	BINDING,
	TYPE_CHECKING,
	EXECUTION,
	UNKNOW
      };

  public:
    Error(const Error::type type,
	  const std::string msg, const int line);
    ~Error();

  public:
    type			getType();
    int				getLine();
    std::string			getMsg();

  private:
    const type			_type;
    const std::string		_msg;
    const int			_line;
  };
}

#endif /* !ERROR_HH_ */
