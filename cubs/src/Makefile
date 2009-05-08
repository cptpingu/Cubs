include ../Makefile.rules

SRC=	main.cc				\
	Configuration.cc		\
	Compiler.cc			\
	Lexer.cc			\
	Utils.cc			\
	Error.cc			\
	ErrorHandler.cc			\
	Parser.cc			\
	Binder.cc			\
	TypeChecker.cc			\
	Execution.cc			\
	Symbol.cc			\
	Variable.cc			\
	SharedString.cc			\
	Scope.cc			\
	CreateAST.cc			\
	GenerateAST.cc			\
	BaseVisitor.cc			\
	ConvertToCppVisitor.cc		\
	PrettyPrinterVisitor.cc		\
	GenerateDotASTVisitor.cc	\
	BinderVisitor.cc		\
	TypeCheckerVisitor.cc		\
	ExecutionVisitor.cc		\
	ASMGeneratorVisitor.cc		\
	BindingPrinterVisitor.cc	\
	TypeCheckingPrinterVisitor.cc	\
	TypedNode.cc			\
	Node.cc				\
	NodeId.cc			\
	NodeIdFunc.cc			\
	NodeType.cc			\
	NodeNumber.cc			\
	NodeStringExpr.cc		\
	NodeBoolean.cc			\
	NodeIf.cc			\
	NodeWhile.cc			\
	NodeOperation.cc		\
	NodeProgram.cc			\
	NodeCallFunc.cc			\
	NodeCompoundInstr.cc		\
	NodeExpressions.cc		\
	NodeExpression.cc		\
	NodeDeclarations.cc		\
	NodeDeclaration.cc		\
	NodeDeclarationBody.cc		\
	NodeIds.cc			\
	NodeInstrs.cc			\
	NodeInstr.cc			\
	NodeAffect.cc			\
	NodeReturn.cc			\
	NodeExit.cc			\
	NodePrint.cc			\
	NodeRead.cc			\
	NodeFactor.cc			\
	NodeFunctions.cc		\
	NodeFunction.cc			\
	NodeHeaderFunc.cc		\
	NodeArguments.cc		\
	NodeArgument.cc

HEADER=$(SRC:.cc=.hh)
EXTRAHEADER=	IVisitable.hh		\
		IVisitor.hh		\
		Configuration.hxx	\
		Symbol.hxx		\
		Traits.hh		\
		Compiler.hxx		\
		Scope.hxx		\
		Flyweight.hh		\
		Flyweight.hxx		\
		SharedString.hxx	\
		Compiler.hxx		\
		Singleton.hh		\
		Singleton.hxx		\
		BaseVisitor.hxx		\
		GenerateAST.hxx		\
		TypedNode.hxx		\
		CreateAST.hxx		\
		Utils.hxx		\
		ASMGeneratorVisitor.hxx	\
		GenerateDotASTVisitor.hxx

TARGET=../$(EXE)

OBJ=$(SRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJ) Makefile.deps
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

Makefile.deps: $(SRC) $(HEADER) $(EXTRAHEADER)
	$(CXX) -MM $(SRC) > Makefile.deps

clean:
	rm -f *.o *.~ *.core *.Dstore *.log *.ml *.err *\#*

distclean:
	rm -f $(EXE)
	rm -f Makefile.deps Makefile.rules

-include Makefile.deps
