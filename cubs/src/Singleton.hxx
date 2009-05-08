/*!
** Construct the singleton.
*/
template<typename T>
Singleton<T>::Singleton()
{

}

/*!
** Destruct the singleton.
*/
template<typename T>
Singleton<T>::~Singleton()
{
}

/*!
** Get the instance of the singleton.
**
** @return Instance of the object
*/
template<typename T>
T&
Singleton<T>::getInstance()
{
  static T object;
  return object;
}
