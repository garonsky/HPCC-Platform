#include "ws_configurator.hpp"
#include "ConfiguratorAPI.hpp"
#include "jstring.hpp"


Cws_configuratorEx::Cws_configuratorEx()
{
    CONFIGURATOR_API::initialize();
}

Cws_configuratorEx::~Cws_configuratorEx()
{
}

bool Cws_configuratorEx::ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp)
{
    StringBuffer strXPath(req.getXPath());
    strXPath.replace('_','/');

    char *pValue = new char[4096];
    CONFIGURATOR_API::getValue(strXPath.str(), pValue);

    resp.setValue(pValue);
    delete[] pValue;
    return true;
}

bool Cws_configuratorEx::onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp)
{
    StringBuffer strXPath(req.getXPath());
    strXPath.replace('_','/');

    CONFIGURATOR_API::setValue(strXPath.str(), req.getValue());
    return true;
}

bool Cws_configuratorEx::ongetTableValue(IEspContext &context, IEspGetTableValueRequest &req, IEspGetTableValueResponse &resp)
{
    StringBuffer strXPath(req.getXPath());
    strXPath.replace('_','/');

    const char *pValue = CONFIGURATOR_API::getTableValue(req.getXPath(), req.getRow());

    if (pValue)
    {
        resp.setValue(pValue);
        return true;
    }
    else
        return false;

}

bool Cws_configuratorEx::onsetTableValue(IEspContext &context, IEspSetTableValueRequest &req, IEspSetTableValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEx::ongetNumberOfRows(IEspContext &context, IEspGetNumberOfRowsRequest &req, IEspGetNumberOfRowsResponse &resp)
{
    StringBuffer strXPath(req.getXPath());
    strXPath.replace('_','/');

    int nRows = CONFIGURATOR_API::getNumberOfRows(strXPath.str());

    resp.setRows(nRows);

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

bool Cws_configuratorEx::onsaveConfigurationFile(IEspContext &context, IEspSaveConfigurationFileRequest &req, IEspSaveConfigurationFileResponse &resp)
{
    return CONFIGURATOR_API::saveConfigurationFile();
}

bool Cws_configuratorEx::onsaveConfigurationFileAs(IEspContext &context, IEspSaveConfigurationFileAsRequest &req, IEspSaveConfigurationFileAsResponse &resp)
{
    return CONFIGURATOR_API::saveConfigurationFileAs(req.getFilePath());
}
