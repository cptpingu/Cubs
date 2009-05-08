#ifndef BINDERVISITOR_HH_
# define BINDERVISITOR_HH_

# include <cassert>
# include "BaseVisitor.hh"
# include "ErrorHandler.hh"
# include "Scope.hh"

namespace MiniCompiler
{
  class BinderVisitor : public NonConstBaseVisitor
  {
    typedef Scope<std::string, AST::NodeId*> ScopeVar;
    typedef Scope<std::string, AST::NodeFunction*> ScopeFunc;

  public:
    BinderVisitor();
    virtual ~BinderVisitor();
    virtual void visit(AST::NodeIds* node);
    virtual void visit(AST::NodeId* node);
    virtual void visit(AST::NodeIdFunc* node);
    virtual void visit(AST::NodeHeaderFunc* node);
    virtual void visit(AST::NodeProgram* node);
    virtual void visit(AST::NodeAffect* node);
    virtual void visit(AST::NodeIf* node);
    virtual void visit(AST::NodeRead* node);
    virtual void visit(AST::NodeArgument* node);
    virtual void visit(AST::NodeArguments* node);
    virtual void visit(AST::NodeReturn* node);
    virtual void visit(AST::NodeExit* node);
    virtual void visit(AST::NodeCallFunc* node);
    virtual void visit(AST::NodeOperation* node);
    virtual void visit(AST::NodeExpression* node);
    virtual void visit(AST::NodeStringExpr* node);
    virtual void visit(AST::NodeBoolean* node);
    virtual void visit(AST::NodeExpressions* node);
    virtual void visit(AST::NodeInstr* node);
    virtual void visit(AST::NodeCompoundInstr* node);
    virtual void visit(AST::NodeFactor* node);
    virtual void visit(AST::NodeInstrs* node);
    virtual void visit(AST::NodeType* node);
    virtual void visit(AST::NodeFunction* node);
    virtual void visit(AST::NodeWhile* node);
    virtual void visit(AST::NodeDeclarationBody* node);
    virtual void visit(AST::NodeFunctions* node);
    virtual void visit(AST::NodeNumber* node);
    virtual void visit(AST::NodeDeclaration* node);
    virtual void visit(AST::NodeDeclarations* node);
    virtual void visit(AST::NodePrint* node);

  private:
    void visitFuncHeader(AST::NodeFunctions* node);

  public:
    const ErrorHandler& getErrors() const;
    void displayVariables(std::ostream& o) const;

  private:
    ScopeVar		_scopeVar;
    ScopeFunc		_scopeFunc;
    ErrorHandler	_errors;
    bool		_isDecl;
    bool		_isArgument;
    AST::NodeFunction*	_currentFunction;
  };
}

#endif /* !BINDERVISITOR_HH_ */
