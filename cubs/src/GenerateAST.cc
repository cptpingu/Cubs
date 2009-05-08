#include <ctime>
#include "GenerateAST.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the GenerateAST, intializing random seed.
  */
  GenerateAST::GenerateAST()
  {
    srand(time(0));
  }

  /*!
  ** Destruct the GenerateAST.
  */
  GenerateAST::~GenerateAST()
  {
  }

  /*!
  ** Construct ids node randomly.
  **
  ** @param node The ids node
  */
  void
  GenerateAST::construct(AST::NodeIds* node)
  {
    assert(node);

    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);

    if (randomConstruct())
    {
      AST::NodeIds* ids = new AST::NodeIds();
      node->setIds(ids);
      construct(ids);
    }
  }

  /*!
  ** Construct program node randomly.
  **
  ** @param node The ids node
  */
  void
  GenerateAST::construct(AST::NodeProgram* node)
  {
    assert(node);

    AST::NodeDeclarations* decls = new AST::NodeDeclarations();
    node->setDecls(decls);
    construct(decls);


    AST::NodeFunctions* funcs = new AST::NodeFunctions();
    node->setFuncs(funcs);
    construct(funcs);

    AST::NodeCompoundInstr* instrs = new AST::NodeCompoundInstr();
    node->setInstrs(instrs);
    construct(instrs);
  }

  /*!
  ** Construct affectation node randomly.
  **
  ** @param node The affectation node
  */
  void
  GenerateAST::construct(AST::NodeAffect* node)
  {
    assert(node);
    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Construct if node randomly.
  **
  ** @param node The if node
  */
  void
  GenerateAST::construct(AST::NodeIf* node)
  {
    assert(node);
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setCond(expr);
    construct(expr);

    AST::NodeCompoundInstr* body = new AST::NodeCompoundInstr();
    node->setBodyExprs(body);
    construct(body);

    if (randomConstruct())
    {
      AST::NodeCompoundInstr* elseExprs = new AST::NodeCompoundInstr();
      node->setElseExprs(elseExprs);
      construct(elseExprs);
    }
  }

  /*!
  ** Construct read node randomly.
  **
  ** @param node The read node
  */
  void
  GenerateAST::construct(AST::NodeRead* node)
  {
    assert(node);
    AST::NodeId* id = new AST::NodeId();
    node->setId(id);
    construct(id);
  }

  /*!
  ** Construct arguments node randomly.
  **
  ** @param node The arguments node
  */
  void
  GenerateAST::construct(AST::NodeArguments* node)
  {
    assert(node);
    AST::NodeArgument* arg = new AST::NodeArgument();
    node->setArgument(arg);
    construct(arg);

    if (randomConstruct())
    {
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
    }
  }

  /*!
  ** Construct argument node randomly.
  **
  ** @param node The argument node
  */
  void
  GenerateAST::construct(AST::NodeArgument* node)
  {
    assert(node);
    AST::NodeDeclarationBody* body = new AST::NodeDeclarationBody();
    node->setDeclarationBody(body);
    construct(body);

    if (randomConstruct())
    {
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
    }
  }

  /*!
  ** Construct return node randomly.
  **
  ** @param node The return node
  */
  void
  GenerateAST::construct(AST::NodeReturn* node)
  {
    assert(node);
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Construct exit node randomly.
  **
  ** @param node The exit node
  */
  void
  GenerateAST::construct(AST::NodeExit* node)
  {
    assert(node);
    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }

  /*!
  ** Construct call function node randomly.
  **
  ** @param node The call function node
  */
  void
  GenerateAST::construct(AST::NodeCallFunc* node)
  {
    assert(node);

    AST::NodeIdFunc* id = new AST::NodeIdFunc();
    node->setId(id);
    construct(id);

    if (randomConstruct())
    {
      AST::NodeExpressions* exprs = new AST::NodeExpressions();
      node->setExprs(exprs);
      construct(exprs);
    }
  }

  /*!
  ** Construct operation node randomly.
  **
  ** @param node The operation node
  */
  void
  GenerateAST::construct(AST::NodeOperation* node)
  {
    assert(node);

    AST::NodeFactor* factor = new AST::NodeFactor();
    node->setLeftFactor(factor);
    construct(factor);
    node->setOpType(AST::Operator::NONE);

    if (randomConstruct())
    {
      node->setOpType(randomOperator());
      AST::NodeFactor* factor = new AST::NodeFactor();
      node->setRightFactor(factor);
      construct(factor);
    }
  }

  /*!
  ** Construct expression node randomly.
  **
  ** @param node The expression node
  */
  void
  GenerateAST::construct(AST::NodeExpression* node)
  {
    assert(node);

    AST::NodeOperation* op = new AST::NodeOperation();
    node->setOperation(op);
    construct(op);
  }

  /*!
  ** Construct string expression node randomly.
  **
  ** @param node The string expression node
  */
  void
  GenerateAST::construct(AST::NodeStringExpr* node)
  {
    assert(node);
    node->setString("String Expression");
  }

  /*!
  ** Construct boolean node randomly.
  **
  ** @param node The boolean node
  */
  void
  GenerateAST::construct(AST::NodeBoolean* node)
  {
    assert(node);
    node->setBool(randomConstruct());
  }

  /*!
  ** Construct expressions node randomly.
  **
  ** @param node The expressions node
  */
  void
  GenerateAST::construct(AST::NodeExpressions* node)
  {
    assert(node);

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);

    if (randomConstruct())
    {
      AST::NodeExpressions* exprs = new AST::NodeExpressions();
      node->setExprs(exprs);
      construct(exprs);
    }
  }

  /*!
  ** Construct instructions node randomly.
  **
  ** @param node The instructions node
  */
  void
  GenerateAST::construct(AST::NodeInstr* node)
  {
    assert(node);

    if (randomConstruct())
    {
      AST::NodeAffect* aff = new AST::NodeAffect();
      node->setAffect(aff);
      construct(aff);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeCallFunc* call = new AST::NodeCallFunc();
      node->setCallFunc(call);
      construct(call);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeCompoundInstr* compoundInstr = new AST::NodeCompoundInstr();
      node->setCompoundInstr(compoundInstr);
      construct(compoundInstr);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeReturn* ret = new AST::NodeReturn();
      node->setReturn(ret);
      construct(ret);
      return;
    }

    if (randomConstruct())
    {
      AST::NodePrint* print = new AST::NodePrint();
      node->setPrint(print);
      construct(print);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeRead* read = new AST::NodeRead();
      node->setRead(read);
      construct(read);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeIf* nIf = new AST::NodeIf();
      node->setIf(nIf);
      construct(nIf);
      return;
    }

    AST::NodeWhile* nWhile = new AST::NodeWhile();
    node->setWhile(nWhile);
    construct(nWhile);
  }

  /*!
  ** Construct compound instruction node randomly.
  **
  ** @param node The compound instruction node
  */
  void
  GenerateAST::construct(AST::NodeCompoundInstr* node)
  {
    assert(node);

    AST::NodeInstrs* instrs = new AST::NodeInstrs();
    node->setInstrs(instrs);
    construct(instrs);
  }

  /*!
  ** Construct factor node randomly.
  **
  ** @param node The factor node
  */
  void
  GenerateAST::construct(AST::NodeFactor* node)
  {
    assert(node);

    if (randomConstruct())
    {
      AST::NodeCallFunc* call = new AST::NodeCallFunc();
      node->setCallFunc(call);
      construct(call);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeId* id = new AST::NodeId();
      node->setId(id);
      construct(id);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeNumber* num = new AST::NodeNumber();
      node->setNumber(num);
      construct(num);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeStringExpr* str = new AST::NodeStringExpr();
      node->setStringExpr(str);
      construct(str);
      return;
    }

    if (randomConstruct())
    {
      AST::NodeBoolean* boolExpr = new AST::NodeBoolean();
      node->setBool(boolExpr);
      construct(boolExpr);
      return;
    }

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpression(expr);
    construct(expr);
  }

  /*!
  ** Construct instructions node randomly.
  **
  ** @param node The instructions node
  */
  void
  GenerateAST::construct(AST::NodeInstrs* node)
  {
    assert(node);
    AST::NodeInstr* instr = new AST::NodeInstr();
    node->setInstr(instr);
    construct(instr);

    if (randomConstruct())
    {
      AST::NodeInstrs* instrs = new AST::NodeInstrs();
      node->setInstrs(instrs);
      construct(instrs);
    }
  }

  /*!
  ** Construct type node randomly.
  **
  ** @param node The type node
  */
  void
  GenerateAST::construct(AST::NodeType* node)
  {
    assert(node);
    node->setType(randomType());
  }

  /*!
  ** Construct function node randomly.
  **
  ** @param node The function node
  */
  void
  GenerateAST::construct(AST::NodeFunction* node)
  {
    assert(node);

    AST::NodeHeaderFunc* header = new AST::NodeHeaderFunc();
    node->setHeaderFunc(header);
    construct(header);

    if (randomConstruct())
    {
      AST::NodeDeclarations* decls = new AST::NodeDeclarations();
      node->setDeclarations(decls);
      construct(decls);
    }

    AST::NodeCompoundInstr* instr = new AST::NodeCompoundInstr();
    node->setCompoundInstr(instr);
    construct(instr);
  }

  /*!
  ** Construct while node randomly.
  **
  ** @param node The while node
  */
  void
  GenerateAST::construct(AST::NodeWhile* node)
  {
    assert(node);

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setCond(expr);
    construct(expr);

    AST::NodeCompoundInstr* body = new AST::NodeCompoundInstr();
    node->setBodyExprs(body);
    construct(body);
  }

  /*!
  ** Construct declaration body node randomly.
  **
  ** @param node The declaration body node
  */
  void
  GenerateAST::construct(AST::NodeDeclarationBody* node)
  {
    assert(node);

    AST::NodeIds* ids = new AST::NodeIds();
    node->setIds(ids);
    construct(ids);

    AST::NodeType* type = new AST::NodeType();
    node->setType(type);
    construct(type);
  }

  /*!
  ** Construct function node randomly.
  **
  ** @param node The function node
  */
  void
  GenerateAST::construct(AST::NodeFunctions* node)
  {
    assert(node);

    AST::NodeFunction* func = new AST::NodeFunction();
    node->setFunc(func);
    construct(func);

    if (randomConstruct())
    {
      AST::NodeFunctions* funcs = new AST::NodeFunctions();
      node->setFuncs(funcs);
      construct(funcs);
    }
  }

  /*!
  ** Construct number node randomly.
  **
  ** @param node The number node
  */
  void
  GenerateAST::construct(AST::NodeNumber* node)
  {
    assert(node);
    node->setNumber(rand() % 1000);
  }

  /*!
  ** Construct declaration node randomly.
  **
  ** @param node The declaration node
  */
  void
  GenerateAST::construct(AST::NodeDeclaration* node)
  {
    assert(node);

    AST::NodeDeclarationBody* bodyDecl = new AST::NodeDeclarationBody();
    node->setBody(bodyDecl);
    construct(bodyDecl);
  }

  /*!
  ** Construct header function node randomly.
  **
  ** @param node The header function node
  */
  void
  GenerateAST::construct(AST::NodeHeaderFunc* node)
  {
    assert(node);

    AST::NodeIdFunc* id = new AST::NodeIdFunc();
    node->setId(id);
    construct(id);

    if (randomConstruct())
    {
      AST::NodeArguments* args = new AST::NodeArguments();
      node->setArguments(args);
      construct(args);
    }

    AST::NodeType* type = new AST::NodeType();
    node->setType(type);
    construct(type);
  }

  /*!
  ** Construct declarations node randomly.
  **
  ** @param node The declarations node
  */
  void
  GenerateAST::construct(AST::NodeDeclarations* node)
  {
    assert(node);

    AST::NodeDeclaration* decl = new AST::NodeDeclaration();
    node->setDeclaration(decl);
    construct(decl);

    if (randomConstruct())
    {
      AST::NodeDeclarations* decls = new AST::NodeDeclarations();
      node->setDeclarations(decls);
      construct(decls);
    }
  }

  /*!
  ** Construct id node randomly.
  **
  ** @param node The id node
  */
  void
  GenerateAST::construct(AST::NodeId* node)
  {
    assert(node);
    node->setId("id");
  }

  /*!
  ** Construct function id node randomly.
  **
  ** @param node The function id node
  */
  void
  GenerateAST::construct(AST::NodeIdFunc* node)
  {
    assert(node);
    node->setId("FuncId");
  }

  /*!
  ** Construct print node randomly.
  **
  ** @param node The print node
  */
  void
  GenerateAST::construct(AST::NodePrint* node)
  {
    assert(node);

    AST::NodeExpression* expr = new AST::NodeExpression();
    node->setExpr(expr);
    construct(expr);
  }
}
