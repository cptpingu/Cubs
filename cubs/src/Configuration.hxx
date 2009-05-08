namespace MiniCompiler
{
  inline
  Configuration::Configuration()
  {
    // Misc
    _keyWords["undefined"] = "undefined";

    // KeyWords
    _keyWords["function"] = "function";
    _keyWords["return"] = "return";
    _keyWords["exit"] = "exit";
    _keyWords["var"] = "var";
    _keyWords["if"] = "if";
    _keyWords["then"] = "then";
    _keyWords["else"] = "else";
    _keyWords["while"] = "while";
    _keyWords["do"] = "do";
    _keyWords["begin"] = "begin";
    _keyWords["end"] = "end";

    // Types
    _keyWords["int"] = "integer";
    _keyWords["string"] = "string";
    _keyWords["bool"] = "boolean";

    // Operator
    _keyWords["+"] = "+";
    _keyWords["/"] = "/";
    _keyWords["-"] = "-";
    _keyWords["*"] = "*";
    _keyWords["%"] = "%";
    _keyWords["!"] = "!";

    // Symbol
    _keyWords["("] = "(";
    _keyWords[")"] = ")";
    _keyWords["="] = "=";
    _keyWords[","] = ",";
    _keyWords[";"] = ";";
    _keyWords[":"] = ":";

    // Comparator
    _keyWords[">"] = ">";
    _keyWords["<"] = "<";
    _keyWords["=="] = _keyWords["="] + _keyWords["="];
    _keyWords[">="] = _keyWords[">"] + _keyWords["="];
    _keyWords["<="] = _keyWords["<"] + _keyWords["="];
    _keyWords["!="] = _keyWords["!"] + _keyWords["="];

    // Boolean
    _keyWords["true"] = "true";
    _keyWords["false"] = "false";

    // Comments
    _keyWords["Comment"] = "//";
    _keyWords["#"] = "#";

    // String expression
    _keyWords["str"] = "\"";

    // Builtins
    _keyWords["print"] = "print";
    _keyWords["read"] = "read";
  }

  inline
  Configuration::~Configuration()
  {
  }
}
