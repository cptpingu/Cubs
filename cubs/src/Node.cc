#include <cassert>
#include "Node.hh"

namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct a node, initializing line to 0.
    */
    Node::Node()
      : _line(0)
    {
    }

    /*!
    ** Destruct a node.
    */
    Node::~Node()
    {
    }

    /*!
    ** Get the line.
    **
    ** @return The line
    */
    unsigned int
    Node::getLine() const
    {
      return _line;
    }

    /*!
    ** Set the line.
    **
    ** @param line The line
    */
    void
    Node::setLine(const unsigned int line)
    {
      _line = line;
    }
  }
}
