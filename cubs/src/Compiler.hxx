namespace MiniCompiler
{
  /*!
  ** Check if given option is valid.
  **
  ** @param option The option
  **
  ** @return If given option is valid
  */
  inline bool
  Compiler::isValidOption(const unsigned char option)
  {
    static const unsigned char _OPTIONS[] =
      {
	'l', 'L', // Lexing
	'p', 'P', // Parsing
	'G',      // Grammar generator
	'O',      // AST viewer
	'c', 'C', // Converting to C++
	's', 'S', // Convert to ASM
	'b', 'B', // Binding
	't', 'T', // Type checking
	'x', 'X', // Execution
	'd', 'D', // Debug
	'V',      // Launch and show all
	0
      };
    const unsigned char* tab = _OPTIONS;

    while (*tab)
    {
      if (option == *tab)
	return true;
      tab++;
    }

    return false;
  }

  /*!
  ** Check if lexing has to be launch.
  **
  ** @return if we launch lexing
  */
  inline bool
  Compiler::launchLexing()
  {
    return _option == 'l' || viewLexer() ||
      launchParsing() || launchConvertToCpp() || launchConvertToASM() ||
      launchBinding() || launchTypeChecking() || launchDotAST() ||
      launchExecution() || launchDebugging() || launchAll();
  }

  /*!
  ** Check if parsing has to be launch.
  **
  ** @return if we launch parsing
  */
  inline bool
  Compiler::launchParsing()
  {
    return _option == 'p' || viewParser() ||
      launchConvertToCpp() || launchBinding() || launchConvertToASM() ||
      launchTypeChecking() || launchExecution() || launchDotAST() ||
      launchDebugging() || launchAll();
  }

  /*!
  ** Check if binding has to be launch.
  **
  ** @return if we launch binding
  */
  inline bool
  Compiler::launchBinding()
  {
    return _option == 'b' || viewBinder() || launchConvertToASM() ||
      checkBeforeConvertToCpp() || launchTypeChecking() ||
      launchExecution() || launchDebugging() || launchAll();
  }

  /*!
  ** Check if type checking has to be launch.
  **
  ** @return if we launch type checking
  */
  inline bool
  Compiler::launchTypeChecking()
  {
    return _option == 't' || viewTypeChecker() ||
      launchExecution() || launchConvertToASM() ||
      checkBeforeConvertToCpp() ||
      launchDebugging() || launchAll();
  }

  /*!
  ** Check if execution has to be launch.
  **
  ** @return if we launch execution
  */
  inline bool
  Compiler::launchExecution()
  {
    return _option == 'x' || viewExecution() ||
      launchAll();
  }

  /*!
  ** Check if debugging has to be launch.
  **
  ** @return if we launch debugging
  */
  inline bool
  Compiler::launchDebugging()
  {
    return _option == 'd' || viewDebug();
  }

  /*!
  ** Check if conversion to C++ has to be launch.
  **
  ** @return if we launch conversion to asm
  */
  inline bool
  Compiler::launchConvertToCpp()
  {
    return _option == 'c' || checkBeforeConvertToCpp();
  }

  /*!
  ** Check if conversion to ASM has to be launch.
  **
  ** @return if we launch conversion to C++
  */
  inline bool
  Compiler::launchConvertToASM()
  {
    return _option == 's' || launchConvertToASMWithPrelude();
  }

  /*!
  ** Check if dot generation has to be launched.
  **
  ** @return if dot generation has to be launched
  */
  inline bool
  Compiler::launchDotAST()
  {
    return _option == 'O';
  }

  /*!
  ** Check if grammar generation has to be launch.
  **
  ** @return if we launch grammar generation
  */
  inline bool
  Compiler::launchGrammarGeneration()
  {
    return viewGrammarGeneration();
  }

  /*!
  ** Check if lexer has to be printed.
  **
  ** @return if we print lexer
  */
  inline bool
  Compiler::viewLexer()
  {
    return _option == 'L' || launchAll();
  }

  /*!
  ** Check if parser has to be printed.
  **
  ** @return if we print parser
  */
  inline bool
  Compiler::viewParser()
  {
    return _option == 'P' || launchAll();
  }

  /*!
  ** Check if binder has to be printed.
  **
  ** @return if we print binder
  */
  inline bool
  Compiler::viewBinder()
  {
    return _option == 'B' || launchAll();
  }

  /*!
  ** Check if type checker has to be printed.
  **
  ** @return if we print type checker
  */
  inline bool
  Compiler::viewTypeChecker()
  {
    return _option == 'T' || launchAll();
  }

  /*!
  ** Check if execution has to be printed.
  **
  ** @return if we print execution
  */
  inline bool
  Compiler::viewExecution()
  {
    return _option == 'X' || launchAll();
  }

  /*!
  ** Check if debugger has to be printed.
  **
  ** @return if we print debugger
  */
  inline bool
  Compiler::viewDebug()
  {
    return _option == 'D';
  }

  /*!
  ** Check if code has to be validate before converting to C++.
  **
  ** @return if we validate code before converting to C++
  */
  inline bool
  Compiler::checkBeforeConvertToCpp()
  {
    return _option == 'C';
  }

  /*!
  ** Check if we also print prelude
  **
  ** @return if we also print prelude when generating asm
  */
  inline bool
  Compiler::launchConvertToASMWithPrelude()
  {
    return _option == 'S';
  }

  /*!
  ** Check if generated grammar has to be printed.
  **
  ** @return if we print generated grammar
  */
  inline bool
  Compiler::viewGrammarGeneration()
  {
    return _option == 'G';
  }

  /*!
  ** Check if we launch everything
  **
  ** @return if everything has to be launched
  */
  inline bool
  Compiler::launchAll()
  {
    return _option == 'V';
  }

  /*!
  ** Get the return value.
  **
  ** @return The return value
  */
  inline int
  Compiler::getReturnValue() const
  {
    return _returnValue;
  }
}
