#ifndef NODEOPERATION_HH_
# define NODEOPERATION_HH_

# include "TypedNode.hh"
# include "NodeFactor.hh"
# include "Utils.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** operation ::= factor symb factor
    **             | factor // operation with no right factor
    **	           | "-" factor // left factor = 0
    */
    class NodeOperation : public TypedNode
    {
    public:
      NodeOperation();
      virtual ~NodeOperation();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      NodeFactor* getLeftFactor() const;
      NodeFactor* getRightFactor() const;
      void setLeftFactor(NodeFactor* node);
      void setRightFactor(NodeFactor* node);
      Operator::type getOpType() const;
      void setOpType(Operator::type opType);

    protected:
      NodeFactor*	_leftFactor;
      NodeFactor*	_rightFactor;
      Operator::type	_opType;
    };
  }
}

#endif /* !NODEOPERATION_HH_ */
