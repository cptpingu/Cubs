#include <cassert>
#include "TypeCheckingPrinterVisitor.hh"
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
  ** Construct the type checking visitor.
  */
  TypeCheckingPrinterVisitor::TypeCheckingPrinterVisitor()
  {
  }

  /*!
  ** Destruct the type checking visitor.
  */
  TypeCheckingPrinterVisitor::~TypeCheckingPrinterVisitor()
  {
  }

  /*!
  ** Print the type near a function node.
  **
  ** @param node The function node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    const AST::NodeHeaderFunc* header = node->getHeaderFunc();
    const AST::NodeDeclarations* decls = node->getDeclarations();
    const AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    Configuration& cfg = Configuration::getInstance();
    _indent << cfg["function"] << '\n';
    _indent << Utils::stringFill(SPACING_CHAR, _tab + INDENT_SIZE) << "/*\n";
    for (unsigned int i = 0; i < node->nbArgument(); ++i)
      _indent << Utils::stringFill(SPACING_CHAR, _tab + INDENT_SIZE) << "** "
	      << Utils::typeToString(node->getArgument(i)->getComputedType())
	      << "\n";
    _indent << Utils::stringFill(SPACING_CHAR, _tab + INDENT_SIZE) << "*/\n";
    header->accept(*this);
    if (decls)
      decls->accept(*this);
    instr->accept(*this);
    _indent << '\n';
  }

  /*!
  ** Print the type near a header function node.
  **
  ** @param node The header function node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    const AST::NodeType* type = node->getType();

    assert(id);
    assert(type);
    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    id->accept(*this);
    _indent << cfg["("];
    if (args)
      args->accept(*this);
    _indent << cfg[")"] << ' ' << cfg[":"] << ' ';
    type->accept(*this);
    _indent << cfg[";"] << '\n';
  }

  /*!
  ** Print the type near a id node.
  **
  ** @param node The id node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Print the type near a function id node.
  **
  ** @param node The function id node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Print the type near a return node.
  **
  ** @param node The return node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["return"] << " <" <<
      Utils::typeToString(node->getComputedType()) << "> ";
    expr->accept(*this);
  }

  /*!
  ** Print the type near an exit node.
  **
  ** @param node The exit node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["exit"] << " <" <<
      Utils::typeToString(node->getComputedType()) << "> ";
    expr->accept(*this);
  }

  /*!
  ** Print the type near a number node.
  **
  ** @param node The number node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Print the type near a operation node.
  **
  ** @param node The operation node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);

    if (node->getOpType() != AST::Operator::NONE)
      _indent << cfg["("];
    leftFactor->accept(*this);
    if (node->getOpType() != AST::Operator::NONE)
    {
      const AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      _indent << ' ' << Utils::OpToString(node->getOpType()) << ' ';
      rightFactor->accept(*this);
      _indent << cfg[")"];
      _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
    }
  }

  /*!
  ** Print the type near a string expression node.
  **
  ** @param node The string expression node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Print the type near a boolean node.
  **
  ** @param node The boolean node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Print the type near a factor node.
  **
  ** @param node The factor node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expression = node->getExpression();
    _indent << cfg["("];
    if (expression)
      expression->accept(*this);
    else
      ConstBaseVisitor::visit(node);
    _indent << cfg[")"];
    _indent << " <" << Utils::typeToString(node->getComputedType()) << "> ";
  }

  /*!
  ** Just get rid of them
  */

  /*!
  ** Print the type near a function call node.
  **
  ** @param node The function call node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an expression node.
  **
  ** @param node The expression node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an argument node.
  **
  ** @param node The argument node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an ids node.
  **
  ** @param node The ids node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeIds* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a program node.
  **
  ** @param node The program node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an affect node.
  **
  ** @param node The affect node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an if node.
  **
  ** @param node The if node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a read node.
  **
  ** @param node The read node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an arguments node.
  **
  ** @param node The arguments node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an expressions node.
  **
  ** @param node The expressions node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an instruction node.
  **
  ** @param node The instruction node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a compound instruction node.
  **
  ** @param node The compound instruction node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near an instructions node.
  **
  ** @param node The instructions node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a type node.
  **
  ** @param node The type node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
    _indent << " <" << Utils::typeToString(node->getComputedType()) << '>';
  }

  /*!
  ** Print the type near a while node.
  **
  ** @param node The while node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a declaration body node.
  **
  ** @param node The declaration body node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a functions node.
  **
  ** @param node The functions node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a declaration node.
  **
  ** @param node The declaration node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a declarations node.
  **
  ** @param node The declarations node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the type near a print node.
  **
  ** @param node The print node
  */
  void
  TypeCheckingPrinterVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Display a type checker in the given stream.
  **
  ** @param o The stream where to display it
  ** @param v The type checker to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const TypeCheckingPrinterVisitor& v)
  {
    v.print(o);
    return o;
  }
}
