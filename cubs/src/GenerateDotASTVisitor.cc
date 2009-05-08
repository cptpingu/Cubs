#include <cassert>
#include "GenerateDotASTVisitor.hh"
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
  ** Construct the generate dot AST visitor,
  ** initializing tabulation.
  */
  GenerateDotASTVisitor::GenerateDotASTVisitor()
  {
  }

  /*!
  ** Destruct the visitor.
  */
  GenerateDotASTVisitor::~GenerateDotASTVisitor()
  {
  }

  /*!
  ** Print the ids node
  **
  ** @param node The ids node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeIds* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::IDS + Utils::intToString(i);
    declareNode(name, NodeName::IDS);
    linkNode(name, _rootName);

    const AST::NodeIds* ids = node->getIds();
    const AST::NodeId* id = node->getId();
    assert(id);
    _rootName = name;
    id->accept(*this);
    if (ids)
    {
      _rootName = name;
      ids->accept(*this);
    }
  }

  /*!
  ** Print the program node
  **
  ** @param node The program node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    _indent << "digraph G\n{\n" << NodeName::PROGRAM <<
      " [label=\"" << NodeName::PROGRAM << "\"," <<
      NodeName::Option::DEFAULT <<"];\n";

    const AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
    {
      _rootName = NodeName::PROGRAM;
      decls->accept(*this);
    }

    const AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
    {
      _rootName = NodeName::PROGRAM;
      funcs->accept(*this);
    }

    const AST::NodeCompoundInstr* instrs = node->getInstrs();
    if (instrs)
    {
      _rootName = NodeName::PROGRAM;
      instrs->accept(*this);
    }
    _indent << "\n}\n";
  }

  /*!
  ** Print the affectation node
  **
  ** @param node The affectation node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::AFFECT + Utils::intToString(i);
    declareNode(name, NodeName::AFFECT);
    linkNode(name, _rootName);

    const AST::NodeId* id = node->getId();
    const AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);
    _rootName = name;
    id->accept(*this);
    _rootName = name;
    expr->accept(*this);
  }

  /*!
  ** Print the if node
  **
  ** @param node The if node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::IF + Utils::intToString(i);
    declareNode(name, NodeName::IF);
    linkNode(name, _rootName);

    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    const AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    _rootName = name;
    cond->accept(*this);
    _rootName = name;
    body->accept(*this);
    if (elseExprs)
    {
      _rootName = name;
      elseExprs->accept(*this);
    }
  }

  /*!
  ** Print the read node
  **
  ** @param node The read node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::READ + Utils::intToString(i);
    declareNode(name, NodeName::READ);
    linkNode(name, _rootName);

    const AST::NodeId* id = node->getId();
    assert(id);

    _rootName = name;
    id->accept(*this);
  }

  /*!
  ** Print the argument node
  **
  ** @param node The argument node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::ARGUMENT + Utils::intToString(i);
    declareNode(name, NodeName::ARGUMENT);
    linkNode(name, _rootName);

    const AST::NodeDeclarationBody* body = node->getDeclarationBody();
    const AST::NodeArguments* args = node->getArguments();

    assert(body);
    _rootName = name;
    body->accept(*this);
    if (args)
    {
      _rootName = name;
      args->accept(*this);
    }
  }

  /*!
  ** Print the arguments node
  **
  ** @param node The arguments node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::ARGUMENTS + Utils::intToString(i);
    declareNode(name, NodeName::ARGUMENTS);
    linkNode(name, _rootName);

    const AST::NodeArgument* arg = node->getArgument();
    const AST::NodeArguments* args = node->getArguments();
    assert(arg);
    _rootName = name;
    arg->accept(*this);
    if (args)
    {
      _rootName = name;
      args->accept(*this);
    }
  }

  /*!
  ** Print the return node
  **
  ** @param node The return node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::RETURN + Utils::intToString(i);
    declareNode(name, NodeName::RETURN);
    linkNode(name, _rootName);

    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _rootName = name;
    expr->accept(*this);
  }

  /*!
  ** Print the exit node
  **
  ** @param node The exit node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::EXIT + Utils::intToString(i);
    declareNode(name, NodeName::EXIT);
    linkNode(name, _rootName);

    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _rootName = name;
    expr->accept(*this);
  }

  /*!
  ** Print the function call node
  **
  ** @param node The function call node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::CALLFUNC + Utils::intToString(i);
    declareNode(name, NodeName::CALLFUNC);
    linkNode(name, _rootName);

    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(id);

    _rootName = name;
    id->accept(*this);
    if (exprs)
    {
      _rootName = name;
      exprs->accept(*this);
    }
  }

  /*!
  ** Print the operation node
  **
  ** @param node The operation node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::OPERATION + Utils::intToString(i);
    if (node->getOpType() != AST::Operator::NONE)
      declareNode(name, Utils::OpToString(node->getOpType()), NodeName::Option::OPERATION);
    else
      declareNode(name, "NONE", NodeName::Option::OPERATION_EMPTY);
    linkNode(name, _rootName);

    const AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);

    _rootName = name;
    leftFactor->accept(*this);
    if (node->getOpType() != AST::Operator::NONE)
    {
      const AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      _rootName = name;
      rightFactor->accept(*this);
    }
  }

  /*!
  ** Print the expression node
  **
  ** @param node The expression node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::EXPRESSION + Utils::intToString(i);
    declareNode(name, NodeName::EXPRESSION);
    linkNode(name, _rootName);

    _rootName = name;
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the string expression node
  **
  ** @param node The string expression node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::STRINGEXPR + Utils::intToString(i);
    declareNode(name, node->getString(), NodeName::Option::STRINGEXPR);
    linkNode(name, _rootName);
  }

  /*!
  ** Print the boolean node
  **
  ** @param node The boolean node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::BOOLEAN + Utils::intToString(i);
    declareNode(name, Utils::boolToString(node->getBool()), NodeName::Option::BOOLEAN);
    linkNode(name, _rootName);
  }

  /*!
  ** Print the expressions node
  **
  ** @param node The expressions node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::EXPRESSIONS + Utils::intToString(i);
    declareNode(name, NodeName::EXPRESSIONS);
    linkNode(name, _rootName);

    const AST::NodeExpression* expr = node->getExpr();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(expr);

    _rootName = name;
    expr->accept(*this);
    if (exprs)
    {
      _rootName = name;
      exprs->accept(*this);
    }
  }

  /*!
  ** Print the instruction node
  **
  ** @param node The instruction node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::INSTR + Utils::intToString(i);
    declareNode(name, NodeName::INSTR);
    linkNode(name, _rootName);

    _rootName = name;
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the compound instruction node
  **
  ** @param node The compound instruction node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::COMPOUNDINSTR + Utils::intToString(i);
    declareNode(name, NodeName::COMPOUNDINSTR);
    linkNode(name, _rootName);

    const AST::NodeInstrs* instrs = node->getInstrs();
    if (instrs)
    {
      _rootName = name;
      instrs->accept(*this);
    }
  }

  /*!
  ** Print the factor node
  **
  ** @param node The factor node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::FACTOR + Utils::intToString(i);
    declareNode(name, NodeName::FACTOR);
    linkNode(name, _rootName);

    _rootName = name;
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Print the instructions node
  **
  ** @param node The instructions node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::INSTRS + Utils::intToString(i);
    declareNode(name, NodeName::INSTRS);
    linkNode(name, _rootName);

    const AST::NodeInstrs* instrs = node->getInstrs();
    const AST::NodeInstr* instr = node->getInstr();
    assert(instr);

    _rootName = name;
    instr->accept(*this);
    if (instrs)
    {
      _rootName = name;
      instrs->accept(*this);
    }
  }

  /*!
  ** Print the type node
  **
  ** @param node The ids node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::TYPE + Utils::intToString(i);
    declareNode(name, node->getType());
    linkNode(name, _rootName);
  }

  /*!
  ** Print the function node
  **
  ** @param node The function node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::FUNCTION + Utils::intToString(i);
    declareNode(name, NodeName::FUNCTION);
    linkNode(name, _rootName);

    AST::NodeHeaderFunc* header = node->getHeaderFunc();
    AST::NodeDeclarations* decls = node->getDeclarations();
    AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    _rootName = name;
    header->accept(*this);
    if (decls)
    {
      _rootName = name;
      decls->accept(*this);
    }
    _rootName = name;
    instr->accept(*this);
  }

  /*!
  ** Print the while node
  **
  ** @param node The while node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::WHILE + Utils::intToString(i);
    declareNode(name, NodeName::WHILE);
    linkNode(name, _rootName);

    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);

    _rootName = name;
    cond->accept(*this);
    _rootName = name;
    body->accept(*this);
  }

  /*!
  ** Print the declaration body node
  **
  ** @param node The declaration body node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::DECLARATIONBODY + Utils::intToString(i);
    declareNode(name, NodeName::DECLARATIONBODY);
    linkNode(name, _rootName);

    const AST::NodeIds* ids = node->getIds();
    const AST::NodeType* type = node->getType();
    assert(ids);
    assert(type);

    _rootName = name;
    ids->accept(*this);
    _rootName = name;
    type->accept(*this);
  }

  /*!
  ** Print the functions node
  **
  ** @param node The functions node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::FUNCTIONS + Utils::intToString(i);
    declareNode(name, NodeName::FUNCTIONS);
    linkNode(name, _rootName);

    AST::NodeFunction* func = node->getFunc();
    AST::NodeFunctions* funcs = node->getFuncs();
    assert(func);
    _rootName = name;
    func->accept(*this);
    if (funcs)
    {
      _rootName = name;
      funcs->accept(*this);
    }
  }

  /*!
  ** Print the number node
  **
  ** @param node The number node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::NUMBER + Utils::intToString(i);
    declareNode(name, Utils::intToString(node->getNumber()), NodeName::Option::NUMBER);
    linkNode(name, _rootName);
  }

  /*!
  ** Print the declaration node
  **
  ** @param node The declaration node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::DECLARATION + Utils::intToString(i);
    declareNode(name, NodeName::DECLARATION);
    linkNode(name, _rootName);

    const AST::NodeDeclarationBody* body = node->getBody();
    assert(body);
    _rootName = name;
    body->accept(*this);
  }

  /*!
  ** Print the function header node
  **
  ** @param node The function header node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::HEADERFUNC + Utils::intToString(i);
    declareNode(name, NodeName::HEADERFUNC);
    linkNode(name, _rootName);

    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    const AST::NodeType* type = node->getType();
    assert(id);
    assert(type);

    _rootName = name;
    id->accept(*this);
    if (args)
    {
      _rootName = name;
      args->accept(*this);
    }
    _rootName = name;
    type->accept(*this);
  }

  /*!
  ** Print the declaration node
  **
  ** @param node The declaration node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::DECLARATIONS + Utils::intToString(i);
    declareNode(name, NodeName::DECLARATIONS);
    linkNode(name, _rootName);

    AST::NodeDeclaration* decl = node->getDeclaration();
    assert(decl);
    _rootName = name;
    decl->accept(*this);
    AST::NodeDeclarations* decls = node->getDeclarations();
    _rootName = name;
    if (decls)
      decls->accept(*this);
  }

  /*!
  ** Print the id node
  **
  ** @param node The id node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::ID + Utils::intToString(i);
    assert(node->getId() != "");
    declareNode(name, node->getId(), NodeName::Option::ID);
    linkNode(name, _rootName);
  }

  /*!
  ** Print the function id node
  **
  ** @param node The function id node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::IDFUNC + Utils::intToString(i);
    assert(node->getId() != "");
    declareNode(name, node->getId(), NodeName::Option::IDFUNC);
    linkNode(name, _rootName);
  }

  /*!
  ** Print the print node
  **
  ** @param node The print node
  */
  void
  GenerateDotASTVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    static unsigned int i = 0;
    i++;
    const std::string name = NodeName::PRINT + Utils::intToString(i);
    declareNode(name, NodeName::PRINT);
    linkNode(name, _rootName);

    const AST::NodeExpression* id = node->getExpr();
    assert(id);
    _rootName = name;
    id->accept(*this);
  }

  /*!
  ** Print the buffered text in the choosen stream.
  **
  ** @param o The stream
  */
  void
  GenerateDotASTVisitor::print(std::ostream& o) const
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
  operator<<(std::ostream& o, const GenerateDotASTVisitor& v)
  {
    v.print(o);
    return o;
  }
}
