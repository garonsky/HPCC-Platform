/*##############################################################################
 *

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

#include "jptree.hpp"
#include "SchemaKey.hpp"
#include "SchemaSelector.hpp"
#include "SchemaField.hpp"
#include "SchemaAnnotation.hpp"
#include "SchemaCommon.hpp"
#include "ConfigSchemaHelper.hpp"
#include "SchemaMapManager.hpp"
#include "SchemaAttributes.hpp"

using namespace CONFIGURATOR;

#define IPropertyTree ::IPropertyTree

CKey* CKey::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);
    assert(pParentNode != NULL);
    assert(pParentNode->getNodeType() == XSD_KEY_ARRAY);

    if (pSchemaRoot == NULL || pParentNode == NULL)
    {
        // TODO: Throw Exception
        return NULL;
    }

    CKey *pKey = NULL;

    if (xpath != NULL && *xpath != 0)
    {
        IPropertyTree* pTree = pSchemaRoot->queryPropTree(xpath);

        if (pTree == NULL)
            return NULL; // no xs:key

        const char* pName = pSchemaRoot->getPropTree(xpath)->queryProp(XML_ATTR_NAME);
        if (pName != NULL)
         {
             pKey = new CKey(pParentNode);
             pKey->setXSDXPath(xpath);
             pKey->setName(pName);
         }
         else
         {
             assert(!"value attribute can be empty!");
             // TODO: throw MakeExceptionFromMap(EX_STR_MISSING_VALUE_ATTRIBUTE_IN_LENGTH);
             return NULL;
         }

         const char *pID = pSchemaRoot->getPropTree(xpath)->queryProp(XML_ATTR_ID);
         if (pID != NULL)
             pKey->setID(pID);

         ::StringBuffer strXPathExt(xpath);
         strXPathExt.append("/").append(XSD_TAG_FIELD);

         if (strXPathExt.charAt(0) == '@')
             strXPathExt.remove(0,1); // remove '@'

         pKey->m_pFieldArray = CFieldArray::load(pKey, pSchemaRoot, strXPathExt.str());

         strXPathExt.clear().set(xpath);
         strXPathExt.append("/").append(XSD_TAG_SELECTOR);

         pKey->m_pSelector = CSelector::load(pKey, pSchemaRoot, strXPathExt.str());
         assert(pKey->m_pFieldArray != NULL && pKey->m_pSelector != NULL);

         strXPathExt.append("/").append(XSD_TAG_ANNOTATION);
         pKey->m_pAnnotation = CAnnotation::load(pKey, pSchemaRoot, strXPathExt.str());
    }
    return pKey;
}

void CKey::populateEnvXPath(::StringBuffer strXPath, unsigned int index)
{
    assert(this->m_pSelector != NULL);

    this->setEnvXPath(strXPath.str());

    if (this->m_pSelector != NULL)
    {
        this->m_pSelector->populateEnvXPath(strXPath.str());
        CConfigSchemaHelper::getInstance()->addKeyForReverseAssociation(this);
    }
    StringBuffer strTemp;
    this->getEnvXPathToKey(strTemp);
}

bool CKey::checkConstraint(const CAttribute *pAttrib, const char *pValue) const
{
    assert(pAttrib != NULL);

    bool bRetVal = true;

    if (pAttrib == NULL)
        return false;

    const CElementArray *pElementArray = dynamic_cast<const CElementArray*>(pAttrib->getParentNodeByType(XSD_ELEMENT_ARRAY));

    assert(pElementArray != NULL);

    for (int idx2 = 0; idx2 < pElementArray->length(); idx2++)
    {
        const CComplexTypeArray *pComplexTypeArray = pElementArray->item(idx2).getComplexTypeArray();

        if (pComplexTypeArray == NULL || pComplexTypeArray->length() == 0)
        {
            assert(!"not expecting to have different attributes in the same elementarray or no complexType with attribute");
            continue;
        }

        const CComplexType *pComplexType = const_cast<const CComplexType*>(&(pComplexTypeArray->item(0)));
        const CAttributeArray *pAttributeArray = const_cast<const CAttributeArray*>(pComplexType->getAttributeArray());

        if (pAttributeArray == NULL || pAttributeArray->length() == 0)
        {
            assert(!"not expecting to not find attributes");
            continue;
        }

        for (int idx3 = 0; idx3 < pAttributeArray->length(); idx3++)
        {
            const CAttribute *pAttribute = &(pAttributeArray->item(idx3));
            assert(pAttribute != NULL);

            if (strcmp(pAttribute->getName(), pAttrib->getName()) != 0)
                continue; // not the attribute that i am looking for

            if (pAttribute->getInstanceValue() != NULL && pValue != NULL && strcmp(pAttribute->getInstanceValue(), pValue) == 0)
                return false;
        }
    }

    return bRetVal;
}

void CKey::dump(::std::ostream& cout, unsigned int offset) const
{
    offset += STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_KEY_STR, offset);
    QUICK_OUT(cout, Name, offset);
    QUICK_OUT(cout, ID, offset);
    QUICK_OUT(cout, XSDXPath,  offset);

    if (m_pFieldArray != NULL)
        m_pFieldArray->dump(cout, offset);
    if (m_pSelector != NULL)
        m_pSelector->dump(cout, offset);

    QuickOutFooter(cout, XSD_KEY_STR, offset);
}

void CKey::getEnvXPathToKey(::StringBuffer &strXPath, int idx) const
{
    const CElement *pElement = dynamic_cast<const CElement*>(this->getParentNodeByType(XSD_ELEMENT));

    if (pElement != NULL && this->getSelector() != NULL && this->getSelector()->getXPath(true) != NULL && \
            (this->getSelector()->getXPath(true))[0] != 0 && this->getFieldArray() != NULL && idx < this->getFieldArray()->length())
        strXPath.setf("%s/%s[%s]", pElement->getEnvXPath(), this->getSelector()->getXPath(true), this->getFieldArray()->item(idx).getXPath(false));
    else
        assert(!"Problem with Key, possible missing fields");
}

CKeyArray* CKeyArray::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);
    assert(pParentNode->getNodeType() == XSD_ELEMENT);

    if (pSchemaRoot == NULL || xpath == NULL)
        return NULL;

    ::StringBuffer strXPathExt(xpath);

    CKeyArray *pKeyArray = new CKeyArray(pParentNode);
    pKeyArray->setXSDXPath(xpath);

    Owned<IPropertyTreeIterator> attributeIter = pSchemaRoot->getElements(xpath, ipt_ordered);

    int count = 1;
    ForEach(*attributeIter)
    {
        strXPathExt.clear().append(xpath).appendf("[%d]",count);

        CKey *pKey = CKey::load(pKeyArray, pSchemaRoot, strXPathExt.str());
        if (pKey != NULL)
            pKeyArray->append(*pKey);

        count++;
    }

    if (pKeyArray->length() == 0)
    {
        delete pKeyArray;
        pKeyArray = NULL;
    }
    return pKeyArray;
}

bool CKeyArray::checkConstraint(const CAttribute *pAttrib, const char *pValue) const
{
    assert(pValue != NULL);

    if (pValue == NULL)
        return false;

    for (int idx = 0; idx < this->length(); idx++)
    {
        if ((this->item(idx)).checkConstraint(pAttrib, pValue) == false)
            return false;
    }
    return true;
}

void CKeyArray::dump(::std::ostream &cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_KEY_ARRAY_STR, offset);
    QUICK_OUT(cout, XSDXPath,  offset);
    QUICK_OUT(cout, EnvXPath,  offset);
    QUICK_OUT_ARRAY(cout, offset);
    QuickOutFooter(cout, XSD_KEY_ARRAY_STR, offset);
}

void CKeyArray::populateEnvXPath(::StringBuffer strXPath, unsigned int index)
{
    this->setEnvXPath(strXPath);
    QUICK_ENV_XPATH_WITH_INDEX(strXPath, index)
}
