#ifndef CONFIGURATION_HH_
# define CONFIGURATION_HH_

# include <map>
# include <string>
# include "Singleton.hh"

namespace MiniCompiler
{
  class Configuration : public Singleton<Configuration>
  {
    friend class Singleton<Configuration>;

  private:
    Configuration();
    ~Configuration();

  public:
    std::string& operator[](const std::string keyword);

  private:
    std::map<std::string, std::string>		_keyWords;
  };
}

# include "Configuration.hxx"

#endif /* !CONFIGURATION_HH_ */
