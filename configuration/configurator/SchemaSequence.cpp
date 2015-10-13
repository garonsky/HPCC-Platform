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

#include <cassert>
#include "jptree.hpp"
#include "XMLTags.h"
#include "SchemaSequence.hpp"
#include "SchemaElement.hpp"
#include "QMLMarkup.hpp"
#include "JSONMarkUp.hpp"

const CXSDNodeBase* CSequence::getNodeByTypeAndNameDescending(NODE_TYPES eNodeType, const char *pName) const
{
    const CXSDNodeBase* pMatchingNode = NULL;

    if (eNodeType == this->getNodeType() && (pName != NULL ? !strcmp(pName, this->getNodeTypeStr()) : true))
        return this;
    if (m_pElementArray != NULL)
        pMatchingNode = m_pElementArray->getNodeByTypeAndNameDescending(eNodeType, pName);

    return pMatchingNode;
}

CSequence* CSequence::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);
    CSequence *pSequence = NULL;

    if (pSchemaRoot == NULL)
        return NULL;
    if (pSchemaRoot->queryPropTree(xpath) == NULL)
        return NULL;  // no sequence node

    StringBuffer strXPath(xpath);
    strXPath.append("/").append(XSD_TAG_ELEMENT);

    CElementArray *pElemArray = CElementArray::load(NULL, pSchemaRoot, strXPath.str());

    if (pElemArray != NULL)
    {
        pSequence = new CSequence(pParentNode, pElemArray);
        pSequence->setXSDXPath(xpath);
    }
    SETPARENTNODE(pElemArray, pSequence)

    return pSequence;
}

void CSequence::dump(std::ostream& cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_SEQUENCE_STR, offset);
    QUICK_OUT(cout, XSDXPath,  offset);

    if (m_pElementArray != NULL)
        m_pElementArray->dump(cout, offset);

    QuickOutFooter(cout, XSD_SEQUENCE_STR, offset);
}

void CSequence::getDocumentation(StringBuffer &strDoc) const
{
    if (m_pElementArray != NULL)
        m_pElementArray->getDocumentation(strDoc);
}

void CSequence::getQML(StringBuffer &strQML, int idx) const
{
    if (m_pElementArray != NULL)
        m_pElementArray->getQML(strQML);
}

void CSequence::getQML2(StringBuffer &strQML, int idx) const
{
    if (m_pElementArray != NULL)
    {
        this->setUIType(this->getParentNode()->getUIType());
        m_pElementArray->getQML2(strQML);
    }
}

void CSequence::getQML3(StringBuffer &strQML, int idx) const
{   
    if (m_pElementArray != NULL)
        m_pElementArray->getQML3(strQML);
}

void CSequence::getJSON(StringBuffer &strJSON, unsigned int offset, int idx) const
{
    if (m_pElementArray != NULL)
    {
        strJSON.append("\n");
        offset += STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_CONTENT_BEGIN_1);

        offset += STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_INNER_CONTENT_BEGIN_1);

        //m_pElementArray->getJSON(strJSON, offset);

        //DEBUG_MARK_JSON
        strJSON.append("\n");
        offset -= STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_INNER_CONTENT_END);
           //DEBUG_MARK_JSON;

        strJSON.append("\n");
        offset -= STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_CONTENT_END);
        //DEBUG_MARK_JSON;
    }
    /*if (m_pElementArray != NULL)
    {
        offset -= STANDARD_OFFSET_1;

        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_CONTENT_BEGIN_1);
        offset += STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_CONTENT_BEGIN_2);

        offset += STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);

        strJSON.append(JSON_INNER_CONTENT_BEGIN_1);
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_INNER_CONTENT_BEGIN_2);

        //m_pElementArray->getJSON(strJSON, offset);

//        offset -= STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);

        strJSON.append(JSON_INNER_CONTENT_END);

        offset -= STANDARD_OFFSET_1;
        QuickOutPad(strJSON, offset);
        strJSON.append(JSON_CONTENT_END);

        //strJSON.append(JSON_CONTENT_BEGIN).append(CJSONMarkUpHelper::createInnerContent(strJSON, )
    }*/
}

void CSequence::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    if (m_pElementArray != NULL)
        m_pElementArray->populateEnvXPath(strXPath);

    this->setEnvXPath(strXPath);
}

void CSequence::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    if (m_pElementArray != NULL)
        m_pElementArray->loadXMLFromEnvXml(pEnvTree);
}

bool CSequence::hasChildElements() const
{
    if (this->m_pElementArray->length() > 0)
        return true;
    else
        return false;
}
