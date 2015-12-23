/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2015 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */

#ifndef _SCHEMA_KEY_HPP_
#define _SCHEMA_KEY_HPP_

#include "SchemaCommon.hpp"
#include "jstring.hpp"

namespace CONFIGURATOR
{

class CSelector;
class CFieldArray;
class CAnnotation;
class CAttribute;

class CKey : public CXSDNode
{
    friend class CKeyArray;
    friend class CKeyRef;

public:

    virtual ~CKey()
    {
    }

    virtual void dump(::std::ostream &cout, unsigned int offset = 0) const;
    virtual void populateEnvXPath(::StringBuffer strXPath, unsigned int index = 1);
    virtual void getDocumentation(::StringBuffer &strDoc) const
    {
        UNIMPLEMENTED;
    }
    virtual void getQML(::StringBuffer &strQML, int idx = -1) const
    {
        UNIMPLEMENTED;
    }

    const CAnnotation* getAnnotation() const
    {
        return m_pAnnotation;
    }

    const CSelector* getSelector() const
    {
        return m_pSelector;
    }

    const CFieldArray* getFieldArray() const
    {
        return m_pFieldArray;
    }

    virtual bool checkConstraint(const CAttribute *pAttrib, const char *pValue) const;
    void getEnvXPathToKey(::StringBuffer &strXPath, int idx = 0) const;
   // void getXSDXPathToKey(::StringBuffer &strXPath, int idx = 0) const;

    static CKey* load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath);

    GETTERSETTER(Name)
    GETTERSETTER(ID)

protected:

    CKey(CXSDNodeBase* pParentNode) : CXSDNode::CXSDNode(pParentNode, XSD_KEY), m_pFieldArray(NULL), m_pSelector(NULL), m_pAnnotation(NULL)
    {
    }

    CFieldArray *m_pFieldArray;
    CSelector *m_pSelector;
    CAnnotation *m_pAnnotation;
};

class CKeyArray : public CIArrayOf<CKey>, public InterfaceImpl, public CXSDNodeBase
{
public:

    virtual ~CKeyArray()
    {
    }

    virtual void dump(::std::ostream& cout, unsigned int offset = 0) const;
    virtual void populateEnvXPath(::StringBuffer strXPath, unsigned int index = 1);

    virtual void getDocumentation(::StringBuffer &strDoc) const
    {
        UNIMPLEMENTED;
    }
    virtual void getQML(::StringBuffer &strQML, int idx = -1) const
    {
        UNIMPLEMENTED;
    }
    virtual void loadXMLFromEnvXml(const ::IPropertyTree *pEnvTree)
    {
        UNIMPLEMENTED;
    }
    virtual bool checkConstraint(const CAttribute *pAttrib, const char *pValue) const;

    static CKeyArray* load(CXSDNodeBase* pParentNode, const ::IPropertyTree *pSchemaRoot, const char* xpath);

protected:

    CKeyArray(CXSDNodeBase* pParentNode = NULL) : CXSDNodeBase::CXSDNodeBase(pParentNode, XSD_KEY_ARRAY)
    {
    }
};

}
#endif // _SCHEMA_KEY_HPP_
