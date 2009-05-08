#include "NodeIds.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct the ids node, initializing all nodes to null.
    */
    NodeIds::NodeIds()
      : _id(0), _ids(0)
    {
    }

    /*!
    ** Destruct the ids node, deleting all nodes.
    */
    NodeIds::~NodeIds()
    {
      delete _id;
      delete _ids;
    }

    /*!
    ** Accept a classic visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIds::accept(Visitor& visitor)
    {
      visitor.visit(this);
    }

    /*!
    ** Accept a const visitor.
    **
    ** @param visitor The visitor
    */
    void
    NodeIds::accept(ConstVisitor& visitor) const
    {
      visitor.visit(this);
    }

    /*!
    ** Get the id node.
    **
    ** @return The id node
    */
    NodeId*
    NodeIds::getId() const
    {
      return _id;
    }

    /*!
    ** Get the ids node.
    **
    ** @return The ids node
    */
    NodeIds*
    NodeIds::getIds() const
    {
      return _ids;
    }

    /*!
    ** Set the id node.
    **
    ** @param id The id node
    */
    void
    NodeIds::setId(NodeId* id)
    {
      _id = id;
    }

    /*!
    ** Set the ids node.
    **
    ** @param node The ids node
    */
    void
    NodeIds::setIds(NodeIds* node)
    {
      _ids = node;
    }
  }
}
