#ifndef _CONFIGURATOR_API_HPP_
#define _CONFIGURATOR_API_HPP_

namespace CONFIGURATOR_API
{

extern "C" int initialize(int argc, char *argv[]);
extern "C" int getNumberOfAvailableComponents();
extern "C" int getNumberOfAvailableServices();
extern "C" const char* getServiceName(int idx, char *pName = 0);
extern "C" const char* getComponentName(int idx, char *pName = 0);

}


#endif // l_CONFIGURATOR_API_HPP_
