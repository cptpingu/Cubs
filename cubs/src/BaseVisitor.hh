#ifndef BASEVISITOR_HH_
# define BASEVISITOR_HH_

# include "IVisitor.hh"

namespace MiniCompiler
{
  template <template <typename T> class ConstifyTrait>
  class BaseVisitor : public IVisitor<ConstifyTrait>
  {
  protected:
    static const unsigned int INDENT_SIZE = 1;
    static const unsigned char SPACING_CHAR = '\t';

  public:
    BaseVisitor();
    virtual ~BaseVisitor();
    virtual void visit(typename ConstifyTrait<AST::NodeIds>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeProgram>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeAffect>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeIf>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeRead>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeArgument>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeArguments>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeReturn>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeExit>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeCallFunc>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeOperation>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeExpression>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeStringExpr>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeBoolean>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeExpressions>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeInstr>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeCompoundInstr>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeFactor>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeInstrs>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeType>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeFunction>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeWhile>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeDeclarationBody>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeFunctions>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeNumber>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeDeclaration>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeHeaderFunc>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeDeclarations>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeId>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodeIdFunc>::ptr node);
    virtual void visit(typename ConstifyTrait<AST::NodePrint>::ptr node);
  };

  typedef BaseVisitor<Traits::Identity> NonConstBaseVisitor;
  typedef BaseVisitor<Traits::Const> ConstBaseVisitor;
}

# include "BaseVisitor.hxx"

#endif /* !BASEVISITOR_HH_ */
