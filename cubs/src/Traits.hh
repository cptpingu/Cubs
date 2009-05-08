#ifndef TRAITS_HH_
# define TRAITS_HH_

namespace Traits
{
  /*!
  ** This namespace contains a lot of useful traits
  */

  template <typename T>
  struct isPointer
  {
    static const bool value = false;
  };

  template <typename T>
  struct isPointer<T*>
  {
    static const bool value = true;
  };

  template <typename T>
  struct isReference
  {
    static const bool value = false;
  };

  template <typename T>
  struct isReference<T&>
  {
    static const bool value = true;
  };

  template <typename T>
  struct Identity
  {
    typedef T type;
    typedef T& ref;
    typedef T* ptr;
  };

  template <typename T>
  struct Const
  {
    typedef const T type;
    typedef const T& ref;
    typedef const T* ptr;
  };

  template<class T>
  struct Constify
  {
    typedef const T t;
  };

  template<class T>
  struct Constify<T&>
  {
    typedef const T& t;
  };

  template<class T>
  struct Constify<const T>
  {
    typedef const T t;
  };

  template<class T>
  struct Constify<const T&>
  {
    typedef const T& t;
  };
}

#endif /* !TRAITS_HH_ */
