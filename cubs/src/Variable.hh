#ifndef VARIABLE_HH_
# define VARIABLE_HH_

# include "Utils.hh"

namespace MiniCompiler
{
  class Variable
  {
    friend std::ostream&
    operator<<(std::ostream& o, const Variable& var);

  public:
    Variable(const Variable& var);
    Variable(const int val);
    Variable(const bool val);
    Variable(const std::string& val);
    ~Variable();

  public:
    AST::Type::type getType() const;
    int getInt() const;
    bool getBool() const;
    const std::string& getString() const;
    void setInt(int val);
    void setBool(bool val);
    void setString(const std::string& val);

    /*!
    ** Assignments
    */
  public:
    Variable& operator=(const Variable& rhs);
    Variable& operator+=(const Variable& rhs);
    Variable& operator-=(const Variable& rhs);
    Variable& operator*=(const Variable& rhs);
    Variable& operator/=(const Variable& rhs);
    Variable& operator%=(const Variable& rhs);

    /*!
    ** Operations
    */
  public:
    const Variable operator+(const Variable &other) const;
    const Variable operator-(const Variable &other) const;
    const Variable operator*(const Variable &other) const;
    const Variable operator/(const Variable &other) const;
    const Variable operator%(const Variable &other) const;

    /*!
    ** Comparators
    */
  public:
    bool operator==(const Variable& other) const;
    bool operator!=(const Variable& other) const;
    bool operator>(const Variable& other) const;
    bool operator<=(const Variable& other) const;
    bool operator<(const Variable& other) const;
    bool operator>=(const Variable& other) const;

  private:
    void dump(std::ostream& o) const;

  public:
    void print(std::ostream& o) const;

  private:
    int				_intVal;
    bool			_boolVal;
    std::string			_stringVal;
    const AST::Type::type	_type;
  };

  std::ostream&
  operator<<(std::ostream& o, const Variable& var);
  std::ostream&
  operator<<(std::ostream& o, const Variable* var);

}

#endif /* !VARIABLE_HH_ */
