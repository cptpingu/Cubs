#include "CreateAST.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the CreateAST with a Lexer.
  ** Intialize all internal lexer with given one,
  ** position in the internal lexer to 0, and size
  ** of the lexer to given one.
  **
  ** @param lexer The given lexer
  */
  CreateAST::CreateAST(const Lexer& lexer)
    : _lexer(lexer), _pos(0), _size(lexer.length())
  {
  }

  /*!
  ** Destruct the CreateAST
  */
  CreateAST::~CreateAST()
  {
  }

  /*!
  ** Create all necessary nodes own by ids node.
  **
  ** @param node The ids node
  */
  void
  CreateAST::construct(AST::NodeIds* node)
  {
    assert(node);
    assert(valid());
    assert(isIds(current()));
    node->setLine(current().getLine());

    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);
    if (!checkValid())
      return;

    // Anything else but coma -> list id is finished
    if (!isComa(current()))
      return;

    nextToken();
    if (!checkValid())
      return;

    if (!isId(current()))
    {
      error("ID", current());
      return;
    }
    AST::NodeIds* ids = new AST::NodeIds();
    node->setIds(ids);
    construct(ids);
  }

  /*!
  ** Create all necessary nodes own by program node.
  **
  ** @param node The program node
  */
  void
  CreateAST::construct(AST::NodeProgram* node)
  {
    assert(node);
    node->setLine(current().getLine());

    // Program is empty, valid but useless.
    if (_size == 0)
      return;

    // We found a var, so it's a variable declaration
    if (isVar(current()))
    {
      AST::NodeDeclarations* decls = new AST::NodeDeclarations();
      node->setDecls(decls);
      construct(decls);
      if (!valid())
	return;
    }

    // We found a function, so it's a function declaration
    if (isFunctions(current()))
    {
      AST::NodeFunctions* funcs = new AST::NodeFunctions();
      node->setFuncs(funcs);
      construct(funcs);
      if (!valid())
	return;
    }

    // Search first valid token
    if (isCompoundInstr(current()))
    {
      AST::NodeCompoundInstr* instrs = new AST::NodeCompoundInstr();
      node->setInstrs(instrs);
      construct(instrs);
      return;
    }

    // So, it's not a valid program
    error("KEYWORD", current());
  }

  /*!
  ** Create all necessary nodes own by affect node.
  **
  ** @param node The affect node
  */
  void
  CreateAST::construct(AST::NodeAffect* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isAffect(current()));
    node->setLine(current().getLine());

    // Set the id
    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);
    if (!checkValid())
      return;

    // Check for = token
    if (!isEqual(current()))
    {
      error(cfg["="], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Now set the expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Create all necessary nodes own by if node.
  **
  ** @param node The if node
  */
  void
  CreateAST::construct(AST::NodeIf* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isIf(current()));
    node->setLine(current().getLine());

    // Get rid of if token
    nextToken();
    if (!checkValid())
      return;

    // Check for cond expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setCond(expr);
    construct(expr);
    if (!checkValid())
      return;

    // Check for then token
    if (!isThen(current()))
    {
      error(cfg["then"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for body expression
    AST::NodeCompoundInstr* body = new AST::NodeCompoundInstr();
    node->setBodyExprs(body);
    construct(body);

    // Now check if there is an else condition
    if (valid() && isElse(current()))
    {
      // Get rid of else token
      nextToken();
      if (!checkValid())
	return;

      // Check for elseExpr expression
      AST::NodeCompoundInstr* elseExprs = new AST::NodeCompoundInstr();
      node->setElseExprs(elseExprs);
      construct(elseExprs);
    }
  }

  /*!
  ** Create all necessary nodes own by read node.
  **
  ** @param node The read node
  */
  void
  CreateAST::construct(AST::NodeRead* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isRead(current()));
    node->setLine(current().getLine());
    nextToken();
    if (!checkValid())
      return;

    // Check for (
    if (!isLeftBracket(current()))
    {
      error(cfg["("], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Set the id
    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);
    if (!checkValid())
      return;

    // Check for )
    if (!isRightBracket(current()))
    {
      error(cfg[")"], current());
      return;
    }
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by arguments node.
  **
  ** @param node The arguments node
  */
  void
  CreateAST::construct(AST::NodeArguments* node)
  {
    assert(node);
    assert(valid());
    assert(isArguments(current()));
    node->setLine(current().getLine());

    AST::NodeArgument* arg = new AST::NodeArgument();
    node->setArgument(arg);
    construct(arg);

    // Check for ;
    if (isSemiColon(current()))
    {
      nextToken();
      if (!checkValid())
	return;
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
    }
  }

  /*!
  ** Create all necessary nodes own by argument node.
  **
  ** @param node The argument node
  */
  void
  CreateAST::construct(AST::NodeArgument* node)
  {
    assert(valid());
    assert(isArgument(current()));
    node->setLine(current().getLine());

    AST::NodeDeclarationBody* body = new AST::NodeDeclarationBody();
    node->setDeclarationBody(body);
    construct(body);

    if (!checkValid())
      return;

    // Just check if there are other arguments, ie check for ,
    if (isComa(current()))
    {
      nextToken();
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
    }
  }

  /*!
  ** Create all necessary nodes own by return node.
  **
  ** @param node The return node
  */
  void
  CreateAST::construct(AST::NodeReturn* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isReturn(current()));
    node->setLine(current().getLine());

    // Check for return keyword
    if (!isReturn(current()))
    {
      error(cfg["return"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for the expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Create all necessary nodes own by exit node.
  **
  ** @param node The exit node
  */
  void
  CreateAST::construct(AST::NodeExit* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isExit(current()));
    node->setLine(current().getLine());

    // Check for exit keyword
    if (!isExit(current()))
    {
      error(cfg["exit"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for the expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Create all necessary nodes own by function call node.
  **
  ** @param node The function call node
  */
  void
  CreateAST::construct(AST::NodeCallFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isCallFunc(current()));
    node->setLine(current().getLine());

    // Let's take care of the func's name
    AST::NodeIdFunc* id = new AST::NodeIdFunc();
    node->setId(id);
    construct(id);
    if (!checkValid())
      return;

    // Check for (
    if (!isLeftBracket(current()))
    {
      error(cfg["("], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check if there are no arguments
    if (isRightBracket(current()))
    {
      nextToken();
      return;
    }

    // So the function has arguments, let's parse them
    AST::NodeExpressions* exprs = new AST::NodeExpressions();
    node->setExprs(exprs);
    construct(exprs);
    if (!checkValid())
      return;

    // Check if there is a )
    if (!isRightBracket(current()))
    {
      error(cfg[")"], current());
      return;
    }
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by operation node.
  **
  ** @param node The operation node
  */
  void
  CreateAST::construct(AST::NodeOperation* node)
  {
    assert(node);
    assert(valid());
    assert(isOperation(current()));
    node->setLine(current().getLine());

    Configuration& cfg = Configuration::getInstance();
    // Check if operation begin with a + or a -
    if (current().getText() == cfg["-"] ||
	current().getText() == cfg["+"])
    {
      // Create cheated left factor, ie 0
      AST::NodeFactor* leftFactor = new AST::NodeFactor();
      AST::NodeNumber* num = new AST::NodeNumber();
      num->setNumber(0);
      leftFactor->setNumber(num);
      node->setLeftFactor(leftFactor);

      // So we set the operator
      node->setOpType(Utils::StringToOp(current().getText()));
      nextToken();
      if (!checkValid())
	return;

      // Check that next token is an expression
      if (!isFactor(current()))
      {
	node->setOpType(AST::Operator::NONE);
	error("EXPRESSION", current());
	return;
      }

      AST::NodeFactor* rightFactor = new AST::NodeFactor();
      node->setRightFactor(rightFactor);
      construct(rightFactor);
    }
    else
    {
      // Create normal left factor
      AST::NodeFactor* factor = new AST::NodeFactor();
      node->setLeftFactor(factor);
      construct(factor);
      node->setOpType(AST::Operator::NONE);
      if (!valid())
	return;

      // So we check for an operator
      if (isOperator(current()))
      {
	node->setOpType(Utils::StringToOp(current().getText()));
	nextToken();
	if (!checkValid())
	  return;
	AST::NodeFactor* factor = new AST::NodeFactor();
	node->setRightFactor(factor);
	construct(factor);
      }
    }
  }

  /*!
  ** Create all necessary nodes own by expression node.
  **
  ** @param node The expression node
  */
  void
  CreateAST::construct(AST::NodeExpression* node)
  {
    assert(node);
    assert(valid());
    assert(isExpression(current()));
    node->setLine(current().getLine());

    AST::NodeOperation* op = new AST::NodeOperation();
    node->setOperation(op);
    construct(op);
  }

  /*!
  ** Create all necessary nodes own by string expression node.
  **
  ** @param node The string expression node
  */
  void
  CreateAST::construct(AST::NodeStringExpr* node)
  {
    assert(node);
    assert(valid());
    assert(isStringExpr(current()));
    node->setLine(current().getLine());

    node->setString(current().getText());
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by boolean node.
  **
  ** @param node The boolean node
  */
  void
  CreateAST::construct(AST::NodeBoolean* node)
  {
    assert(node);
    assert(valid());
    assert(isBoolean(current()));
    node->setLine(current().getLine());
    node->setBool(Utils::stringToBool(current().getText()));
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by expressions node.
  **
  ** @param node The expressions node
  */
  void
  CreateAST::construct(AST::NodeExpressions* node)
  {
    assert(node);
    assert(valid());
    assert(isExpressions(current()));
    node->setLine(current().getLine());

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);

    // Check if there is remaining expressions
    if (valid() && isComa(current()))
    {
      nextToken();
      if (!checkValid())
	return;

      // Now check if there is a valid "expressions"
      if (!isExpressions(current()))
      {
	error("EXPRESSION", current());
	return;
      }
      AST::NodeExpressions* exprs = new AST::NodeExpressions();
      node->setExprs(exprs);
      construct(exprs);
    }
  }

  /*!
  ** When reaching: id =, id (, begin, if, while, return, print, read
  **
  ** Create all necessary nodes own by instruction node.
  **
  ** @param node The instruction node
  */
  void
  CreateAST::construct(AST::NodeInstr* node)
  {
    assert(node);
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isInstr(current()));
    node->setLine(current().getLine());

    // Check if it's an affectation or a callfunc,
    // ie if there is an id and no builtins
    if (isId(current()) &&
	!isPrint(current()) && !isRead(current()))
    {
      if (!checkNextValid())
	return;

      // So, it's an affectation
      if (isEqual(next()))
      {
	AST::NodeAffect* aff = new AST::NodeAffect();
	node->setAffect(aff);
	construct(aff);
	if (!checkValid())
	  return;

	// Check for remaining ;
	if (!isSemiColon(current()))
	{
	  error(cfg[";"], current());
	  return;
	}

	// Skip ; token
	nextToken();
	return;
      }

      // So, it's in a call func
      if (isLeftBracket(next()))
      {
	AST::NodeCallFunc* call = new AST::NodeCallFunc();
	node->setCallFunc(call);
	construct(call);
	if (!checkValid())
	  return;

	// Check for remaining ;
	if (!isSemiColon(current()))
	{
	  error(cfg[";"], current());
	  return;
	}

	// Skip ; token
	nextToken();
	return;
      }

      // We reached this line, only if there is no valid instruction
      // in the next token
      error(cfg["="] + " or " + cfg["("], next());
      nextToken();
      return;
    }

    // Check if it's a compound instruction, ie begin keywords
    if (isCompoundInstr(current()))
    {
      AST::NodeCompoundInstr* compoundInstr = new AST::NodeCompoundInstr();
      node->setCompoundInstr(compoundInstr);
      construct(compoundInstr);
      return;
    }

    // Check if it's a return instruction, ie return keywords
    if (isReturn(current()))
    {
      AST::NodeReturn* ret = new AST::NodeReturn();
      node->setReturn(ret);
      construct(ret);
      if (!checkValid())
	return;

      // Check for remaining ;
      if (!isSemiColon(current()))
      {
	error(cfg[";"], current());
	return;
      }

      // Skip ; token
      nextToken();
      return;
    }

    // Check if it's a return instruction, ie return keywords
    if (isExit(current()))
    {
      AST::NodeExit* ret = new AST::NodeExit();
      node->setExit(ret);
      construct(ret);
      if (!checkValid())
	return;

      // Check for remaining ;
      if (!isSemiColon(current()))
      {
	error(cfg[";"], current());
	return;
      }

      // Skip ; token
      nextToken();
      return;
    }

    // Check if it's a print builtin instruction, ie print keywords
    if (isPrint(current()))
    {
      AST::NodePrint* print = new AST::NodePrint();
      node->setPrint(print);
      construct(print);
      if (!checkValid())
	return;

      // Check for remaining ;
      if (!isSemiColon(current()))
      {
	error(cfg[";"], current());
	return;
      }

      // Skip ; token
      nextToken();
      return;
    }

    // Check if it's a read builtin instruction, ie read keywords
    if (isRead(current()))
    {
      AST::NodeRead* read = new AST::NodeRead();
      node->setRead(read);
      construct(read);
      if (!checkValid())
	return;

      // Check for remaining ;
      if (!isSemiColon(current()))
      {
	error(cfg[";"], current());
	return;
      }

      // Skip ; token
      nextToken();
      return;
    }

    // Check if it's an if instruction, ie if keywords
    if (isIf(current()))
    {
      AST::NodeIf* nIf = new AST::NodeIf();
      node->setIf(nIf);
      construct(nIf);
      return;
    }

    // Check if it's a while instruction, ie while keywords
    if (isWhile(current()))
    {
      AST::NodeWhile* nWhile = new AST::NodeWhile();
      node->setWhile(nWhile);
      construct(nWhile);
      return;
    }

    // We reached this line, only if there is no valid instruction
    error("INSTRUCTION", current());
  }

  /*!
  ** Create all necessary nodes own by compound instruction node.
  **
  ** @param node The instruction node
  */
  void
  CreateAST::construct(AST::NodeCompoundInstr* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isCompoundInstr(current()));
    node->setLine(current().getLine());

    // Get rid of the begin token
    nextToken();
    if (!checkValid())
      return;

    if (isEnd(current()))
    {
      nextToken();
      return;
    }

    // Check that it is an instruction
    if (!isInstrs(current()))
    {
      error("INSTRUCTION", current());
      return;
    }

    AST::NodeInstrs* instrs = new AST::NodeInstrs();
    node->setInstrs(instrs);
    construct(instrs);
    if (!checkValid())
      return;

    if (!isEnd(current()))
      error(cfg["end"], current());
    nextToken();
  }

  /*!
  ** When reaching:  id, id (, value, string, (
  **
  ** Create all necessary nodes own by factor node.
  **
  ** @param node The factor node
  */
  void
  CreateAST::construct(AST::NodeFactor* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(isFactor(current()));
    assert(valid());
    node->setLine(current().getLine());

    // Check if there is an ID
    if (isId(current()))
    {
      // Check if it's a call func
      if (nextValid() && isLeftBracket(next()))
      {
	AST::NodeCallFunc* call = new AST::NodeCallFunc();
	node->setCallFunc(call);
	construct(call);
	return;
      }
      // So it's a simple id
      AST::NodeId* id = new AST::NodeId();
      node->setId(id);
      construct(id);
      return;
    }

    // Check if it's a number
    if (isValue(current()))
    {
      AST::NodeNumber* num = new AST::NodeNumber();
      node->setNumber(num);
      construct(num);
      return;
    }

    // Check if it's a string expression
    if (isStringExpr(current()))
    {
      AST::NodeStringExpr* str = new AST::NodeStringExpr();
      node->setStringExpr(str);
      construct(str);
      return;
    }

    // Check if it's a boolean
    if (isBoolean(current()))
    {
      AST::NodeBoolean* boolExpr = new AST::NodeBoolean();
      node->setBool(boolExpr);
      construct(boolExpr);
      return;
    }

    // Check if it's an expression
    if (isLeftBracket(current()))
    {
      nextToken();
      if (!checkValid())
	return;
      AST::NodeExpression* expr = new AST::NodeExpression();
      node->setExpression(expr);
      construct(expr);
      if (!checkValid())
	return;

      // Check for end of the expression, ie )
      if (!isRightBracket(current()))
      {
	error(cfg[")"], current());
	return;
      }
      nextToken();
      return;
    }

    // It's not a valid Factor
    error("ID, VALUE, STRING or " + cfg["("], current());
  }

  /*!
  ** When reaching: id, begin, if, while, return, print, read
  **
  ** Create all necessary nodes own by instructions node.
  **
  ** @param node The instructions node
  */
  void
  CreateAST::construct(AST::NodeInstrs* node)
  {
    assert(node);
    assert(isInstrs(current()));
    assert(valid());
    node->setLine(current().getLine());

    AST::NodeInstr* instr = new AST::NodeInstr();
    node->setInstr(instr);
    construct(instr);

    // Check if instructions remains
    if (valid() && isInstrs(current()))
    {
      AST::NodeInstrs* instrs = new AST::NodeInstrs();
      node->setInstrs(instrs);
      construct(instrs);
      return;
    }
  }

  /*!
  ** Create all necessary nodes own by type node.
  **
  ** @param node The type node
  */
  void
  CreateAST::construct(AST::NodeType* node)
  {
    assert(node);
    assert(valid());
    assert(isType(current()));
    node->setLine(current().getLine());
    node->setType(current().getText());
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by function node.
  **
  ** @param node The function node
  */
  void
  CreateAST::construct(AST::NodeFunction* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isFunction(current()));
    node->setLine(current().getLine());

    // Launch header func
    AST::NodeHeaderFunc* header = new AST::NodeHeaderFunc();
    node->setHeaderFunc(header);
    construct(header);
    if (!checkValid())
      return;

    // Not mandatory declarations
    if (isVar(current()))
    {
      AST::NodeDeclarations* decls = new AST::NodeDeclarations();
      node->setDeclarations(decls);
      construct(decls);
      if (!checkValid())
	return;
    }

    // Check for compound expression, ie begin keywords
    if (!isBegin(current()))
    {
      error(cfg["begin"], current());
      return;
    }
    AST::NodeCompoundInstr* instr = new AST::NodeCompoundInstr();
    node->setCompoundInstr(instr);
    construct(instr);
  }

  /*!
  ** Create all necessary nodes own by while node.
  **
  ** @param node The while node
  */
  void
  CreateAST::construct(AST::NodeWhile* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isWhile(current()));
    node->setLine(current().getLine());

    // Get rid of while token
    nextToken();
    if (!checkValid())
      return;

    // Check for cond expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setCond(expr);
    construct(expr);
    if (!checkValid())
      return;

    // Check for do token
    if (!isDo(current()))
    {
      error(cfg["do"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for body expression
    AST::NodeCompoundInstr* body = new AST::NodeCompoundInstr();
    node->setBodyExprs(body);
    construct(body);
  }

  /*!
  ** Create all necessary nodes own by declaration body node.
  **
  ** @param node The declaration body node
  */
  void
  CreateAST::construct(AST::NodeDeclarationBody* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isDeclarationBody(current()));
    node->setLine(current().getLine());

    AST::NodeIds* ids = new AST::NodeIds();
    node->setIds(ids);
    construct(ids);

    if (!checkValid())
      return;
    if (!isColon(current()))
    {
      error(cfg[":"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    if (!isType(current()))
    {
      error("TYPE", current());
      return;
    }
    AST::NodeType* type = new AST::NodeType();
    node->setType(type);
    construct(type);
  }

  /*!
  ** Create all necessary nodes own by functions node.
  **
  ** @param node The functions node
  */
  void
  CreateAST::construct(AST::NodeFunctions* node)
  {
    assert(node);
    assert(valid());
    assert(isFunctions(current()));
    node->setLine(current().getLine());

    AST::NodeFunction* func = new AST::NodeFunction();
    node->setFunc(func);
    construct(func);

    // Search if function remains
    if (valid() && isFunctions(current()))
    {
      AST::NodeFunctions* funcs = new AST::NodeFunctions();
      node->setFuncs(funcs);
      construct(funcs);
    }
  }

  /*!
  ** Create all necessary nodes own by number node.
  **
  ** @param node The number node
  */
  void
  CreateAST::construct(AST::NodeNumber* node)
  {
    assert(valid());
    assert(isValue(current()));
    node->setLine(current().getLine());

    int i = 0;
    assert(Utils::fromString<int> (i, current().getText()));
    Utils::fromString<int> (i, current().getText());
    node->setNumber(i);
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by declaration node.
  **
  ** @param node The declaration node
  */
  void
  CreateAST::construct(AST::NodeDeclaration* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isDeclaration(current()));
    node->setLine(current().getLine());

    nextToken();
    if (!checkValid())
      return;

    if (!isId(current()))
    {
      error("ID", current());
      return;
    }

    AST::NodeDeclarationBody* bodyDecl = new AST::NodeDeclarationBody();
    node->setBody(bodyDecl);
    construct(bodyDecl);
    if (!checkValid())
      return;

    // Search for ;
    if (!isSemiColon(current()))
    {
      error(cfg[";"], current());
      return;
    }
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by header function node.
  **
  ** @param node The header function node
  */
  void
  CreateAST::construct(AST::NodeHeaderFunc* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isHeaderFunc(current()));
    node->setLine(current().getLine());

    nextToken();
    if (!checkValid())
      return;

    // Check for id
    if (!isId(current()))
    {
      error("ID", current());
      return;
    }

    AST::NodeIdFunc* id = new AST::NodeIdFunc();
    node->setId(id);
    construct(id);
    if (!checkValid())
      return;

    // Check for (
    if (!isLeftBracket(current()))
    {
      error(cfg["("], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for arguments
    if (isArguments(current()))
    {
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
      if (!checkValid())
	return;
    }
    // Check for )
    if (!isRightBracket(current()))
    {
      error(cfg[")"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check for :
    if (!isColon(current()))
    {
      error(cfg[":"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Check type
    AST::NodeType* type = new AST::NodeType();
    node->setType(type);
    construct(type);
    if (!checkValid())
      return;

    // Check for ;
    if (!isSemiColon(current()))
    {
      error(";", current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;
  }

  /*!
  ** Create all necessary nodes own by declarations node.
  **
  ** @param node The declarations node
  */
  void
  CreateAST::construct(AST::NodeDeclarations* node)
  {
    assert(node);
    assert(valid());
    assert(isDeclarations(current()));
    node->setLine(current().getLine());

    AST::NodeDeclaration* decl = new AST::NodeDeclaration();
    node->setDeclaration(decl);
    construct(decl);

    if (!valid())
      return;
    if (isVar(current()))
    {
      AST::NodeDeclarations* decls = new AST::NodeDeclarations();
      node->setDeclarations(decls);
      construct(decls);
    }
  }

  /*!
  ** Create all necessary nodes own by id node.
  **
  ** @param node The id node
  */
  void
  CreateAST::construct(AST::NodeId* node)
  {
    assert(node);
    assert(valid());
    assert(isId(current()));
    node->setLine(current().getLine());
    node->setId(current().getText());
    nextToken();
  }

  /*!
  ** Create all necessary nodes own by id function node.
  **
  ** @param node The id function node
  */
  void
  CreateAST::construct(AST::NodeIdFunc* node)
  {
    assert(node);
    assert(valid());
    assert(isId(current()));
    node->setId(current().getText());
    node->setLine(current().getLine());

    // Check if function has not a builtin name
    Configuration& cfg = Configuration::getInstance();
    if (current().getText() == cfg["print"] ||
	current().getText() == cfg["read"])
    {
      _errors.addError(Error::PARSER,
		       "A function must not be name like a builtin",
		       current().getLine());
    }

    nextToken();
  }

  /*!
  ** Create all necessary nodes own by print node.
  **
  ** @param node The print node
  */
  void
  CreateAST::construct(AST::NodePrint* node)
  {
    assert(node);
    Configuration& cfg = Configuration::getInstance();
    assert(valid());
    assert(isPrint(current()));
    node->setLine(current().getLine());

    // Get rid of print token
    nextToken();
    if (!checkValid())
      return;

    // Let's test is there is a (
    if (!isLeftBracket(current()))
    {
      error(cfg["("], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

    // Ok, so now check if there is an expression
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
    if (!checkValid())
      return;

    // Finally, test if there is a )
    if (!isRightBracket(current()))
    {
      error(cfg[")"], current());
      return;
    }
    nextToken();
    if (!checkValid())
      return;

  }

  /*!
  ** Get all errors.
  **
  ** @return The errors
  */
  const ErrorHandler&
  CreateAST::getErrors() const
  {
    return _errors;
  }
}
