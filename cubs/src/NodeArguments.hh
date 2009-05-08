#ifndef NODEARGUMENTS_HH_
# define NODEARGUMENTS_HH_

# include "Node.hh"
# include "NodeArgument.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** arguments ::= argument
    **             | argument ";" arguments
    */
    class NodeArguments : public Node
    {
    public:
      NodeArguments();
      virtual ~NodeArguments();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeArgument* getArgument() const;
      NodeArguments* getArguments() const;
      void setArgument(NodeArgument* node);
      void setArguments(NodeArguments* node);

    private:
      NodeArgument*		_argument;
      NodeArguments*		_arguments;
    };
  }
}

#endif /* !NODEARGUMENTS_HH_ */
