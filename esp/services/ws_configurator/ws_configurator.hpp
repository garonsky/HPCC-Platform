#ifndef _WSCONFIGURATOR_HPP_
#define _WSCONFIGURATOR_HPP_

#include "ws_configurator_esp.ipp"

class Cws_configuratorEx : public Cws_configurator
{
public:
    IMPLEMENT_IINTERFACE

    Cws_configuratorEx();
    virtual ~Cws_configuratorEx();

    virtual bool ongetValue(IEspContext &context, IEspGetValueRequest &req, IEspGetValueResponse &resp);
    virtual bool onsetValue(IEspContext &context, IEspSetValueRequest &req, IEspSetValueResponse &resp);
    virtual bool ongetTableValue(IEspContext &context, IEspGetTableValueRequest &req, IEspGetTableValueResponse &resp);
    virtual bool onsetTableValue(IEspContext &context, IEspSetTableValueRequest &req, IEspSetTableValueResponse &resp);
    virtual bool ongetNumberOfRows(IEspContext &context, IEspGetNumberOfRowsRequest &req, IEspGetNumberOfRowsResponse &resp);
    virtual bool onopenConfigurationFile(IEspContext &context, IEspOpenConfigurationFileRequest &req, IEspOpenConfigurationFileResponse &resp);
    virtual bool ongetJSONForComponent(IEspContext &context, IEspGetJSONForComponentRequest &req, IEspGetJSONForComponentResponse &resp);
    virtual bool ongetNumberOfAvailableComponents(IEspContext &context, IEspGetNumberOfAvailableComponentsRequest &req, IEspGetNumberOfAvailableComponentsResponse &resp);
    virtual bool ongetComponentName(IEspContext &context, IEspGetComponentNameRequest &req, IEspGetComponentNameResponse &resp);
};

#endif // _WSCONFIGURATOR_HPP_

