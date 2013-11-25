#include "jptree.hpp"
#include "SchemaRestriction.hpp"
#include "SchemaEnumeration.hpp"
#include "SchemaAttributes.hpp"
#include "XMLTags.h"
#include "DojoJSMarkup.hpp"
#include "ConfigSchemaHelper.hpp"
#include "QMLMarkup.hpp"
#include "DocumentationMarkup.hpp"
#include "SchemaMapManager.hpp"

CRestriction::~CRestriction()
{
    CConfigSchemaHelper::getInstance()->getSchemaMapManager()->removeMapOfXPathToRestriction(this->getEnvXPath());
}

void CRestriction::dump(std::ostream& cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_RESTRICTION_STR, offset);

    QUICK_OUT_2(Base);
    QUICK_OUT_2(ID);
    QUICK_OUT(cout, XSDXPath,  offset);
    QUICK_OUT(cout, EnvXPath,  offset);
    QUICK_OUT(cout, EnvValueFromXML,  offset);

    if (m_pEnumerationArray != NULL)
    {
        m_pEnumerationArray->dump(cout, offset);
    }

    QuickOutFooter(cout, XSD_RESTRICTION_STR, offset);
}

void CRestriction::getDocumentation(StringBuffer &strDoc) const
{
    if (m_pEnumerationArray != NULL)
    {
        strDoc.appendf("<%s>",DM_PARA);
        DEBUG_MARK_STRDOC

        m_pEnumerationArray->getDocumentation(strDoc);

        strDoc.appendf("</%s>",DM_PARA);
        DEBUG_MARK_STRDOC
    }
}

void CRestriction::getDojoJS(StringBuffer &strJS) const
{
    StringBuffer strID;

    if (m_pEnumerationArray != NULL)
    {
        strJS.append(DJ_MEMORY_BEGIN);
        m_pEnumerationArray->getDojoJS(strJS);
        strJS.append(DJ_MEMORY_END);

        assert(this->getConstAncestorNode(3) != NULL && this->getConstAncestorNode(3)->getNodeType() == XSD_ATTRIBUTE);

        const CAttribute *pAttrib3 = dynamic_cast<const CAttribute*>(this->getConstAncestorNode(3));

        strJS.append(createDojoComboBox(pAttrib3->getName(), strID, pAttrib3->getDefault()));

        StringBuffer strToolTip(DJ_TOOL_TIP_BEGIN);

        strToolTip.append(DJ_TOOL_TIP_CONNECT_ID_BEGIN);
        strToolTip.append(strID.str());
        strToolTip.append(DJ_TOOL_TIP_CONNECT_ID_END);
        StringBuffer strTT(pAttrib3->getAnnotation()->getAppInfo()->getToolTip());
        strTT.replaceString("\"","\\\"");

        strToolTip.append(DJ_TOOL_TIP_LABEL_BEGIN).append(strTT.str()).append(DJ_TOOL_TIP_LABEL_END);
        strToolTip.append(DJ_TOOL_TIP_END);

        CConfigSchemaHelper::getInstance()->addToolTip(strToolTip.str());
    }
}

void CRestriction::getQML(StringBuffer &strQML) const
{
    if (m_pEnumerationArray != NULL)
    {
        assert(this->getConstAncestorNode(3) != NULL && this->getConstAncestorNode(3)->getNodeType() == XSD_ATTRIBUTE);

        const CAttribute *pAttrib = dynamic_cast<const CAttribute*>(this->getConstAncestorNode(3));

        assert(pAttrib != NULL);

        strQML.append(QML_ROW_BEGIN);
        strQML.append(QML_RECTANGLE_LIGHT_STEEEL_BLUE_BEGIN);
        DEBUG_MARK_QML;

        strQML.append(QML_TEXT_BEGIN_2).append("\"").append(pAttrib->getName()).append("\"").append(QML_TEXT_END_2);

        strQML.append(QML_RECTANGLE_LIGHT_STEEEL_BLUE_END);

        StringBuffer strComboBoxID("combobox");
        CQMLMarkupHelper::getRandomID(&strComboBoxID);

        strQML.append(QML_COMBO_BOX_BEGIN);
        strQML.append(strComboBoxID);
        DEBUG_MARK_QML;

        strQML.append(QML_LIST_MODEL_BEGIN);
        DEBUG_MARK_QML;

        m_pEnumerationArray->getQML(strQML);
        DEBUG_MARK_QML;

        strQML.append(QML_LIST_MODEL_END);

        strQML.append(QML_COMBO_BOX_CURRENT_INDEX).append(QML_APP_DATA_GET_INDEX_BEGIN).append(this->getEnvXPath()).append(QML_APP_DATA_GET_INDEX_END);
        DEBUG_MARK_QML;

        strQML.append(QML_ON_CURRENT_INDEX_CHANGED).append(QML_APP_DATA_SET_INDEX_BEGIN).append(this->getEnvXPath()).append("\", ").append(strComboBoxID).append(QML_APP_DATA_SET_INDEX_END);
        DEBUG_MARK_QML;

        strQML.append(QML_COMBO_BOX_END);

        strQML.append(QML_ROW_END);
        DEBUG_MARK_QML;
    }
}

void CRestriction::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    this->setEnvXPath(strXPath);

    CConfigSchemaHelper::getInstance()->getSchemaMapManager()->addMapOfXPathToRestriction(this->getEnvXPath(), this);

    if (this->m_pEnumerationArray != NULL)
    {
        this->m_pEnumerationArray->populateEnvXPath(strXPath);
    }
}

void CRestriction::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    if (m_pEnumerationArray != NULL)
    {
        m_pEnumerationArray->loadXMLFromEnvXml(pEnvTree);
    }
}


CRestriction* CRestriction::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    if (pParentNode == NULL || pSchemaRoot == NULL)
    {
        return NULL;
    }

    IPropertyTree *pTree = pSchemaRoot->queryPropTree(xpath);

    const char* pID =  NULL;
    const char* pBase =  NULL;

    // TODO: handle Base in restrictions

    pID = pTree->queryProp(XML_ATTR_ID);
    pBase = pTree->queryProp(XML_ATTR_BASE);


    CRestriction* pRestriction = new CRestriction(pParentNode, pID, pBase);

    pRestriction->setXSDXPath(xpath);

    StringBuffer strXPathExt(xpath);

    strXPathExt.append("/").append(XSD_TAG_ENUMERATION);

    CEnumerationArray *pEnumerationArray = CEnumerationArray::load(pRestriction, pSchemaRoot, strXPathExt.str());

    if (pEnumerationArray != NULL)
    {
        pRestriction->setEnumerationArray(pEnumerationArray);
    }

    return pRestriction;
}

void  CRestriction::traverseAndProcessNodes() const
{
    CXSDNodeBase::processEntryHandlers(this);
    CXSDNodeBase::processExitHandlers(this);
}

const char* CRestriction::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length () == 0)
    {
        m_strXML.append("<").append(getBase()).append("\n");
        m_strXML.append("<").append(getID()).append("\n");

        // TODO
      /*  if (m_pBase != NULL)
        {
            m_strXML.append(m_pBase->getXML(NULL));
        }*/

        m_strXML.append("/>\n");
    }

    return m_strXML.str();
}
