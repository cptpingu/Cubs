#include <cassert>
#include <iostream>
#include <stdexcept>
#include "Compiler.hh"
#include "PrettyPrinterVisitor.hh"
#include "GenerateAST.hh"
#include "BinderVisitor.hh"
#include "BindingPrinterVisitor.hh"
#include "TypeCheckingPrinterVisitor.hh"
#include "GenerateDotASTVisitor.hh"
#include "ConvertToCppVisitor.hh"
#include "ASMGeneratorVisitor.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the compiler for a given file.
  **
  ** @param fileName The name of the file to proceed
  */
  Compiler::Compiler(const std::string& fileName)
    : _fileName(fileName), _lexer(0), _parser(0),
      _binder(0), _typeChecker(0), _execution(0),
      _option('x'), _returnValue(0)
  {
  }

  /*!
  ** Destruct the compiler.
  */
  Compiler::~Compiler()
  {
    delete _lexer;
    delete _parser;
    delete _binder;
    delete _typeChecker;
    delete _execution;
  }

  /*!
  ** Set an option.
  **
  ** @param option The option
  */
  void
  Compiler::setOption(const unsigned char option)
  {
    _option = option;
  }

  /*!
  ** Launch lexing of the given file.
  **
  ** @param fileName The name of the file
  */
  void
  Compiler::lexFile(const std::string& fileName)
  {
    std::stringstream buffer;
    std::ifstream file(fileName.c_str());

    if (!file)
      throw std::exception();

    buffer << file.rdbuf();
    file.close();

    _lexer = new Lexer(buffer);
  }

  /*!
  ** Display all lexed symbol in the given stream.
  ** Lexer must be correct.
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::displayLexedSymbols(std::ostream& o)
  {
    assert(_lexer);
    o << *_lexer;
  }

  /*!
  ** Display the syntax tree in the given stream.
  ** Parser must be correct.
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::displaySyntaxTree(std::ostream& o)
  {
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    PrettyPrinterVisitor visitor;
    visitor.visit(tree);
    o << visitor;
  }

  /*!
  ** Launch parsing of the symbol table.
  ** Lexer must be correct.
  */
  void
  Compiler::parseFile()
  {
    assert(_lexer);
    _parser = new Parser(*_lexer);
    _parser->construct();
  }

  /*!
  ** Launch grammar generation.
  */
  void
  Compiler::generateGrammar(std::ostream& o) const
  {
    AST::NodeProgram* generatedGrammar = new AST::NodeProgram();
    GenerateAST grammar;
    grammar.construct(generatedGrammar);
    PrettyPrinterVisitor visitor;
    visitor.visit(generatedGrammar);
    o << visitor;
  }

  /*!
  ** Launch the binder.
  ** Parser must be correct.
  */
  void
  Compiler::bind()
  {
    assert(_parser);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    _binder = new Binder();
    _binder->bind(tree);
  }

  /*!
  ** Launch the type checker.
  ** Binder must be correct.
  */
  void
  Compiler::typeCheck()
  {
    assert(_parser);
    assert(_binder);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    _typeChecker = new TypeChecker();
    _typeChecker->checkTypes(tree);
  }

  /*!
  ** Launch the execution.
  ** Type checker must be correct.
  **
  ** @return 0 if no errors occured, else a different value.
  */
  int
  Compiler::execution()
  {
    assert(_parser);
    assert(_binder);
    assert(_typeChecker);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);

    _execution = new Execution();
    _execution->activeVerbose(viewExecution());
    return _execution->execute(tree);
  }

  /*!
  ** Launch the execution in debug mode.
  ** Type checker must be correct.
  **
  ** @return 0 if no errors occured, else a different value.
  */
  int
  Compiler::debugging()
  {
    assert(_parser);
    assert(_binder);
    assert(_typeChecker);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);

    _execution = new Execution();
    _execution->activeVerbose(viewDebug());
    return _execution->debug(tree);
  }

  /*!
  ** Display the AST with bind information.
  ** Parser and binder must exists, and parser must be correct.
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::displayBinding(std::ostream& o)
  {
    assert(_parser);
    assert(_binder);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    BindingPrinterVisitor printer;
    printer.visit(tree);
    o << printer;
  }

  /*!
  ** Display the AST with type information.
  ** Parser, binder and type checker must exists,
  ** and parser must be correct.
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::displayTypeChecking(std::ostream& o)
  {
    assert(_parser);
    assert(_binder);
    assert(_typeChecker);
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    TypeCheckingPrinterVisitor printer;
    printer.visit(tree);
    o << printer;
  }

  /*!
  ** Convert parsed grammar to cpp
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::convertToCpp(std::ostream& o)
  {
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    ConvertToCppVisitor visitor;
    visitor.visit(tree);
    o << visitor;
  }

  /*!
  ** Convert parsed grammar to asm
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::convertToASM(std::ostream& o)
  {
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    ASMGeneratorVisitor visitor;
    visitor.printPrelude(launchConvertToASMWithPrelude());
    visitor.visit(tree);
    o << visitor;
  }

  /*!
  ** Generate an AST in dotty format.
  ** You must redirect it in a file, then type:
  ** dot -Tpng file.dot file.png
  **
  ** @param o The stream where to display it
  */
  void
  Compiler::generateDotAST(std::ostream& o)
  {
    AST::NodeProgram* tree = _parser->getSyntaxTree();
    assert(tree);
    GenerateDotASTVisitor visitor;
    visitor.visit(tree);
    o << visitor;
  }

  /*!
  ** Main function of the compiler, launch all needed steps.
  ** Check first if option is valid, then launch wanted step.
  **
  ** @return Error type
  */
  Error::type
  Compiler::execute()
  {
    if (!isValidOption(_option))
      return Error::INVALID_OPTION;

    if (launchLexing() || launchConvertToCpp())
    {
      try
      {
	lexFile(_fileName);
      }
      catch (const std::exception&)
      {
	return Error::FILE_NOT_FOUND;
      }
      if (viewLexer())
	displayLexedSymbols(std::cout);

      if (_lexer->hasErrors())
      {
	_lexer->displayErrors();
	return Error::LEXER;
      }
    }

    if (launchParsing())
    {
      parseFile();
      if (_parser->hasErrors())
      {
	_parser->displayErrors();
	return Error::PARSER;
      }
      else
	if (viewParser())
	  displaySyntaxTree(std::cout);
    }

    if (launchBinding())
    {
      bind();
      if (viewBinder())
	displayBinding(std::cout);
      if (_binder->hasErrors())
      {
	_binder->displayErrors();
	return Error::BINDING;
      }
    }

    if (launchTypeChecking())
    {
      typeCheck();
      if (viewTypeChecker())
	displayTypeChecking(std::cout);
      if (_typeChecker->hasErrors())
      {
	_typeChecker->displayErrors();
	return Error::TYPE_CHECKING;
      }
    }

    if (launchExecution())
    {
      try
      {
	_returnValue = execution();
      }
      catch (const Error::type)
      {
	std::cerr << "A division by zero has occured..." << std::endl;
	return Error::EXECUTION;
      }
    }

    if (launchDebugging())
    {
      try
      {
	_returnValue = debugging();
      }
      catch (const Error::type)
      {
	std::cerr << "A division by zero has occured..." << std::endl;
	return Error::EXECUTION;
      }
    }

    if (launchConvertToCpp())
      convertToCpp(std::cout);

    if (launchGrammarGeneration())
      generateGrammar(std::cout);

    if (launchDotAST())
      generateDotAST(std::cout);

    if (launchConvertToASM())
      convertToASM(std::cout);

    return Error::NONE;
  }
}
