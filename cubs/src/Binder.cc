#include <cassert>
#include "Binder.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the binder.
  */
  Binder::Binder()
  {
  }

  /*!
  ** Destruct the binder.
  */
  Binder::~Binder()
  {
  }

  /*!
  ** Bind the given AST.
  **
  ** @param node The root of AST
  */
  void
  Binder::bind(AST::NodeProgram* node)
  {
    assert(node);
    _visitor.visit(node);
  }

  /*!
  ** Check if there are errors in bind step.
  **
  ** @return If errors occured
  */
  bool
  Binder::hasErrors() const
  {
    return _visitor.getErrors().hasErrors();
  }

  /*!
  ** Display all errors encountered.
  */
  void
  Binder::displayErrors() const
  {
    std::cerr << _visitor.getErrors();
  }
}
