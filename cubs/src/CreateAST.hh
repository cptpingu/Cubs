#ifndef CREATEAST_HH_
# define CREATEAST_HH_

# include <cassert>
# include "Lexer.hh"
# include "Configuration.hh"
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
# include "NodeOperation.hh"
# include "NodeExpression.hh"
# include "NodeStringExpr.hh"
# include "NodeBoolean.hh"
# include "NodeExpressions.hh"
# include "NodeInstr.hh"
# include "NodeCompoundInstr.hh"
# include "NodeFactor.hh"
# include "NodeInstrs.hh"
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
# include "ErrorHandler.hh"
# include "Error.hh"

namespace MiniCompiler
{
  class CreateAST
  {
  public:
    CreateAST(const Lexer& lexer);
    ~CreateAST();
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

  public:
    const ErrorHandler& getErrors() const;

  private:
    void error(std::string attempted,
	       const Symbol& symb);
    bool isId(const Symbol& symb) const;
    bool isIds(const Symbol& symb) const;
    bool isIf(const Symbol& symb) const;
    bool isThen(const Symbol& symb) const;
    bool isElse(const Symbol& symb) const;
    bool isWhile(const Symbol& symb) const;
    bool isDo(const Symbol& symb) const;
    bool isLeftBracket(const Symbol& symb) const;
    bool isRightBracket(const Symbol& symb) const;
    bool isType(const Symbol& symb) const;
    bool isKeyword(const Symbol& symb) const;
    bool isSemiColon(const Symbol& symb) const;
    bool isOperator(const Symbol& symb) const;
    bool isValue(const Symbol& symb) const;
    bool isComa(const Symbol& symb) const;
    bool isComparator(const Symbol& symb) const;
    bool isStringExpr(const Symbol& symb) const;
    bool isBoolean(const Symbol& symb) const;
    bool isColon(const Symbol& symb) const;
    bool isCallFunc(const Symbol& lSymb,
		    const Symbol& rSymb) const;
    bool isVar(const Symbol& symb) const;
    bool isRead(const Symbol& symb) const;
    bool isPrint(const Symbol& symb) const;
    bool isBegin(const Symbol& symb) const;
    bool isEnd(const Symbol& symb) const;
    bool isEqual(const Symbol& symb) const;
    bool isDeclaration(const Symbol& symb) const;
    bool isDeclarations(const Symbol& symb) const;
    bool isFunctions(const Symbol& symb) const;
    bool isFunction(const Symbol& symb) const;
    bool isHeaderFunc(const Symbol& symb) const;
    bool isCompoundInstr(const Symbol& symb) const;
    bool isProgram(const Symbol& symb) const;
    bool isReturn(const Symbol& symb) const;
    bool isExit(const Symbol& symb) const;
    bool isFactor(const Symbol& symb) const;
    bool isOperation(const Symbol& symb) const;
    bool isAffect(const Symbol& symb) const;
    bool isArguments(const Symbol& symb) const;
    bool isArgument(const Symbol& symb) const;
    bool isDeclarationBody(const Symbol& symb) const;
    bool isCallFunc(const Symbol& symb) const;
    bool isExpression(const Symbol& symb) const;
    bool isExpressions(const Symbol& symb) const;
    bool isInstrs(const Symbol& symb) const;
    bool isInstr(const Symbol& symb) const;

  private:
    void nextToken();
    const Symbol& current() const;
    const Symbol& next() const;
    bool valid() const;
    bool nextValid() const;
    bool checkValid();
    bool checkNextValid();

  private:
    const Lexer&	_lexer;
    unsigned int	_pos;
    const unsigned int	_size;
    ErrorHandler	_errors;
  };
}

# include "CreateAST.hxx"

#endif /* !CREATEAST_HH_ */
