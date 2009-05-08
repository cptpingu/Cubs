#include "TypeCheckerVisitor.hh"
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
  ** Construct the type checker visitor.
  */
  TypeCheckerVisitor::TypeCheckerVisitor()
    : _type(AST::Type::UNDEFINED)
  {
  }

  /*!
  ** Destruct the type checker visitor.
  */
  TypeCheckerVisitor::~TypeCheckerVisitor()
  {
  }

  /*!
  ** Get all errors.
  **
  ** @return All errors encountered
  */
  const ErrorHandler&
  TypeCheckerVisitor::getErrors() const
  {
    return _errors;
  }

  /*!
  ** We need to type all function first, ie getting
  ** the return type then and set it to the function node.
  ** After that, we type all arguments.
  ** Hence, we browse all function header.
  ** The function code, ie declarations and compound instruction,
  ** will be typed later.
  **
  ** @param node A function node
  */
  void
  TypeCheckerVisitor::visitFuncHeader(AST::NodeFunctions* node)
  {
    assert(node);
    AST::NodeFunction* func = node->getFunc();
    assert(func);
    AST::NodeHeaderFunc* header = func->getHeaderFunc();
    assert(header);

    // Get the return type
    AST::NodeType* retType = header->getType();
    assert(retType);
    retType->accept(*this);
    func->setComputedType(retType->getComputedType());

    // Type the function id
    AST::NodeIdFunc* id = header->getId();
    assert(id);
    id->accept(*this);

    // Type all arguments of this function
    AST::NodeArguments* args = header->getArguments();
    if (args)
      args->accept(*this);

    // Go to the next function declaration
    AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
      visitFuncHeader(funcs);
  }

  /*!
  ** Construct a type mismatch error and add it to the error handler.
  **
  ** @param ref Type expected
  ** @param current Current type
  */
  void
  TypeCheckerVisitor::typeMismatch(const AST::TypedNode* ref,
				   const AST::TypedNode* current)
  {
    assert(ref);
    assert(current);

    const AST::Type::type refType = ref->getComputedType();
    const AST::Type::type curType = current->getComputedType();
    const int refLine = ref->getLine();
    const int curLine = current->getLine();
    std::stringstream buf;
    buf <<"Type mismatch, expected <" <<
      Utils::typeToString(refType) << "> located at line " <<
      refLine << ", but was <" << Utils::typeToString(curType) << ">";
    _errors.addError(Error::TYPE_CHECKING, buf.str(), curLine);
  }

  /*!
  ** Check type validity in program node.
  **
  ** @param node A program node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeProgram* node)
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
  ** Check type validity in function id node.
  **
  ** @param node A function id node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeIdFunc* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
    AST::NodeFunction* ref = node->getRef();
    assert(ref);
    node->setComputedType(ref->getComputedType());
  }

  /*!
  ** Check type id in program node.
  **
  ** @param node An id node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeId* node)
  {
    assert(node);

    // Ok, so we are in a leaf of this AST
    // Just check direct type, or type from referenced node
    if (!node->isDeclaration())
    {
      AST::NodeId* ref = node->getRef();
      assert(ref);
      node->setComputedType(ref->getComputedType());
      return;
    }

    // It's not a var, but a declaration
    // So, its direct type is stored in _type var
    node->setComputedType(_type);
  }

  /*!
  ** Check type validity in function header node.
  **
  ** @param node A function header node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeHeaderFunc*)
  {
    // Nothing to do because we do all work in visitFuncHeader
  }

  /*!
  ** Check type validity in declarations node.
  **
  ** @param node A declarations node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeDeclarations* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in function node.
  **
  ** @param node A function node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeFunction* node)
  {
    assert(node);

    // Don't go in header, because we already type all header
    // in visitFuncHeader, called previously
    assert(node);
    AST::NodeDeclarations* decls = node->getDeclarations();
    AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(instr);
    if (decls)
      decls->accept(*this);
    instr->accept(*this);
  }

  /*!
  ** Check type validity in return node.
  **
  ** @param node A return node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeReturn* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
    AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    node->setComputedType(expr->getComputedType());

    // Check that return type and function return type are compatible
    AST::NodeFunction* refFunc = node->getRefFunc();
    if (node->getComputedType() != refFunc->getComputedType())
      typeMismatch(refFunc, node);
  }

  /*!
  ** Check type validity in exit node.
  **
  ** @param node An exit node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeExit* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
    AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    node->setComputedType(expr->getComputedType());

    // Check that exit builtin has an integer argument
    if (node->getComputedType() != AST::Type::INTEGER)
    {
      Configuration& cfg = Configuration::getInstance();
      _errors.addError(Error::TYPE_CHECKING,
		       "You must exit an " + cfg["int"] + " value",
		       node->getLine());
      return;
    }
  }

  /*!
  ** Check type validity in compound instruction node.
  **
  ** @param node A compound instruction node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeCompoundInstr* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in functions node.
  **
  ** @param node A functions node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeFunctions* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in affectation node.
  **
  ** @param node An affectation node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeAffect* node)
  {
    assert(node);
    AST::NodeId* id = node->getId();
    AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);
    id->accept(*this);
    expr->accept(*this);

    // Check that variable and expression are compatible
    if (id->getComputedType() != expr->getComputedType())
      typeMismatch(id, expr);
  }

  /*!
  ** Check type validity in if node.
  **
  ** @param node An if node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeIf* node)
  {
    assert(node);
    AST::NodeExpression* cond = node->getCond();
    AST::NodeCompoundInstr* body = node->getBodyExprs();
    AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    cond->accept(*this);
    if (cond->getComputedType() != AST::Type::BOOLEAN)
    {
      Configuration& cfg = Configuration::getInstance();
      _errors.addError(Error::TYPE_CHECKING,
		       "\"" + cfg["if"] + "\" instruction must take a " +
		       cfg["bool"] + " expression",
		       node->getLine());
    }
    body->accept(*this);
    if (elseExprs)
      elseExprs->accept(*this);
  }

  /*!
  ** Check type validity in read node.
  **
  ** @param node A read node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeRead* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in argument node.
  **
  ** @param node An argument node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeArgument* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in arguments node.
  **
  ** @param node An arguments node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeArguments* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in function call node.
  **
  ** @param node A function call node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeCallFunc* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
    AST::NodeIdFunc* id = node->getId();
    assert(id);
    node->setComputedType(id->getComputedType());

    // Check that call func and declared func are same number of arguments
    AST::NodeFunction* refFunc = node->getId()->getRef();
    assert(refFunc);
    assert(refFunc->nbArgument() == node->nbArgument());

    // Now check that all argument types match the correct one
    AST::NodeExpression* exprType = 0;
    AST::NodeId* idType = 0;
    for (unsigned int i = 0; i < refFunc->nbArgument(); i++)
    {
      exprType = node->getArgument(i);
      idType = refFunc->getArgument(i);
      assert(exprType);
      assert(idType);
      if (exprType->getComputedType() != idType->getComputedType())
	typeMismatch(idType, exprType);
    }
  }

  /*!
  ** Check type validity in operation node.
  **
  ** @param node An operation node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeOperation* node)
  {
    assert(node);
    AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);

    leftFactor->accept(*this);
    AST::Type::type lh = leftFactor->getComputedType();
    if (node->getOpType() != AST::Operator::NONE)
    {
      AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      rightFactor->accept(*this);

      // Check here if type is compatible
      if (lh != rightFactor->getComputedType())
      {
	typeMismatch(rightFactor, leftFactor);
	return;
      }

      // Check if type is compatible with given operator
      Configuration& cfg = Configuration::getInstance();
      switch (node->getOpType())
      {
	case AST::Operator::PLUS:
	  if (lh == AST::Type::BOOLEAN)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Can't make addition on " + cfg["bool"],
			     node->getLine());
	  break;
	case AST::Operator::MINUS:
	  if (lh != AST::Type::INTEGER)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Substract can only be performed on " + cfg["int"],
			     node->getLine());
	  break;
	case AST::Operator::DIV:
	  if (lh != AST::Type::INTEGER)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Division can only be performed on " + cfg["int"],
			     node->getLine());
	  break;
	case AST::Operator::MUL:
	  if (lh != AST::Type::INTEGER)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Multiplication can only be performed on " + cfg["int"],
			     node->getLine());
	  break;
	case AST::Operator::MODULO:
	  if (lh != AST::Type::INTEGER)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Modulo can only be performed on " + cfg["int"],
			     node->getLine());
	  break;
	case AST::Operator::SUP:
	case AST::Operator::SUPEQUAL:
	case AST::Operator::INF:
	case AST::Operator::INFEQUAL:
	  node->setComputedType(AST::Type::BOOLEAN);
	  if (lh != AST::Type::INTEGER)
	    _errors.addError(Error::TYPE_CHECKING,
			     "Comparison can only be performed on " + cfg["int"],
			     node->getLine());
	  return;
	case AST::Operator::DIFF:
	case AST::Operator::EQUAL:
	  node->setComputedType(AST::Type::BOOLEAN);
	  return;
	default:
	  assert(false);
      }
    }

    node->setComputedType(lh);
  }

  /*!
  ** Check type validity in expression node.
  **
  ** @param node An expression node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeExpression* node)
  {
    assert(node);
    AST::NodeOperation* op = node->getOperation();
    assert(op);
    op->accept(*this);
    node->setComputedType(op->getComputedType());
  }

  /*!
  ** Check type validity in string expression node.
  **
  ** @param node A string expression node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeStringExpr* node)
  {
    assert(node);
    node->setComputedType(AST::Type::STRING);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in boolean node.
  **
  ** @param node A boolean node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeBoolean* node)
  {
    assert(node);
    node->setComputedType(AST::Type::BOOLEAN);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in expressions node.
  **
  ** @param node An expressions node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeExpressions* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in instruction node.
  **
  ** @param node An instruction node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeInstr* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in factor node.
  **
  ** @param node A factor node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeFactor* node)
  {
    assert(node);
    AST::NodeId* id = node->getId();
    AST::NodeCallFunc* callFunc = node->getCallFunc();
    AST::NodeNumber* number = node->getNumber();
    AST::NodeStringExpr* stringExpr = node->getStringExpr();
    AST::NodeBoolean* boolExpr = node->getBool();
    AST::NodeExpression* expression = node->getExpression();
    unsigned int nb = 0;

    nb += id ? 1 : 0;
    nb += callFunc ? 1 : 0;
    nb += number ? 1 : 0;
    nb += stringExpr ? 1 : 0;
    nb += boolExpr ? 1 : 0;
    nb += expression ? 1 : 0;
    assert(nb == 1);

    if (id)
    {
      id->accept(*this);
      node->setComputedType(id->getComputedType());
      return;
    }
    if (callFunc)
    {
      callFunc->accept(*this);
      node->setComputedType(callFunc->getComputedType());
      return;
    }
    if (number)
    {
      number->accept(*this);
      node->setComputedType(number->getComputedType());
      return;
    }
    if (stringExpr)
    {
      stringExpr->accept(*this);
      node->setComputedType(stringExpr->getComputedType());
      return;
    }
    if (boolExpr)
    {
      boolExpr->accept(*this);
      node->setComputedType(boolExpr->getComputedType());
      return;
    }
    if (expression)
    {
      expression->accept(*this);
      node->setComputedType(expression->getComputedType());
      return;
    }
  }

  /*!
  ** Check type validity in instructions node.
  **
  ** @param node A instructions node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeInstrs* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in type node.
  **
  ** @param node A type node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeType* node)
  {
    assert(node);
    node->setComputedType(Utils::stringToType(node->getType()));
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in while node.
  **
  ** @param node A while node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeWhile* node)
  {
    assert(node);
    AST::NodeExpression* cond = node->getCond();
    AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);

    cond->accept(*this);
    if (cond->getComputedType() != AST::Type::BOOLEAN)
    {
      Configuration& cfg = Configuration::getInstance();
      _errors.addError(Error::TYPE_CHECKING,
		       "\"" + cfg["while"] + "\" instruction must take a " +
		       cfg["bool"] + " expression",
		       node->getLine());
    }
    body->accept(*this);
  }

  /*!
  ** Check type validity in declaration body node.
  **
  ** @param node A declaration body node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeDeclarationBody* node)
  {
    assert(node);
    AST::NodeIds* ids = node->getIds();
    AST::NodeType* type = node->getType();
    assert(ids);
    assert(type);

    assert(_type == AST::Type::UNDEFINED);
    type->accept(*this);
    _type = type->getComputedType();
    ids->accept(*this);
    _type = AST::Type::UNDEFINED;
  }

  /*!
  ** Check type validity in number node.
  **
  ** @param node A number node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeNumber* node)
  {
    assert(node);
    node->setComputedType(AST::Type::INTEGER);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in declaration node.
  **
  ** @param node A declaration node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeDeclaration* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in print node.
  **
  ** @param node A print node
  */
  void
  TypeCheckerVisitor::visit(AST::NodePrint* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }

  /*!
  ** Check type validity in ids node.
  **
  ** @param node A ids node
  */
  void
  TypeCheckerVisitor::visit(AST::NodeIds* node)
  {
    assert(node);
    NonConstBaseVisitor::visit(node);
  }
}
