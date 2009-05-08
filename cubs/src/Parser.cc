#include "Parser.hh"

#include "NodeCompoundInstr.hh"
#include "NodeInstrs.hh"
#include "NodeInstr.hh"
#include "NodeAffect.hh"
#include "NodeId.hh"
#include "NodeExpression.hh"
#include "NodeFactor.hh"
#include "NodeNumber.hh"

#include <sstream>

namespace MiniCompiler
{
  /*!
  ** Construct the parser, with the given lexer.
  ** Inialize the visitor with the given lexer, and
  ** set node program to null.
  **
  ** @param lexer The lexer
  */
  Parser::Parser(const Lexer& lexer)
    : _astCreator(lexer), _node(0)
  {
  }

  /*!
  ** Destruct the parser, deleting the node program.
  */
  Parser::~Parser()
  {
    delete _node;
  }

  /*!
  ** Construct the AST.
  */
  void
  Parser::construct()
  {
    _node = new AST::NodeProgram();
    _astCreator.construct(_node);
  }

  /*!
  ** Get if errors occured.
  **
  ** @return If has errors
  */
  bool
  Parser::hasErrors() const
  {
    return _astCreator.getErrors().hasErrors();
  }

  /*!
  ** Display all errors.
  */
  void
  Parser::displayErrors() const
  {
    std::cerr << _astCreator.getErrors();
  }

  /*!
  ** Get the AST.
  **
  ** @return The syntax tree
  */
  AST::NodeProgram*
  Parser::getSyntaxTree() const
  {
    return _node;
  }
}
