namespace MiniCompiler
{
  /*!
  ** Get a random value modulo the given value.
  **
  ** @param mod The modulo
  **
  ** @return A random value modulo a given value
  */
  inline bool
  GenerateAST::randomConstruct(const unsigned int mod) const
  {
    return rand() % mod;
  }

  /*!
  ** Get a random value modulo 2
  **
  ** @return A random value modulo 2
  */
  inline bool
  GenerateAST::randomConstruct() const
  {
    return randomConstruct(2);
  }

  /*!
  ** Get a random operator.
  **
  ** @return A random operator
  */
  inline AST::Operator::type
  GenerateAST::randomOperator() const
  {
    return AST::Operator::type((rand() % 11) + 1);
  }

  /*!
  ** Get a random type.
  **
  ** @return A random type
  */
  inline const std::string&
  GenerateAST::randomType() const
  {
    Configuration& cfg = Configuration::getInstance();
    switch (rand() % 3)
    {
      case 0:
	return cfg["int"];
      case 1:
	return cfg["string"];
      case 2:
	return cfg["bool"];
      default:
	return cfg["int"];
    }
  }
}
