#include <cassert>
#include "ConvertToCppVisitor.hh"
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
  ** Construct the cpp convertor visitor,
  ** initializing tabulation.
  */
  ConvertToCppVisitor::ConvertToCppVisitor()
  {
    _tab = 0;
  }

  /*!
  ** Destruct the visitor.
  */
  ConvertToCppVisitor::~ConvertToCppVisitor()
  {
  }

  /*!
  ** This function is used to get all function prototypes.
  **
  ** @param node The functions node
  */
  void
  ConvertToCppVisitor::visitFuncHeader(const AST::NodeFunctions* node)
  {
    assert(node);
    const AST::NodeFunction* func = node->getFunc();
    assert(func);
    const AST::NodeHeaderFunc* header = func->getHeaderFunc();
    assert(header);

    _indent << Utils::stringFill(SPACING_CHAR, _tab);

    // Get the return type
    const AST::NodeType* retType = header->getType();
    assert(retType);
    retType->accept(*this);
    _indent << ' ';

    // Get the function id
    const AST::NodeIdFunc* id = header->getId();
    assert(id);
    id->accept(*this);
    _indent << '(';

    // Get all arguments of this function
    const AST::NodeArguments* args = header->getArguments();
    if (args)
      args->accept(*this);
    _indent << ");\n";

    // Go to the next function declaration
    const AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
      visitFuncHeader(funcs);
  }

  /*!
  ** Convert the ids node
  **
  ** @param node The ids node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeIds*)
  {
    // Nothing to do here, because we have done it
    // in declaration body
    assert(false);
  }

  /*!
  ** Convert the program node
  **
  ** @param node The program node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "#include <iostream>\n\n";
    const AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
      decls->accept(*this);
    _indent << '\n';
    const AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
    {
      visitFuncHeader(funcs);
      _indent << '\n';
      funcs->accept(*this);
    }
    _indent << '\n';
    const AST::NodeCompoundInstr* instrs = node->getInstrs();
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "int main()\n" ;
    if (instrs)
      instrs->accept(*this);
  }

  /*!
  ** Convert the affectation node
  **
  ** @param node The affectation node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    const AST::NodeId* id = node->getId();
    const AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);
    id->accept(*this);
    _indent << " = ";
    expr->accept(*this);
  }

  /*!
  ** Convert the if node
  **
  ** @param node The if node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    const AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    _indent << "if (";
    cond->accept(*this);
    _indent << ")\n";
    body->accept(*this);
    if (elseExprs)
    {
      _indent << Utils::stringFill(SPACING_CHAR, _tab) << "else\n";
      elseExprs->accept(*this);
    }
  }

  /*!
  ** Convert the read node
  **
  ** @param node The read node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    const AST::NodeId* id = node->getId();
    assert(id);

    _indent << "std::cin >> ";
    id->accept(*this);
  }

  /*!
  ** Convert the argument node
  **
  ** @param node The argument node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    const AST::NodeDeclarationBody* body = node->getDeclarationBody();
    assert(body);

    body->accept(*this);
  }

  /*!
  ** Convert the arguments node
  **
  ** @param node The arguments node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    const AST::NodeArgument* arg = node->getArgument();
    assert(arg);
    const AST::NodeArguments* args = node->getArguments();

    arg->accept(*this);
    if (args)
    {
      _indent << ", ";
      args->accept(*this);
    }
  }

  /*!
  ** Convert the return node
  **
  ** @param node The return node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << "return ";
    expr->accept(*this);
  }

  /*!
  ** Convert the exit node
  **
  ** @param node The exit node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << "exit(";
    expr->accept(*this);
    _indent << ')';
  }

  /*!
  ** Convert the function call node
  **
  ** @param node The function call node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(id);

    id->accept(*this);
    _indent << '(';
    if (exprs)
      exprs->accept(*this);
    _indent << ')';
  }

  /*!
  ** Convert the operation node
  **
  ** @param node The operation node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Convert the expression node
  **
  ** @param node The expression node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Convert the string expression node
  **
  ** @param node The string expression node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    _indent << "std::string(\"";
    _indent << node->getString();
    _indent << "\")";
  }

  /*!
  ** Convert the boolean node
  **
  ** @param node The boolean node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    _indent << (node->getBool() ? "true" : "false");
  }

  /*!
  ** Convert the expressions node
  **
  ** @param node The expressions node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(expr);

    expr->accept(*this);
    if (exprs)
    {
      _indent <<", ";
      exprs->accept(*this);
    }
  }

  /*!
  ** Convert the instruction node
  **
  ** @param node The instruction node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
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
      _indent << ";\n";
    }
    else
      if (callFunc)
      {
	callFunc->accept(*this);
	_indent << ";\n";
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
	      _indent << ";\n";
	    }
	    else
	      if (nExit)
	      {
		nExit->accept(*this);
		_indent << ";\n";
	      }
	      else
		if (nPrint)
		{
		  nPrint->accept(*this);
		  _indent << ";\n";
		}
		else
		  if (nRead)
		  {
		    nRead->accept(*this);
		    _indent << ";\n";
		  }
  }

  /*!
  ** Convert the compound instruction node
  **
  ** @param node The compound instruction node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    const AST::NodeInstrs* instrs = node->getInstrs();

    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "{\n";
    _tab += INDENT_SIZE;
    if (instrs)
      instrs->accept(*this);
    _tab -= INDENT_SIZE;
    _indent << Utils::stringFill(SPACING_CHAR, _tab) <<  "}\n";
  }

  /*!
  ** Convert the factor node
  **
  ** @param node The factor node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    const AST::NodeExpression* expression = node->getExpression();
    if (expression)
    {
      _indent << '(';
      expression->accept(*this);
      _indent << ')';
    }
    else
      ConstBaseVisitor::visit(node);
  }

  /*!
  ** Convert the instructions node
  **
  ** @param node The instructions node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Convert the type node
  **
  ** @param node The ids node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    if (node->getType() == cfg["int"])
      _indent << "int";
    else
      if (node->getType() == cfg["bool"])
	_indent << "bool";
      else
	if (node->getType() == cfg["string"])
	  _indent << "std::string";
	else
	  assert(false);
  }

  /*!
  ** Convert the function node
  **
  ** @param node The function node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    AST::NodeHeaderFunc* header = node->getHeaderFunc();
    AST::NodeDeclarations* decls = node->getDeclarations();
    AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    header->accept(*this);
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "{\n";
    _tab += INDENT_SIZE;
    if (decls)
      decls->accept(*this);
    AST::NodeInstrs* instrs = instr->getInstrs();
    if (instrs)
      instrs->accept(*this);
    _tab -= INDENT_SIZE;
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "}\n";
  }

  /*!
  ** Convert the while node
  **
  ** @param node The while node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);

    _indent << "while (";
    cond->accept(*this);
    _indent << ")\n";
    body->accept(*this);
  }

  /*!
  ** Convert the declaration body node
  **
  ** @param node The declaration body node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    const AST::NodeIds* ids = node->getIds();
    const AST::NodeType* type = node->getType();
    assert(ids);
    assert(type);

    const AST::NodeId* id = 0;
    while (ids)
    {
      type->accept(*this);
      _indent << ' ';
      id = ids->getId();
      assert(id);
      id->accept(*this);
      ids = ids->getIds();
      if (ids)
	_indent << ", ";
    }
  }

  /*!
  ** Convert the functions node
  **
  ** @param node The functions node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Convert the number node
  **
  ** @param node The number node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Convert the declaration node
  **
  ** @param node The declaration node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    const AST::NodeDeclarationBody* body = node->getBody();
    assert(body);
    const AST::NodeIds* ids = body->getIds();
    assert(ids);
    const AST::NodeType* type = body->getType();
    assert(type);

    const AST::NodeId* id = 0;
    while (ids)
    {
      _indent << Utils::stringFill(SPACING_CHAR, _tab);
      type->accept(*this);
      _indent << ' ';
      id = ids->getId();
      assert(id);
      id->accept(*this);
      ids = ids->getIds();
      _indent << ";\n";
    }

  }

  /*!
  ** Convert the function header node
  **
  ** @param node The function header node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    const AST::NodeType* type = node->getType();
    assert(id);
    assert(type);

    type->accept(*this);
    _indent << ' ';
    id->accept(*this);
    _indent << '(';
    if (args)
      args->accept(*this);
    _indent << ")\n";
  }

  /*!
  ** Convert the declaration node
  **
  ** @param node The declaration node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Convert the id node
  **
  ** @param node The id node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Convert the function id node
  **
  ** @param node The function id node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Convert the print node
  **
  ** @param node The print node
  */
  void
  ConvertToCppVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    const AST::NodeExpression* id = node->getExpr();
    assert(id);

    _indent << "std::cout << ";
    id->accept(*this);
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
  operator<<(std::ostream& o, const ConvertToCppVisitor& v)
  {
    v.print(o);
    return o;
  }
}
