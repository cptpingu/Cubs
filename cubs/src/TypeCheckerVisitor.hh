#ifndef TYPECHECKERVISITOR_HH_
# define TYPECHECKERVISITOR_HH_

# include <cassert>
# include "Utils.hh"
# include "BaseVisitor.hh"
# include "ErrorHandler.hh"

namespace MiniCompiler
{
  class TypeCheckerVisitor : public NonConstBaseVisitor
  {
  public:
    TypeCheckerVisitor();
    virtual ~TypeCheckerVisitor();
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
    void typeMismatch(const AST::TypedNode* ref,
		      const AST::TypedNode* current);
    void visitFuncHeader(AST::NodeFunctions* node);

  public:
    const ErrorHandler& getErrors() const;

  private:
    ErrorHandler	_errors;
    AST::Type::type	_type;
  };
}

#endif /* !TYPECHECKERVISITOR_HH_ */
