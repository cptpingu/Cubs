#ifndef IVISITABLE_HH_
# define IVISITABLE_HH_

# include "IVisitor.hh"

namespace MiniCompiler
{
  class IVisitable
  {
  public:
    IVisitable() {}
    virtual ~IVisitable() {}
    virtual void accept(Visitor& visitor) = 0;
    virtual void accept(ConstVisitor& visitor) const = 0;
  };
}

#endif /* !IVISITABLE_HH_ */
