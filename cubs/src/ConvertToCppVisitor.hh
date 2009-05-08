#ifndef CONVERTTOCPPVISITOR_HH_
# define CONVERTTOCPPVISITOR_HH_

# include <iomanip>
# include <sstream>
# include "PrettyPrinterVisitor.hh"

namespace MiniCompiler
{
  class ConvertToCppVisitor : public PrettyPrinterVisitor
  {
    friend std::ostream&
    operator<<(std::ostream& o, const ConvertToCppVisitor& v);

  public:
    ConvertToCppVisitor();
    virtual ~ConvertToCppVisitor();

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

  private:
    void visitFuncHeader(const AST::NodeFunctions* node);
  };
}

#endif /* !CONVERTTOCPPVISITOR_HH_ */
