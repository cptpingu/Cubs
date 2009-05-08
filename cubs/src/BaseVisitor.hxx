#include <cassert>
#include "BaseVisitor.hh"
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
#include "NodePrint.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the base visitor.
  */
  template <template <typename T> class ConstifyTrait>
  BaseVisitor<ConstifyTrait>::BaseVisitor()
  {
  }

  /*!
  ** Destruct the base visitor.
  */
  template <template <typename T> class ConstifyTrait>
  BaseVisitor<ConstifyTrait>::~BaseVisitor()
  {
  }

  /*!
  ** Visit an ids node.
  **
  ** @param node The ids node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeIds>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeIds>::ptr ids = node->getIds();
    typename ConstifyTrait<AST::NodeId>::ptr id = node->getId();
    assert(id);
    id->accept(*this);
    if (ids)
      ids->accept(*this);
  }

  /*!
  ** Visit a program node.
  **
  ** @param node The program node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeProgram>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeDeclarations>::ptr decls = node->getDecls();
    if (decls)
      decls->accept(*this);
    typename ConstifyTrait<AST::NodeFunctions>::ptr funcs = node->getFuncs();
    if (funcs)
      funcs->accept(*this);
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr instrs = node->getInstrs();
    if (instrs)
      instrs->accept(*this);
  }

  /*!
  ** Visit an affect node.
  **
  ** @param node The affect node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeAffect>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeId>::ptr id = node->getId();
    typename ConstifyTrait<AST::NodeExpression>::ptr expr = node->getExpr();
    assert(id);
    assert(expr);
    id->accept(*this);
    expr->accept(*this);
  }

  /*!
  ** Visit a if node.
  **
  ** @param node The if node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeIf>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr cond = node->getCond();
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr body = node->getBodyExprs();
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    cond->accept(*this);
    body->accept(*this);
    if (elseExprs)
      elseExprs->accept(*this);
  }

  /*!
  ** Visit a read node.
  **
  ** @param node The read node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeRead>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeId>::ptr id = node->getId();
    assert(id);

    id->accept(*this);
  }

  /*!
  ** Visit an argument node.
  **
  ** @param node The argument node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeArgument>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeDeclarationBody>::ptr body = node->getDeclarationBody();
    typename ConstifyTrait<AST::NodeArguments>::ptr args = node->getArguments();

    assert(body);
    body->accept(*this);
    if (args)
      args->accept(*this);
  }

  /*!
  ** Visit an arguments node.
  **
  ** @param node The arguments node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeArguments>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeArgument>::ptr arg = node->getArgument();
    typename ConstifyTrait<AST::NodeArguments>::ptr args = node->getArguments();

    assert(arg);
    arg->accept(*this);
    if (args)
      args->accept(*this);
  }

  /*!
  ** Visit a return node.
  **
  ** @param node The return node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeReturn>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr expr = node->getExpr();
    assert(expr);

    expr->accept(*this);
  }

  /*!
  ** Visit an exit node.
  **
  ** @param node The exit node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeExit>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr expr = node->getExpr();
    assert(expr);

    expr->accept(*this);
  }

  /*!
  ** Visit a function call node.
  **
  ** @param node The function call node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeCallFunc>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeIdFunc>::ptr id = node->getId();
    typename ConstifyTrait<AST::NodeExpressions>::ptr exprs = node->getExprs();
    assert(id);

    id->accept(*this);
    if (exprs)
      exprs->accept(*this);
  }

  /*!
  ** Visit an operation node.
  **
  ** @param node The operation node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeOperation>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeFactor>::ptr leftFactor = node->getLeftFactor();
    assert(leftFactor);

    leftFactor->accept(*this);
    if (node->getOpType() != AST::Operator::NONE)
    {
      typename ConstifyTrait<AST::NodeFactor>::ptr rightFactor = node->getRightFactor();
      assert(rightFactor);
      rightFactor->accept(*this);
    }
  }

  /*!
  ** Visit an expression node.
  **
  ** @param node The expression node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeExpression>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeOperation>::ptr op = node->getOperation();
    assert(op);
    op->accept(*this);
  }

  /*!
  ** Visit a string expression node.
  **
  ** @param node The string expression node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeStringExpr>::ptr)
  {
  }

  /*!
  ** Visit a boolean node.
  **
  ** @param node The boolean node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeBoolean>::ptr)
  {
  }

  /*!
  ** Visit an expressions node.
  **
  ** @param node The expressions node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeExpressions>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr expr = node->getExpr();
    typename ConstifyTrait<AST::NodeExpressions>::ptr exprs = node->getExprs();
    assert(expr);

    expr->accept(*this);
    if (exprs)
      exprs->accept(*this);
  }

  /*!
  ** Visit an instruction node.
  **
  ** @param node The instruction node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeInstr>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeAffect>::ptr affect = node->getAffect();
    typename ConstifyTrait<AST::NodeCallFunc>::ptr callFunc = node->getCallFunc();
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr compoundInstr = node->getCompoundInstr();
    typename ConstifyTrait<AST::NodeIf>::ptr nIf = node->getIf();
    typename ConstifyTrait<AST::NodeWhile>::ptr nWhile = node->getWhile();
    typename ConstifyTrait<AST::NodeReturn>::ptr nReturn = node->getReturn();
    typename ConstifyTrait<AST::NodeExit>::ptr nExit = node->getExit();
    typename ConstifyTrait<AST::NodePrint>::ptr nPrint = node->getPrint();
    typename ConstifyTrait<AST::NodeRead>::ptr nRead = node->getRead();
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

    if (affect)
      affect->accept(*this);
    else
      if (callFunc)
	callFunc->accept(*this);
      else
	if (compoundInstr)
	  compoundInstr->accept(*this);
	else
	  if (nIf)
	    nIf->accept(*this);
	  else
	    if (nWhile)
	      nWhile->accept(*this);
	    else
	      if (nReturn)
		nReturn->accept(*this);
	      else
		if (nExit)
		  nExit->accept(*this);
		else
		  if (nPrint)
		    nPrint->accept(*this);
		  else
		    if (nRead)
		      nRead->accept(*this);
  }

  /*!
  ** Visit a compound instruction node.
  **
  ** @param node The compound instruction node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeCompoundInstr>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeInstrs>::ptr instrs = node->getInstrs();
    if (instrs)
      instrs->accept(*this);
  }

  /*!
  ** Visit a factor node.
  **
  ** @param node The factor node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeFactor>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeId>::ptr id = node->getId();
    typename ConstifyTrait<AST::NodeCallFunc>::ptr callFunc = node->getCallFunc();
    typename ConstifyTrait<AST::NodeNumber>::ptr number = node->getNumber();
    typename ConstifyTrait<AST::NodeStringExpr>::ptr stringExpr = node->getStringExpr();
    typename ConstifyTrait<AST::NodeBoolean>::ptr boolExpr = node->getBool();
    typename ConstifyTrait<AST::NodeExpression>::ptr expression = node->getExpression();
    unsigned int nb = 0;

    nb += id ? 1 : 0;
    nb += callFunc ? 1 : 0;
    nb += number ? 1 : 0;
    nb += stringExpr ? 1 : 0;
    nb += boolExpr ? 1 : 0;
    nb += expression ? 1 : 0;
    assert(nb == 1);

    if (id)
      id->accept(*this);
    else if (callFunc)
      callFunc->accept(*this);
    else if (number)
      number->accept(*this);
    else if (stringExpr)
      stringExpr->accept(*this);
    else if (boolExpr)
      boolExpr->accept(*this);
    else if (expression)
      expression->accept(*this);
  }

  /*!
  ** Visit an instructions node.
  **
  ** @param node The instructions node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeInstrs>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeInstrs>::ptr instrs = node->getInstrs();
    typename ConstifyTrait<AST::NodeInstr>::ptr instr = node->getInstr();
    assert(instr);

    instr->accept(*this);
    if (instrs)
      instrs->accept(*this);
  }

  /*!
  ** Visit an type node.
  **
  ** @param node The type node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeType>::ptr)
  {
  }

  /*!
  ** Visit a function node.
  **
  ** @param node The function node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeFunction>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeHeaderFunc>::ptr header = node->getHeaderFunc();
    typename ConstifyTrait<AST::NodeDeclarations>::ptr decls = node->getDeclarations();
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    header->accept(*this);
    if (decls)
      decls->accept(*this);
    instr->accept(*this);
  }

  /*!
  ** Visit an while node.
  **
  ** @param node The while node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeWhile>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr cond = node->getCond();
    typename ConstifyTrait<AST::NodeCompoundInstr>::ptr body = node->getBodyExprs();
    assert(cond);
    assert(body);

    cond->accept(*this);
    body->accept(*this);
  }

  /*!
  ** Visit an declaration body node.
  **
  ** @param node The ids node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeDeclarationBody>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeIds>::ptr ids = node->getIds();
    typename ConstifyTrait<AST::NodeType>::ptr type = node->getType();
    assert(ids);
    assert(type);

    ids->accept(*this);
    type->accept(*this);
  }

  /*!
  ** Visit a functions node.
  **
  ** @param node The functions node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeFunctions>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeFunction>::ptr func = node->getFunc();
    typename ConstifyTrait<AST::NodeFunctions>::ptr funcs = node->getFuncs();
    assert(func);
    func->accept(*this);
    if (funcs)
      funcs->accept(*this);
  }

  /*!
  ** Visit a number node.
  **
  ** @param node The number node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeNumber>::ptr)
  {
  }

  /*!
  ** Visit a declaration node.
  **
  ** @param node The declaration node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeDeclaration>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeDeclarationBody>::ptr body = node->getBody();
    assert(body);
    body->accept(*this);
  }

  /*!
  ** Visit a header function node.
  **
  ** @param node The header function node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeHeaderFunc>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeIdFunc>::ptr id = node->getId();
    typename ConstifyTrait<AST::NodeArguments>::ptr args = node->getArguments();
    typename ConstifyTrait<AST::NodeType>::ptr type = node->getType();

    assert(id);
    assert(type);
    id->accept(*this);
    if (args)
      args->accept(*this);
    type->accept(*this);
  }

  /*!
  ** Visit a declarations node.
  **
  ** @param node The declarations node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeDeclarations>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeDeclaration>::ptr decl = node->getDeclaration();
    assert(decl);
    decl->accept(*this);
    typename ConstifyTrait<AST::NodeDeclarations>::ptr decls = node->getDeclarations();
    if (decls)
      decls->accept(*this);
  }

  /*!
  ** Visit an id node.
  **
  ** @param node The id node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeId>::ptr)
  {
  }

  /*!
  ** Visit a function id node.
  **
  ** @param node The function id node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodeIdFunc>::ptr)
  {
  }

  /*!
  ** Visit a print node.
  **
  ** @param node The print node
  */
  template <template <typename T> class ConstifyTrait>
  void
  BaseVisitor<ConstifyTrait>::visit(typename ConstifyTrait<AST::NodePrint>::ptr node)
  {
    assert(node);
    typename ConstifyTrait<AST::NodeExpression>::ptr id = node->getExpr();
    assert(id);
    id->accept(*this);
  }
}
