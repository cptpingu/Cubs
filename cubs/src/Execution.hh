#ifndef EXECUTION_HH_
# define EXECUTION_HH_

# include "Error.hh"
# include "ErrorHandler.hh"
# include "NodeProgram.hh"
# include "ExecutionVisitor.hh"

namespace MiniCompiler
{
  class Execution
  {
  public:
    Execution();
    ~Execution();
    int execute(AST::NodeProgram* node);
    int debug(AST::NodeProgram* node);
    void activeVerbose(bool v);

  private:
    ExecutionVisitor	_visitor;
    bool		_verbose;
  };
}

#endif /* !EXECUTION_HH_ */
