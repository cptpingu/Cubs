#ifndef NODE_HH_
# define NODE_HH_

# include <iostream>
# include <vector>
# include "IVisitable.hh"
# include "Lexer.hh"

namespace MiniCompiler
{
  namespace AST
  {
    class Node : public IVisitable
    {
    public:
      typedef std::vector<Node*>::const_iterator iter;
      Node();
      virtual ~Node();
      unsigned int getLine() const;
      void setLine(const unsigned int line);
      virtual void accept(Visitor& visitor) = 0;
      virtual void accept(ConstVisitor& visitor) const = 0;

    protected:
      unsigned int	_line;
    };
  }
}

#endif /* !NODE_HH_ */
