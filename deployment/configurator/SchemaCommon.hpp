﻿#ifndef _SCHEMA_COMMON_HPP_
#define _SCHEMA_COMMON_HPP_


#include <iostream>
#include "jiface.hpp"
#include "jstring.hpp"
#include "jlib.hpp"
#include "ExceptionStrings.hpp"

#define QUICK_OUT(X,Y,Z) QuickOut(X,#Y,get##Y(),Z);
#define QUICK_OUT_2(Y) QuickOut(cout, #Y, get##Y(), offset);
#define QUICK_OUT_ARRAY(X,Z) for (int idx=0; idx < this->length(); idx++)               \
                             {                                                          \
                                QuickOutPad(X,Z+STANDARD_OFFSET_1);                     \
                                X << idx+1 << "]" << std::endl;                         \
                                (this->item(idx)).dump(cout,Z);                         \
                             }

#define QUICK_DOC_ARRAY(X) for (int idx=0; idx < this->length(); idx++)                 \
                           {                                                            \
                                (this->item(idx)).getDocumentation(X);                  \
                           }

#define QUICK_DOJO_JS_ARRAY(X) for (int idx=0; idx < this->length(); idx++)             \
                           {                                                            \
                                (this->item(idx)).getDojoJS(X);                         \
                           }

#define QUICK_QML_ARRAY(X) for (int idx=0; idx < this->length(); idx++)                 \
                           {                                                            \
                                (this->item(idx)).getQML(X);                            \
                           }

#define QUICK_ENV_XPATH(X) for (int idx=0; idx < this->length(); idx++)                 \
                            {                                                           \
                                 (this->item(idx)).populateEnvXPath(X, idx+1);          \
                            }

#define QUICK_LOAD_ENV_XML(X)   assert(X != NULL);                                        \
                                for (int idx=0; idx < this->length(); idx++)              \
                                {                                                         \
                                     (this->item(idx)).loadXMLFromEnvXml(X);              \
                                }

#define QUICK_TRAVERSE_AND_PROCESS  for (int idx=0; idx < this->length(); idx++)        \
{                                                                                       \
    CXSDNodeBase::processEntryHandlers(this);                                           \
    this->item(idx).traverseAndProcessNodes();                                          \
    CXSDNodeBase::processExitHandlers(this);                                            \
}

#define GETTER(X) virtual const char* get##X() const { return m_str##X.str(); }
#define SETTER(X) virtual void set##X(const char* p) { m_str##X.clear().append(p); }
#define GETTERSETTER(X) protected: StringBuffer m_str##X; public: GETTER(X) SETTER(X) public:
#define SETPARENTNODE(X, Y) if (X!= NULL && Y != NULL) X->setParentNode(Y);
//#define DEBUG_MARK_STRDOC strDoc.append(__FILE__).append(":").append(__LINE__).append("\n");
#define DEBUG_MARK_STRDOC
#define DEBUG_MARK_COMMENT(X) X.append("//  ").append(__FILE__).append(":").append(__LINE__).append("\n");
#define DEBUG_MARK_STRJS DEBUG_MARK_COMMENT(strJS)
#define DEBUG_MARK_QML DEBUG_MARK_COMMENT(strQML)
//#define DEBUG_MARK_QML
//#define DEBUG_MARK_STRJS

enum NODE_TYPES
{
    XSD_ERROR = 0x0,
    XSD_ANNOTATION = 0x1,
    XSD_APP_INFO = 0x2,
    XSD_ATTRIBUTE = 0x4,
    XSD_ATTRIBUTE_ARRAY = 0x8,
    XSD_ATTRIBUTE_GROUP = 0x10,
    XSD_ATTRIBUTE_GROUP_ARRAY = 0x20,
    XSD_CHOICE = 0x40,
    XSD_COMPLEX_CONTENT = 0x80,
    XSD_COMPLEX_TYPE = 0x100,
    XSD_COMPLEX_TYPE_ARRAY = 0x200,
    XSD_DOCUMENTATION = 0x400,
    XSD_ELEMENT = 0x800,
    XSD_ELEMENT_ARRAY = 0x1000,
    XSD_EXTENSION = 0x2000,
    XSD_INCLUDE =  0x4000,
    XSD_INCLUDE_ARRAY = 0x8000,
    XSD_RESTRICTION = 0x10000,
    XSD_SCHEMA = 0x20000,
    XSD_SEQUENCE = 0x40000,
    XSD_SIMPLE_TYPE = 0x80000,
    XSD_SIMPLE_TYPE_ARRAY = 0x100000,
    XSD_ENUMERATION = 0x200000,
    XSD_ENUMERATION_ARRAY = 0x4000000
};

static const char* XSD_ERROR_STR("ERROR");
static const char* XSD_ANNOTATION_STR("Annotation");
static const char* XSD_APP_INFO_STR("AppInfo");
static const char* XSD_ATTRIBUTE_STR("Attribute");
static const char* XSD_ATTRIBUTE_ARRAY_STR("AttributeArray");
static const char* XSD_ATTRIBUTE_GROUP_STR("AttributeGroup");
static const char* XSD_ATTRIBUTE_GROUP_ARRAY_STR("AttributeGroupArray");
static const char* XSD_CHOICE_STR("Choice");
static const char* XSD_COMPLEX_CONTENT_STR("ComplexContent");
static const char* XSD_COMPLEX_TYPE_STR("ComplexType");
static const char* XSD_COMPLEX_TYPE_ARRAY_STR("ComplexTypeArray");
static const char* XSD_DOCUMENTATION_STR("Documentation");
static const char* XSD_ELEMENT_STR("Element");
static const char* XSD_ELEMENT_ARRAY_STR("ElementArray");
static const char* XSD_EXTENSION_STR("Extension");
static const char* XSD_INCLUDE_STR("Include");
static const char* XSD_INCLUDE_ARRAY_STR("IncludeArray");
static const char* XSD_RESTRICTION_STR("Restriction");
static const char* XSD_SCHEMA_STR("Schema");
static const char* XSD_SEQUENCE_STR("Sequence");
static const char* XSD_SIMPLE_TYPE_STR("SimpleType");
static const char* XSD_SIMPLE_TYPE_ARRAY_STR("SimpleTypeArray");
static const char* XSD_ENUMERATION_STR("Enumeration");
static const char* XSD_ENUMERATION_ARRAY_STR("EnumerationArray");

static const char* DEFAULT_SCHEMA_DIRECTORY("/opt/HPCCSystems/componentfiles/configxml/");

static const char* XML_ENV_VALUE_OPTIONAL("optional");
static const char* XML_ENV_VALUE_REQUIRED("required");

static unsigned int STANDARD_OFFSET_1 = 3;
static unsigned int STANDARD_OFFSET_2 = 6;

static void QuickOutPad(std::ostream& cout, unsigned int offset)
{
    while(offset > 0)
    {
        cout << " ";
        offset--;
    }
}

static void QuickOutHeader(std::ostream &cout, const char* pLabel, unsigned int offset = 0)
{
    QuickOutPad(cout,offset);
    cout << "\033[32m-- " << pLabel << " START" << " --" << "\033[0m" << std::endl;
}

static void QuickOutFooter(std::ostream &cout, const char* pLabel, unsigned int offset = 0)
{
    QuickOutPad(cout,offset);
    //cout << "<--- FINISH " << pLabel << std::endl;
    cout << "\033[31m" << "-- " << pLabel << " FINISH" << " --" << "\033[0m" << std::endl;
}

static void QuickOut(std::ostream &cout, const char* pLabel, const char* pValue, unsigned int offset = 0)
{
    if (pLabel && strlen(pValue) > 0)
    {
        QuickOutPad(cout,offset+STANDARD_OFFSET_2);
        cout << "\033[34m" << pLabel << ":\t\033[0m" << "\033[34m'\033[0m" << pValue << "\033[34m'" << "\033[0m" << std::endl;
    }
}

static void QuickOut(std::ostream &cout, const char* pLabel, int value, unsigned int offset = 0)
{
    QuickOutPad(cout,offset);
    cout << pLabel << ": " << value << std::endl;
}

class InterfaceImpl : public IInterface
{
public:

    InterfaceImpl()
    {
        atomic_set(&xxcount, 1);
    }

    virtual void Link() const
    {
        atomic_inc(&xxcount);
    }

    virtual bool Release() const
    {
        if (atomic_dec_and_test(&xxcount))
        {
           delete this;
           return true;
        }

        return false;
    }

private:

    mutable atomic_t xxcount;
};


class CXSDNodeBase;

class CXSDNodeHandler : public CInterface
{
public:

    virtual void onEventEntry(const CXSDNodeBase *pNode) const = 0;
    virtual void onEventExit(const CXSDNodeBase *pNode) const = 0;

};

class CXSDNodeBase
{
public:

    CXSDNodeBase(CXSDNodeBase* pParentNode = NULL, NODE_TYPES eNodeType = XSD_ERROR);

    virtual ~CXSDNodeBase();

    GETTERSETTER(XSDXPath)
    GETTERSETTER(EnvXPath)
    GETTERSETTER(EnvValueFromXML)


    void dumpStdOut() const;

    virtual CXSDNodeBase* getParentNode()
    {
        return m_pParentNode;
    }

    virtual const CXSDNodeBase* getConstAncestorNode(unsigned iLevel) const;

    virtual const CXSDNodeBase* getConstParentNode() const
    {
        return m_pParentNode;
    }

    virtual const CXSDNodeBase* getParentNodeByType(NODE_TYPES eNodeType, const CXSDNodeBase *pParent = NULL) const;

    virtual const CXSDNodeBase* getNodeByTypeAndNameAscending(NODE_TYPES eNodeType, const char *pName) const;

    virtual const CXSDNodeBase* getNodeByTypeAndNameDescending(NODE_TYPES eNodeType, const char *pName) const;

    void setParentNode(CXSDNodeBase *pParentNode)
    {
        if (m_pParentNode == NULL)  // Should only be set once, otherwise it's an external schema and should have parent set
        {
            m_pParentNode = pParentNode;
        }
    }

    const char* getNodeTypeStr() const
    {
        return m_pNodeType;
    }

    virtual NODE_TYPES getNodeType() const
    {
        return m_eNodeType;
    }

    virtual void dump(std::ostream& cout, unsigned int offset = 0) const = 0;

    virtual void traverseAndProcessNodes() const = 0;

    virtual const char* getXML(const char* /*pComponent*/)
    {
        return NULL;
    }

    virtual void getDocumentation(StringBuffer &strDoc) const = 0;

    virtual void getDojoJS(StringBuffer &strJS) const = 0;

    virtual void getQML(StringBuffer &strQML) const
    {
    }

    virtual void populateEnvXPath(StringBuffer strXPath, unsigned int index = 1)
    {
    }

    virtual void loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
    {
    }

    static void addEntryHandler(CXSDNodeHandler &Handler)
    {
        s_callBackEntryHandlersArray.append(Handler);
    }

    static void addExitHandler(CXSDNodeHandler &Handler)
    {
        s_callBackExitHandlersArray.append(Handler);
    }

protected:

    static void processEntryHandlers(const CXSDNodeBase *pBase);

    static void processExitHandlers(const CXSDNodeBase *pBase);

    CXSDNodeBase*               m_pParentNode;
    StringBuffer                m_strXML;
    NODE_TYPES                  m_eNodeType;
    char                        m_pNodeType[1024];
    static CIArrayOf<CXSDNodeHandler>  s_callBackEntryHandlersArray;
    static CIArrayOf<CXSDNodeHandler>  s_callBackExitHandlersArray;

private:

} __attribute__((aligned (32)));


class CXSDNode : public CInterface, public CXSDNodeBase
{
public:

    IMPLEMENT_IINTERFACE

    CXSDNode(CXSDNodeBase *pParentNode, NODE_TYPES pNodeType = XSD_ERROR );

    virtual bool checkSelf(NODE_TYPES eNodeType, const char *pName, const char* pCompName) const;

    virtual const CXSDNodeBase* getParentNodeByType(NODE_TYPES eNodeType) const;

    virtual const CXSDNodeBase* getNodeByTypeAndNameAscending(NODE_TYPES eNodeType, const char *pName) const;

    virtual const CXSDNodeBase* getNodeByTypeAndNameDescending(NODE_TYPES eNodeType, const char *pName) const;

private:

};

#endif // _SCHEMA_COMMON_HPP_
