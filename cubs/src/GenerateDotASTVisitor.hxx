namespace MiniCompiler
{
  /*!
  ** Write a rule for the dot parser.
  ** Declare a node and his style.
  **
  ** @param nodeName The name of the node
  ** @param labelName The label to put on the node
  ** @param style Additionnal style
  */
  inline void
  GenerateDotASTVisitor::declareNode(const std::string& nodeName,
				     const std::string& labelName,
				     const std::string& style)
  {
    _indent << nodeName << " [label=\"" << labelName <<
	    "\"," << style << "];\n";
  }

  /*!
  ** Write a rule for the dot parser.
  ** Declare a node, and apply default style.
  **
  ** @param nodeName The name of the rootName
  ** @param labelName The label to put on the node
  */
  inline void
  GenerateDotASTVisitor::declareNode(const std::string& nodeName,
				     const std::string& labelName)
  {
    declareNode(nodeName, labelName, NodeName::Option::DEFAULT);
  }

  /*!
  ** Link a node with the given root one.
  ** A style has to be given.
  **
  ** @param rootName The name of the parent node
  ** @param nodeName The name of the current node
  ** @param style Additionnal style
  */
  inline void
  GenerateDotASTVisitor::linkNode(const std::string& nodeName,
				  const std::string& rootName,
				  const std::string& style)
  {
    _indent << rootName << " -> " << nodeName << " [" << style << "];\n";
  }

  /*!
  ** Link a node with the given root one.
  ** A default style will be applied.
  **
  ** @param rootName The name of the parent node
  ** @param nodeName The name of the current node
  */
  inline void
  GenerateDotASTVisitor::linkNode(const std::string& nodeName,
				  const std::string& rootName)
  {
    linkNode(nodeName, rootName, "");
  }
}
