#ifdef CONFIGURATOR_STATIC_LIB

#include "ConfiguratorAPI.hpp"
#include "BuildSet.hpp"
#include "ConfigSchemaHelper.hpp"
#include "ConfiguratorMain.hpp"
#include "jstring.hpp"


namespace CONFIGURATOR_API
{

static CConfigSchemaHelper *s_pConfigSchemaHelper = NULL;

int getNumberOfAvailableComponents()
{
    assert(s_pConfigSchemaHelper != NULL);

    StringArray arrComps;

    CBuildSetManager::getInstance()->getBuildSetComponents(arrComps);

    return arrComps.length();
}

int getNumberOfAvailableServices()
{
    assert(s_pConfigSchemaHelper != NULL);

    StringArray arrServices;

    CBuildSetManager::getInstance()->getBuildSetServices(arrServices);

    return arrServices.length();
}

const char* getServiceName(int idx, char *pName)
{
    assert(s_pConfigSchemaHelper != NULL);

    if (pName != NULL)
    {
        strncpy(pName, CBuildSetManager::getInstance()->getServiceName(idx), CBuildSetManager::getInstance()->getServiceName(idx) == NULL ? 0 : strlen(CBuildSetManager::getInstance()->getServiceName(idx)));
    }

    return CBuildSetManager::getInstance()->getServiceName(idx);
}

const char* getComponentName(int idx, char *pName)
{
    assert(s_pConfigSchemaHelper != NULL);

    if (pName != NULL)
    {
        strncpy(pName, CBuildSetManager::getInstance()->getComponentName(idx), CBuildSetManager::getInstance()->getComponentName(idx) == NULL ? 0 : strlen(CBuildSetManager::getInstance()->getComponentName(idx)));
    }

    return CBuildSetManager::getInstance()->getComponentName(idx);
}

int initialize(int argc, char *argv[])
{
    assert(s_pConfigSchemaHelper == NULL);

    ConfiguratorMain(argc, argv);

    s_pConfigSchemaHelper = CConfigSchemaHelper::getInstance();

    return 1;
}

}

#endif // CONFIGURATOR_STATIC_LIB
