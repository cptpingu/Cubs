#include <cassert>
#include "ExecutionVisitor.hh"
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
  ** Construct an execution visitor, settting tabulation to default,
  ** show Code, variables and special variables to false, isBreak and isExit
  ** to false, and return value to 0.
  */
  ExecutionVisitor::ExecutionVisitor()
    : _tab(INDENT_SIZE), _break(false), _exit(false), _showCode(false),
      _showVariables(false), _showSpecialVariables(false), _returnValue(0)
  {
    _registry.open();
  }

  /*!
  ** Destruct an execution visitor, closing last open scope.
  */
  ExecutionVisitor::~ExecutionVisitor()
  {
    _registry.closeAndDelete();
  }

  /*!
  ** Print buffered text in the given stream.
  **
  ** @param o The given stream
  */
  void
  ExecutionVisitor::print(std::ostream& o) const
  {
    o << _indent.str();
  }

  /*!
  ** Set if code has to be displayed.
  **
  ** @param show If code has to be display
  */
  void
  ExecutionVisitor::setShowCode(bool show)
  {
    _showCode = show;
  }

  /*!
  ** Set if variables has to be displayed.
  **
  ** @param show If variables has to be displayed
  */
  void
  ExecutionVisitor::setShowVariables(bool show)
  {
    _showVariables = show;
  }

  /*!
  ** Set if special variables has to be displayed.
  **
  ** @param show If special variables has to be displayed
  */
  void
  ExecutionVisitor::setShowSpecialVariables(bool show)
  {
    _showSpecialVariables = show;
  }

  /*!
  ** Get the return value of the executed code.
  **
  ** @return Exited value of executed code
  */
  int
  ExecutionVisitor::getReturnValue() const
  {
    return _returnValue;
  }

  /*!
  ** Flush displaying on standard output.
  */
  void
  ExecutionVisitor::flushToScreen()
  {
    if (_showCode)
    {
      print(std::cout);
      _indent.str("");
      _indent.clear();
    }
    if (_showVariables)
    {
      if (!_showSpecialVariables)
	_registry.setFilter(Exec::SEPARATOR);
      std::cout << '\n' << _registry;
    }
  }

  /*!
  ** Add a variable to the registry.
  **
  ** @param name The name of the variable
  ** @param var The variable to put
  */
  void
  ExecutionVisitor::addVar(const std::string& name, const Variable& var)
  {
    Variable* curvar = _registry.getFromCurrent(name);

    // if we found a variable, we delete it.
    delete curvar;

    _registry.put(name, new Variable(var));
  }

  /*!
  ** Change a variable value.
  **
  ** @param name The variable name
  ** @param var The new value of this variable
  */
  void
  ExecutionVisitor::changeVar(const std::string& name, const Variable& var)
  {
    Variable* curvar = _registry.getFromAll(name);
    assert(curvar);
    *curvar = var;
  }

  /*!
  ** Get the wanted variable. Variable name must exist.
  **
  ** @param name The name of the variable
  **
  ** @return A pointer on variable, or null (must not happen !)
  */
  Variable*
  ExecutionVisitor::getVar(const std::string& name)
  {
    Variable* curvar = _registry.getFromCurrent(name);
    assert(curvar);
    return curvar;
  }

  /*!
  ** Display the execution on the given stream.
  **
  ** @param o The stream where to display it
  ** @param v The execution visitor to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const ExecutionVisitor& v)
  {
    v.print(o);
    return o;
  }

  /*!
  ** Execute a program node.
  **
  ** @param node The program node
  */
  void
  ExecutionVisitor::visit(const AST::NodeProgram* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    const AST::NodeDeclarations* decls = node->getDecls();
    if (decls)
    {
      decls->accept(*this);
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
  ** Execute an affect node.
  **
  ** @param node The affect node
  */
  void
  ExecutionVisitor::visit(const AST::NodeAffect* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeId* id = node->getId();
    const AST::NodeExpression* expr = node->getExpr();
    assert(id);
    assert(expr);
    id->accept(*this);
    _indent << ' ' << cfg["="] << ' ';
    expr->accept(*this);

    // Assign value to the variable.
    // To do that, we get the variable in the registry,
    // then assign the computed value.
    //Variable var = _registry.getFromAll(id->getId());
    changeVar(id->getId(), *getVar(Exec::NODE_EXPR));
  }

  /*!
  ** Execute a read node.
  **
  ** @param node The read node
  */
  void
  ExecutionVisitor::visit(const AST::NodeRead* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeId* id = node->getId();
    assert(id);

    _indent << cfg["read"];
    _indent << cfg["("];
    id->accept(*this);

    // Let's get variable to detect type.
    Variable var = *getVar(id->getId());

    // Get the user's choice
    std::string in = "";
    std::cin >> in;

    // Now test if user's choice compatible with variable type
    // and fill variable.
    switch (var.getType())
    {
      case AST::Type::BOOLEAN:
	if (in == "true" || in == "1")
	  addVar(id->getId(), Variable(bool(true)));
	else
	  if (in == "false" || in == "0")
	    addVar(id->getId(), Variable(bool(false)));
	break;
      case AST::Type::INTEGER:
	{
	  int nb = 0;
	  assert(Utils::fromString<int>(nb, in));
	  Utils::fromString<int>(nb, in);
	  Variable v = nb;
	  addVar(id->getId(), v);
	}
	break;
      case AST::Type::STRING:
	{
	  Variable v = in;
	  addVar(id->getId(), v);
	}
	break;
      default:
	assert(false);
    }

    _indent << cfg[")"];
  }

  /*!
  ** Execute an argument node.
  **
  ** @param node The argument node
  */
  void
  ExecutionVisitor::visit(const AST::NodeArgument* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeDeclarationBody* body = node->getDeclarationBody();
    const AST::NodeArguments* args = node->getArguments();
    assert(body);

    const AST::NodeIds* ids = body->getIds();
    const AST::NodeId* id = 0;
    while (ids)
    {
      id = ids->getId();
      _indent << id->getId();
      ids = ids->getIds();
      if (ids)
	_indent << cfg[","] << ' ';
    }
    const AST::NodeType* type = body->getType();
    assert(type);
    _indent << ' ' << cfg[":"] << ' ' << type->getType();

    if (args)
    {
      _indent << cfg[";"] << ' ';
      args->accept(*this);
    }
  }

  /*!
  ** Execute an arguments node.
  **
  ** @param node The arguments node
  */
  void
  ExecutionVisitor::visit(const AST::NodeArguments* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
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
  ** Execute a return node.
  **
  ** @param node The return node
  */
  void
  ExecutionVisitor::visit(const AST::NodeReturn* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["return"] << ' ';
    expr->accept(*this);
    flushToScreen();
    addVar(Exec::NODE_RETURN, *getVar(Exec::NODE_EXPR));
    _break = true;
  }

  /*!
  ** Execute an exit node.
  **
  ** @param node The exit node
  */
  void
  ExecutionVisitor::visit(const AST::NodeExit* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    assert(expr);
    _indent << cfg["exit"] << ' ';
    expr->accept(*this);
    Variable var = *getVar(Exec::NODE_EXPR);
    _returnValue = var.getInt();
    _exit = true;
  }

  /*!
  ** Execute a function call node.
  **
  ** @param node The function call node
  */
  void
  ExecutionVisitor::visit(const AST::NodeCallFunc* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(id);

    id->accept(*this);
    _indent << cfg["("];
    if (exprs)
      exprs->accept(*this);
    _indent << cfg[")"];
    flushToScreen();

    // Check that call func and declared func are same number of arguments
    const AST::NodeFunction* refFunc = id->getRef();
    assert(refFunc);
    assert(refFunc->nbArgument() == node->nbArgument());

    // Fill a scope directly, searching only arg's name
    _registry.open();
    const AST::NodeExpression* exprValue = 0;
    const AST::NodeId* idValue = 0;
    Variable* var = 0;
    for (unsigned int i = 0; i < refFunc->nbArgument(); ++i)
    {
      exprValue = node->getArgument(i);
      assert(exprValue);
      idValue = refFunc->getArgument(i);
      assert(idValue);
      std::stringstream buf;
      buf << Exec::NODE_ARG << i << Exec::SEPARATOR;
      var = _registry.getFromAll(buf.str());
      assert(var);
      addVar(idValue->getId(), *var);
    }

    _indent << ";\n";
    // Jump to the referenced function
    refFunc->accept(*this);

    // We store the return value
    assert(getVar(Exec::NODE_RETURN));
    Variable varReturn = *getVar(Exec::NODE_RETURN);
    _registry.closeAndDelete();

    // Then assign it
    addVar(Exec::NODE_CALLFUNC, varReturn);
  }

  /*!
  ** Execute an operation node.
  **
  ** @param node The operation node
  */
  void
  ExecutionVisitor::visit(const AST::NodeOperation* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;

    // Go in left factor
    const AST::NodeFactor* leftFactor = node->getLeftFactor();
    assert(leftFactor);
    leftFactor->accept(*this);
    Variable var = *getVar(Exec::NODE_FACTOR);

    // Search if there are a right factor for this operation
    if (node->getOpType() != AST::Operator::NONE)
    {
      // Go in right factor
      const AST::NodeFactor* rightFactor = node->getRightFactor();
      assert(rightFactor);
      _indent << ' ' << Utils::OpToString(node->getOpType()) << ' ';
      rightFactor->accept(*this);

      Variable boolVar = false;
      Variable rightVar = *getVar(Exec::NODE_FACTOR);
      switch (node->getOpType())
      {
	case AST::Operator::PLUS:
	  var += rightVar;
	  break;
	case AST::Operator::MINUS:
	  var -= rightVar;
	  break;
	case AST::Operator::DIV:
	  if (rightVar == 0)
	    throw Error::EXECUTION;
	  var /= rightVar;
	  break;
	case AST::Operator::MUL:
	  var *= rightVar;
	  break;
	case AST::Operator::MODULO:
	  if (rightVar == 0)
	    throw Error::EXECUTION;
	  var %= rightVar;
	  break;

	  // Here we need a boolean variable
	case AST::Operator::EQUAL:
	  boolVar = var == rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	case AST::Operator::SUP:
	  boolVar = var > rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	case  AST::Operator::SUPEQUAL:
	  boolVar = var >= rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	case  AST::Operator::INF:
	  boolVar = var < rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	case  AST::Operator::INFEQUAL:
	  boolVar = var <= rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	case  AST::Operator::DIFF:
	  boolVar = var != rightVar;
	  addVar(Exec::NODE_OPERATION, boolVar);
	  return;
	default:
	  assert(false);
      }
    }

    addVar(Exec::NODE_OPERATION, var);
  }

  /*!
  ** Execute an expression node.
  **
  ** @param node The expression node
  */
  void
  ExecutionVisitor::visit(const AST::NodeExpression* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    const AST::NodeOperation* op = node->getOperation();
    assert(op);
    op->accept(*this);
    Variable opVar = *getVar(Exec::NODE_OPERATION);
    addVar(Exec::NODE_EXPR, opVar);
  }

  /*!
  ** Execute a string expression node.
  **
  ** @param node The string expression node
  */
  void
  ExecutionVisitor::visit(const AST::NodeStringExpr* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    _indent << cfg["str"];
    const std::string s = node->getString();
    Variable tmpVar = Utils::activeSpecialChar(s);
    addVar(Exec::NODE_STRING, tmpVar);
    _indent << s;
    _indent << cfg["str"];
  }

  /*!
  ** Execute a boolean node.
  **
  ** @param node The boolean node
  */
  void
  ExecutionVisitor::visit(const AST::NodeBoolean* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const bool b = node->getBool();
    Variable tmpVar = b;
    addVar(Exec::NODE_BOOL, tmpVar);
    _indent << (b ? cfg["true"] : cfg["false"]);
  }

  /*!
  ** Execute an expressions node.
  **
  ** @param node The expressions node
  */
  void
  ExecutionVisitor::visit(const AST::NodeExpressions* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;

    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* expr = node->getExpr();
    const AST::NodeExpressions* exprs = node->getExprs();
    assert(expr);

    expr->accept(*this);
    Variable var = *getVar(Exec::NODE_EXPR);
    addVar("%arg0%", var);

    // Check if there are other arguments to the call func
    unsigned int i = 1;
    while (exprs)
    {
      _indent << cfg[","] << ' ';
      expr = exprs->getExpr();
      assert(expr);
      expr->accept(*this);
      Variable var = *getVar(Exec::NODE_EXPR);
      std::stringstream buf;
      buf << Exec::NODE_ARG << i << Exec::SEPARATOR;
      addVar(buf.str(), var);
      i++;
      exprs = exprs->getExprs();
    }
  }

  /*!
  ** Execute a instruction node.
  **
  ** @param node The instruction node
  */
  void
  ExecutionVisitor::visit(const AST::NodeInstr* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
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
      _indent << '\n';
    }
    else
      if (callFunc)
      {
	callFunc->accept(*this);
	// No ; because it was done in Node CallFunc
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
	      _indent << '\n';
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
    flushToScreen();
  }

  /*!
  ** Execute a compound instruction node.
  **
  ** @param node The compound instruction node
  */
  void
  ExecutionVisitor::visit(const AST::NodeCompoundInstr* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeInstrs* instrs = node->getInstrs();

    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["begin"] << '\n';
    _tab += INDENT_SIZE;
    flushToScreen();
    if (instrs)
      instrs->accept(*this);
    _tab -= INDENT_SIZE;
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["end"] << '\n';
    flushToScreen();
  }

  /*!
  ** Execute a factor node.
  **
  ** @param node The factor node
  */
  void
  ExecutionVisitor::visit(const AST::NodeFactor* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
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

    if (id)
    {
      id->accept(*this);
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_ID));
      return;
    }
    if (callFunc)
    {
      callFunc->accept(*this);
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_CALLFUNC));
      return;
    }
    if (number)
    {
      number->accept(*this);
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_NUMBER));
      return;
    }
    if (stringExpr)
    {
      stringExpr->accept(*this);
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_STRING));
      return;
    }
    if (boolExpr)
    {
      boolExpr->accept(*this);
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_BOOL));
      return;
    }
    if (expression)
    {
      Configuration& cfg = Configuration::getInstance();
      _indent << cfg["("];
      expression->accept(*this);
      _indent << cfg[")"];
      addVar(Exec::NODE_FACTOR, *getVar(Exec::NODE_EXPR));
      return;
    }
  }

  /*!
  ** Execute an instructions node.
  **
  ** @param node The instructions node
  */
  void
  ExecutionVisitor::visit(const AST::NodeInstrs* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Execute a type node.
  **
  ** @param node The type node
  */
  void
  ExecutionVisitor::visit(const AST::NodeType* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    _indent << node->getType();
  }

  /*!
  ** Execute a function node.
  **
  ** @param node The function node
  */
  void
  ExecutionVisitor::visit(const AST::NodeFunction* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeHeaderFunc* header = node->getHeaderFunc();
    const AST::NodeDeclarations* decls = node->getDeclarations();
    const AST::NodeCompoundInstr* instr = node->getCompoundInstr();
    assert(header);
    assert(instr);

    header->accept(*this);
    const AST::NodeType* type = header->getType();
    assert(type);
    const std::string t = type->getType();

    // Let's affect a default value in case off no return instruction
    if (t == cfg["int"])
      addVar(Exec::NODE_RETURN, Variable(int(0)));
    else
      if (t == cfg["bool"])
	addVar(Exec::NODE_RETURN, Variable(bool(false)));
      else
	if (t == cfg["string"])
	  addVar(Exec::NODE_RETURN, Variable(std::string("")));
	else
	  assert(false);

    if (decls)
      decls->accept(*this);
    instr->accept(*this);
    _indent << '\n';

    // Function is finished so, no break is possible.
    _break = false;
  }

  /*!
  ** Execute an if node.
  **
  ** @param node The if node
  */
  void
  ExecutionVisitor::visit(const AST::NodeIf* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    const AST::NodeCompoundInstr* elseExprs = node->getElseExprs();
    assert(cond);
    assert(body);

    _indent << cfg["if"] << ' ';
    cond->accept(*this);
    _indent << ' ' << cfg["then"] << '\n';
    flushToScreen();

    // Here we check if we enter in if block
    // The "== true" is ugly but necessary
    const Variable* var = getVar(Exec::NODE_EXPR);
    assert(var);
    if (*var == true)
      body->accept(*this);
    else
      if (elseExprs)
      {
	_indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["else"] << '\n';
	flushToScreen();
	elseExprs->accept(*this);
      }
  }

  /*!
  ** Execute a while node.
  **
  ** @param node The while node
  */
  void
  ExecutionVisitor::visit(const AST::NodeWhile* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* cond = node->getCond();
    const AST::NodeCompoundInstr* body = node->getBodyExprs();
    assert(cond);
    assert(body);

    const Variable* var = 0;
    bool continueLoop = true;
    while (continueLoop && !_exit && !_break)
    {
      _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["while"] << ' ';
      cond->accept(*this);
      var = getVar(Exec::NODE_EXPR);
      assert(var);
      continueLoop = *var == true;
      _indent << ' ' << cfg["do"] << '\n';
      flushToScreen();
      if (continueLoop)
	body->accept(*this);
    }
  }

  /*!
  ** Execute a declaration body node.
  **
  ** @param node The declaration body node
  */
  void
  ExecutionVisitor::visit(const AST::NodeDeclarationBody* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
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
  ** Execute a functions node.
  **
  ** @param node The functions node
  */
  void
  ExecutionVisitor::visit(const AST::NodeFunctions* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Execute a number node.
  **
  ** @param node The number node
  */
  void
  ExecutionVisitor::visit(const AST::NodeNumber* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    const int nb = node->getNumber();
    Variable tmpVar(nb);
    addVar(Exec::NODE_NUMBER, tmpVar);
    _indent << nb;
  }

  /*!
  ** Execute a declaration node.
  **
  ** @param node The declaration node
  */
  void
  ExecutionVisitor::visit(const AST::NodeDeclaration* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeDeclarationBody* body = node->getBody();
    assert(body);
    _indent << cfg["var"] << ' ';
    body->accept(*this);
    _indent << cfg[";"] << '\n';
    flushToScreen();
  }

  /*!
  ** Execute a function header node.
  **
  ** @param node The function header node
  */
  void
  ExecutionVisitor::visit(const AST::NodeHeaderFunc* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeIdFunc* id = node->getId();
    const AST::NodeArguments* args = node->getArguments();
    const AST::NodeType* type = node->getType();

    assert(id);
    assert(type);
    _indent << Utils::stringFill(SPACING_CHAR, _tab) << cfg["function"] << ' ';
    id->accept(*this);
    _indent << cfg["("];
    if (args)
      args->accept(*this);
    _indent << cfg[")"] << ' ' << cfg[":"] << ' ';
    type->accept(*this);
    _indent << cfg[";"] << '\n';
  }

  /*!
  ** Execute a declarations node.
  **
  ** @param node The declarations node
  */
  void
  ExecutionVisitor::visit(const AST::NodeDeclarations* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    _indent << Utils::stringFill(SPACING_CHAR, _tab);
    ConstBaseVisitor::visit(node);
  }

  /*!
  ** Execute a id node.
  **
  ** @param node The id node
  */
  void
  ExecutionVisitor::visit(const AST::NodeId* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    assert(node->getId() != "");
    _indent << node->getId();

    // If it's a declaration, put it in the registry
    if (node->isDeclaration())
    {
      switch (node->getComputedType())
      {
	case AST::Type::INTEGER:
	  _registry.put(node->getId(), new Variable(int(0)));
	  break;
	case AST::Type::BOOLEAN:
	  _registry.put(node->getId(), new Variable(bool(false)));
	  break;
	case AST::Type::STRING:
	  _registry.put(node->getId(), new Variable(std::string("")));
	  break;
	default:
	  assert(false);
      }
      return;
    }

    // So, it's simple var. Just get the associated value
    Variable* var = _registry.getFromAll(node->getId());
    assert(var);
    addVar(Exec::NODE_ID, *var);
  }

  /*!
  ** Execute a function id node.
  **
  ** @param node The function id node
  */
  void
  ExecutionVisitor::visit(const AST::NodeIdFunc* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    assert(node->getId() != "");
    _indent << node->getId();
  }

  /*!
  ** Execute a print node.
  **
  ** @param node The print node
  */
  void
  ExecutionVisitor::visit(const AST::NodePrint* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
    Configuration& cfg = Configuration::getInstance();
    const AST::NodeExpression* id = node->getExpr();
    assert(id);

    _indent << cfg["print"] << cfg["("];
    id->accept(*this);
    Variable v = *getVar(Exec::NODE_EXPR);
    v.print(std::cout);
    _indent << cfg[")"];
  }

  /*!
  ** Execute an ids node.
  **
  ** @param node The ids node
  */
  void
  ExecutionVisitor::visit(const AST::NodeIds* node)
  {
    assert(node);
    if (_break)
      return;
    if (_exit)
      return;
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
}
