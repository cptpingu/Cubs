#include <cassert>
#include "Configuration.hh"
#include "Variable.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the variable with another one.
  **
  ** @param var The variable used to create this one
  */
  Variable::Variable(const Variable& var)
    : _intVal(var.getInt()), _boolVal(var.getBool()),
      _stringVal(var.getString()), _type(var.getType())
  {
  }

  /*!
  ** Construct the variable using an integer value.
  **
  ** @param val The integer value
  */
  Variable::Variable(const int val)
    : _intVal(val), _boolVal(false),
      _stringVal(""), _type(AST::Type::INTEGER)
  {
  }

  /*!
  ** Construct the variable, using a boolean value.
  **
  ** @param val The boolean value
  */
  Variable::Variable(const bool val)
    : _intVal(0), _boolVal(val),
      _stringVal(""), _type(AST::Type::BOOLEAN)
  {
  }

  /*!
  ** Construct the variable, using a string value.
  **
  ** @param val The string value
  */
  Variable::Variable(const std::string& val)
    : _intVal(0), _boolVal(false),
      _stringVal(val), _type(AST::Type::STRING)
  {
  }

  /*!
  ** Destruct the variable
  */
  Variable::~Variable()
  {
  }

  /*!
  ** Copy all attribute from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator=(const Variable &rhs)
  {
    // Check for self-assignment !
    if (this == &rhs)
      return *this;

    assert(_type == rhs.getType());
    _intVal = rhs.getInt();
    _boolVal = rhs.getBool();
    _stringVal = rhs.getString();

    return *this;
  }

  /*!
  ** Add value from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator+=(const Variable& rhs)
  {
    assert(_type == rhs.getType());
    assert(_type != AST::Type::BOOLEAN);
    _intVal += rhs.getInt();
    _stringVal += rhs.getString();

    return *this;
  }

  /*!
  ** Substract value from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator-=(const Variable& rhs)
  {
    assert(_type == rhs.getType());
    assert(_type == AST::Type::INTEGER);
    _intVal -= rhs.getInt();

    return *this;
  }

  /*!
  ** Multiply value from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator*=(const Variable& rhs)
  {
    assert(_type == rhs.getType());
    assert(_type == AST::Type::INTEGER);
    _intVal *= rhs.getInt();

    return *this;
  }

  /*!
  ** Divide value from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator/=(const Variable& rhs)
  {
    assert(_type == rhs.getType());
    assert(_type == AST::Type::INTEGER);
    _intVal /= rhs.getInt();

    return *this;
  }

  /*!
  ** Apply modulo value from another variable.
  **
  ** @param rhs The variable use to fill ours
  **
  ** @return Our variable
  */
  Variable&
  Variable::operator%=(const Variable& rhs)
  {
    assert(_type == rhs.getType());
    assert(_type == AST::Type::INTEGER);
    _intVal %= rhs.getInt();

    return *this;
  }

  /*!
  ** Create a new variable adding our with another one.
  **
  ** @param rhs Another variable
  **
  ** @return A new variable obtained with ours
  */
  const Variable
  Variable::operator+(const Variable& other) const
  {
    return Variable(*this) += other;
  }

  /*!
  ** Create a new variable substracting our with another one.
  **
  ** @param rhs Another variable
  **
  ** @return A new variable obtained with ours
  */
  const Variable
  Variable::operator-(const Variable& other) const
  {
    return Variable(*this) -= other;
  }

  /*!
  ** Create a new variable mutliplying our with another one.
  **
  ** @param rhs Another variable
  **
  ** @return A new variable obtained with ours
  */
  const Variable
  Variable::operator*(const Variable& other) const
  {
    return Variable(*this) *= other;
  }

  /*!
  ** Create a new variable divide our with another one.
  **
  ** @param rhs Another variable
  **
  ** @return A new variable obtained with ours
  */
  const Variable
  Variable::operator/(const Variable& other) const
  {
    return Variable(*this) /= other;
  }

  /*!
  ** Create a new variable with a value from our variable our with another one.
  **
  ** @param rhs Another variable
  **
  ** @return A new variable obtained with ours
  */
  const Variable
  Variable::operator%(const Variable& other) const
  {
    return Variable(*this) %= other;
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is equal to our
  */
  bool
  Variable::operator==(const Variable& other) const
  {
    assert(_type == other.getType());

    switch (_type)
    {
      case AST::Type::INTEGER:
	return _intVal == other.getInt();
      case AST::Type::BOOLEAN:
	return _boolVal == other.getBool();
      case AST::Type::STRING:
	return _stringVal == other.getString();
      default:
	assert(false);
    }
    return false;
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is different to our
  */
  bool
  Variable::operator!=(const Variable& other) const
  {
    return !(*this == other);
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is superior to our
  */
  bool
  Variable::operator>(const Variable& other) const
  {
    assert(_type == other.getType());
    assert(_type == AST::Type::INTEGER);

    return _intVal > other.getInt();
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is inferior or equal to our
  */
  bool
  Variable::operator<=(const Variable& other) const
  {
    return !(*this > other);
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is inferior to our
  */
  bool
  Variable::operator<(const Variable& other) const
  {
    assert(_type == other.getType());
    assert(_type == AST::Type::INTEGER);

    return _intVal < other.getInt();
  }

  /*!
  ** Compare our variable with another one.
  **
  ** @param other The variable to compare with our
  **
  ** @return If given variable is superior or equal to our
  */
  bool
  Variable::operator>=(const Variable& other) const
  {
    return !(*this < other);
  }

  /*!
  ** Get the type of the variable.
  **
  ** @return The variable type
  */
  AST::Type::type
  Variable::getType() const
  {
    return _type;
  }

  /*!
  ** Get the integer value store in our variable.
  **
  ** @return The integer value stored in our variable
  */
  int
  Variable::getInt() const
  {
    return _intVal;
  }

  /*!
  ** Get the boolean value store in our variable.
  **
  ** @return The boolean value stored in our variable
  */
  bool
  Variable::getBool() const
  {
    return _boolVal;
  }

  /*!
  ** Get the string value store in our variable.
  **
  ** @return The string value stored in our variable
  */
  const std::string&
  Variable::getString() const
  {
    return _stringVal;
  }

  /*!
  ** Set the integer value of our variable.
  **
  ** @param val The integer value of our variable
  */
  void
  Variable::setInt(int val)
  {
    _intVal = val;
  }

  /*!
  ** Set the boolean value of our variable.
  **
  ** @param val The boolan value of our variable
  */
  void
  Variable::setBool(bool val)
  {
    _boolVal = val;
  }

  /*!
  ** Set the string value of our variable.
  **
  ** @param val The string value of our variable
  */
  void
  Variable::setString(const std::string& val)
  {
    _stringVal = val;
  }

  /*!
  ** Dump our variable, ie display his type, line and value.
  **
  ** @param o The stream where to display it
  */
  void
  Variable::dump(std::ostream& o) const
  {
    Configuration& cfg = Configuration::getInstance();

    switch (_type)
    {
      case AST::Type::INTEGER:
	o << '(' << cfg["int"] << ") " << _intVal;
	break;
      case AST::Type::BOOLEAN:
	o << '(' << cfg["bool"] << ") " << (_boolVal ? "true" : "false");
	break;
      case AST::Type::STRING:
	o << '(' << cfg["string"] << ") " << (_stringVal != "" ? _stringVal : "<empty>");
	break;
      default:
	o << '(' << cfg["undefined"] << ')';
    }
  }

  /*!
  ** Print the variable value.
  **
  ** @param o The stream where to display it
  */
  void
  Variable::print(std::ostream& o) const
  {
    Configuration& cfg = Configuration::getInstance();

    switch (_type)
    {
      case AST::Type::INTEGER:
	o <<  _intVal;
	break;
      case AST::Type::BOOLEAN:
	o << (_boolVal ? cfg["true"] : cfg["false"]);
	break;
      case AST::Type::STRING:
	o  << _stringVal;
	break;
      default:
	assert(false);
    }
  }

  /*!
  ** Dump the given variable in the given stream.
  **
  ** @param o The stream where to display it
  ** @param var The variable to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const Variable& var)
  {
    var.dump(o);
    return o;
  }

  /*!
  ** Dereferenced and dump the given variable in the given stream.
  **
  ** @param o The stream where to display it
  ** @param var The variable to display
  **
  ** @return The modified stream
  */
  std::ostream&
  operator<<(std::ostream& o, const Variable* var)
  {
    o << *var;
    return o;
  }
}
