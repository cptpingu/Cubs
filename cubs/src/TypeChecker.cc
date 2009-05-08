#include <cassert>
#include "TypeChecker.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the type checker.
  */
  TypeChecker::TypeChecker()
  {
  }

  /*!
  ** Destruct the type checker.
  */
  TypeChecker::~TypeChecker()
  {
  }

  /*!
  ** Check the type coherence of the AST.
  **
  ** @param node The root of the AST
  */
  void
  TypeChecker::checkTypes(AST::NodeProgram* node)
  {
    assert(node);
    _visitor.visit(node);
  }

  /*!
  ** Check if has errors.
  **
  ** @return If errors occured during type checking
  */
  bool
  TypeChecker::hasErrors() const
  {
    return _visitor.getErrors().hasErrors();
  }

  /*!
  ** Display all errors encountered.
  */
  void
  TypeChecker::displayErrors() const
  {
    std::cerr << _visitor.getErrors();
  }
}
