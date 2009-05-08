#include <cassert>
#include "Traits.hh"

namespace MiniCompiler
{
  /*!
  ** Construct the scope parametized by a Key and pointer Data.
  */
  template <typename Key, typename Data>
  inline
  Scope<Key, Data>::Scope()
    : _filter("")
  {
    assert(::Traits::isPointer<Data>::value);
  }

  /*!
  ** Destruct the scope.
  */
  template <typename Key, typename Data>
  inline
  Scope<Key, Data>::~Scope()
  {
  }

  /*!
  ** Return an iterator on the beginning of the list in the current scope.
  **
  ** @return An iterator on the beginning of the list
  */
  template <typename Key, typename Data>
  inline typename Scope<Key, Data>::const_list_iterator
  Scope<Key, Data>::beginAll()
  {
    return _stack.begin();
  }

  /*!
  ** Return an iterator on the end of the list in the current scope.
  **
  ** @return An iterator on the end of the list
  */
  template <typename Key, typename Data>
  inline typename Scope<Key, Data>::const_list_iterator
  Scope<Key, Data>::endAll()
  {
    return _stack.end();
  }

  /*!
  ** Return an iterator on the beginning of the map in the current scope.
  **
  ** @return An iterator on the beginning of the map
  */
  template <typename Key, typename Data>
  inline typename Scope<Key, Data>::const_map_iterator
  Scope<Key, Data>::begin()
  {
    return _stack.begin()->begin();
  }

  /*!
  ** Return an iterator on the end of the map in the current scope.
  **
  ** @return An iterator on the end of the map
  */
  template <typename Key, typename Data>
  inline typename Scope<Key, Data>::const_map_iterator
  Scope<Key, Data>::end()
  {
    return _stack.begin()->end();
  }

  /*!
  ** Put a new Key Data pair, in the current scope.
  **
  ** @param key The key of the pair
  ** @param value The Data represented by a pointer
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::put(const Key& key, const Data& value)
  {
    typename std::list< std::map<Key, Data> >::iterator i;

    assert(!_stack.empty());
    i = _stack.begin();
    (*i)[key] = value;
  }

  /*!
  ** Set a filter for displaying.
  **
  ** @param special The filter
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::setFilter(const std::string& special)
  {
    _filter = special;
  }

  /*!
  ** Try to get the data searching in all scope.
  **
  ** @param key The key associated to the Data
  **
  ** @return The data, or 0 if doesn't found
  */
  template <typename Key, typename Data>
  inline Data
  Scope<Key, Data>::getFromCurrent(const Key& key)
  {
    assert(!_stack.empty());
    if (_stack.front().find(key) != _stack.front().end())
      return (_stack.front()[key]);

    return (0);
  }

  /*!
  ** Try to get the data searching in all scope.
  **
  ** @param key The key associated to the Data
  **
  ** @return The data, or 0 if doesn't found
  */
  template <typename Key, typename Data>
  inline Data
  Scope<Key, Data>::getFromAll(const Key& key) const
  {
    assert(!_stack.empty());

    // Search for the wanted key in all scope
    for (iter i = _stack.begin(); i != _stack.end(); ++i)
      if (i->find(key) != i->end())
      {
	std::map<Key, Data> m = *i;
	return m[key];
      }

    // Can't find the wanted key
    return 0;
  }

  /*!
  ** Open a scope.
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::open()
  {
    std::map<Key, Data> m;

    _stack.push_front(m);
  }

  /*!
  ** Close a scope.
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::close()
  {
    _stack.pop_front();
  }

  /*!
  ** Gets number of scope
  **
  ** @return Number of scope
  */
  template <typename Key, typename Data>
  inline unsigned int
  Scope<Key, Data>::size() const
  {
    return _stack.size();
  }

  /*!
  ** Delete all Data contains in current scope,
  ** and close this scope.
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::closeAndDelete()
  {
    iter i = _stack.begin();
    for (mapIter j = i->begin(); j != i->end(); ++j)
      delete j->second;

    close();
  }

  /*!
  ** Print all scope to the given stream.
  **
  ** @param o The stream
  */
  template <typename Key, typename Data>
  inline void
  Scope<Key, Data>::print(std::ostream& o) const
  {
    std::string shift = "";
    bool first = true;
    unsigned int t = _filter.length();

    o << "____________________________\n";
    for (iter i = _stack.begin(); i != _stack.end(); ++i)
    {
      if (!first)
	o << "----------------------------\n";
      for (mapIter j = i->begin(); j != i->end(); ++j)
      {
	if (t <= 0 || _filter != j->first.substr(0, t))
	  o << shift << j->first << '=' << j->second << "\n";
      }
      shift += ">>";
      first = false;
    }
    o << '\n';
  }

  /*!
  ** Print the scope in the given stream.
  **
  ** @param o The stream
  ** @param scope The scope to display
  **
  ** @return The modified stream
  */
  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& o, const Scope<Key, Data>& scope)
  {
    scope.print(o);
    return o;
  }
}
