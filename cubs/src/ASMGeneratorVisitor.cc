#include <cassert>
#include "ASMGeneratorVisitor.hh"
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
  namespace
  {
    /*!
    ** Escape a string, changing special char into asm number.
    ** Example: "toto\ntata", into : db "toto", 10, "tata", 0.
    **
    ** @param s The string to escape
    **
    ** @return The escaped string
    */
    std::string
    escape_string(const std::string& s)
    {
      int nb = s.length();
      std::stringstream ss;

      for (int i = 0; i < nb; ++i)
      {
	if (s[i] == '\\' && i + 1 < nb)
	{
	  switch (s[i + 1])
	  {
	    case 'n':
	      ss << "\", " << 10 << ", \"";
	      break;
	    case 't':
	      ss << "\", " << 9 << ", \"";
	      break;
	    case '"':
	      ss << "\", '\"', \"";
	      break;
	    case '\\':
	      ss << "\\";
	      break;
	    default:
	      ss << s[i + 1];
	  }
	  i++;
	}
	else
	  ss << s[i];
      }

      return ss.str();
    }
  }

  /*!
  ** Construct the asm convertor visitor,
  ** initializing tabulation.
  ** Also add prelude.
  */
  ASMGeneratorVisitor::ASMGeneratorVisitor()
    : _printPrelude(false), _stackShifting(0)
  {
    _tab = 0;
    _scope.open();
  }

  /*!
  ** Destruct the visitor.
  */
  ASMGeneratorVisitor::~ASMGeneratorVisitor()
  {
    _scope.close();
  }

  /*!
  ** Convert the ids node
  **
  ** @param node The ids node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeIds*)
  {
    // Nothing to do here, because we have done it
    // in declaration body
    assert(false);
  }

  /*!
  ** Force initialization of all variables.
  */
  void
  ASMGeneratorVisitor::initVariables()
  {
    for (ScopeVar::const_map_iterator it = _scope.begin();
	 it != _scope.end(); ++it)
      switch (it->second->second)
      {
	case AST::Type::STRING:
	  _indent << "\tmov\tdword " << it->second->first << ", _empty\t; Automatic initialization\n";
	  break;
	case AST::Type::BOOLEAN:
	case AST::Type::INTEGER:
	  _indent << "\tmov\tdword " << it->second->first << ", 0\t; Automatic initialization\n";
	  break;
	case AST::Type::UNDEFINED:
	  // Special value : Just ignore it. Use to preserve arguments.
	  break;
	default:
	  assert(false);
      }
  }

  /*!
  ** Convert the program node
  **
  ** @param node The program node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    writeHeader();
    const AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
      decls->accept(*this);

    _indent << "\nsection .text\n"
      "\tglobal\t_start\n"
      "\textern  _scanf, _printf, _getchar, _putchar, _malloc, _free\n";
    writePrelude();
    const AST::NodeFunctions* funcs = node->getFuncs();
    if (funcs)
      funcs->accept(*this);
    _indent << '\n';
    const AST::NodeCompoundInstr* instrs = node->getInstrs();
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << "_start:\n";
    initVariables();
    if (instrs)
      instrs->accept(*this);
    _indent << "\tmov\teax, 1\t\t; The system call for exit (sys_exit)\n"
      "\tmov\tebx, 0\t\t; Exit with return code of 0 (no error)\n"
      "\tint\t80h\n";
    writePostlude();
  }

  /*!
  ** Convert the affectation node
  **
  ** @param node The affectation node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    const AST::NodeId* id = node->getId();
    const AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);

    expr->accept(*this);

    _indent << "\tmov\t";
    id->accept(*this);
    _indent << ", edx\t; Just affect an expression\n";
  }

  /*!
  ** Convert the if node
  **
  ** @param node The if node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    const AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);
    static unsigned int globaliIfLabelCount = 0;
    globaliIfLabelCount++;
    unsigned int ifLabelCount = globaliIfLabelCount;

    cond->accept(*this);
    _indent << "\ttest\teax, eax\n"
      "\tjz\tif_jump_" << ifLabelCount << "\t; If expr then\n";
    body->accept(*this);
    if (elseExprs)
      _indent << "\tjmp\tend_if_jump_" << ifLabelCount << "\t; Else\n";
    _indent << "if_jump_" << ifLabelCount << ":\n";
    if (elseExprs)
    {
      elseExprs->accept(*this);
      _indent << "end_if_jump_" << ifLabelCount << ":\n";
    }
  }

  /*!
  ** Convert the read node
  **
  ** @param node The read node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    const AST::NodeId* id = node->getId();
    assert(id);

    switch (id->getComputedType())
    {
      case AST::Type::INTEGER:
	_indent << "\tcall\t__read_int\t; Store the integer";
	break;
      case AST::Type::BOOLEAN:
	_indent << "\tcall\t__read_bool\t; Store the boolean";
	break;
      case AST::Type::STRING:
	_indent << "\tcall\t__read_string\t; Store the string";
	break;
      default:
	  assert(false);
    }
    _indent << " value into the eax register\n"
      "\tmov\t";
    id->accept(*this);
    _indent << ", eax\t; Copy back to our variable\n";
  }

  /*!
  ** Convert the argument node
  **
  ** @param node The argument node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    const AST::NodeDeclarationBody* body = node->getDeclarationBody();
    assert(body);

    const AST::NodeIds* ids = body->getIds();
    assert(ids);
    const AST::NodeType* type = body->getType();
    assert(type);

    const AST::NodeId* id = 0;
    while (ids)
    {
      id = ids->getId();
      assert(id);
      type->accept(*this);
      std::stringstream ss;
      ss << "[ebp + " << _stackShifting << "]";
      _scope.put(id->getId(), Utils::makePair(ss.str(), AST::Type::UNDEFINED));
      _stackShifting += LOCAL_VAR_SIZE;
      ids = ids->getIds();
    }
  }

  /*!
  ** Convert the arguments node
  **
  ** @param node The arguments node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    const AST::NodeArgument* arg = node->getArgument();
    assert(arg);
    const AST::NodeArguments* args = node->getArguments();

    // Start to 8 because of "frame pointer + base pointer" = esp + ebp = 4 + 4 = 8
    _stackShifting = 8;

    arg->accept(*this);
    while (args)
    {
      arg = args->getArgument();
      assert(arg);
      arg->accept(*this);
      args = args->getArguments();
    }

    _stackShifting = 0;
  }

  /*!
  ** Convert the return node
  **
  ** @param node The return node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);

    expr->accept(*this);
    _indent << "\tmov\teax, edx\t; eax is used to put returned value\n"
      "\tmov\tesp, ebp\n"
      "\tpop\tebp\n"
      "\tret\t\t\t; Return\n";
  }

  /*!
  ** Convert the exit node
  **
  ** @param node The exit node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);

    expr->accept(*this);
    _indent << "\tmov\teax, 1\t\t; The system call for exit (sys_exit)\n"
      "\tmov\tebx, edx\t; Exit with given return code\n"
      "\tint\t80h\n";
  }

  /*!
  ** Convert the function call node
  **
  ** @param node The function call node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(id);

    _indent << "\tpush\tebp\t\t; Create a scope to save arguments\n"
      "\tmov\tebp, esp\n";

    if (exprs)
      exprs->accept(*this);

    _indent << "\tcall\t";
    id->accept(*this);
    _indent << "\t; Just call the function using __cdecl convention\n"
      "\tmov\tedx, eax\t; Copy result of the function into edx\n"
      "\tmov\tesp, ebp\n"
      "\tpop\tebp\t\t; Close the arguments scope\n";
  }

  /*!
  ** Convert the operation node
  **
  ** @param node The operation node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    const AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);

    leftFactor->accept(*this);

    if (node->getOpType() != AST::Operator::NONE)
    {
      _indent << "\n\tpush\tedx\t\t; Save edx into the stack to help computing expression\n";
      const AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      rightFactor->accept(*this);
      _indent << "\tmov\tecx, edx\t; Move current edx into ecx\n"
	"\tpop\tedx\t\t; Restore edx from the stack to help computing expression\n\t";

      switch (node->getOpType())
      {
	case AST::Operator::PLUS:
	  switch (node->getComputedType())
	  {
	    case AST::Type::STRING:
	      _indent << "mov\tesi, ecx\n"
		"\tmov\tedi, edx\n"
		"\tcall\t__concat\t; Concat edx and ecx\n"
		"\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	      break;
	    case AST::Type::INTEGER:
	      _indent << "add\tedx, ecx\t; Compute chunk's add expression in edx\n";
	      break;
	    default:
	      assert(false);
	  }
	  break;
	case AST::Operator::MINUS:
	  _indent << "sub\tedx, ecx\t; Compute chunk's sub expression in edx\n";
	  break;
	case AST::Operator::DIV:
	  _indent << "mov\teax, edx\t; The eax register must contains the left factor\n"
	    "\txor\tedx, edx\t; Put edx to 0\n"
	    "\tdiv\tecx\t; The ecx register must contains the right factor\n"
	    "\tmov\tedx, eax\t; Result of the division is written into eax\n";
	  break;
	case AST::Operator::MUL:
	  _indent << "mov\teax, edx\t; The eax register must contains the left factor\n"
	    "\txor\tedx, edx\t; Put edx to 0\n"
	    "\tmul\tecx\t\t; The ecx register must contains the right factor\n"
	    "\tmov\tedx, eax\t; Result of the multiplication is written into eax\n";
	  break;
	case AST::Operator::MODULO:
	  _indent << "mov\teax, edx\t; The eax register must contains the left factor\n"
	    "\txor\tedx, edx\t; Put edx to 0\n"
	    "\tdiv\tecx\t\t; The ecx register must contains the right factor\n"
	    "\t\t\t\t; Remains of the division is written into eax, nothing to do\n";
	  break;
	  // FIXME : Just take care of the stack
	case AST::Operator::EQUAL:
	  _indent << "push\tecx\t\t; Eq cmp : second arg\n"
	    "\tpush\tedx\t\t; Eq cmp : first arg\n"
	    "\tcall\t"
		  << (leftFactor->getComputedType() == AST::Type::STRING ?
		      "__streq" : "__is_eq")
		  << "\t\t; Check if edx == ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	case AST::Operator::SUP:
	  _indent << "push\tecx\t\t; Sup cmp : second arg\n"
	    "\tpush\tedx\t\t; Sup cmp : first arg\n"
	    "\tcall\t__is_sup\t\t; Check if edx > ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	case AST::Operator::SUPEQUAL:
	  _indent << "push\tecx\t\t; Supeq cmp : second arg\n"
	    "\tpush\tedx\t\t; Supeq cmp : first arg\n"
	    "\tcall\t__is_supeq\t\t; Check if edx >= ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	case AST::Operator::INF:
	  _indent << "push\tecx\t\t; Inf cmp : second arg\n"
	    "\tpush\tedx\t\t; Inf cmp : first arg\n"
	    "\tcall\t__is_inf\t\t; Check if edx < ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	case AST::Operator::INFEQUAL:
	  _indent << "push\tecx\t\t; Infeq cmp : second arg\n"
	    "\tpush\tedx\t\t; Infeq cmp : first arg\n"
	    "\tcall\t__is_infeq\t\t; Check if edx <= ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	case AST::Operator::DIFF:
	  _indent << "push\tecx\t\t; Diff cmp : second arg\n"
	    "\tpush\tedx\t\t; Diff cmp : first arg\n"
	    "\tcall\t"
		  << (leftFactor->getComputedType() == AST::Type::STRING ?
		      "__strdiff" : "__is_diff")
		  << "\t\t; Check if edx != ecx, and store result in eax\n"
	    "\tmov\tedx, eax\t; Copy resulting strings in eax\n";
	  break;
	default:
	  assert(false);
      }
    }
  }

  /*!
  ** Convert the expression node
  ** Put the result in the edx register
  **
  ** @param node The expression node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeExpression* node)
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
  ASMGeneratorVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    static unsigned int strCountLabel = 0;

    const std::string& s = escape_string(node->getString());
    if (_strings.find(s) == _strings.end())
    {
      strCountLabel++;
      std::stringstream ss;
      ss << "_string" << strCountLabel;
      _strings[s] = ss.str();
    }

    _indent << _strings[s];
  }

  /*!
  ** Convert the boolean node
  **
  ** @param node The boolean node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    _indent << (node->getBool() ? "1\t\t; True" : "0\t\t; False");
  }

  /*!
  ** Convert the expressions node
  **
  ** @param node The expressions node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    const AST::NodeExpressions* exprs = node->getExprs();
    std::list<const AST::NodeExpression*> list;

    // Just push each arguments in descedant order,
    // to evaluate them from right to left.
    list.push_front(expr);
    while (exprs)
    {
      expr = exprs->getExpr();
      assert(expr);
      list.push_front(expr);
      exprs = exprs->getExprs();
    }

    // Then just evaluate them from right to left.
    for (std::list<const AST::NodeExpression*>::const_iterator it = list.begin();
	 it != list.end(); ++it)
    {
      (*it)->accept(*this);
      _indent << "\tpush\tedx\t\t; Save argument\n";
    }
  }

  /*!
  ** Convert the instruction node
  **
  ** @param node The instruction node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeInstr* node)
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

    if (affect)
      affect->accept(*this);
    else if (callFunc)
      callFunc->accept(*this);
    else if (nIf)
      nIf->accept(*this);
    else if (nWhile)
      nWhile->accept(*this);
    else if (nReturn)
      nReturn->accept(*this);
    else if (nExit)
      nExit->accept(*this);
    else if (nPrint)
      nPrint->accept(*this);
    else if (nRead)
      nRead->accept(*this);
  }

  /*!
  ** Convert the compound instruction node
  **
  ** @param node The compound instruction node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    const AST::NodeInstrs* instrs = node->getInstrs();

    //     _indent << "\tpush\tebp\t\t; Begin\n"
    //       "\tmov\tebp, esp\n";
    if (instrs)
      instrs->accept(*this);
    //     _indent << "\tmov\tesp, ebp\n"
    //       "\tpop\tebp\t\t; End\n";
  }

  /*!
  ** Convert the factor node
  **
  ** @param node The factor node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    const AST::NodeId* id = node->getId();
    const AST::NodeCallFunc* callFunc = node->getCallFunc();
    const AST::NodeNumber* number = node->getNumber();
    const AST::NodeStringExpr* stringExpr = node->getStringExpr();
    const AST::NodeBoolean* boolExpr = node->getBool();
    const AST::NodeExpression* expression = node->getExpression();
    unsigned int nb = 0;

    nb += id ? 1 : 0;
    nb += callFunc ? 1 : 0;
    nb += number ? 1 : 0;
    nb += stringExpr ? 1 : 0;
    nb += boolExpr ? 1 : 0;
    nb += expression ? 1 : 0;
    assert(nb == 1);

    if (callFunc)
    {
      callFunc->accept(*this);
      return;
    }
    else if (expression)
    {
      expression->accept(*this);
      return;
    }

    _indent << "\tmov\tedx, ";

    if (id)
      id->accept(*this);
    else if (number)
      number->accept(*this);
    else if (stringExpr)
      stringExpr->accept(*this);
    else if (boolExpr)
      boolExpr->accept(*this);

    _indent << "\n";
  }

  /*!
  ** Convert the instructions node
  **
  ** @param node The instructions node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeInstrs* node)
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
  ASMGeneratorVisitor::visit(const AST::NodeType*)
  {
    if (declaringGlobalVar())
      _indent << "dd";
  }

  /*!
  ** Convert the function node
  **
  ** @param node The function node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    AST::NodeHeaderFunc* header = node->getHeaderFunc();
    AST::NodeDeclarations* decls = node->getDeclarations();
    AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    _scope.open();
    header->accept(*this);
    _indent << "\tpush\tebp\t\t; Begin\n"
      "\tmov\tebp, esp\n";
    if (decls)
      decls->accept(*this);
    AST::NodeInstrs* instrs = instr->getInstrs();
    if (instrs)
      instrs->accept(*this);
    _indent << "\tmov\tesp, ebp\n"
      "\tpop\tebp\t\t; End\n"
      "\tret\t\t; exit function\n";
    _scope.close();
  }

  /*!
  ** Convert the while node
  **
  ** @param node The while node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);
    static unsigned int globalWhileLabelCount = 0;
    globalWhileLabelCount++;
    unsigned int whileLabelCount = globalWhileLabelCount;

    _indent << "while_" << whileLabelCount << ":\n";
    cond->accept(*this);
    _indent << "\ttest\teax, eax\n"
      "\tjz\tend_while_" << whileLabelCount << "\t; While expr do\n";
    body->accept(*this);
    _indent << "\tjmp\twhile_" << whileLabelCount << "\n"
      "end_while_" << whileLabelCount << ":\n";
  }

  /*!
  ** Convert the declaration body node
  **
  ** @param node The declaration body node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    const AST::NodeIds* ids = node->getIds();
    assert(ids);
    const AST::NodeType* type = node->getType();
    assert(type);
    // Start to 8 because of "frame pointer + base pointer" = esp + ebp = 4 + 4 = 8
    unsigned int sizeToAllocate = 8;

    const AST::NodeId* id = 0;
    while (ids)
    {
      id = ids->getId();
      assert(id);

      if (declaringGlobalVar())
      {
	_indent << '\t';
	_scope.put(id->getId(),
		   Utils::makePair("[" + id->getId() + "]",
				   Utils::stringToType(type->getType())));
	_indent << id->getId() << ' ';
      }

      type->accept(*this);

      if (!declaringGlobalVar())
      {
	std::stringstream ss;
	ss << "[ebp - " << sizeToAllocate << "]";
	_scope.put(id->getId(), Utils::makePair(ss.str(),
						Utils::stringToType(type->getType())));
      }
      else
	_indent << " 0\t; var " << id->getId() << " : " << type->getType() << ";\n";

      sizeToAllocate += LOCAL_VAR_SIZE;
      ids = ids->getIds();
    }

    if (!declaringGlobalVar())
    {
      _indent << "\tsub\tesp, " << sizeToAllocate
	      << "\t; Let's allocate places for local variables\n";
      initVariables();
    }
  }

  /*!
  ** Convert the functions node
  **
  ** @param node The functions node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeFunctions* node)
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
  ASMGeneratorVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    _indent << node->getNumber();
  }

  /*!
  ** Convert the declaration node
  **
  ** @param node The declaration node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    const AST::NodeDeclarationBody* body = node->getBody();
    assert(body);
    body->accept(*this);
  }

  /*!
  ** Convert the function header node
  **
  ** @param node The function header node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    assert(id);

    id->accept(*this);
    _indent << ":\n";
    if (args)
      args->accept(*this);
  }

  /*!
  ** Convert the declaration node
  **
  ** @param node The declaration node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeDeclarations* node)
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
  ASMGeneratorVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    _indent << (*_scope.getFromAll(node->getId())).first;
  }

  /*!
  ** Convert the function id node
  **
  ** @param node The function id node
  */
  void
  ASMGeneratorVisitor::visit(const AST::NodeIdFunc* node)
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
  ASMGeneratorVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);

    expr->accept(*this);
    _indent << "\tmov eax, edx\t; Prepare to being print\n";
    _indent << "\tcall\t";
    switch (expr->getComputedType())
    {
      case AST::Type::INTEGER:
	_indent << "__print_int";
	break;
      case AST::Type::BOOLEAN:
	_indent << "__print_bool";
	break;
      case AST::Type::STRING:
	_indent << "__print_string";
	break;
      case AST::Type::UNDEFINED:
      default:
	assert(false);
    }
    _indent << "\t; print value contained in eax\n";
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
  operator<<(std::ostream& o, const ASMGeneratorVisitor& v)
  {
    v.print(o);
    return o;
  }
}
