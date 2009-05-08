namespace MiniCompiler
{
  namespace AST
  {
    /*!
    ** Construct a node and computed type to Undefined.
    */
    inline
    TypedNode::TypedNode()
      : _computedType(Type::UNDEFINED)
    {
    }

    /*!
    ** Destruct a node.
    */
    inline
    TypedNode::~TypedNode()
    {
    }

    /*!
    ** Get the computed type.
    **
    ** @return The computed type
    */
    inline Type::type
    TypedNode::getComputedType() const
    {
      return _computedType;
    }

    /*!
    ** Set the computed type.
    **
    ** @param type The computed type
    */
    inline void
    TypedNode::setComputedType(const Type::type type)
    {
      _computedType = type;
    }
  }
}
