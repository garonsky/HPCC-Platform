#ifndef _SCHEMA_SEQUENCE_HPP_
#define _SCHEMA_SEQUENCE_HPP_

#include "SchemaCommon.hpp"

class CElementArray;
class IPropertyTree;

class CSequence : public CXSDNode
{
public:

    CSequence(CXSDNodeBase* pParentNode = NULL, CElementArray* pElemArray = NULL) : CXSDNode::CXSDNode(pParentNode, XSD_SEQUENCE), p_mElementArray(pElemArray)
    {
    }

    virtual ~CSequence()
    {
    }

    virtual void dump(std::ostream& cout, unsigned int offset  = 0) const;

    virtual void getDocumentation(StringBuffer &strDoc) const;

    virtual void getDojoJS(StringBuffer &strJS) const;

    virtual void getQML(StringBuffer &strQML) const;

    virtual void populateEnvXPath(StringBuffer strXPath, unsigned int index = 1);

    virtual void loadXMLFromEnvXml(const IPropertyTree *pEnvTree);

    virtual void traverseAndProcessNodes() const;

    static CSequence* load(CXSDNodeBase* pRootNode, const IPropertyTree *pSchemaRoot, const char* xpath = NULL);

protected:

    CElementArray *p_mElementArray;

private:

};

#endif // _SCHEMA_SEQUENCE_HPP_
