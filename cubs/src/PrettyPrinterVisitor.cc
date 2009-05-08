#include <cassert>
#include "PrettyPrinterVisitor.hh"
#include "Utils.hh"
#include "NodeIds.hh"
#include "NodeProgram.hh"
#include "NodeAffect.hh"
#include "NodeIf.hh"
#include "NodeRead.hh"
#include "NodeArgument.hh"
#include "NodeArguments.hh"
#include "NodeReturn.hh"
#include "NodeExit.hh"
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
  ** Construct the pretty printer visitor,
  ** initializing tabulation.
  */
  PrettyPrinterVisitor::PrettyPrinterVisitor()
    : _tab(INDENT_SIZE)
  {
  }

  /*!
  ** Destruct the visitor.
  */
  PrettyPrinterVisitor::~PrettyPrinterVisitor()
  {
  }

  /*!
  ** Print the ids node
  **
  ** @param node The ids node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeIds* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIds* ids = node->getIds();
    const AST::NodeId* id = node->getId();
    assert(id);
    id->accept(*this);
    if (ids)
    {
      _indent << cfg[","] << ' ';
      ids->accept(*this);
    }
  }

  /*!
  ** Print the program node
  **
  ** @param node The program node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    const AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
    {
      decls->accept(*this);
      _indent << '\n';
    }
    const AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
    {
      funcs->accept(*this);
      _indent << '\n';
    }
    const AST::NodeCompoundInstr* instrs = node->getInstrs();
    if (instrs)
    {
      instrs->accept(*this);
      _indent << '\n';
    }
  }

  /*!
  ** Print the affectation node
  **
  ** @param node The affectation node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeId* id = node->getId();
    const AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);
    id->accept(*this);
    _indent << ' ' << cfg["="] << ' ';
    expr->accept(*this);
  }

  /*!
  ** Print the if node
  **
  ** @param node The if node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    const AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    _indent << cfg["if"] << ' ';
    cond->accept(*this);
    _indent << ' ' << cfg["then"] << '\n';
    body->accept(*this);
    if (elseExprs)
    {
      _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["else"] << '\n';
      elseExprs->accept(*this);
    }
  }

  /*!
  ** Print the read node
  **
  ** @param node The read node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeId* id = node->getId();
    assert(id);

    _indent << cfg["read"];
    _indent << cfg["("];
    id->accept(*this);
    _indent << cfg[")"];
  }

  /*!
  ** Print the argument node
  **
  ** @param node The argument node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    const AST::NodeDeclarationBody* body = node->getDeclarationBody();
    const AST::NodeArguments* args = node->getArguments();

    assert(body);
    body->accept(*this);
    if (args)
    {
      Configuration& cfg = Configuration::getInstance();
      _indent << cfg[";"] << ' ';
      args->accept(*this);
    }
  }

  /*!
  ** Print the arguments node
  **
  ** @param node The arguments node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeArgument* arg = node->getArgument();
    const AST::NodeArguments* args = node->getArguments();

    assert(arg);
    arg->accept(*this);
    if (args)
    {
      _indent << cfg[";"] << ' ';
      args->accept(*this);
    }
  }

  /*!
  ** Print the return node
  **
  ** @param node The return node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["return"] << ' ';
    expr->accept(*this);
  }

  /*!
  ** Print the exit node
  **
  ** @param node The exit node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["exit"] << ' ';
    expr->accept(*this);
  }

  /*!
  ** Print the function call node
  **
  ** @param node The function call node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(id);

    id->accept(*this);
    _indent << cfg["("];
    if (exprs)
      exprs->accept(*this);
    _indent << cfg[")"];
  }

  /*!
  ** Print the operation node
  **
  ** @param node The operation node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    const AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);

    leftFactor->accept(*this);
    if (node->getOpType() != AST::Operator::NONE)
    {
      const AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      _indent << ' ' << Utils::OpToString(node->getOpType()) << ' ';
      rightFactor->accept(*this);
    }
  }

  /*!
  ** Print the expression node
  **
  ** @param node The expression node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the string expression node
  **
  ** @param node The string expression node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    _indent << cfg["str"];
    _indent << node->getString();
    _indent << cfg["str"];
  }

  /*!
  ** Print the boolean node
  **
  ** @param node The boolean node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    _indent << (node->getBool() ? cfg["true"] : cfg["false"]);
  }

  /*!
  ** Print the expressions node
  **
  ** @param node The expressions node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(expr);

    expr->accept(*this);
    if (exprs)
    {
      Configuration& cfg = Configuration::getInstance();
      _indent << cfg[","] << ' ';
      exprs->accept(*this);
    }
  }

  /*!
  ** Print the instruction node
  **
  ** @param node The instruction node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeAffect* affect = node->getAffect();
    const AST::NodeCallFunc* callFunc = node->getCallFunc();
    const AST::NodeCompoundInstr* compoundInstr = node->getCompoundInstr();
    const AST::NodeIf* nIf = node->getIf();
    const AST::NodeWhile* nWhile = node->getWhile();
    const AST::NodeReturn* nReturn = node->getReturn();
    const AST::NodeExit* nExit = node->getExit();
    const AST::NodePrint* nPrint = node->getPrint();
    const AST::NodeRead* nRead = node->getRead();
    unsigned int nb = 0;

    nb += affect ? 1 : 0;
    nb += callFunc ? 1 : 0;
    nb += compoundInstr ? 1 : 0;
    nb += nIf ? 1 : 0;
    nb += nWhile ? 1 : 0;
    nb += nReturn ? 1 : 0;
    nb += nExit ? 1 : 0;
    nb += nPrint ? 1 : 0;
    nb += nRead ? 1 : 0;
    assert(nb == 1);

    if (compoundInstr)
    {
      compoundInstr->accept(*this);
      return;
    }

    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    if (affect)
    {
      affect->accept(*this);
      _indent << cfg[";"] << '\n';
    }
    else
      if (callFunc)
      {
	callFunc->accept(*this);
	_indent << cfg[";"] << '\n';
      }
      else
	if (nIf)
	  nIf->accept(*this);
	else
	  if (nWhile)
	    nWhile->accept(*this);
	  else
	    if (nReturn)
	    {
	      nReturn->accept(*this);
	      _indent << cfg[";"] << '\n';
	    }
	    else
	      if (nExit)
	      {
		nExit->accept(*this);
		_indent << cfg[";"] << '\n';
	      }
	      else
		if (nPrint)
		{
		  nPrint->accept(*this);
		  _indent << cfg[";"] << '\n';
		}
		else
		  if (nRead)
		  {
		    nRead->accept(*this);
		    _indent << cfg[";"] << '\n';
		  }
  }

  /*!
  ** Print the compound instruction node
  **
  ** @param node The compound instruction node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeInstrs* instrs = node->getInstrs();

    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["begin"] << '\n';
    _tab += INDENT_SIZE;
    if (instrs)
      instrs->accept(*this);
    _tab -= INDENT_SIZE;
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["end"] << '\n';
  }

  /*!
  ** Print the factor node
  **
  ** @param node The factor node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expression = node->getExpression();
    if (expression)
    {
      _indent << cfg["("];
      expression->accept(*this);
      _indent << cfg[")"];
    }
    else
      ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the instructions node
  **
  ** @param node The instructions node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the type node
  **
  ** @param node The ids node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    _indent << node->getType();
  }

  /*!
  ** Print the function node
  **
  ** @param node The function node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
    _indent << '\n';
  }

  /*!
  ** Print the while node
  **
  ** @param node The while node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);

    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["while"] << ' ';
    cond->accept(*this);
    _indent << ' ' << cfg["do"] << '\n';
    body->accept(*this);
  }

  /*!
  ** Print the declaration body node
  **
  ** @param node The declaration body node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIds* ids = node->getIds();
    const AST::NodeType* type = node->getType();
    assert(ids);
    assert(type);

    ids->accept(*this);
    _indent << ' ' << cfg[":"] << ' ';
    type->accept(*this);
  }

  /*!
  ** Print the functions node
  **
  ** @param node The functions node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the number node
  **
  ** @param node The number node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    _indent << node->getNumber();
  }

  /*!
  ** Print the declaration node
  **
  ** @param node The declaration node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeDeclarationBody* body = node->getBody();
    assert(body);
    _indent << cfg["var"] << ' ';
    body->accept(*this);
    _indent << cfg[";"] << '\n';
  }

  /*!
  ** Print the function header node
  **
  ** @param node The function header node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    const AST::NodeType* type = node->getType();

    assert(id);
    assert(type);
    _indent << cfg["function"] << ' ';
    id->accept(*this);
    _indent << cfg["("];
    if (args)
      args->accept(*this);
    _indent << cfg[")"] << ' ' << cfg[":"] << ' ';
    type->accept(*this);
    _indent << cfg[";"] << '\n';
  }

  /*!
  ** Print the declaration node
  **
  ** @param node The declaration node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the id node
  **
  ** @param node The id node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    assert(node->getId() != "");
    _indent << node->getId();
  }

  /*!
  ** Print the function id node
  **
  ** @param node The function id node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    assert(node->getId() != "");
    _indent << node->getId();
  }

  /*!
  ** Print the print node
  **
  ** @param node The print node
  */
  void
  PrettyPrinterVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* id = node->getExpr();
    assert(id);

    _indent << cfg["print"] << cfg["("];
    id->accept(*this);
    _indent << cfg[")"];
  }

  /*!
  ** Print the buffered text in the choosen stream.
  **
  ** @param o The stream
  */
  void
  PrettyPrinterVisitor::print(std::ostream& o) const
  {
    o << _indent.str();
  }

  /*!
  ** Print the buffered text of the given Pretty Printer in the choosen stream.
  **
  ** @param o The stream
  ** @param v The pretty printer
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const PrettyPrinterVisitor& v)
  {
    v.print(o);
    return o;
  }
}
