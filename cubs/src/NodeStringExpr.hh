#ifndef NODESTRINGEXPR_HH_
# define NODESTRINGEXPR_HH_

# include "Node.hh"
# include "TypedNode.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** stringexpr ::= ".*"
    */
    class NodeStringExpr : public TypedNode
    {
    public:
      NodeStringExpr();
      virtual ~NodeStringExpr();
      virtual void accept(Visitor& visitor);
      virtual void accept(ConstVisitor& visitor) const;

    public:
      const std::string& getString() const;
      void setString(const std::string& s);

    private:
      std::string	_stringExpr;
    };
  }
}

#endif /* !NODESTRINGEXPR_HH_ */
