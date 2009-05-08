#ifndef COMPILER_HH_
# define COMPILER_HH_

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include "Error.hh"
# include "Lexer.hh"
# include "Parser.hh"
# include "Binder.hh"
# include "TypeChecker.hh"
# include "Execution.hh"

namespace MiniCompiler
{
  class Compiler
  {
  public:
    Compiler(const std::string& fileName);
    ~Compiler();

  public:
    Error::type execute();
    void setOption(const unsigned char option);
    void displayLexedSymbols(std::ostream& o);
    void displaySyntaxTree(std::ostream& o);
    void displayBinding(std::ostream& o);
    void displayTypeChecking(std::ostream& o);
    void convertToCpp(std::ostream& o);
    void convertToASM(std::ostream& o);
    void generateDotAST(std::ostream& o);
    void generateGrammar(std::ostream& o) const;

  public:
    void lexFile(const std::string& fileName);
    void parseFile();
    void bind();
    void typeCheck();
    int execution();
    int debugging();

  private:
    static bool isValidOption(const unsigned char option);
    bool launchLexing();
    bool launchParsing();
    bool launchBinding();
    bool launchTypeChecking();
    bool launchExecution();
    bool launchDebugging();
    bool launchConvertToCpp();
    bool launchConvertToASM();
    bool launchGrammarGeneration();
    bool launchDotAST();
    bool viewLexer();
    bool viewParser();
    bool viewBinder();
    bool viewTypeChecker();
    bool viewExecution();
    bool viewDebug();
    bool checkBeforeConvertToCpp();
    bool launchConvertToASMWithPrelude();
    bool viewGrammarGeneration();
    bool launchAll();

  public:
    int getReturnValue() const;

  private:
    const std::string	_fileName;
    Lexer*		_lexer;
    Parser*		_parser;
    Binder*		_binder;
    TypeChecker*	_typeChecker;
    Execution*		_execution;
    unsigned char	_option;
    int			_returnValue;
  };
}

# include "Compiler.hxx"

#endif /* !COMPILER_HH_ */
