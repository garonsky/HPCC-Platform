#ifndef _WSCONFIGURATOR_HPP_
#define _WSCONFIGURATOR_HPP_

#include "ws_configurator_esp.ipp"

class Cws_configuratorEX : public Cws_configurator
{
public:
    IMPLEMENT_IINTERFACE

    Cws_configuratorEX();
    virtual ~Cws_configuratorEX();

    virtual bool ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp);
    virtual bool onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp);
    virtual bool ongetTableValue(IEspContext &context, IEspGetTableValueRequest &req, IEspGetTableValueResponse &resp);
    virtual bool onsetTableValue(IEspContext &context, IEspSetTableValueRequest &req, IEspSetTableValueResponse &resp);
    virtual bool ongetNumberOfRows(IEspContext &context, IEspGetNumberOfRowsRequest &req, IEspGetNumberOfRowsResponse &resp);
};

#endif // _WSCONFIGURATOR_HPP_

