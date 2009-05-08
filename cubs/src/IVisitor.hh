#ifndef IVISITOR_HH_
# define IVISITOR_HH_

# include "Traits.hh"

namespace MiniCompiler
{
  class IVisitable;
  namespace AST
  {
    class NodeIds;
    class NodeProgram;
    class NodeAffect;
    class NodeIf;
    class NodeRead;
    class NodeArgument;
    class NodeArguments;
    class NodeReturn;
    class NodeExit;
    class NodeCallFunc;
    class NodeOperation;
    class NodeExpression;
    class NodeStringExpr;
    class NodeBoolean;
    class NodeExpressions;
    class NodeInstr;
    class NodeCompoundInstr;
    class NodeFactor;
    class NodeInstrs;
    class NodeType;
    class NodeFunction;
    class NodeWhile;
    class NodeDeclarationBody;
    class NodeFunctions;
    class NodeNumber;
    class NodeDeclaration;
    class NodeHeaderFunc;
    class NodeDeclarations;
    class NodeId;
    class NodeIdFunc;
    class NodePrint;
  }

  template < template <typename T> class ConstifyTrait>
  class IVisitor
  {
  public:
    IVisitor() {}
    virtual ~IVisitor() {}
    virtual void visit(typename ConstifyTrait<AST::NodeIds>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeProgram>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeAffect>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeIf>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeRead>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeArgument>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeArguments>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeReturn>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeExit>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeCallFunc>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeOperation>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeExpression>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeStringExpr>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeBoolean>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeExpressions>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeInstr>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeCompoundInstr>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeFactor>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeInstrs>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeType>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeFunction>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeWhile>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeDeclarationBody>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeFunctions>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeNumber>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeDeclaration>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeHeaderFunc>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeDeclarations>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeId>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodeIdFunc>::ptr node) = 0;
    virtual void visit(typename ConstifyTrait<AST::NodePrint>::ptr node) = 0;
  };

  typedef IVisitor<Traits::Identity> Visitor;
  typedef IVisitor<Traits::Const> ConstVisitor;
}

#endif /* !IVISITOR_HH_ */
