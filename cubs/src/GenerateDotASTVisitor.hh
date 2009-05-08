#ifndef GENERATEDOTASTVISITOR_HH_
# define GENERATEDOTASTVISITOR_HH_

# include <iomanip>
# include <sstream>
# include "BaseVisitor.hh"

namespace MiniCompiler
{
  namespace NodeName
  {
    static const std::string PROGRAM		= "Program";
    static const std::string IDS		= "Ids";
    static const std::string AFFECT		= "Affect";
    static const std::string IF			= "If";
    static const std::string READ		= "Read";
    static const std::string ARGUMENT		= "Argument";
    static const std::string ARGUMENTS		= "Arguments";
    static const std::string RETURN		= "Return";
    static const std::string EXIT		= "Exit";
    static const std::string CALLFUNC		= "CallFunc";
    static const std::string OPERATION		= "Operation";
    static const std::string EXPRESSION		= "Expression";
    static const std::string STRINGEXPR		= "StringExpression";
    static const std::string BOOLEAN		= "Boolean";
    static const std::string EXPRESSIONS	= "Expressions";
    static const std::string INSTR		= "Instr";
    static const std::string COMPOUNDINSTR	= "CompoundInstr";
    static const std::string FACTOR		= "Factor";
    static const std::string INSTRS		= "Instrs";
    static const std::string TYPE		= "Type";
    static const std::string FUNCTION		= "Function";
    static const std::string WHILE		= "While";
    static const std::string DECLARATIONBODY	= "DeclarationBody";
    static const std::string FUNCTIONS		= "Functions";
    static const std::string NUMBER		= "Number";
    static const std::string DECLARATION	= "Declaration";
    static const std::string HEADERFUNC		= "HeaderFunc";
    static const std::string DECLARATIONS	= "Declarations";
    static const std::string ID			= "Id";
    static const std::string IDFUNC		= "IdFunc";
    static const std::string PRINT		= "Print";

    namespace Option
    {
      static const std::string DEFAULT		= "color=\"0.650 0.700 0.700\",";
      static const std::string STRINGEXPR	= "color=\"green\",";
      static const std::string BOOLEAN		= "color=\"thistle2\",";
      static const std::string NUMBER		= "color=\"goldenrod3\",";
      static const std::string ID		= "color=\"red\",";
      static const std::string IDFUNC		= "color=\"orange\",";
      static const std::string OPERATION	= "color=\"yellow\",";
      static const std::string OPERATION_EMPTY	= "color=\"yellowGreen\",";
    }
  }

  class GenerateDotASTVisitor : public ConstBaseVisitor
  {
    friend std::ostream&
    operator<<(std::ostream& o, const GenerateDotASTVisitor& v);

  public:
    GenerateDotASTVisitor();
    virtual ~GenerateDotASTVisitor();

  public:
    virtual void visit(const AST::NodeIds* node);
    virtual void visit(const AST::NodeProgram* node);
    virtual void visit(const AST::NodeAffect* node);
    virtual void visit(const AST::NodeIf* node);
    virtual void visit(const AST::NodeRead* node);
    virtual void visit(const AST::NodeArgument* node);
    virtual void visit(const AST::NodeArguments* node);
    virtual void visit(const AST::NodeReturn* node);
    virtual void visit(const AST::NodeExit* node);
    virtual void visit(const AST::NodeCallFunc* node);
    virtual void visit(const AST::NodeOperation* node);
    virtual void visit(const AST::NodeExpression* node);
    virtual void visit(const AST::NodeStringExpr* node);
    virtual void visit(const AST::NodeBoolean* node);
    virtual void visit(const AST::NodeExpressions* node);
    virtual void visit(const AST::NodeInstr* node);
    virtual void visit(const AST::NodeCompoundInstr* node);
    virtual void visit(const AST::NodeFactor* node);
    virtual void visit(const AST::NodeInstrs* node);
    virtual void visit(const AST::NodeType* node);
    virtual void visit(const AST::NodeFunction* node);
    virtual void visit(const AST::NodeWhile* node);
    virtual void visit(const AST::NodeDeclarationBody* node);
    virtual void visit(const AST::NodeFunctions* node);
    virtual void visit(const AST::NodeNumber* node);
    virtual void visit(const AST::NodeDeclaration* node);
    virtual void visit(const AST::NodeHeaderFunc* node);
    virtual void visit(const AST::NodeDeclarations* node);
    virtual void visit(const AST::NodeId* node);
    virtual void visit(const AST::NodeIdFunc* node);
    virtual void visit(const AST::NodePrint* node);

  protected:
    void print(std::ostream& o) const;
    void declareNode(const std::string& nodeName,
		     const std::string& labelName,
		     const std::string& style);
    void declareNode(const std::string& nodeName,
		     const std::string& labelName);
    void linkNode(const std::string& nodeName,
		  const std::string& rootName,
		  const std::string& style);
    void linkNode(const std::string& nodeName,
		  const std::string& rootName);

  protected:
    std::string		_rootName;
    std::stringstream	_indent;
  };
}

# include "GenerateDotASTVisitor.hxx"

#endif /* !GENERATEDOTASTVISITOR_HH_ */
