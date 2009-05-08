#include <iostream>
#include "Utils.hh"
#include "Compiler.hh"
#include "SharedString.hh"

namespace
{
  /*!
  ** Find the maximum value beetween two given arguments.
  **
  ** @param a The first integer
  ** @param b The second integer
  **
  ** @return Greater of two
  */
  inline
  int max(int a, int b)
  {
    if (a > b)
      return a;

    return b;
  }

  /*!
  ** Just display the usage of the program.
  **
  ** @param prog The binary name and path
  **
  ** @return A return value of 42
  */
  int
  usage(const std::string& prog)
  {
    std::cout << "Usage: " << prog << " [-lLpPbBtTxXVGOcCsS] files...\n" << std::nl;
    std::cout << "\tl: Launch lexer" << std::nl;
    std::cout << "\tL: Launch and show lexer" << std::nl;
    std::cout << "\tp: Launch parser" << std::nl;
    std::cout << "\tP: Launch and show parser" << std::nl;
    std::cout << "\tb: Launch binding" << std::nl;
    std::cout << "\tB: Launch and show binding" << std::nl;
    std::cout << "\tt: Launch type checking" << std::nl;
    std::cout << "\tT: Launch and show type checking" << std::nl;
    std::cout << "\tx: Launch execution" << std::nl;
    std::cout << "\tX: Launch and show execution" << std::nl;
    std::cout << "\td: Launch debugging" << std::nl;
    std::cout << "\tD: Launch debugging and show special variables" << std::nl;
    std::cout << "\tV: Launch execution and show all except debugging" << std::nl;
    std::cout << std::nl << "Extra:" << std::nl;
    std::cout << "\tG: Launch and show grammar generator" << std::nl;
    std::cout << "\tO: Launch and show dotty tree generation" << std::nl;
    std::cout << "\tc: Convert to Cpp without checking given code" << std::nl;
    std::cout << "\tC: Convert to Cpp checking given code" << std::nl;
    std::cout << "\ts: Convert to ASM without prelude" << std::nl;
    std::cout << "\tS: Convert to ASM with prelude" << std::nl;

    return 42;
  }

  /*!
  ** Launch execution of a given step for the given file.
  **
  ** @param filename The file to proceed
  ** @param option The step to apply on it
  **
  ** @return 0 if no errors occured, else a different value
  */
  int
  executeFile(const std::string& filename,
	      const char option)
  {
    mystd::SharedString::clear();
    MiniCompiler::Compiler compiler(filename);
    MiniCompiler::Error::type res = MiniCompiler::Error::NONE;

    try
    {
      compiler.setOption(option);
      res = compiler.execute();
      std::cerr << std::nl;
      switch (res)
      {
	case MiniCompiler::Error::NONE:
	  {
	    int ret = compiler.getReturnValue();
	    std::cerr << "Execution succeed with code " << ret << std::nl;
	    return ret;
	  }
	  break;
	case MiniCompiler::Error::INVALID_OPTION:
	  std::cerr << option << " : Invalid option !" << std::nl;
	  break;
	case MiniCompiler::Error::FILE_NOT_FOUND:
	  std::cerr << filename << " : File not found !" << std::nl;
	  break;
	case MiniCompiler::Error::LEXER:
	  std::cerr << "Lexing error !" << std::nl;
	  break;
	case MiniCompiler::Error::PARSER:
	  std::cerr << "Parsing error !" << std::nl;
	  break;
	case MiniCompiler::Error::BINDING:
	  std::cerr << "Binding error !" << std::nl;
	  break;
	case MiniCompiler::Error::TYPE_CHECKING:
	  std::cerr << "Type checking error !" << std::nl;
	  break;
	case MiniCompiler::Error::EXECUTION:
	  std::cerr << "Execution error !" << std::nl;
	  break;
	default:
	  std::cerr << "Unknow error !" << std::nl;
      }
    }
    catch (...)
    {
      std::cerr << "An error occured..." << std::nl;
      res = MiniCompiler::Error::UNKNOW;
    }

    return res;
  }

  /*!
  ** Launch the given file with the given options.
  ** Will launch file many times if there are many options.
  **
  ** @param filename The file to proceed
  ** @param options The steps to apply on it
  **
  ** @return The maximum value founded
  */
  int
  executeFileWithOptions(const std::string& filename,
			 const std::string& options)
  {
    typedef std::string::const_iterator iter;
    int res = 0;
    iter i = options.begin();

    if(*i == '-')
      ++i;
    for (; i != options.end(); ++i)
      res = max(res, executeFile(filename, *i));

    return res;
  }
}

/*!
** The main function of this program.
** Expected a facultativ option and one or many files.
**
** @param argc Number of argument
** @param argv All arguments
**
** @return 0 if no errors, else a different value
*/
int main(int argc, char** argv)
{
  int res = 0;
  int begin = 1;
  std::string options;

  if (argc > 1 && argv[1][0] == '-')
  {
    options = argv[1];
    begin++;
  }

  if (argc > 1 && argv[1][0] != '-')
    options = "x";

  if (begin >= argc)
    return usage(argv[0]);

  for (int i = begin; i < argc; i++)
    res = max(res, executeFileWithOptions(argv[i], options));

  return res;
}
