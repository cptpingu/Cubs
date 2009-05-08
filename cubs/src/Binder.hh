#ifndef BINDER_HH_
# define BINDER_HH_

# include "Error.hh"
# include "ErrorHandler.hh"
# include "NodeProgram.hh"
# include "BinderVisitor.hh"

namespace MiniCompiler
{
  class Binder
  {
  public:
    Binder();
    ~Binder();
    void bind(AST::NodeProgram* node);
    bool hasErrors() const;
    void displayErrors() const;

  private:
    BinderVisitor	_visitor;
  };
}

#endif /* !BINDER_HH_ */
