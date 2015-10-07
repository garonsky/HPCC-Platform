#include "ws_configurator.hpp"
#include "ConfiguratorAPI.hpp"


Cws_configuratorEX::Cws_configuratorEX()
{
}

Cws_configuratorEX::~Cws_configuratorEX()
{
}

bool Cws_configuratorEX::ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEX::onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEX::ongetTableValue(IEspContext &context, IEspGetTableValueRequest &req, IEspGetTableValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEX::onsetTableValue(IEspContext &context, IEspSetTableValueRequest &req, IEspSetTableValueResponse &resp)
{
    return true;
}

bool Cws_configuratorEX::ongetNumberOfRows(IEspContext &context, IEspGetNumberOfRowsRequest &req, IEspGetNumberOfRowsResponse &resp)
{
    return true;
}




