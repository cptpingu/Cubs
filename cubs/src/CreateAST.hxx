namespace MiniCompiler
{
  /*!
  ** Add an error to the error handler.
  **
  ** @param attempted Token attempted
  ** @param symb Token reach
  */
  inline void
  CreateAST::error(std::string attempted,
		   const Symbol& symb)
  {
    _errors.addError(Error::PARSER,
		     "Expected <" + attempted +
		     "> but was <" + symb.getText() + ">",
		     symb.getLine());
  }

  /*!
  ** Go to the next token.
  */
  inline void
  CreateAST::nextToken()
  {
    _pos++;
  }

  /*!
  ** Get the current token.
  **
  ** @return Current symbol
  */
  inline const Symbol&
  CreateAST::current() const
  {
    assert(valid());
    return _lexer[_pos];
  }

  /*!
  ** Get the next token.
  **
  ** @return Next symbol
  */
  inline const Symbol&
  CreateAST::next() const
  {
    assert(valid());
    assert(nextValid());
    return _lexer[_pos + 1];
  }

  /*!
  ** Check if position in the lexer is valid.
  **
  ** @return If current position is valid
  */
  inline bool
  CreateAST::valid() const
  {
    return _pos < _size;
  }

  /*!
  ** Check if next position in the lexer is valid.
  **
  ** @return If next position is valid
  */
  inline bool
  CreateAST::nextValid() const
  {
    return _pos + 1 < _size;
  }

  /*!
  ** Check if current position in the lexer is valid.
  ** If it's invalid, then add an error to the error
  ** handler, filled correctly.
  **
  ** @return If current position is valid
  */
  inline bool
  CreateAST::checkValid()
  {
    if (valid())
      return true;
    _errors.addError(Error::PARSER,
		     "Unexpected end of file",
		     _lexer[_size - 1].getLine());
    return false;
  }

  /*!
  ** Check if next position in the lexer is valid.
  ** If it's invalid, then add an error to the error
  ** handler, filled correctly.
  **
  ** @return If next position is valid
  */
  inline bool
  CreateAST::checkNextValid()
  {
    if (nextValid())
      return true;
    _errors.addError(Error::PARSER,
		     "Unexpected end of file",
		     _lexer[_size - 1].getLine());
    return false;
  }

  /*!
  ** Check if given symbol can be an id.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an id
  */
  inline bool
  CreateAST::isId(const Symbol& symb) const
  {
    return symb.getType() == Symbol::ID;
  }

  /*!
  ** Check if given symbol can be a left bracket.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a left bracket
  */
  inline bool
  CreateAST::isLeftBracket(const Symbol& symb) const
  {
    return symb.getType() == Symbol::LEFT_BRACKET;
  }

  /*!
  ** Check if given symbol can be a right bracket.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a right bracket
  */
  inline bool
  CreateAST::isRightBracket(const Symbol& symb) const
  {
    return symb.getType() == Symbol::RIGHT_BRACKET;
  }

  /*!
  ** Check if given symbol can be a type.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a type
  */
  inline bool
  CreateAST::isType(const Symbol& symb) const
  {
    return symb.getType() == Symbol::TYPE;
  }

  /*!
  ** Check if given symbol can be a keyword.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a keyword
  */
  inline bool
  CreateAST::isKeyword(const Symbol& symb) const
  {
    return symb.getType() == Symbol::KEYWORD;
  }

  /*!
  ** Check if given symbol can be a semi colon.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a semi colon
  */
  inline bool
  CreateAST::isSemiColon(const Symbol& symb) const
  {
    return symb.getType() == Symbol::SEMI_COLON;
  }

  /*!
  ** Check if given symbol can be an operator.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an operator
  */
  inline bool
  CreateAST::isOperator(const Symbol& symb) const
  {
    return symb.getType() == Symbol::OPERATOR ||
      symb.getType() == Symbol::COMPARATOR;
  }

  /*!
  ** Check if given symbol can be a value.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a value
  */
  inline bool
  CreateAST::isValue(const Symbol& symb) const
  {
    return symb.getType() == Symbol::VALUE;
  }

  /*!
  ** Check if given symbol can be a coma.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a coma
  */
  inline bool
  CreateAST::isComa(const Symbol& symb) const
  {
    return symb.getType() == Symbol::COMA;
  }

  /*!
  ** Check if given symbol can be a comparator.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a comparator
  */
  inline bool
  CreateAST::isComparator(const Symbol& symb) const
  {
    return symb.getType() == Symbol::COMPARATOR;
  }

  /*!
  ** Check if given symbol can be a string expression.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a string expression
  */
  inline bool
  CreateAST::isStringExpr(const Symbol& symb) const
  {
    return symb.getType() == Symbol::STRING_EXPR;
  }

  /*!
  ** Check if given symbol can be a boolean.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a boolean
  */
  inline bool
  CreateAST::isBoolean(const Symbol& symb) const
  {
    return symb.getType() == Symbol::BOOLEAN;
  }

  /*!
  ** Check if given symbol can be a colon.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a colon
  */
  inline bool
  CreateAST::isColon(const Symbol& symb) const
  {
    return symb.getType() == Symbol::COLON;
  }

  /*!
  ** Check if given symbol is a call func.
  **
  ** @param rSymb First symbol
  ** @param lSymb Second symbol
  **
  ** @return If given symbol is a call func
  */
  inline bool
  CreateAST::isCallFunc(const Symbol& rSymb,
			const Symbol& lSymb) const
  {
    return isId(rSymb) && isLeftBracket(lSymb);
  }

  /*!
  ** Check if given symbol can be an ids
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an ids
  */
  inline bool
  CreateAST::isIds(const Symbol& symb) const
  {
    return isId(symb);
  }

  /*!
  ** Check if given symbol can be an operation
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an operation
  */
  inline bool
  CreateAST::isOperation(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return isFactor(symb) || symb.getText() == cfg["-"] ||
      symb.getText() == cfg["+"];
  }

  /*!
  ** Check if given symbol can be an affectation
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an affectation
  */
  inline bool
  CreateAST::isAffect(const Symbol& symb) const
  {
    return isId(symb);
  }

  /*!
  ** Check if given symbol can be an arguments
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an arguments
  */
  inline bool
  CreateAST::isArguments(const Symbol& symb) const
  {
    return isArgument(symb);
  }

  /*!
  ** Check if given symbol can be an argument.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an argument
  */
  inline bool
  CreateAST::isArgument(const Symbol& symb) const
  {
    return isDeclarationBody(symb);
  }

  /*!
  ** Check if given symbol can be a declaration body.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a declaration body
  */
  inline bool
  CreateAST::isDeclarationBody(const Symbol& symb) const
  {
    return isIds(symb);
  }

  /*!
  ** Check if given symbol may be a call func.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol may be a call func
  */
  inline bool
  CreateAST::isCallFunc(const Symbol& symb) const
  {
    return isId(symb);
  }

  /*!
  ** Check if given symbol can be an expression.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an expression
  */
  inline bool
  CreateAST::isExpression(const Symbol& symb) const
  {
    return isOperation(symb);
  }

  /*!
  ** Check if given symbol can be an expressions.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an expressions
  */
  inline bool
  CreateAST::isExpressions(const Symbol& symb) const
  {
    return isExpression(symb);
  }

  /*!
  ** Check if given symbol can be an instruction.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an instruction
  */
  inline bool
  CreateAST::isInstr(const Symbol& symb) const
  {
    return isId(symb) || isIf(symb) || isRead(symb) ||
      isWhile(symb) || isPrint(symb) || isReturn(symb) ||
      isExit(symb) || isCompoundInstr(symb);
  }

  /*!
  ** Check if given symbol can be an instructions.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an instructions
  */
  inline bool
  CreateAST::isInstrs(const Symbol& symb) const
  {
    return isInstr(symb);
  }

  /*!
  ** Check if given symbol can be a variable.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a variable
  */
  inline bool
  CreateAST::isVar(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["var"];
  }

  /*!
  ** Check if given symbol can be a read.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a read
  */
  inline bool
  CreateAST::isRead(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["read"];
  }

  /*!
  ** Check if given symbol can be a print.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a print
  */
  inline bool
  CreateAST::isPrint(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["print"];
  }

  /*!
  ** Check if given symbol can be a begin.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a begin
  */
  inline bool
  CreateAST::isBegin(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["begin"];
  }

  /*!
  ** Check if given symbol can be a end.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a end
  */
  inline bool
  CreateAST::isEnd(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["end"];
  }

  /*!
  ** Check if given symbol can be a if.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a if
  */
  inline bool
  CreateAST::isIf(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["if"];
  }

  /*!
  ** Check if given symbol can be a then.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a then
  */
  inline bool
  CreateAST::isThen(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["then"];
  }

  /*!
  ** Check if given symbol can be an else.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an else
  */
  inline bool
  CreateAST::isElse(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["else"];
  }

  /*!
  ** Check if given symbol can be a while.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a while
  */
  inline bool
  CreateAST::isWhile(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["while"];
  }

  /*!
  ** Check if given symbol can be a do.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a do
  */
  inline bool
  CreateAST::isDo(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["do"];
  }

  /*!
  ** Check if given symbol can be a declaration.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a declaration
  */
  inline bool
  CreateAST::isDeclaration(const Symbol& symb) const
  {
    return isVar(symb);
  }

  /*!
  ** Check if given symbol can be a declarations.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a declarations
  */
  inline bool
  CreateAST::isDeclarations(const Symbol& symb) const
  {
    return isDeclaration(symb);
  }

  /*!
  ** Check if given symbol can be a functions.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a functions
  */
  inline bool
  CreateAST::isFunctions(const Symbol& symb) const
  {
    return isFunction(symb);
  }

  /*!
  ** Check if given symbol can be a function.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a function
  */
  inline bool
  CreateAST::isFunction(const Symbol& symb) const
  {
    return isHeaderFunc(symb);
  }

  /*!
  ** Check if given symbol can be a function header.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a function header
  */
  inline bool
  CreateAST::isHeaderFunc(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["function"];
  }

  /*!
  ** Check if given symbol can be a compound instruction.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a compound instruction
  */
  inline bool
  CreateAST::isCompoundInstr(const Symbol& symb) const
  {
    return isBegin(symb);
  }

  /*!
  ** Check if given symbol can be a program.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a program
  */
  inline bool
  CreateAST::isProgram(const Symbol& symb) const
  {
    return isDeclarations(symb) || isFunctions(symb) || isCompoundInstr(symb);
  }

  /*!
  ** Check if given symbol can be an equal.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an equal
  */
  inline bool
  CreateAST::isEqual(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["="];
  }

  /*!
  ** Check if given symbol can be a return.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a return
  */
  inline bool
  CreateAST::isReturn(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["return"];
  }

  /*!
  ** Check if given symbol can be an exit.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is an exit
  */
  inline bool
  CreateAST::isExit(const Symbol& symb) const
  {
    Configuration& cfg = Configuration::getInstance();
    return symb.getText() == cfg["exit"];
  }

  /*!
  ** Check if given symbol can be a factor.
  **
  ** @param symb The given symbol
  **
  ** @return If given symbol is a factor
  */
  inline bool
  CreateAST::isFactor(const Symbol& symb) const
  {
    return isId(symb) || isValue(symb) || isBoolean(symb) ||
      isStringExpr(symb) || isLeftBracket(symb);
  }
}
