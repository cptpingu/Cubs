#ifndef ASMGENERATORVISITOR_HH_
# define ASMGENERATORVISITOR_HH_

# include <iomanip>
# include <sstream>
# include <map>
# include <utility>
# include "Scope.hh"
# include "PrettyPrinterVisitor.hh"

namespace MiniCompiler
{
  class ASMGeneratorVisitor : public PrettyPrinterVisitor
  {
    friend std::ostream&
    operator<<(std::ostream& o, const ASMGeneratorVisitor& v);

    typedef Scope<std::string, std::pair<std::string, AST::Type::type>*> ScopeVar;
    typedef std::map<std::string, std::string> ROStrings;

    static const unsigned int LOCAL_VAR_SIZE = 4;

  public:
    ASMGeneratorVisitor();
    virtual ~ASMGeneratorVisitor();
    void printPrelude(bool hasToBePrint);
    void initVariables();

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
    void writeHeader();
    void writePrelude();
    void writePostlude();
    bool declaringGlobalVar() const;

  protected:
    ScopeVar		_scope;
    ROStrings		_strings;
    bool		_printPrelude;
    unsigned int	_stackShifting;
  };
}

# include "ASMGeneratorVisitor.hxx"

#endif /* !ASMGENERATORVISITOR_HH_ */
