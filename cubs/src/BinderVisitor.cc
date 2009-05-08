#include "BinderVisitor.hh"
#include "NodeIds.hh"
#include "NodeProgram.hh"
#include "NodeAffect.hh"
#include "NodeIf.hh"
#include "NodeRead.hh"
#include "NodeArgument.hh"
#include "NodeArguments.hh"
#include "NodeReturn.hh"
#include "NodeCallFunc.hh"
#include "NodeOperation.hh"
#include "NodeExpression.hh"
#include "NodeStringExpr.hh"
#include "NodeBoolean.hh"
#include "NodeExpressions.hh"
#include "NodeInstr.hh"
#include "NodeCompoundInstr.hh"
#include "NodeFactor.hh"
#include "NodeInstrs.hh"
#include "NodeType.hh"
#include "NodeFunction.hh"
#include "NodeWhile.hh"
#include "NodeDeclarationBody.hh"
#include "NodeFunctions.hh"
#include "NodeNumber.hh"
#include "NodeDeclaration.hh"
#include "NodeHeaderFunc.hh"
#include "NodeDeclarations.hh"
#include "NodeId.hh"
#include "NodeIdFunc.hh"
#include "NodePrint.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the binder visitor, settings isDeclaration to false,
  ** _isArgument tu false and _currentFunction to null.
  ** Open the function and the variable scope.
  */
  BinderVisitor::BinderVisitor()
    : _isDecl(false), _isArgument(false), _currentFunction(0)
  {
    _scopeVar.open();
    _scopeFunc.open();
  }

  /*!
  ** Destruct the binder visitor.
  ** Close the function and the variable scope.
  */
  BinderVisitor::~BinderVisitor()
  {
    _scopeVar.close();
    _scopeFunc.close();
  }

  /*!
  ** Get all errors encountered.
  **
  ** @return Errors encountered
  */
  const ErrorHandler&
  BinderVisitor::getErrors() const
  {
    return _errors;
  }

  /*!
  ** Display the variable and function scope to the given stream.
  **
  ** @param o The stream where to display it
  */
  void
  BinderVisitor::displayVariables(std::ostream& o) const
  {
    o << _scopeVar;
    o << _scopeFunc;
  }

  /*!
  ** Visit all header a take care of each declared functions.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visitFuncHeader(AST::NodeFunctions* node)
  {
    assert(node);
    AST::NodeFunction* func = node->getFunc();
    assert(func);
    AST::NodeHeaderFunc* header = func->getHeaderFunc();
    assert(header);

    // Ok so there is a function declaration. Just go to
    // the NodeId which take care of adding it in the scope.
    AST::NodeIdFunc* id = header->getId();
    AST::NodeArguments* args = header->getArguments();
    assert(id);
    _isDecl = true;
    _currentFunction = func;

    // Let's bind all function declaration
    id->accept(*this);

    // If function has arguments, we bind it in advance
    _scopeVar.open();
    _isArgument = true;
    if (args)
      args->accept(*this);
    _isArgument = false;
    _scopeVar.close();

    _currentFunction = 0;
    _isDecl = false;

    AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
      visitFuncHeader(funcs);
  }

  /*!
  ** Bind the program node.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeProgram* node)
  {
    assert(node);
    AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
      decls->accept(*this);
    AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
    {
      visitFuncHeader(funcs);
      funcs->accept(*this);
    }
    AST::NodeCompoundInstr* instrs = node->getInstrs();
    if (instrs)
      instrs->accept(*this);
  }

  /*!
  ** Bind the function id node.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeIdFunc* node)
  {
    // If it's a declaration
    if (_isDecl)
    {
      // Check that it's not already defined
      AST::NodeFunction* var = _scopeFunc.getFromCurrent(node->getId());
      if (!var)
      {
	assert(_currentFunction);
	node->setRef(_currentFunction);
	node->setDeclaration(true);
	_scopeFunc.put(node->getId(), _currentFunction);
      }
      else
      {
	// Else, it's a redefinition
	_errors.addError(Error::BINDING, "Function " +
			 node->getId() + " already defined at line " +
			 Utils::intToString(var->getHeaderFunc()->getId()->getLine()),
			 node->getLine());
      }
    }
    // So it's a simple call func
    else
    {
      // Check that the function has been declared
      AST::NodeFunction* var = _scopeFunc.getFromAll(node->getId());
      if (var)
	node->setRef(var);
      else
	_errors.addError(Error::BINDING, "Function " +
			 node->getId() + " is undeclared",
			 node->getLine());
    }
  }

  /*!
  ** Bind the id node.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeId* node)
  {
    assert(node);

    // If it's a declaration
    if (_isDecl)
    {
      // Check that it's not already defined
      AST::NodeId* var = _scopeVar.getFromCurrent(node->getId());
      if (!var)
      {
	node->setRef(node);
	node->setDeclaration(true);
	_scopeVar.put(node->getId(), node);

	// Now we have add the var declaration, let's
	// check if it's a function argument.
	if (_isArgument)
	{
	  // It's an argument so let's bind it to his associated function
	  assert(_currentFunction);
	  _currentFunction->addArgument(node);
	}

      }
      else
      {
	// Else, it's a redefinition
	_errors.addError(Error::BINDING, "Variable " +
			 node->getId() + " already defined at line " +
			 Utils::intToString(var->getLine()),
			 node->getLine());
      }
    }
    // So it's a simple var
    else
    {
      // Check that the variable has been declared
      AST::NodeId* var = _scopeVar.getFromAll(node->getId());
      if (var)
	node->setRef(var);
      else
	_errors.addError(Error::BINDING,"Variable " +
			 node->getId() + " is undeclared",
			 node->getLine());
    }
  }

  /*!
  ** Bind the function header node.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeHeaderFunc* node)
  {
    assert(node);
    // Just get the args, because other binding
    // procedure was already done in visitFuncHeader
    AST::NodeArguments* args = node->getArguments();

    _isDecl = true;
    if (args)
      args->accept(*this);
    _isDecl = false;
  }

  /*!
  **  Here, we just warn we are in declaration area.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeDeclarations* node)
  {
    assert(node);
    _isDecl = true;
    NonConstBaseVisitor::visit(node);
    _isDecl = false;
  }

  /*!
  ** Open a scope for the function.
  ** Also set the current function flag.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeFunction* node)
  {
    assert(node);
    _scopeVar.open();
    _currentFunction = node;
    NonConstBaseVisitor::visit(node);
    _currentFunction = 0;
    _scopeVar.close();
  }

  /*!
  ** Bind the return node.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeReturn* node)
  {
    assert(node);

    // We are not in a function, so throw an error !
    if (!_currentFunction)
    {
	_errors.addError(Error::BINDING,
			 "return outside any function",
			 node->getLine());
	return;
    }

    // We are in a function, so bind return to it
    node->setRefFunc(_currentFunction);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the function call node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeCallFunc* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);

    // So let's get all expr to fill call func arguments
    AST::NodeExpressions* exprs = node->getExprs();
    while (exprs)
    {
      assert(exprs->getExpr());
      node->addArgument(exprs->getExpr());
      exprs = exprs->getExprs();
    }

    // Let's check if function is declared
    assert(node->getId());
    AST::NodeFunction* refFunc = node->getId()->getRef();
    if (!refFunc)
      return;

    // Ok, so now check that's function call has the right
    // number of arguments
    unsigned int nbCall = node->nbArgument();
    assert(refFunc);
    unsigned int nbRef = refFunc->nbArgument();
    if (nbCall != nbRef)
    {
      std::stringstream buf;
      buf << "Call function <" << node->getId()->getId() <<
	"> with " << nbCall << " argument" << (nbCall > 1 ? "s" : "") <<
	" but function has " << nbRef << " argument" << (nbRef > 1 ? "s" : "");
      _errors.addError(Error::BINDING, buf.str(), node->getLine());
      return;
    }
  }

  /*!
  **  Just get rid of them
  */

  /*!
  ** Bind the exit node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeExit* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the compound instruction node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeCompoundInstr* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the functions node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeFunctions* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the affect node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeAffect* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the if node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeIf* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the read node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeRead* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the argument node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeArgument* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the arguments node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeArguments* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the operation node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeOperation* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the expression node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeExpression* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the string expression node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeStringExpr* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the boolean node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeBoolean* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the expressions node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeExpressions* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the instruction node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeInstr* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the factor node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeFactor* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the instructions node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeInstrs* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the type node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeType* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the while exit node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeWhile* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the declaration body node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeDeclarationBody* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the number node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeNumber* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the declaration node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeDeclaration* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the print node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodePrint* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Bind the ids node. Nothing to do, just call base visitor.
  **
  ** @param node The node to visit
  */
  void
  BinderVisitor::visit(AST::NodeIds* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }
}
