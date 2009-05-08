#ifndef TYPECHECKER_HH_
# define TYPECHECKER_HH_

# include "Error.hh"
# include "ErrorHandler.hh"
# include "NodeProgram.hh"
# include "TypeCheckerVisitor.hh"

namespace MiniCompiler
{
  class TypeChecker
  {
  public:
    TypeChecker();
    ~TypeChecker();
    void checkTypes(AST::NodeProgram* node);
    bool hasErrors() const;
    void displayErrors() const;

  private:
    TypeCheckerVisitor	_visitor;
  };
}

#endif /* !TYPECHECKER_HH_ */
