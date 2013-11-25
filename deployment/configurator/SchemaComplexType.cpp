#include <cassert>
#include "jstring.hpp"
#include "jptree.hpp"
#include "XMLTags.h"
#include "SchemaComplexType.hpp"
#include "SchemaSequence.hpp"
#include "SchemaComplexContent.hpp"
#include "SchemaAttributes.hpp"
#include "SchemaChoice.hpp"
#include "SchemaComplexType.hpp"
#include "SchemaElement.hpp"
#include "SchemaSchema.hpp"
#include "ConfigSchemaHelper.hpp"
#include "DocumentationMarkup.hpp"
#include "ExceptionStrings.hpp"
#include "SchemaMapManager.hpp"

void CComplexType::dump(std::ostream& cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_COMPLEX_TYPE_STR, offset);

    QUICK_OUT_2(Name)
    QUICK_OUT(cout, XSDXPath,   offset);

    if (m_pSequence != NULL)
    {
        m_pSequence->dump(cout, offset);
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->dump(cout, offset);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->dump(cout, offset);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->dump(cout, offset);
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->dump(cout, offset);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->dump(cout, offset);
    }

    if (m_pAnnotation != NULL)
    {
        m_pAnnotation->dump(cout, offset);
    }

    QuickOutFooter(cout, XSD_COMPLEX_TYPE_STR, offset);
}

void CComplexType::getDocumentation(StringBuffer &strDoc) const
{
    if (m_pSequence != NULL)
    {
        m_pSequence->getDocumentation(strDoc);
    }

    if (m_pComplexContent != NULL)
    {
        strDoc.append(DM_SECT3_BEGIN);
        DEBUG_MARK_STRDOC
        m_pComplexContent->getDocumentation(strDoc);
        strDoc.append(DM_SECT3_END);
    }

    if (m_pAttributeArray != NULL)
    {
        if (this->getConstParentNode()->getConstParentNode()->getNodeType() == XSD_SCHEMA)
            strDoc.appendf("<%s>\n", DM_TABLE_ROW);

        m_pAttributeArray->getDocumentation(strDoc);

        if (this->getConstParentNode()->getConstParentNode()->getNodeType() == XSD_SCHEMA)
            strDoc.appendf("</%s>\n", DM_TABLE_ROW);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->getDocumentation(strDoc);
    }

    if (m_pElementArray != NULL)
    {
        strDoc.append(DM_SECT3_BEGIN);
        DEBUG_MARK_STRDOC;
        m_pElementArray->getDocumentation(strDoc);
        strDoc.append(DM_SECT3_END);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->getDocumentation(strDoc);
    }
}

void CComplexType::getDojoJS(StringBuffer &strJS) const
{
    if (m_pSequence != NULL)
    {
        m_pSequence->getDojoJS(strJS);
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->getDojoJS(strJS);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->getDojoJS(strJS);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->getDojoJS(strJS);
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->getDojoJS(strJS);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->getDojoJS(strJS);
    }
}

void CComplexType::getQML(StringBuffer &strQML) const
{
    if (m_pSequence != NULL)
    {
        m_pSequence->getQML(strQML);
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->getQML(strQML);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->getQML(strQML);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->getQML(strQML);
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->getQML(strQML);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->getQML(strQML);
    }
}

void CComplexType::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    this->setEnvXPath(strXPath);

    if (m_pSequence != NULL)
    {
        m_pSequence->populateEnvXPath(strXPath);
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->populateEnvXPath(strXPath);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->populateEnvXPath(strXPath);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->populateEnvXPath(strXPath);
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->populateEnvXPath(strXPath);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->populateEnvXPath(strXPath);
    }
}

void CComplexType::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    if (m_pSequence != NULL)
    {
        m_pSequence->loadXMLFromEnvXml(pEnvTree);
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->loadXMLFromEnvXml(pEnvTree);
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->loadXMLFromEnvXml(pEnvTree);
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->loadXMLFromEnvXml(pEnvTree);
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->loadXMLFromEnvXml(pEnvTree);
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->loadXMLFromEnvXml(pEnvTree);
    }
}

void CComplexType::traverseAndProcessNodes() const
{
    CComplexType::processEntryHandlers(this);

    if (m_pSequence != NULL)
    {
        m_pSequence->traverseAndProcessNodes();
    }

    if (m_pComplexContent != NULL)
    {
        m_pComplexContent->traverseAndProcessNodes();
    }

    if (m_pAttributeArray != NULL)
    {
        m_pAttributeArray->traverseAndProcessNodes();
    }

    if (m_pChoice != NULL)
    {
        m_pChoice->traverseAndProcessNodes();
    }

    if (m_pElementArray != NULL)
    {
        m_pElementArray->traverseAndProcessNodes();
    }

    if (m_pAttributeGroupArray != NULL)
    {
        m_pAttributeGroupArray->traverseAndProcessNodes();
    }

    CComplexType::processExitHandlers(this);
}

const char* CComplexType::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length() == 0)
    {
        if (m_pComplexContent != NULL)
        {
            m_strXML.append(m_pComplexContent->getXML(NULL));
        }
        if (m_pAttributeArray != NULL)
        {
            m_strXML.append(m_pAttributeArray->getXML(NULL));
        }
        if (m_pChoice != NULL)
        {
            m_strXML.append(m_pChoice->getXML(NULL));
        }
        if (m_pElementArray != NULL)
        {
            m_strXML.append(m_pElementArray->getXML(NULL));
        }
    }

    return m_strXML.str();
}

CComplexType* CComplexType::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);

    CComplexContent *pComplexContent = NULL;
    CAttributeArray *pAttributeArray =  NULL;
    CChoice *pChoice = NULL;
    CElementArray *pElementArray = NULL;
    CSequence *pSequence  = NULL;
    CAttributeGroupArray *pAttributeGroupArray = NULL;
    CAnnotation *pAnnotation = NULL;

    if (pSchemaRoot == NULL)
    {
        return NULL;
    }

    IPropertyTree *pTree = pSchemaRoot->queryPropTree(xpath);

    const char* pName = pTree->queryProp(XML_ATTR_NAME);

    StringBuffer strXPathExt(xpath);

    StringBuffer strXPathExt2(strXPathExt);
    strXPathExt2.append("*");

    Owned<IPropertyTreeIterator> iter = pSchemaRoot->getElements(strXPathExt2.str());


    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_SEQUENCE);
    pSequence = CSequence::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_ANNOTATION);
    pAnnotation = CAnnotation::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_COMPLEX_CONTENT);
    pComplexContent = CComplexContent::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_ATTRIBUTE);
    pAttributeArray = CAttributeArray::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_CHOICE);
    pChoice = CChoice::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_ELEMENT);
    pElementArray = CElementArray::load(NULL, pSchemaRoot, strXPathExt.str());

    strXPathExt.clear().append(xpath).append("/").append(XSD_TAG_ATTRIBUTE_GROUP);
    pAttributeGroupArray = CAttributeGroupArray::load(NULL, pSchemaRoot, strXPathExt.str());

    CComplexType *pComplexType = new CComplexType(pParentNode, pName, pSequence, pComplexContent, pAttributeArray, pChoice, pElementArray, pAttributeGroupArray, pAnnotation);

    pComplexType->setXSDXPath(xpath);

    assert(pComplexType != NULL);

    if (pComplexType != NULL)
    {

        SETPARENTNODE(pSequence, pComplexType)
        SETPARENTNODE(pComplexContent, pComplexType)
        SETPARENTNODE(pAttributeArray, pComplexType)
        SETPARENTNODE(pChoice, pComplexType)
        SETPARENTNODE(pElementArray, pComplexType)
        SETPARENTNODE(pAttributeGroupArray, pComplexType)
        SETPARENTNODE(pAnnotation, pComplexType);

        if (pName != NULL)
        {
            CConfigSchemaHelper::getInstance()->getSchemaMapManager()->setComplexTypeWithName(pName, pComplexType);
        }
    }

    return pComplexType;
}

void CComplexTypeArray::dump(std::ostream& cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_COMPLEX_TYPE_ARRAY_STR, offset);

    QUICK_OUT(cout, XSDXPath,   offset);
    QUICK_OUT_ARRAY(cout, offset);

    QuickOutFooter(cout, XSD_COMPLEX_TYPE_ARRAY_STR, offset);
}

void CComplexTypeArray::getDocumentation(StringBuffer &strDoc) const
{
    QUICK_DOC_ARRAY(strDoc);
}

void CComplexTypeArray::getDojoJS(StringBuffer &strJS) const
{
    QUICK_DOJO_JS_ARRAY(strJS);
}

void CComplexTypeArray::getQML(StringBuffer &strQML) const
{
   QUICK_QML_ARRAY(strQML);
}

void CComplexTypeArray::traverseAndProcessNodes() const
{
    QUICK_TRAVERSE_AND_PROCESS;
}

const char* CComplexTypeArray::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length() == 0)
    {
        int length = this->length();

        for (int idx = 0; idx < length; idx++)
        {
            CComplexType &ComplexType = this->item(idx);

            m_strXML.append(ComplexType.getXML(NULL));

            if (idx+1 < length)
            {
                m_strXML.append("\n");
            }
        }
    }

    return m_strXML.str();
}

void CComplexTypeArray::populateEnvXPath(StringBuffer strXPath, unsigned int index)
{
    assert(index == 1);  // Only 1 array of elements per node

    this->setEnvXPath(strXPath);

    QUICK_ENV_XPATH(strXPath)
}


void CComplexTypeArray::loadXMLFromEnvXml(const IPropertyTree *pEnvTree)
{
    assert(pEnvTree != NULL);

    if (pEnvTree->hasProp(this->getEnvXPath()) == false)
    {
        throw MakeExceptionFromMap(EX_STR_XPATH_DOES_NOT_EXIST_IN_TREE);
    }
    else
    {
        QUICK_LOAD_ENV_XML(pEnvTree);
    }
}

CComplexTypeArray* CComplexTypeArray::load(CXSDNodeBase* pParentNode, const IPropertyTree *pSchemaRoot, const char* xpath)
{
    assert(pSchemaRoot != NULL);

    if (pSchemaRoot == NULL)
    {
        return NULL;
    }

    CComplexTypeArray *pComplexTypeArray = new CComplexTypeArray(pParentNode);

    pComplexTypeArray->setXSDXPath(xpath);

    Owned<IPropertyTreeIterator> complexTypeIter = pSchemaRoot->getElements(xpath);

    int count = 1;

    ForEach(*complexTypeIter)
    {
        StringBuffer strXPathExt(xpath);
        strXPathExt.appendf("[%d]", count);

        CComplexType *pComplexType = CComplexType::load(pComplexTypeArray, pSchemaRoot, strXPathExt.str());

        assert(pComplexType != NULL);

        if (pComplexType != NULL)
        {
            pComplexTypeArray->append(*pComplexType);
        }

        count++;
    }

    if (pComplexTypeArray->length() == 0)
    {
        delete pComplexTypeArray;
        pComplexTypeArray = NULL;
    }

    return pComplexTypeArray;
}

CComplexTypeArray* CComplexTypeArray::load(CXSDNodeBase* pParentNode, const char* pSchemaFile)
{
    assert(false);  // why do still need to call this?
    assert(pSchemaFile != NULL);

    if (pSchemaFile == NULL)
    {
        return NULL;
    }

    if (pParentNode == NULL)
    {
        Linked<IPropertyTree> pSchemaRoot;

        StringBuffer schemaPath;

        schemaPath.appendf("%s%s", DEFAULT_SCHEMA_DIRECTORY, pSchemaFile);
        pSchemaRoot.setown(createPTreeFromXMLFile(schemaPath.str()));

        return CComplexTypeArray::load(pParentNode, pSchemaRoot, XSD_TAG_COMPLEX_TYPE);
    }
    else
    {
        CSchema *pSchema = (dynamic_cast<CSchema*>(pParentNode));

        if (pSchema != NULL)
        {
            return pSchema->getComplexTypeArray();
        }
    }

    return NULL;
}
