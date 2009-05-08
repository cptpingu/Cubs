#ifndef FLYWEIGHT_HH_
# define FLYWEIGHT_HH_

# include <set>
# include <cassert>

namespace mystd
{
  template <typename T>
  class Flyweight
  {
    template <class U>
    friend std::ostream& operator<<(std::ostream& o, const Flyweight<U>& s);

    typedef typename std::set<T>::iterator		iterator;
    typedef typename std::set<T>::const_iterator	const_iterator;

  public:
    Flyweight();
    Flyweight(const Flyweight& fly);
    Flyweight(const T& elt);
    ~Flyweight();

    static void clear();
    static unsigned int size();

    const Flyweight& operator=(const Flyweight& fly);
    const Flyweight& operator=(const T& s);
    bool operator==(const Flyweight& fly);
    bool operator==(const T& elt);
    bool operator!=(const Flyweight& fly);
    bool operator!=(const T& elt);
    operator const T&() const;
    bool operator<(const Flyweight& fly) const;
    Flyweight operator+(const Flyweight& fly) const;

  protected:
    static std::set<T>& getInstance();
    const T* add(const T& s);

  protected:
    const T*		_elt;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& o, const Flyweight<T>& s);
}

# include "Flyweight.hxx"

#endif /* !FLYWEIGHT_HH_ */
