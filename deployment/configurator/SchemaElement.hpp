#ifndef _SCHEMA_ELEMENT_HPP_
#define _SCHEMA_ELEMENT_HPP_

#include "jiface.hpp"
#include "jstring.hpp"
#include "jlib.hpp"
#include "jarray.hpp"
#include "SchemaCommon.hpp"

class CAnnotation;
class CComplexTypeArray;
class IPropertyTree;
class CAttributeArray;

static const char* DEFAULT_ELEMENT_ARRAY_XPATH(".");

class CElement : public CXSDNode
{
public:

    virtual ~CElement()
    {
    }

    GETTERSETTER(Name)
    GETTERSETTER(MaxOccurs)
    GETTERSETTER(MinOccurs)
    GETTERSETTER(Type)
    GETTERSETTER(Title)

    virtual const char* getXML(const char* /*pComponent*/);

    virtual void dump(std::ostream &cout, unsigned int offset = 0) const;

    virtual void getDocumentation(StringBuffer &strJS) const;

    virtual void getDojoJS(StringBuffer &strDoc) const;

    virtual void getQML(StringBuffer &strQML) const;

    virtual void populateEnvXPath(StringBuffer strXPath, unsigned int index = 1);

    virtual void loadXMLFromEnvXml(const IPropertyTree *pEnvTree);

    virtual void traverseAndProcessNodes() const;

    bool isTopLevelElement() const
    {
        return m_bTopLevelElement;
    }

    void setTopLevelElement(bool b = true)
    {
        m_bTopLevelElement =  b;
    }

    void setParentIndex(int index)
    {
        m_nParentIndex = index;
    }

    int getParentIndex() const
    {
        return m_nParentIndex;
    }

    const CAnnotation* getAnnotation() const
    {
        return m_pAnnotation;
    }

    const CAttributeArray* getAttributeArray() const
    {
        return m_pAttributeArray;
    }

    const CComplexTypeArray* getComplexTypeArray() const
    {
        return m_pComplexTypeArray;
    }

    static const CXSDNodeBase* getAncestorElement(const CXSDNodeBase *pNode)
    {
         return pNode->getParentNodeByType(XSD_ELEMENT);
    }

    static const CElement* getTopMostElement(const CXSDNodeBase *pNode);

    static bool isAncestorTopElement(const CXSDNodeBase *pNode)
    {
        return (pNode != NULL && pNode->getParentNodeByType(XSD_ELEMENT) == getTopMostElement(pNode));
    }

    static CElement* load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath);

protected:

    CElement(CXSDNodeBase* pParentNode, const char* pName = "") : CXSDNode::CXSDNode(pParentNode, XSD_ELEMENT), m_strMinOccurs(""), m_strMaxOccurs(""), m_strName(pName), m_pAnnotation(NULL),
        m_pComplexTypeArray(NULL), m_pAttributeArray(NULL), m_bTopLevelElement(false), m_nParentIndex(-1)
    {
    }

    CAnnotation * m_pAnnotation;
    CComplexTypeArray* m_pComplexTypeArray;
    CAttributeArray* m_pAttributeArray;

    bool m_bTopLevelElement;
    int m_nParentIndex;

private:

    CElement() : CXSDNode::CXSDNode(NULL, XSD_ELEMENT), m_strMinOccurs(""), m_strMaxOccurs(""), m_strName(""), m_pAnnotation(NULL),
        m_pComplexTypeArray(NULL), m_pAttributeArray(NULL), m_bTopLevelElement(false)
    {
    }
};

class CElementArray : public CIArrayOf<CElement>, public InterfaceImpl, public CXSDNodeBase
{
public:

    CElementArray(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot = NULL) : CXSDNodeBase::CXSDNodeBase(pParentNode, XSD_ELEMENT_ARRAY), m_pSchemaRoot(pSchemaRoot)
    {
    }

    virtual ~CElementArray()
    {
    }

    virtual void dump(std::ostream &cout, unsigned int offset = 0) const;

    virtual void getDocumentation(StringBuffer &strDoc) const;

    virtual void getDojoJS(StringBuffer &strJS) const;

    virtual void getQML(StringBuffer &strQML) const;

    virtual void populateEnvXPath(StringBuffer strXPath, unsigned int index = 1);

    virtual void loadXMLFromEnvXml(const IPropertyTree *pEnvTree);

    virtual void traverseAndProcessNodes() const;

    virtual const char* getXML(const char* /*pComponent*/);

    virtual int getCountOfSiblingElements(const char *pXPath) const;

    virtual void setSchemaRoot(const IPropertyTree *pSchemaRoot)
    {
        assert(m_pSchemaRoot == NULL);
        assert(pSchemaRoot);

        m_pSchemaRoot = pSchemaRoot;
    }

    const IPropertyTree* getSchemaRoot() const
    {
        return m_pSchemaRoot;
    }

    static CElementArray* load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath = DEFAULT_ELEMENT_ARRAY_XPATH);

    static CElementArray* load(const char *pSchemaFile);

protected:

    const IPropertyTree *m_pSchemaRoot;

private:

    CElementArray() : CXSDNodeBase::CXSDNodeBase(NULL, XSD_ELEMENT_ARRAY)
    {
    }
};

#endif // _SCHEMA_ELEMENT_HPP_
