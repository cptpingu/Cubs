
namespace mystd
{
  /*!
  ** Default constructor. Add a object by default.
  */
  template <typename T>
  inline
  Flyweight<T>::Flyweight()
    : _elt(add(T()))
  {
  }

  /*!
  ** Constructor used when user give another flyweight.
  ** Just copy location of the internal element.
  **
  ** @param s The given flyweight
  */
  template <typename T>
  inline
  Flyweight<T>::Flyweight(const Flyweight<T>& fly)
    : _elt(fly._elt)
  {
  }

  /*!
  ** Constructor used when user give another flyweight.
  ** Just copy location of the internal element.
  **
  ** @param s The given flyweight
  */
  template <typename T>
  inline
  Flyweight<T>::Flyweight(const T& elt)
    : _elt(add(elt))
  {
  }

  /*!
  ** Just the destructor, nothing special to do !
  */
  template <typename T>
  inline
  Flyweight<T>::~Flyweight()
  {
  }

  /*!
  ** Special method to clear the flyweight.
  ** Make attention that no variables still point on it, before call it.
  */
  template <typename T>
  inline void
  Flyweight<T>::clear()
  {
    std::set<T>& set = getInstance();
    set.clear();
  }

  /*!
  ** Just use to get the size of the flyweight.
  */
  template <typename T>
  inline unsigned int
  Flyweight<T>::size()
  {
    std::set<T>& set = getInstance();
    return set.size();
  }

  /*!
  ** Get the flyweight instance. With that design, it can
  ** be only one instance of the flyweight in the application.
  **
  ** @return A reference on the flyweight
  */
  template <typename T>
  inline std::set<T>&
  Flyweight<T>::getInstance()
  {
    static std::set<T>	set;
    return set;
  }

  /*!
  ** Just affect a new element. Change local element, and add it
  ** to the flyweight if necessary.
  **
  ** @param s The string to affect
  **
  ** @return The object itself
  */
  template <typename T>
  inline const Flyweight<T>&
  Flyweight<T>::operator=(const T& s)
  {
    if (*this != s)
    {
      _elt = add(s);
    }
    return *this;
  }

  /*!
  ** Just affect a new element. Change local elment.
  ** Don't try to add it to the flyweight because it isn't necessary.
  **
  ** @param s The my::string to affect
  **
  ** @return The object itself
  */
  template <typename T>
  inline const Flyweight<T>&
  Flyweight<T>::operator=(const Flyweight<T>& fly)
  {
    if (this != &fly)
    {
      *this = *fly._elt;
    }
    return *this;
  }

  /*!
  ** Add a given string to the flyweight. All element is unique.
  ** Then, return an adress on the element.
  **
  ** @param s The string to add to the flyweight
  **
  ** @return Adress of the inserted, or existant string
  */
  template <typename T>
  inline const T*
  Flyweight<T>::add(const T& s)
  {
    std::set<T>& set = getInstance();
    set.insert(s);
    const_iterator it = set.find(s);
    assert(it != set.end());
    return &*it;
  }

  /*!
  ** Compare two flyweights.
  **
  ** @param s The flyweight to compare with
  **
  ** @return If current object is equal to the given one
  */
  template <typename T>
  inline bool
  Flyweight<T>::operator==(const Flyweight<T>& fly)
  {
    return _elt == fly._elt;
  }

  /*!
  ** Compare a string with our element.
  **
  ** @param s The element to compare with
  **
  ** @return If current object is equal to the given one
  */
  template <typename T>
  inline bool
  Flyweight<T>::operator==(const T& elt)
  {
    return *_elt == elt;
  }

  /*!
  ** Compare two flyweight.
  **
  ** @param s The my::string to compare with
  **
  ** @return If current object is different to the given one
  */
  template <typename T>
  inline bool
  Flyweight<T>::operator!=(const Flyweight<T>& elt)
  {
    return !operator==(elt);
  }

  /*!
  ** Compare a string with our my::string.
  **
  ** @param s The string to compare with
  **
  ** @return If current object is different to the given one
  */
  template <typename T>
  inline bool
  Flyweight<T>::operator!=(const T& elt)
  {
    return !operator==(elt);
  }

  /*!
  ** This particular redefinition is used when an implicit cast
  ** into T is done.
  **
  ** @return The std::string contained in our my::string
  */
  template <typename T>
  inline
  Flyweight<T>::operator const T&() const
  {
    return *_elt;
  }

  /*!
  ** Just use to make able our element to be compatible
  ** with algorithm which need the operator< to be redefined.
  ** Present only for the sake of speed.
  **
  ** @param s The element to compare with
  **
  ** @return If current object is inferior to the given one
  */
  template <typename T>
  inline bool
  Flyweight<T>::operator<(const Flyweight<T>& s) const
  {
    return _elt < s._elt;
  }

  /*!
  ** Just extract elements contained into the two flyweights,
  ** and concat them. Not that element is save into the flyweight, because
  ** adding two element make a temporary element.
  ** Make a particular attention when concatening elements, it can lead to
  ** the creation of a lot of useless elements in the flyweight.
  **
  ** @param s The element to concat with
  **
  ** @return An element
  */
  template <typename T>
  inline Flyweight<T>
  Flyweight<T>::operator+(const Flyweight<T>& fly) const
  {
    return *_elt + *fly._elt;
  }

  /*!
  ** Just redefined the stream operator<< to make it easy to display a my::string.
  **
  ** @param o The stream where to write
  ** @param s The element to write
  **
  ** @return The given stream
  */
  template <typename T>
  inline std::ostream&
  operator<<(std::ostream& o, const Flyweight<T>& s)
  {
    return o << *s._elt;
  }
}
