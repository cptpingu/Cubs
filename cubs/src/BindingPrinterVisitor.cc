#include <cassert>
#include "BindingPrinterVisitor.hh"
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
  ** Construct the binding printer visitor.
  */
  BindingPrinterVisitor::BindingPrinterVisitor()
  {
  }

  /*!
  ** Destruct the binding printer visitor.
  */
  BindingPrinterVisitor::~BindingPrinterVisitor()
  {
  }

  /*!
  ** Print the binding information for the id node.
  **
  ** @param node The id node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    assert(node->getId() != "");
    _indent << node->getId() << " /* " << node->getRef() << " */";
  }

  /*!
  ** Print the binding information for the function id node.
  **
  ** @param node The function id node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    assert(node->getId() != "");
    _indent << node->getId() << " /* " << node->getRef() << " */";
  }

  /*!
  ** Print the binding information for the return node.
  **
  ** @param node The return node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["return"] << " /* " << node->getRefFunc() << " */ ";
    expr->accept(*this);
  }

  /*!
  ** Print the binding information for the header function node.
  **
  ** @param node The header function node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeHeaderFunc* node)
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
  ** Print the binding information for the program node.
  **
  ** @param node The program node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    _indent << "Program __main__ /* " << node <<
      " */ " << cfg["("] << cfg[")"] <<
      " " << cfg[":"] << " " << cfg["int"] << cfg[";"] << "\n" <<
      cfg["begin"] << "\n";
    PrettyPrinterVisitor::visit(node);
    _indent << cfg["end"] << '\n';
  }

  /*!
  ** Print the binding information for the function call node.
  **
  ** @param node The function call node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    assert(id);

    id->accept(*this);
    _indent << cfg["("];

    // Let's show all binded arguments
    AST::NodeExpressions* exprs = node->getExprs();
    AST::NodeExpression* expr = 0;
    unsigned int pos = 0;
    while (exprs)
    {
      expr = exprs->getExpr();
      assert(expr);
      expr->accept(*this);
      exprs = exprs->getExprs();

      // Firstly, check that's function was binded correctly
      AST::NodeFunction* refFunc = node->getId()->getRef();
      if (refFunc)
      {
	// Manage unsynchronized numbers of arguments
	if (pos < refFunc->nbArgument())
	  _indent << " /* " << refFunc->getArgument(pos) << " */";
	else
	  _indent << " /* Can't bind */";
	if (exprs)
	  _indent << cfg[","] << ' ';
	pos++;
      }
    }
    _indent << cfg[")"];
  }

  /*!
  ** Print the binding information for the function node.
  **
  ** @param node The function node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeFunction* node)
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
	      << node->getArgument(i) << "\n";
    _indent << Utils::stringFill(SPACING_CHAR, _tab + INDENT_SIZE) << "*/\n";
    header->accept(*this);
    if (decls)
      decls->accept(*this);
    instr->accept(*this);
    _indent << '\n';
  }

  /*!
  ** Just get rid of them
  */

  /*!
  ** Print the binding information for the ids node.
  **
  ** @param node The ids node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeIds* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the exit node.
  **
  ** @param node The exit node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the affect node.
  **
  ** @param node The affect node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the if node.
  **
  ** @param node The if node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the read node.
  **
  ** @param node The read node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the argument node.
  **
  ** @param node The argument node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the arguments node.
  **
  ** @param node The arguments node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the operation node.
  **
  ** @param node The operation node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the expression node.
  **
  ** @param node The expression node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the string expression node.
  **
  ** @param node The string expression node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the boolean node.
  **
  ** @param node The boolean node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the expressions node.
  **
  ** @param node The expressions node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the instruction node.
  **
  ** @param node The instruction node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the compound instruction node.
  **
  ** @param node The compound instruction node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the factor node.
  **
  ** @param node The factor node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the instructions node.
  **
  ** @param node The instructions node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the type node.
  **
  ** @param node The type node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the while node.
  **
  ** @param node The while node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the declaration body node.
  **
  ** @param node The declaration body node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the functions node.
  **
  ** @param node The functions node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the number node.
  **
  ** @param node The number node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the declaration node.
  **
  ** @param node The declarartion node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the declarations node.
  **
  ** @param node The declarations node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }

  /*!
  ** Print the binding information for the print node.
  **
  ** @param node The print node
  */
  void
  BindingPrinterVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    PrettyPrinterVisitor::visit(node);
  }
}
