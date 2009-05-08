#ifndef PARSER_HH_
# define PARSER_HH_

# include "Error.hh"
# include "ErrorHandler.hh"
# include "Lexer.hh"
# include "NodeProgram.hh"
# include "CreateAST.hh"

namespace MiniCompiler
{
  class Parser
  {
  public:
    Parser(const Lexer& lexer);
    ~Parser();
    void construct();
    bool hasErrors() const;
    void displayErrors() const;
    AST::NodeProgram* getSyntaxTree() const;

  private:
    CreateAST		_astCreator;
    AST::NodeProgram*	_node;
  };
}

#endif /* !PARSER_HH_ */
