#include "ws_configurator.hpp"
#include "ConfiguratorAPI.hpp"


Cws_configuratorEx::Cws_configuratorEx()
{
}

Cws_configuratorEx::~Cws_configuratorEx()
{
}

bool Cws_configuratorEx::ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEx::onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp)
{
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
    return CONFIGURATOR_API::openConfigurationFile("");
}
