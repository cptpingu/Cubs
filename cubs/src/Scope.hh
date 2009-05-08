#ifndef SCOPE_HH_
# define SCOPE_HH_

# include <map>
# include <list>
# include <iostream>

namespace MiniCompiler
{
  template <typename Key, typename Data>
  class Scope
  {
    typedef typename std::map<Key, Data>::const_iterator mapIter;
    typedef typename std::list<std::map<Key, Data> >::const_iterator iter;

  public:
    typedef mapIter const_map_iterator;
    typedef iter const_list_iterator;
    Scope();
    ~Scope();

  public:
    const_list_iterator beginAll();
    const_list_iterator endAll();
    const_map_iterator begin();
    const_map_iterator end();
    void open();
    void close();
    void closeAndDelete();
    void print(std::ostream& o) const;
    Data getFromCurrent(const Key& key);
    Data getFromAll(const Key& key) const;
    void put(const Key& key, const Data& value);
    void setFilter(const std::string& special);
    unsigned int size() const;

  private:
    std::list<std::map<Key, Data> >	_stack;
    std::string				_filter;
  };

  template <typename Key, typename Data>
  std::ostream&
  operator<<(std::ostream& o, const Scope<Key, Data>& scope);
}

# include "Scope.hxx"

#endif /* !SCOPE_HH_ */
