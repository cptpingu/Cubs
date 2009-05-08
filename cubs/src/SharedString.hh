#ifndef SHAREDSTRING_HH_
# define SHAREDSTRING_HH_

# include <string>
# include <cassert>
# include "Flyweight.hh"

namespace mystd
{
  class SharedString : public Flyweight<std::string>
  {
    typedef Flyweight<std::string> super;

  public:
    SharedString();
    SharedString(const SharedString& s);
    SharedString(const std::string& s);
    SharedString(const char* s);
    ~SharedString();

    const SharedString& operator=(const char* s);
    bool operator==(const char* s);
    bool operator!=(const char* s);
    char& operator[](const unsigned int i);
    const char& operator[](const unsigned int i) const;
    unsigned int length() const;
    SharedString operator+(const SharedString& fly) const;
  };
}

# include "SharedString.hxx"

#endif /* !SHAREDSTRING_HH_ */
