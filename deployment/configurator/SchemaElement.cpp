#include <cassert>
#include "jptree.hpp"
#include "jstring.hpp"
#include "XMLTags.h"
#include "SchemaAnnotation.hpp"
#include "SchemaCommon.hpp"
#include "SchemaElement.hpp"
#include "SchemaComplexType.hpp"
#include "SchemaElement.hpp"
#include "SchemaAttributes.hpp"
#include "SchemaAppInfo.hpp"
#include "SchemaDocumentation.hpp"
#include "DocumentationMarkup.hpp"
#include "ConfigSchemaHelper.hpp"
#include "DojoJSMarkup.hpp"
#include "ConfigSchemaHelper.hpp"
#include "DojoHelper.hpp"
#include "QMLMarkup.hpp"
#include "SchemaMapManager.hpp"
#include "ConfiguratorMain.hpp"

CElement* CElement::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);
    assert(pParentNode != NULL);

    if (pSchemaRoot == NULL || pParentNode == NULL)
    {
        return NULL;
    }

    CElement *pElement = new CElement();

    pElement->setXSDXPath(xpath);

    IPropertyTree *pTree = pSchemaRoot->queryPropTree(xpath);

    if (pElement != NULL && pTree != NULL)
    {
        pElement->setName(pTree->queryProp(XML_ATTR_NAME));
    }

    Owned<IAttributeIterator> iterAttrib = pTree->getAttributes(true);

    ForEach(*iterAttrib)
    {
        if (strcmp(iterAttrib->queryName(), XML_ATTR_NAME) == 0)
        {
            pElement->setName(iterAttrib->queryValue());
        }
        else if (strcmp(iterAttrib->queryName(), XML_ATTR_MAXOCCURS) == 0)
        {
            pElement->setMaxOccurs(iterAttrib->queryValue());
        }
        else if (strcmp(iterAttrib->queryName(), XML_ATTR_MINOCCURS) == 0)
        {
            pElement->setMinOccurs(iterAttrib->queryValue());
        }
        else if (strcmp(iterAttrib->queryName(), XML_ATTR_TYPE) == 0)
        {
            pElement->setType(iterAttrib->queryValue());
        }

        assert(iterAttrib->queryValue() != NULL);
    }

    assert(strlen(pElement->getName()) > 0);

    StringBuffer strXPathExt(xpath);

    strXPathExt.append("/").append(XSD_TAG_ANNOTATION);
    pElement->m_pAnnotation = CAnnotation::load(pElement, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_COMPLEX_TYPE);
    pElement->m_pComplexTypeArray = CComplexTypeArray::load(pElement, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_ATTRIBUTE);
    pElement->m_pAttributeArray = CAttributeArray::load(pElement, pSchemaRoot, strXPathExt.str());

    if (pElement->m_pAnnotation != NULL && pElement->m_pAnnotation->getAppInfo() != NULL && strlen(pElement->m_pAnnotation->getAppInfo()->getTitle()) > 0)
    {
        /****  MUST FIX TO HAVE CORRECT UI TAB LABELS (but getName is expected to return the XPATH name *****/
        //pElement->setName(pElement->m_pAnnotation->getAppInfo()->getTitle());
        pElement->setTitle(pElement->m_pAnnotation->getAppInfo()->getTitle());
    }
    else
    {
        pElement->setTitle(pElement->getName());
    }

    SETPARENTNODE(pElement, pParentNode);

    return pElement;
}

const CElement* CElement::getTopMostElement(const CXSDNodeBase *pNode)
{
    if (pNode == NULL)
    {
        return NULL;
    }
    else if (pNode->getNodeType() == XSD_ELEMENT)
    {
        if (pNode->getParentNodeByType(XSD_ELEMENT) == NULL)
        {
            assert(dynamic_cast<const CElement*>(pNode) != NULL);

            return dynamic_cast<const CElement*>(pNode);
        }
    }

    return getTopMostElement(pNode->getParentNodeByType(XSD_ELEMENT));
}

const char* CElement::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length () == 0)
    {
        m_strXML.append("\n<").append(getName()).append(" ");

        if (m_pAnnotation != NULL)
        {
            m_strXML.append(m_pAnnotation->getXML(NULL));
        }
        if (m_pComplexTypeArray != NULL)
        {
            m_strXML.append(m_pComplexTypeArray->getXML(NULL));
        }
        if (m_pAttributeArray != NULL)
        {
            m_strXML.append(m_pAttributeArray->getXML(NULL));
        }

//        m_strXML.append("/>\n");
    }

    return m_strXML.str();
}

void CElement::dump(std::ostream &cout, unsigned int offset) const
{
    offset += STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_ELEMENT_STR, offset);

    QUICK_OUT(cout, Name, offset);
    QUICK_OUT(cout, Type, offset);
    QUICK_OUT(cout, MinOccurs, offset);
    QUICK_OUT(cout, MaxOccurs, offset);
    QUICK_OUT(cout, Title,  offset);
    QUICK_OUT(cout, XSDXPath,  offset);
    QUICK_OUT(cout, EnvXPath,  offset);
    QUICK_OUT(cout, EnvValueFromXML,  offset);

    if (m_pAnnotation != NULL)
    {
        m_pAnnotation->dump(cout, offset);
    }

    if (m_pComplexTypeArray != NULL)
    {
        m_pComplexTypeArray->dump(cout, offset);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->dump(cout, offset);
    }

    QuickOutFooter(cout, XSD_ELEMENT_STR, offset);
}

void CElement::getDocumentation(StringBuffer &strDoc) const
{
    const CXSDNodeBase *pGrandParentNode = this->getConstParentNode()->getConstParentNode();

    assert(pGrandParentNode != NULL);

    if (pGrandParentNode == NULL)
    {
        return;
    }

    if (m_pAnnotation != NULL && m_pAnnotation->getAppInfo() != NULL && m_pAnnotation->getAppInfo()->getViewType() != NULL && stricmp(m_pAnnotation->getAppInfo()->getViewType(), "none") == 0)
    {
        return;
    }

    if (this->getName() != NULL && (stricmp(this->getName(), "Instance") == 0 || stricmp(this->getName(), "Note") == 0 || stricmp(this->getName(), "Notes") == 0 ||  stricmp(this->getName(), "Topology") == 0 ))
    {
        return; // don't document instance
    }

    assert(strlen(this->getName()) > 0);

    if (pGrandParentNode->getNodeType() == XSD_SCHEMA)
    {
        StringBuffer strName(this->getName());

        strName.replace(' ', '_');

        strDoc.append(DM_HEADING);

        // component name would be here
        strDoc.appendf("<%s %s=\"%s%s\">\n", DM_SECT2, DM_ID, strName.str(),"_mod");
        strDoc.appendf("<%s>%s</%s>\n", DM_TITLE_LITERAL, this->getName(), DM_TITLE_LITERAL);

        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getDocumentation(strDoc);
            DEBUG_MARK_STRDOC;
        }

        strDoc.append(DM_SECT3_BEGIN);
        DEBUG_MARK_STRDOC;
        strDoc.append(DM_TITLE_BEGIN).append(DM_TITLE_END);

        if (m_pComplexTypeArray != NULL)
        {
            m_pComplexTypeArray->getDocumentation(strDoc);
        }

        strDoc.append(DM_SECT3_END);
        return;
    }
    else if (m_pComplexTypeArray != NULL)
    {
        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getDocumentation(strDoc);
            DEBUG_MARK_STRDOC;
        }

        if (pGrandParentNode->getNodeType() == XSD_CHOICE)
        {
            strDoc.appendf("%s%s%s", DM_PARA_BEGIN, this->getName(), DM_PARA_END);
        }
        else
        {
            strDoc.appendf("%s%s%s", DM_TITLE_BEGIN, this->getName(), DM_TITLE_END);
        }

        DEBUG_MARK_STRDOC;

        m_pComplexTypeArray->getDocumentation(strDoc);
    }
    else if (m_pComplexTypeArray == NULL)
    {
        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getDocumentation(strDoc);
            DEBUG_MARK_STRDOC;
        }

        strDoc.appendf("%s%s%s", DM_PARA_BEGIN, this->getName(), DM_PARA_END);
        DEBUG_MARK_STRDOC;

        if (m_pAnnotation != NULL && m_pAnnotation->getDocumentation() != NULL)
        {
            m_pAnnotation->getDocumentation(strDoc);
            DEBUG_MARK_STRDOC;
        }

        if (m_pAttributeArray != NULL)
        {
            m_pAttributeArray->getDocumentation(strDoc);
        }
    }
}

void CElement::getDojoJS(StringBuffer &strJS) const
{
    //TODO: Handle tree view
    if (stricmp(this->getType(), "NodeType") == 0)
    {
        return;
    }

    const CXSDNodeBase *pGrandParentNode = this->getConstAncestorNode(2);

    assert(pGrandParentNode != NULL);

    if (pGrandParentNode == NULL)
    {
        return;
    }

    if (m_pAnnotation != NULL && m_pAnnotation->getAppInfo() != NULL && m_pAnnotation->getAppInfo()->getViewType() != NULL)
    {
        if (stricmp(m_pAnnotation->getAppInfo()->getViewType(), "none") == 0)
        {
            return;
        }
        /*else if (stricmp(m_pAnnotation->getAppInfo()->getViewType(), "list") == 0)
        {
            strJS.append("if (cp != null) dojo.place(\"<div><H1>").append(this->getName()).append("</H1></div>\", cp.containerNode, cp.containerNode.length);\n");
          //  return;
        }*/
    }

    assert(strlen(this->getName()) > 0);

    if (pGrandParentNode->getNodeType() == XSD_SCHEMA)
    {
        strJS.append(DJ_START);
        DEBUG_MARK_STRJS;

        if (m_pAnnotation != NULL)
        {
            m_pAnnotation->getDojoJS(strJS);
        }

        if (m_pComplexTypeArray != NULL)
        {
            m_pComplexTypeArray->getDojoJS(strJS);
        }

        strJS.append(CConfigSchemaHelper::getInstance()->getToolTipJS());
        strJS.append(DJ_FINISH);

        return;
    }
    else if (CDojoHelper::IsElementATab(this) == false)
    {
        strJS.append(DJ_LAYOUT_BEGIN);
        DEBUG_MARK_STRJS;

        if (m_pAnnotation != NULL && m_pAnnotation->getAppInfo() != NULL && stricmp(m_pAnnotation->getAppInfo()->getViewType(), "list") == 0)
        {
            strJS.append(DJ_DIV_HEADING_BEGIN).append(this->getTitle()).append(DJ_DIV_HEADING_END);
            DEBUG_MARK_STRJS;
        }

        if (m_pComplexTypeArray != NULL)
        {
            m_pComplexTypeArray->getDojoJS(strJS);
        }

        if (this->getConstAncestorNode(2)->getNodeType() == XSD_SEQUENCE)
        {
            strJS.append(DJ_LAYOUT_CONCAT_BEGIN);
            DEBUG_MARK_STRJS;
            strJS.append(createDojoColumnLayout(this->getTitle(), getRandomID()));
            DEBUG_MARK_STRJS;
            strJS.append(DJ_LAYOUT_CONCAT_END);
            DEBUG_MARK_STRJS;
        }

        strJS.append(DJ_LAYOUT_END);
        DEBUG_MARK_STRJS;
    }
    else if (m_pComplexTypeArray != NULL)
    {
        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getDojoJS(strJS);
        }

        if (pGrandParentNode->getNodeType() == XSD_CHOICE)
        {
            //strJS.append(DJ_LAYOUT_END);
            //DEBUG_MARK_STRJS;
        }
        else
        {

        }

        m_pComplexTypeArray->getDojoJS(strJS);

        //strJS.append(DJ_LAYOUT_END);
        //DEBUG_MARK_STRJS;
    }
    else if (m_pComplexTypeArray == NULL)
    {
        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getDojoJS(strJS);
        }

        if (CDojoHelper::IsElementATab(this) == true)
        {
            genTabDojoJS(strJS, this->getTitle());
        }

        if (m_pAnnotation != NULL && m_pAnnotation->getDocumentation() != NULL)
        {
            m_pAnnotation->getDojoJS(strJS);
        }

        if (m_pAttributeArray != NULL)
        {
            m_pAttributeArray->getDojoJS(strJS);
        }

        strJS.append(DJ_TABLE_PART_2);
    }
}

void CElement::getQML(StringBuffer &strQML) const
{
    //TODO: Handle tree view
    if (stricmp(this->getType(), "NodeType") == 0)
    {
        return;
    }

    const CXSDNodeBase *pGrandParentNode = this->getConstAncestorNode(2);

    assert(pGrandParentNode != NULL);

    if (pGrandParentNode == NULL)
    {
        return;
    }

    if (m_pAnnotation != NULL && m_pAnnotation->getAppInfo() != NULL && m_pAnnotation->getAppInfo()->getViewType() != NULL)
    {
        if (stricmp(m_pAnnotation->getAppInfo()->getViewType(), "none") == 0)
        {
            return;
        }
    }

    assert(strlen(this->getTitle()) > 0);

    if (pGrandParentNode->getNodeType() == XSD_SCHEMA)
    {
        strQML.append(QML_START);
        DEBUG_MARK_QML;
        strQML.append(QML_TAB_VIEW_BEGIN);
        DEBUG_MARK_QML;

        if (m_pAnnotation != NULL)
        {
            m_pAnnotation->getQML(strQML);
        }

        if (m_pComplexTypeArray != NULL)
        {
            m_pComplexTypeArray->getQML(strQML);
        }

        strQML.append(QML_TAB_VIEW_STYLE);
        DEBUG_MARK_QML;
        strQML.append(QML_TAB_VIEW_END);
        DEBUG_MARK_QML;
        strQML.append(QML_TAB_TEXT_STYLE);
        DEBUG_MARK_QML;
        strQML.append(QML_END);
        DEBUG_MARK_QML;

        return;
    }
    else if (CDojoHelper::IsElementATab(this) == false)
    {
        if (m_pComplexTypeArray != NULL)
        {
            m_pComplexTypeArray->getQML(strQML);
        }

        if (this->getConstAncestorNode(2)->getNodeType() == XSD_SEQUENCE  && this->m_pComplexTypeArray == NULL)
        {
            strQML.append(QML_ROW_BEGIN);
            DEBUG_MARK_QML;

            strQML.append(QML_TABLE_VIEW_BEGIN);
            DEBUG_MARK_QML;

            strQML.append(QML_MODEL).append(modelNames[CConfigSchemaHelper::getInstance(0)->getNumberOfTables()]);
            DEBUG_MARK_QML;

            const CElement *pElement = dynamic_cast<const CElement*>(this->getParentNodeByType(XSD_ELEMENT));
            assert(pElement != NULL);

            strQML.append(QML_PROPERTY_STRING_TABLE_BEGIN).append(modelNames[CConfigSchemaHelper::getInstance()->getNumberOfTables()]).append(QML_PROPERTY_STRING_TABLE_PART_1).append(pElement->getXSDXPath()).append(QML_PROPERTY_STRING_TABLE_END);
            DEBUG_MARK_QML;

            CQMLMarkupHelper::getTableViewColumn(strQML, this->getTitle(), this->getEnvXPath());
            DEBUG_MARK_QML;

            CConfigSchemaHelper::getInstance()->incTables();

            strQML.append(QML_TABLE_VIEW_END);
            DEBUG_MARK_QML;

            strQML.append(QML_ROW_END);
            DEBUG_MARK_QML;
        }
    }
    else if (m_pComplexTypeArray != NULL)
    {
        if (m_pAnnotation != NULL)
        {
            m_pAnnotation->getQML(strQML);
        }

        CQMLMarkupHelper::getTabQML(strQML, this->getTitle());
        DEBUG_MARK_QML;

        strQML.append(QML_GRID_LAYOUT_BEGIN_1);
        DEBUG_MARK_QML;

        m_pComplexTypeArray->getQML(strQML);

        strQML.append(QML_GRID_LAYOUT_END);
        DEBUG_MARK_QML;

        strQML.append(QML_TAB_END);
        DEBUG_MARK_QML;

    }
    else if (m_pComplexTypeArray == NULL)
    {
        if (m_pAnnotation!= NULL)
        {
            m_pAnnotation->getQML(strQML);
        }

        if (m_pAnnotation != NULL && m_pAnnotation->getDocumentation() != NULL)
        {
            m_pAnnotation->getQML(strQML);
        }

        if (CDojoHelper::IsElementATab(this) == true)
        {
            CQMLMarkupHelper::getTabQML(strQML, this->getTitle());
            DEBUG_MARK_QML;

            strQML.append(QML_GRID_LAYOUT_BEGIN);
            DEBUG_MARK_QML;
        }

        if (m_pAttributeArray != NULL)
        {
            m_pAttributeArray->getQML(strQML);
        }

        if (CDojoHelper::IsElementATab(this) == true)
        {
            strQML.append(QML_GRID_LAYOUT_END);
            DEBUG_MARK_QML;

            strQML.append(QML_TAB_END);
            DEBUG_MARK_QML;
        }
    }
}

void CElement::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    assert(strXPath.length() > 0);

    strXPath.append("/").append(this->getName()).append("[").append(index).append("]");

    this->setEnvXPath(strXPath);

    if (m_pComplexTypeArray != NULL)
    {
        m_pComplexTypeArray->populateEnvXPath(strXPath);
    }
    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->populateEnvXPath(strXPath);
    }
}

void CElement::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    CConfigSchemaHelper::getInstance()->getSchemaMapManager()->addMapOfXPathToElement(this->getEnvXPath(), this);

/*    if (this->getConstAncestorNode(2)->getNodeType() == XSD_SCHEMA)
    {
        m_bTopLevelElement = true;
    }*/

    if (m_pComplexTypeArray != NULL)
    {
        try
        {
            m_pComplexTypeArray->loadXMLFromEnvXml(pEnvTree);
        }
        catch (...)
        {
            // node described in XSD doesn't exist in XML
            // time to do validation?
        }
    }
    if (m_pAttributeArray != NULL)
    {
        try
        {
            m_pAttributeArray->loadXMLFromEnvXml(pEnvTree);
        }
        catch (...)
        {
        }
    }

    if (m_pAttributeArray == NULL && m_pComplexTypeArray == NULL)
    {
        const char* pValue =  pEnvTree->queryPropTree(this->getEnvXPath())->queryProp("");

        if (pValue != NULL)
        {
            this->setEnvValueFromXML(pValue);

//            CConfigSchemaHelper::getInstance()->getSchemaMapManager()->addMapOfXPathToElement(this->getEnvXPath(), this);
            CConfigSchemaHelper::getInstance()->appendElementXPath(this->getEnvXPath());
        }
    }
}

void CElement::traverseAndProcessNodes() const
{
    CXSDNodeBase::processEntryHandlers(this);

    if (m_pAnnotation != NULL)
    {
        m_pAnnotation->traverseAndProcessNodes();
    }

    if (m_pComplexTypeArray != NULL)
    {
        m_pComplexTypeArray->traverseAndProcessNodes();
    }

    CXSDNodeBase::processExitHandlers(this);
}

void CElementArray::dump(std::ostream &cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_ELEMENT_ARRAY_STR, offset);

    QUICK_OUT(cout, XSDXPath,  offset);
    QUICK_OUT(cout, EnvXPath,  offset);
    QUICK_OUT_ARRAY(cout, offset);

    QuickOutFooter(cout, XSD_ELEMENT_ARRAY_STR, offset);
}

void CElementArray::getDocumentation(StringBuffer &strDoc) const
{
    QUICK_DOC_ARRAY(strDoc);
}

void CElementArray::getDojoJS(StringBuffer &strDoc) const
{
    QUICK_DOJO_JS_ARRAY(strDoc);
}

void CElementArray::getQML(StringBuffer &strQML) const
{
    QUICK_QML_ARRAY(strQML);
}

void CElementArray::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    assert(index == 1);  // Only 1 array of elements per node

    this->setEnvXPath(strXPath);

    StringBuffer mapKey(strXPath);

    for (int idx=0; idx < this->length(); idx++)
    {
        (this->item(idx)).populateEnvXPath(strXPath, 1);

        mapKey.setf("%s[%d]", this->getXSDXPath(), idx+1);

        CConfigSchemaHelper::getInstance()->getSchemaMapManager()->addMapOfXPathToElementArray(mapKey.str(), this);
    }
}

void CElementArray::traverseAndProcessNodes() const
{
    QUICK_TRAVERSE_AND_PROCESS;
}

const char* CElementArray::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length() == 0)
    {
        int length = this->length();

        for (int idx = 0; idx < length; idx++)
        {
            CElement &Element = this->item(idx);

            m_strXML.append(Element.getXML(NULL));

            if (idx+1 < length)
            {
                m_strXML.append("\n");
            }
        }
    }

    return m_strXML.str();
}

void CElementArray::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    int nUniqueElements = this->length();

    for (int idx = 0; idx < nUniqueElements; idx++)
    {
        StringBuffer strXPath(this->item(idx).getEnvXPath());

        if (pEnvTree->hasProp(strXPath.str()) == false)
        {
            continue;
        }

        int subIndex = 1;

        do
        {
            StringBuffer strEnvXPath(this->item(idx).getEnvXPath());
            CConfigSchemaHelper::stripXPathIndex(strEnvXPath);

            strEnvXPath.appendf("[%d]",subIndex);

            if (pEnvTree->hasProp(strEnvXPath.str()) == false)
            {
                break;
            }

            CElement *pElement = NULL;
            if (subIndex > 1)
            {
                pElement = CElement::load(this, this->getSchemaRoot(), this->item(idx).getXSDXPath());
                pElement->populateEnvXPath(this->getEnvXPath(), subIndex);

                this->append(*pElement);
            }
            else
            {
                pElement = &(this->item(idx));

                if (pElement->getConstAncestorNode(2)->getNodeType() == XSD_SCHEMA)
                {
                    pElement->setTopLevelElement(true);
                }
            }
            pElement->loadXMLFromEnvXml(pEnvTree);

            subIndex++;
        }
        while (true);
    }
}

CElementArray* CElementArray::load(const char* pSchemaFile)
{
    assert(pSchemaFile != NULL);

    if (pSchemaFile == NULL)
    {
        return NULL;
    }

    Linked<IPropertyTree> pSchemaRoot;

    StringBuffer schemaPath;

    schemaPath.appendf("%s%s", DEFAULT_SCHEMA_DIRECTORY, pSchemaFile);

    pSchemaRoot.setown(createPTreeFromXMLFile(schemaPath.str()));

    return CElementArray::load(NULL, pSchemaRoot, XSD_TAG_ELEMENT);
}

CElementArray* CElementArray::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);

    if (pSchemaRoot == NULL)
    {
        return NULL;
    }

    CElementArray *pElemArray = new CElementArray(pParentNode);

    assert(pElemArray != NULL);

    pSchemaRoot->Link();
    pElemArray->setSchemaRoot(pSchemaRoot);

    StringBuffer strXPathExt(xpath);
    pElemArray->setXSDXPath(xpath);

    Owned<IPropertyTreeIterator> elemIter = pSchemaRoot->getElements(xpath);

    int count = 1;

    ForEach(*elemIter)
    {
        strXPathExt.set(xpath);
        strXPathExt.appendf("[%d]", count);

        CElement *pElem = CElement::load(pElemArray, pSchemaRoot, strXPathExt.str());

        assert(pElem);

        pElemArray->append(*pElem);

        count++;
    }

    if (pElemArray->length() == 0)
    {
        return NULL;
    }

    SETPARENTNODE(pElemArray, pParentNode);

    return pElemArray;
}

int CElementArray::getCountOfSiblingElements(const char *pXPath) const
{
    assert(pXPath != NULL && *pXPath != 0);

    int count = 0;

    for (int idx=0; idx < this->length(); idx++)
    {
        if (strcmp(this->item(idx).getXSDXPath(), pXPath) == 0)
        {
            count++;
        }
    }

    return count;
}
