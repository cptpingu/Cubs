#include "SharedString.hh"

namespace mystd
{
  /*!
  ** Default constructor. Add an empty SharedString by default.
  */
  SharedString::SharedString()
    : super()
  {
  }

  /*!
  ** Constructor used when user give another SharedString.
  ** Just copy location of the SharedString.
  **
  ** @param s The given SharedString
  */
  SharedString::SharedString(const SharedString& s)
    : super(s)
  {
  }

  /*!
  ** Constructor used when user give a C style string.
  ** Convert it into an std::string, before treat it.
  **
  ** @param s The given C style string.
  */
  SharedString::SharedString(const char* s)
    : super(std::string(s))
  {
  }

  /*!
  ** Constructor used when user give a string.
  **
  ** @param s The given string.
  */
  SharedString::SharedString(const std::string& s)
    : super(s)
  {
  }

  /*!
  ** Just the destructor, nothing special to do !
  */
  SharedString::~SharedString()
  {
  }
}
