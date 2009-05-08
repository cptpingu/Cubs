#ifndef EXECUTIONVISITOR_HH_
# define EXECUTIONVISITOR_HH_

# include <iostream>
# include <iomanip>
# include <sstream>
# include <list>
# include "Utils.hh"
# include "BaseVisitor.hh"
# include "Variable.hh"
# include "Scope.hh"

namespace MiniCompiler
{
  namespace Exec
  {
    static const std::string SEPARATOR		= "%";
    static const std::string NODE_EXPR		= SEPARATOR + "nodeexpression" + SEPARATOR;
    static const std::string NODE_RETURN	= SEPARATOR + "return" + SEPARATOR;
    static const std::string NODE_ARG		= SEPARATOR + "arg";
    static const std::string NODE_CALLFUNC	= SEPARATOR + "nodecallfunc" + SEPARATOR;
    static const std::string NODE_FACTOR	= SEPARATOR + "nodefactor" + SEPARATOR;
    static const std::string NODE_OPERATION	= SEPARATOR + "nodeoperation" + SEPARATOR;
    static const std::string NODE_STRING	= SEPARATOR + "nodestring" + SEPARATOR;
    static const std::string NODE_BOOL		= SEPARATOR + "nodebool" + SEPARATOR;
    static const std::string NODE_NUMBER	= SEPARATOR + "nodenumber" + SEPARATOR;
    static const std::string NODE_ID		= SEPARATOR + "nodeid" + SEPARATOR;
  }

  class ExecutionVisitor : public ConstBaseVisitor
  {
    friend std::ostream&
    operator<<(std::ostream& o, const ExecutionVisitor& v);

    typedef Scope<std::string, Variable*> Registry;

  public:
    ExecutionVisitor();
    virtual ~ExecutionVisitor();

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

  public:
    void setShowCode(bool show);
    void setShowVariables(bool show);
    void setShowSpecialVariables(bool show);
    int getReturnValue() const;

  protected:
    void addVar(const std::string& name, const Variable& var);
    void changeVar(const std::string& name, const Variable& var);
    Variable* getVar(const std::string& name);
    void print(std::ostream& o) const;
    void flushToScreen();

  protected:
    std::stringstream	_indent;
    unsigned int	_tab;
    Registry		_registry;
    bool		_break;
    bool		_exit;
    bool		_showCode;
    bool		_showVariables;
    bool		_showSpecialVariables;
    int			_returnValue;
  };
}

#endif /* !EXECUTIONVISITOR_HH_ */
