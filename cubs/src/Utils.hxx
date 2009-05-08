namespace MiniCompiler
{
  /*!
  ** Make a new instance of a pair.
  **
  ** @param elt1 The first element.
  ** @param elt2 The second one.
  **
  ** @return A pointer on a new instance of a pair
  */
  template <typename C1, typename C2>
  inline std::pair<C1, C2>*
  Utils::makePair(C1 elt1, C2 elt2)
  {
    std::pair<C1, C2>* p = new std::pair<C1, C2>();

    p->first = elt1;
    p->second = elt2;

    return p;
  }

  /*!
  ** Get an element from a std::vector.
  **
  ** @param elt The element to get
  ** @param tab The table
  **
  ** @return Founded element
  */
  template<typename T>
  T
  Utils::getEltFromArray(const T elt, const std::vector<T> tab)
  {
    typename std::vector<T>::const_iterator result;

    return find(tab.begin(), tab.end(), elt);
  }

  /*!
  ** Get an element from a classic table.
  **
  ** @param elt The element to get
  ** @param tab The table
  **
  ** @return Founded element
  */
  template<typename T>
  T
  Utils::getEltFromArray(const T elt, const T* const tab)
  {
    while (*tab)
    {
      if (elt == *tab)
	return elt;
      tab++;
    }

    return 0;
  }

  /*!
  ** Check if an element is contains by the given vector.
  **
  ** @param elt The element to get
  ** @param tab The table
  **
  ** @return If element was found
  */
  template<typename T>
  bool
  Utils::isInArray(const T elt, const std::vector<T> tab)
  {
    return getEltFromArray(elt, tab) != tab.end();
  }

  /*!
  ** Check if an element is contains by the given classic table.
  **
  ** @param elt The element to get
  ** @param tab The table
  **
  ** @return If element was found
  */
  template<typename T>
  bool
  Utils::isInArray(const T elt, const T* const tab)
  {
    return getEltFromArray(elt, tab) != 0;
  }

  /*!
  ** Convert a string to a choosen type
  **
  ** @param t The dst type
  ** @param s The string to convert
  ** @param f The stream option
  **
  ** @return The dst type
  */
  template <typename T>
  bool
  Utils::fromString(T& t,
		    const std::string& s,
		    std::ios_base& (*f)(std::ios_base&))
  {
    std::istringstream iss (s);

    return !(iss >> f >> t).fail ();
  }

  /*!
  ** Interpret special char like \n
  **
  ** @param s The string where the special char were
  **
  ** @return The modified string
  */
  inline const std::string
  Utils::activeSpecialChar(const std::string& s)
  {
    unsigned int i = 0;
    unsigned int size = s.length();
    std::string stringExpr = "";

    while (i < size)
    {
      if (s[i] == '\\' && i + 1 < size)
      {
	if (s[i + 1] == 'n')
	  stringExpr += '\n';
	else
	  if (s[i + 1] == 'f')
	    stringExpr += '\f';
	  else
	    if (s[i + 1] == 'v')
	      stringExpr += '\v';
	    else
	      if (s[i + 1] == 'r')
		stringExpr += '\r';
	      else
		if (s[i + 1] == 't')
		  stringExpr += '\t';
		else
		  stringExpr += s[i + 1];
	i++;
      }
      else
	stringExpr += s[i];
      i++;
    }

    return stringExpr;
  }
}

namespace std
{

  /*!
  ** Just append a \n or a \r\n depending on the OS.
  ** Replace the std::endl function, to avoid flushing.
  **
  ** @param os The stream tp modify
  **
  ** @return Correct newline constant
  */
  template <class charT, class traits>
  inline basic_ostream<charT, traits>&
  nl(basic_ostream<charT, traits>& os)
  {
#ifdef __WIN32__
    os << "\r\n";
#else
    os << '\n';
#endif
    return os;
  }
}
