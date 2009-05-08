#ifndef GENERATEAST_HH_
# define GENERATEAST_HH_

# include <cassert>
# include <cstdlib>
# include "IVisitor.hh"
# include "NodeIds.hh"
# include "NodeProgram.hh"
# include "NodeAffect.hh"
# include "NodeIf.hh"
# include "NodeRead.hh"
# include "NodeArgument.hh"
# include "NodeArguments.hh"
# include "NodeReturn.hh"
# include "NodeExit.hh"
# include "NodeCallFunc.hh"
# include "NodeExpression.hh"
# include "NodeStringExpr.hh"
# include "NodeBoolean.hh"
# include "NodeExpressions.hh"
# include "NodeInstr.hh"
# include "NodeCompoundInstr.hh"
# include "NodeFactor.hh"
# include "NodeInstrs.hh"
# include "NodeOperation.hh"
# include "NodeType.hh"
# include "NodeFunction.hh"
# include "NodeWhile.hh"
# include "NodeDeclarationBody.hh"
# include "NodeFunctions.hh"
# include "NodeNumber.hh"
# include "NodeDeclaration.hh"
# include "NodeHeaderFunc.hh"
# include "NodeDeclarations.hh"
# include "NodeId.hh"
# include "NodeIdFunc.hh"
# include "NodePrint.hh"
# include "Utils.hh"
# include "Configuration.hh"

namespace MiniCompiler
{
  class GenerateAST
  {
  public:
    GenerateAST();
    ~GenerateAST();
    void construct(AST::NodeIds* node);
    void construct(AST::NodeProgram* node);
    void construct(AST::NodeAffect* node);
    void construct(AST::NodeIf* node);
    void construct(AST::NodeRead* node);
    void construct(AST::NodeArgument* node);
    void construct(AST::NodeArguments* node);
    void construct(AST::NodeReturn* node);
    void construct(AST::NodeExit* node);
    void construct(AST::NodeCallFunc* node);
    void construct(AST::NodeOperation* node);
    void construct(AST::NodeExpression* node);
    void construct(AST::NodeStringExpr* node);
    void construct(AST::NodeBoolean* node);
    void construct(AST::NodeExpressions* node);
    void construct(AST::NodeInstr* node);
    void construct(AST::NodeCompoundInstr* node);
    void construct(AST::NodeFactor* node);
    void construct(AST::NodeInstrs* node);
    void construct(AST::NodeType* node);
    void construct(AST::NodeFunction* node);
    void construct(AST::NodeWhile* node);
    void construct(AST::NodeDeclarationBody* node);
    void construct(AST::NodeFunctions* node);
    void construct(AST::NodeNumber* node);
    void construct(AST::NodeDeclaration* node);
    void construct(AST::NodeHeaderFunc* node);
    void construct(AST::NodeDeclarations* node);
    void construct(AST::NodeId* node);
    void construct(AST::NodeIdFunc* node);
    void construct(AST::NodePrint* node);

  private:
    bool randomConstruct() const;
    bool randomConstruct(const unsigned int mod) const;
    AST::Operator::type randomOperator() const;
    const std::string& randomType() const;
  };
}

# include "GenerateAST.hxx"

#endif /* !GENERATEAST_HH_ */
