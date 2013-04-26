#include "jptree.hpp"
#include "XMLTags.h"
#include "SchemaInclude.hpp"
#include "SchemaSchema.hpp"
#include "ConfigSchemaHelper.hpp"

void CInclude::dump(std::ostream& cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_INCLUDE_STR, offset);

    QUICK_OUT(cout, SchemaLocation, offset);

    QuickOutFooter(cout, XSD_INCLUDE_STR, offset);
}

const char* CInclude::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length() == 0)
    {
//        m_strXML.append(m_pSchema->getXML(NULL));
    }

    return m_strXML.str();
}

CInclude* CInclude::load(CXSDNodeBase* pParentNode, IPropertyTree *pSchemaRoot, const char* xpath)
{
    if (pParentNode == NULL || pSchemaRoot == NULL || xpath == NULL)
    {
        return NULL;
    }

    CInclude *pInclude = NULL;
    IPropertyTree *pTree = pSchemaRoot->queryPropTree(xpath);

    if (pTree != NULL)
    {
        const char *pSchemaLocation = pSchemaRoot->queryPropTree(xpath)->queryProp(XML_ATTR_SCHEMA_LOCATION);

        if (pSchemaLocation != NULL)
        {
            CSchema* pSchema = CConfigSchemaHelper::getInstance()->getSchemaForXSD(pSchemaLocation);

            if (pSchema == NULL)
            {
                pSchema = CSchema::load(pSchemaLocation, pParentNode);
            }

            pInclude = new CInclude(pParentNode, pSchemaLocation);
            pInclude->setIncludedSchema(pSchema);
        }
    }

    return pInclude;
}

CIncludeArray* CIncludeArray::load(CXSDNodeBase* pParentNode, IPropertyTree *pSchemaRoot, const char *xpath)
{
    if (pSchemaRoot == NULL)
    {
        return NULL;
    }

    CIncludeArray *pIncludeArray = new CIncludeArray(pParentNode);


    Owned<IPropertyTreeIterator> elemIter = pSchemaRoot->getElements(xpath);

    int count = 1;

    ForEach(*elemIter)
    {
        StringBuffer strXPathExt(xpath);
        strXPathExt.appendf("[%d]", count);

        CInclude *pInclude = CInclude::load(pIncludeArray, pSchemaRoot, strXPathExt.str());

        if (pInclude != NULL)
        {
            pIncludeArray->append(*pInclude);
        }

        count++;
    }

    if (pIncludeArray->length() == 0)
    {
        return NULL;
    }

    return pIncludeArray;
}

const char* CIncludeArray::getXML(const char* /*pComponent*/)
{
    if (m_strXML.length() == 0)
    {
        int length = this->length();

        for (int idx = 0; idx < length; idx++)
        {
            CInclude &Include = this->item(idx);

            m_strXML.append(Include.getXML(NULL));

            if (idx+1 < length)
            {
                m_strXML.append("\n");
            }
        }
    }

    return m_strXML.str();
}

void CIncludeArray::dump(std::ostream &cout, unsigned int offset) const
{
    offset+= STANDARD_OFFSET_1;

    QuickOutHeader(cout, XSD_INCLUDE_ARRAY_STR, offset);

    QUICK_OUT_ARRAY(cout, offset);

    QuickOutFooter(cout, XSD_INCLUDE_ARRAY_STR, offset);
}
