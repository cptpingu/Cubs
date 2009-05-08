#include <cassert>
#include "Execution.hh"

namespace MiniCompiler
{
  /*!
  ** Construct an Execution, setting verbose to false.
  */
  Execution::Execution()
    : _verbose(false)
  {
  }

  /*!
  ** Destruct an Execution.
  */
  Execution::~Execution()
  {
  }

  /*!
  ** Launch the execution step.
  **
  ** @param node The root of the AST
  **
  ** @return The exiting value of the program launched
  */
  int
  Execution::execute(AST::NodeProgram* node)
  {
    assert(node);
    _visitor.setShowCode(_verbose);
    _visitor.setShowVariables(false);
    _visitor.setShowSpecialVariables(false);
    _visitor.visit(node);

    return _visitor.getReturnValue();
  }

  /*!
  ** Launch the execution step in debug mode,
  ** displaying all variable at each executed line.
  **
  ** @param node The root of the AST
  **
  ** @return The exiting value of the program launched
  */
  int
  Execution::debug(AST::NodeProgram* node)
  {
    assert(node);
    _visitor.setShowCode(true);
    _visitor.setShowVariables(true);
    _visitor.setShowSpecialVariables(_verbose);
    _visitor.visit(node);

    return _visitor.getReturnValue();
  }

  /*!
  ** Choose if we activate the verbose mode.
  **
  ** @param v Can verbose mode must be activated ?
  */
  void
  Execution::activeVerbose(bool v)
  {
    _verbose = v;
  }
}
