#include "ws_configurator.hpp"
#include "ConfiguratorAPI.hpp"


Cws_configuratorEx::Cws_configuratorEx()
{
    CONFIGURATOR_API::initialize();
}

Cws_configuratorEx::~Cws_configuratorEx()
{
}

bool Cws_configuratorEx::ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp)
{
    char *pValue = new char[1024];
    CONFIGURATOR_API::getValue(req.getXPath(), pValue);

    resp.setValue(pValue);
    delete[] pValue;
    return true;
}

bool Cws_configuratorEx::onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp)
{
    CONFIGURATOR_API::setValue(req.getXPath(), req.getValue());
    return true;
}

bool Cws_configuratorEx::ongetTableValue(IEspContext &context, IEspGetTableValueRequest &req, IEspGetTableValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEx::onsetTableValue(IEspContext &context, IEspSetTableValueRequest &req, IEspSetTableValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEx::ongetNumberOfRows(IEspContext &context, IEspGetNumberOfRowsRequest &req, IEspGetNumberOfRowsResponse &resp)
{
    return true;
}

bool Cws_configuratorEx::onopenConfigurationFile(IEspContext &context, IEspOpenConfigurationFileRequest &req, IEspOpenConfigurationFileResponse &resp)
{
    if (CONFIGURATOR_API::openConfigurationFile(req.getFilePath()))
    {
        resp.setCode(1);
    }
    else
    {
        resp.setCode(0);
    }
    return true;
}

bool Cws_configuratorEx::ongetJSONForComponent(IEspContext &context, IEspGetJSONForComponentRequest &req, IEspGetJSONForComponentResponse &resp)
{
    char *pJSON = NULL;
    CONFIGURATOR_API::getJSONByComponentKey(req.getComponentName(), &pJSON);

    if (pJSON != NULL)
    {
        resp.setJSON(pJSON);
        free(pJSON);

        return true;
    }
    else
    {
        return false;
    }
}

bool Cws_configuratorEx::ongetNumberOfAvailableComponents(IEspContext &context, IEspGetNumberOfAvailableComponentsRequest &req, IEspGetNumberOfAvailableComponentsResponse &resp)
{
    resp.setNumber(CONFIGURATOR_API::getNumberOfAvailableComponents());
    return true;
}

bool Cws_configuratorEx::ongetComponentName(IEspContext &context, IEspGetComponentNameRequest &req, IEspGetComponentNameResponse &resp)
{
    char pName[1024];
    CONFIGURATOR_API::getComponentName(req.getNumber(),pName);
    resp.setComponentName(pName);
    return true;
}

bool Cws_configuratorEx::ongetNavigatorJSON(IEspContext &context, IEspGetNavigatorJSONRequest &req, IEspGetNavigatorJSONResponse &resp)
{
    char *pJSON = NULL;
    CONFIGURATOR_API::getNavigatorJSON(&pJSON);
    resp.setJSON(pJSON);
    return true;
}