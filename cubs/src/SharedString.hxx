
namespace mystd
{
  /*!
  ** Just affect a new string. Change local string.
  ** Convert the C style string into a string, before trying to
  ** add it to the flyweight.
  **
  ** @param s The C style string to affect
  **
  ** @return The object itself
  */
  inline const SharedString&
  SharedString::operator=(const char* s)
  {
    assert(s);
    return operator=(std::string(s));
  }

  /*!
  ** Compare a C style string with our my::string.
  **
  ** @param s The C style string to compare with
  **
  ** @return If current object is equal to the given one
  */
  inline bool
  SharedString::operator==(const char* s)
  {
    assert(s);
    return *_elt == std::string(s);
  }

  /*!
  ** Compare a C style string with our my::string.
  **
  ** @param s The C style string to compare with
  **
  ** @return If current object is different to the given one
  */
  inline bool
  SharedString::operator!=(const char* s)
  {
    assert(s);
    return !operator==(s);
  }

  /*!
  ** Just extract elements contained into the two flyweights,
  ** and concat them. Not that element is save into the flyweight, because
  ** adding two element make a temporary element.
  ** Make a particular attention when concatening elements, it can lead to
  ** the creation of a lot of useless elements in theflyweight.
  **
  ** @param s The element to concat with
  **
  ** @return An element
  */
  inline SharedString
  SharedString::operator+(const SharedString& fly) const
  {
    return SharedString(super::operator+(fly));
  }

  /*!
  ** Just get the char at the given position.
  ** Here we must const_cast the result, because
  ** exceptionnaly, we need to modify the character.
  **
  ** @param i The index of the character to get
  **
  ** @return The character to get
  */
  inline char&
  SharedString::operator[](const unsigned int i)
  {
    assert(i < (*_elt).length());
    return (*const_cast<std::string*>(_elt))[i];
  }

  /*!
  ** Just get the char at the given position.
  **
  ** @param i The index of the character to get
  **
  ** @return The character to get
  */
  inline const char&
  SharedString::operator[](const unsigned int i) const
  {
    assert(i < (*_elt).length());
    return (*_elt)[i];
  }

  /*!
  ** Just get the size of the pointed string.
  **
  ** @return The size of the internal string
  */
  inline unsigned int
  SharedString::length() const
  {
    return _elt->length();
  }
}
