#include "ConfigSchemaHelper.hpp"
#include "SchemaAttributes.hpp"
#include "SchemaElement.hpp"
#include "SchemaEnumeration.hpp"
#include "jptree.hpp"
#include "XMLTags.h"
#include "ExceptionStrings.hpp"
#include <cstring>
#include "jfile.hpp"
#include "BuildSet.hpp"

#define LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET for (int idx = 0; idx < CBuildSetManager::getInstance()->getSchemaCount(); idx++)

CConfigSchemaHelper* CConfigSchemaHelper::s_pCConfigSchemaHelper = NULL;


CConfigSchemaHelper* CConfigSchemaHelper::getInstance(const char* pDefaultDirOverride)
{
    // not thread safe!!!

    if (s_pCConfigSchemaHelper == NULL)
    {
        s_pCConfigSchemaHelper = new CConfigSchemaHelper();
        s_pCConfigSchemaHelper->m_nTables = 0;
    }

    return s_pCConfigSchemaHelper;
}

CConfigSchemaHelper* CConfigSchemaHelper::getInstance(const char* pBuildSetFileName, const char *pBaseDirectory, const char *pDefaultDirOverride)
{
    assert(pBuildSetFileName != NULL);
    assert(pBaseDirectory != NULL);

    if (s_pCConfigSchemaHelper == NULL && pBuildSetFileName != NULL && pBaseDirectory != NULL)
    {
       s_pCConfigSchemaHelper = new CConfigSchemaHelper(pBuildSetFileName, pBaseDirectory, pDefaultDirOverride);
       s_pCConfigSchemaHelper->m_nTables = 0;
    }

    return s_pCConfigSchemaHelper;

}

CConfigSchemaHelper::CConfigSchemaHelper(const char* pBuildSetFile, const char* pBuildSetDir, const char* pDefaultDirOverride) : m_pEnvPropertyTree(NULL)
{
    assert(pBuildSetFile != NULL);
    assert(pBuildSetDir != NULL);

    CBuildSetManager::getInstance(pBuildSetFile, pBuildSetDir);
}

CConfigSchemaHelper::~CConfigSchemaHelper()
{
}

bool CConfigSchemaHelper::getValue(const char *pXPath, char *pValue)
{
    static int counter = 0;
    itoa(counter, pValue, 10);
    counter++;

    CAttribute **pAttribute = m_attributePtrsMap.getValue(pXPath);

    if ((**pAttribute).isInstanceValueValid() == true)
    {
        strcpy(pValue, (**pAttribute).getEnvValueFromXML());
    }
    else
    {
        pValue = NULL;
    }
    return true;
}

void CConfigSchemaHelper::setValue(const char *pXPath, const char *pValue)
{
    assert(pXPath != NULL && pXPath[0] != 0);
    assert(pValue != NULL);

    CAttribute **pAttribute = m_attributePtrsMap.getValue(pXPath);

    assert(pAttribute != NULL && *pAttribute != NULL);

    (*pAttribute)->setEnvValueFromXML(pValue);
    (*pAttribute)->setInstanceAsValid();

    setEnvTreeProp(pXPath, pValue);
}

int CConfigSchemaHelper::getIndex(const char *pXPath)
{
    CRestriction *pRestriction = *(this->m_restrictionPtrsMap.getValue(pXPath));

    assert(pRestriction != NULL);
    assert(pRestriction->getEnumerationArray() != NULL);

    return pRestriction->getEnumerationArray()->getEnvValueNodeIndex();
}

void CConfigSchemaHelper::setIndex(const char *pXPath, int newIndex)
{
    assert(newIndex >= 0);

    CRestriction *pRestriction = *(this->m_restrictionPtrsMap.getValue(pXPath));

    assert(pRestriction != NULL);
    assert(pRestriction->getEnumerationArray() != NULL);

    pRestriction->getEnumerationArray()->setEnvValueNodeIndex(newIndex);

    setEnvTreeProp(pXPath, pRestriction->getEnumerationArray()->item(newIndex).getValue());
}

bool CConfigSchemaHelper::populateBuildSet()
{
    return CBuildSetManager::getInstance()->populateBuildSet();
}

bool CConfigSchemaHelper::populateSchema()
{

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pSchemaName != NULL)
        {
            CXSDNodeBase *pNull = NULL;
            CSchema *pSchema = CSchema::load(pSchemaName, pNull);
            m_schemaMap.setValue(pSchemaName, pSchema);
        }
    }

    return true;
}

void CConfigSchemaHelper::printConfigSchema(StringBuffer &strXML) const
{
    const char *pComponent = NULL;
    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pComponent == NULL || strcmp(pComponent, pSchemaName) == 0)
        {
            const char* pXSDSchema = pSchemaName;

            if (pXSDSchema == NULL)
            {
                continue;
            }

            pSchema = m_schemaMap.getValue(pSchemaName);

            if (pSchema != NULL)
            {
                if (strXML.length() > 0 ? strcmp(strXML.str(), pXSDSchema) == 0 : true)
                pSchema->dump(std::cout);
            }
        }
    }
}

const char* CConfigSchemaHelper::printDocumentation(const char* comp)
{
    assert(comp);

    if (comp == NULL)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;


    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_schemaMap.getValue(pSchemaName);

             assert(pSchema != NULL);

             if (pSchema != NULL)
             {
                static StringBuffer strDoc;
                strDoc.clear(); // needed when printing more than 1 component
                pSchema->getDocumentation(strDoc);

                return strDoc.str();
             }
        }
    }

    return NULL;
}


const char* CConfigSchemaHelper::printDojoJS(const char* comp)
{
    assert(comp);

    if (comp == NULL)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_schemaMap.getValue(pSchemaName);

             assert(pSchema != NULL);

             if (pSchema != NULL)
             {
                static StringBuffer strDoc;
                pSchema->getDojoJS(strDoc);

                return strDoc.str();
             }
        }
    }

    return NULL;
}

const char* CConfigSchemaHelper::printQML(const char* comp) const
{
    if (comp == NULL)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_schemaMap.getValue(pSchemaName);

             assert(pSchema != NULL);

             if (pSchema != NULL)
             {
                static StringBuffer strQML;
                pSchema->getQML(strQML);

                return strQML.str();
             }
        }
    }

    return NULL;
}

void CConfigSchemaHelper::printDump(const char* comp) const
{
    if (comp == NULL)
    {
        return;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_schemaMap.getValue(pSchemaName);

             assert(pSchema != NULL);

             if (pSchema != NULL)
             {
                pSchema->dump(std::cout);
            }
        }
    }
}

void CConfigSchemaHelper::dumpStdOut() const
{
    assert("NOT IMPLEMENTED");
}

//test purposes
bool CConfigSchemaHelper::getXMLFromSchema(StringBuffer& strXML, const char* pComponent)
{
    CAttributeArray *pAttributeArray = NULL;
    CElementArray *pElementArray = NULL;
    CSchema* pSchema = NULL;

    strXML.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Environment>\n\t<Software>");

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pComponent == NULL || strcmp(pComponent, pSchemaName) == 0)
        {

            if (pSchemaName == NULL)
            {
                continue;
            }

            pSchema = m_schemaMap.getValue(pSchemaName);

            if (pSchema != NULL)
            {
                strXML.append(pSchema->getXML(NULL));
            }
        }
    }

    strXML.append("\t</Software>\n</Environment>\n");

    return true;
}

CSchema* CConfigSchemaHelper::getSchemaForXSD(const char* pComponent)
{
    return m_schemaMap.getValue(pComponent);
}

void CConfigSchemaHelper::setSchemaForXSD(const char* pComponent, CSchema *pSchema)
{
    assert(pSchema != NULL);

    if (pSchema != NULL)
    {
        m_schemaMap.setValue(pComponent, pSchema);
    }
}

CSimpleType* CConfigSchemaHelper::getSimpleTypeWithName(const char* pName)
{
    assert(pName != NULL);

    if (pName == NULL)
    {
        return NULL;
    }

    CSimpleType *pSimpleType = NULL;

    pSimpleType = *(m_simpleTypePtrMap.getValue(pName));

    assert(pSimpleType != NULL);

    return pSimpleType;
}

void CConfigSchemaHelper::setSimpleTypeWithName(const char* pName, CSimpleType *pSimpleType)
{
    assert (pSimpleType != NULL);

    if (pName == NULL || pSimpleType == NULL)
    {
        return;
    }

    if (m_simpleTypePtrMap.getValue(pName) != NULL)
    {
        throw MakeExceptionFromMap(EX_STR_SIMPLE_TYPE_ALREADY_DEFINED);
    }

    m_simpleTypePtrMap.setValue(pName, pSimpleType);
}

CComplexType* CConfigSchemaHelper::getComplexTypeWithName(const char* pName)
{
    assert(pName != NULL);

    if (pName == NULL)
    {
        return NULL;
    }

    CComplexType *pComplexType = NULL;

    pComplexType = *(m_complexTypePtrsMap.getValue(pName));

    assert(pComplexType != NULL);

    return pComplexType;
}

void CConfigSchemaHelper::setComplexTypeWithName(const char* pName, CComplexType *pComplexType)
{
    assert (pComplexType != NULL);

    if (pName == NULL || pComplexType == NULL)
    {
        return;
    }

    if (m_complexTypePtrsMap.getValue(pName) != NULL)
    {
        throw MakeExceptionFromMap(EX_STR_COMPLEX_TYPE_ALREADY_DEFINED);
    }

    m_complexTypePtrsMap.setValue(pName, pComplexType);
}

CAttributeGroup* CConfigSchemaHelper::getAttributeGroup(const char* pName)
{
    assert(pName != NULL);

    if (pName == NULL)
    {
        return NULL;
    }

    CAttributeGroup *pAttributeGroup = NULL;

    pAttributeGroup = *(m_attributeGroupTypePtrsMap.getValue(pName));

    assert(pAttributeGroup != NULL);

    return pAttributeGroup;
}

void CConfigSchemaHelper::setAttributeGroupTypeWithName(const char* pName, CAttributeGroup *pAttributeGroup)
{
    assert (pAttributeGroup != NULL);

    if (pName == NULL || pAttributeGroup == NULL)
    {
        return;
    }

    if (m_attributeGroupTypePtrsMap.getValue(pName) != NULL)
    {
        throw MakeExceptionFromMap(EX_STR_ATTRIBUTE_GROUP_ALREADY_DEFINED);
    }

    m_attributeGroupTypePtrsMap.setValue(pName, pAttributeGroup);
}

void CConfigSchemaHelper::addExtensionToBeProcessed(CExtension *pExtension)
{
    assert(pExtension != NULL);

    if (pExtension != NULL)
    {
        m_extensionArr.append(*pExtension);
    }
}

void CConfigSchemaHelper::addAttributeGroupToBeProcessed(CAttributeGroup *pAttributeGroup)
{
    assert(pAttributeGroup != NULL);

    if (pAttributeGroup != NULL)
    {
        m_attributeGroupArr.append(*pAttributeGroup);
    }
}

void CConfigSchemaHelper::processExtensionArr()
{
    int length = m_extensionArr.length();

    for (int idx = 0; idx < length; idx++)
    {
        CExtension &Extension = (m_extensionArr.item(idx));
        const char *pName = Extension.getBase();

        assert(pName != NULL);

        if (pName != NULL)
        {
            CXSDNodeBase *pNodeBase = NULL;

            pNodeBase = m_simpleTypePtrMap.getValue(pName) != NULL ? dynamic_cast<CSimpleType*>(*(m_simpleTypePtrMap.getValue(pName))) : NULL;

            if (pNodeBase == NULL)
            {
                pNodeBase = m_complexTypePtrsMap.getValue(pName) != NULL ? dynamic_cast<CComplexType*>(*(m_complexTypePtrsMap.getValue(pName))) : NULL ;
            }

            assert(pNodeBase != NULL);

            if (pNodeBase != NULL)
            {
                Extension.setBaseNode(pNodeBase);
            }
        }
    }
}

void CConfigSchemaHelper::processAttributeGroupArr()
{
    int length = m_attributeGroupArr.length();

    for (int idx = 0; idx < length; idx++)
    {
        CAttributeGroup &AttributeGroup = (m_attributeGroupArr.item(idx));
        const char *pRef = AttributeGroup.getRef();

        assert(pRef != NULL && pRef[0] != 0);

        if (pRef != NULL && pRef[0] != 0)
        {
            CAttributeGroup *pAttributeGroup = NULL;

            pAttributeGroup = *(m_attributeGroupTypePtrsMap.getValue(pRef));

            assert(pAttributeGroup != NULL);

            if (pAttributeGroup != NULL)
            {
                AttributeGroup.setRefNode(pAttributeGroup);
            }
        }
    }
}

void CConfigSchemaHelper::populateEnvXPath()
{
    CSchema* pSchema = NULL;
    StringBuffer strXPath;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        pSchema = m_schemaMap.getValue(CBuildSetManager::getInstance()->getBuildSetSchema(idx));

        if (pSchema != NULL)
        {
            pSchema->populateEnvXPath(strXPath);
        }
    }
}

void CConfigSchemaHelper::loadEnvFromConfig(const char *pEnvFile)
{
    assert(pEnvFile != NULL);

    Linked<IPropertyTree> pEnvXMLRoot;

    try
    {
        pEnvXMLRoot.setown(createPTreeFromXMLFile(pEnvFile));
    }
    catch (...)
    {
        MakeExceptionFromMap(EX_STR_CAN_NOT_PROCESS_ENV_XML);
    }

    CSchema* pSchema = NULL;

    this->setEnvPropertyTree(pEnvXMLRoot.getLink());
    this->setEnvFilePath(pEnvFile);

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        pSchema = m_schemaMap.getValue(CBuildSetManager::getInstance()->getBuildSetSchema(idx));

        if (pSchema != NULL)
        {
            pSchema->loadXMLFromEnvXml(pEnvXMLRoot);
        }
    }
}

void CConfigSchemaHelper::traverseAndProcessArray(const char *pXSDName)
{
    const char *pComponent = NULL;
    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetSchema(idx);

        if (pComponent == NULL || strcmp(pComponent,pSchemaName) == 0)
        {
            if (pSchemaName == NULL || (pXSDName != NULL && strcmp(pXSDName, pSchemaName) != 0))
            {
                continue;
            }

            pSchema = m_schemaMap.getValue(pSchemaName);

            if (pSchema != NULL)
            {
                pSchema->traverseAndProcessNodes();
            }
        }
    }
}

void CConfigSchemaHelper::addToolTip(const char *js)
{
    assert (js != NULL);
    assert (js[0] != 0);

    if (js == NULL || js[0] == 0)
    {
        return;
    }

    m_strToolTipsJS.append(js);
}

const char* CConfigSchemaHelper::getToolTipJS() const
{
    static StringBuffer strJS;

    strJS.clear();

    for (int idx = 0; idx < m_strToolTipsJS.length(); idx++)
    {
        strJS.append(m_strToolTipsJS.item(idx));
    }

    return strJS.str();
}

void CConfigSchemaHelper::addMapOfXPathToAttribute(const char*pXPath, CAttribute *pAttribute)
{
    assert (pAttribute != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    // TODO:: throw exception if problems here

    assert(m_attributePtrsMap.find(pXPath) == NULL);

    // should I remove automatically?

    m_attributePtrsMap.setValue(pXPath, pAttribute);
    m_strArrayEnvXPaths.append(pXPath);
}

void CConfigSchemaHelper::removeMapOfXPathToAttribute(const char*pXPath)
{
    assert (m_attributePtrsMap.find(pXPath) != NULL);

    m_attributePtrsMap.remove(pXPath);
}

void CConfigSchemaHelper::addMapOfXPathToElementArray(const char*pXPath, CElementArray *pElementArray)
{
    assert (pElementArray != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    if (m_elementArrayPtrsMap.find(pXPath) != NULL)
    {
        return;  // already mapped, we must be dealing with live data
    }
    m_elementArrayPtrsMap.setValue(pXPath, pElementArray);
}

void CConfigSchemaHelper::removeMapOfXPathToElementArray(const char*pXPath)
{
    assert (m_elementArrayPtrsMap.find(pXPath) != NULL);
    m_elementArrayPtrsMap.remove(pXPath);
}

void CConfigSchemaHelper::addMapOfXPathToElement(const char* pXPath, CElement *pElement)
{
    assert (pElement != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    assert(m_elementPtrsMap.find(pXPath) == NULL);

    m_elementPtrsMap.setValue(pXPath, pElement);
    m_strArrayEnvXPaths.append(pXPath);
}

void CConfigSchemaHelper::removeMapOfXPathToElement(const char*pXPath)
{
    assert (m_elementPtrsMap.find(pXPath) != NULL);
    m_elementPtrsMap.remove(pXPath);
}

void CConfigSchemaHelper::addMapOfXPathToRestriction(const char*pXPath, CRestriction *pRestriction)
{
    assert (pRestriction != NULL);
    assert(pXPath != NULL && *pXPath != 0);
    assert(m_restrictionPtrsMap.find(pXPath) == NULL);

    m_restrictionPtrsMap.setValue(pXPath, pRestriction);
}

void CConfigSchemaHelper::removeMapOfXPathToRestriction(const char*pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    m_restrictionPtrsMap.remove(pXPath);
}

void CConfigSchemaHelper::setEnvTreeProp(const char *pXPath, const char* pValue)
{
    assert(pXPath != NULL && pXPath[0] != 0);

    CAttribute *pAttribute = *(m_attributePtrsMap.getValue(pXPath));

    assert(pAttribute != NULL);

    StringBuffer strPropName("@");
    strPropName.append(pAttribute->getName());

    if (this->getEnvPropertyTree()->queryPropTree(pAttribute->getConstAncestorNode(1)->getEnvXPath())->queryProp(strPropName.str()) == NULL)
    {
        //should check if this attribute is optional for validation
        this->getEnvPropertyTree()->queryPropTree(pAttribute->getConstAncestorNode(1)->getEnvXPath())->setProp(strPropName.str(), pValue);
    }
    else if (strcmp (this->getEnvPropertyTree()->queryPropTree(pAttribute->getConstAncestorNode(1)->getEnvXPath())->queryProp(strPropName.str()), pValue) == 0)
    {
        return; // nothing changed
    }
    else
    {
        this->getEnvPropertyTree()->queryPropTree(pAttribute->getConstAncestorNode(1)->getEnvXPath())->setProp(strPropName.str(), pValue);
    }


    StringBuffer strXML;

    strXML.appendf("<"XML_HEADER">\n<!-- Edited with THE CONFIGURATOR -->\n");
    toXML(this->getEnvPropertyTree(), strXML, 0, XML_SortTags | XML_Format);

    Owned<IFile>   pFile;
    Owned<IFileIO> pFileIO;

    pFile.setown(createIFile(getEnvFilePath()));
    pFileIO.setown(pFile->open(IFOcreaterw));

    pFileIO->write(0, strXML.length(), strXML.str());
}


const char* CConfigSchemaHelper::getTableValue(const char* pXPath,  int nRow) const
{
    assert(pXPath != NULL);

    CAttribute **pAttribute = (m_attributePtrsMap.getValue(pXPath));
    CElement **pElement = NULL;

    if (pAttribute == NULL)
    {
        pElement = m_elementPtrsMap.getValue(pXPath);

        assert(pElement != NULL);

        return (*pElement)->getEnvValueFromXML();
    }
    else
    {
        assert(pAttribute != NULL);

        if (nRow == 1)
        {
            return (*pAttribute)->getEnvValueFromXML();
        }
        else
        {
            StringBuffer strXPath(pXPath);
            StringBuffer strXPathOrignal(pXPath);

            CConfigSchemaHelper::stripXPathIndex(strXPath);
            CConfigSchemaHelper::stripXPathIndex(strXPath);

            strXPath.appendf("[%d]", nRow);

            char pTemp[64];
            int offset = strlen(itoa(nRow, pTemp, 10)) - 1;

            strXPath.append((String(strXPathOrignal).substring(strXPath.length()-offset, strXPathOrignal.length()))->toCharArray());

            pAttribute = (m_attributePtrsMap.getValue(strXPath.str()));

            assert(pAttribute != NULL);

            return (*pAttribute)->getEnvValueFromXML();
        }
    }
}

int CConfigSchemaHelper::getElementArraySize(const char *pXPath) const
{
    assert(pXPath != NULL);

    CElementArray **pElementArray = m_elementArrayPtrsMap.getValue(pXPath);

    //assert(pElementArray != NULL);
    if (pElementArray == NULL)
    {
        return 0;
    }

    return (**pElementArray).getCountOfSiblingElements(pXPath);
}

const char* CConfigSchemaHelper::getAttributeXSDXPathFromEnvXPath(const char* pEnvXPath) const
{
    assert(pEnvXPath != NULL && *pEnvXPath != 0);

    CAttribute **pAttribute = m_attributePtrsMap.getValue(pEnvXPath);

    assert(pAttribute != NULL);

    return (*pAttribute)->getXSDXPath();
}

const char* CConfigSchemaHelper::getElementArrayXSDXPathFromEnvXPath(const char* pEnvXPath) const
{
    assert(pEnvXPath != NULL && *pEnvXPath != 0);

    CElementArray **pElementArray = m_elementArrayPtrsMap.getValue(pEnvXPath);

    assert(pElementArray != NULL);

    return (*pElementArray)->getXSDXPath();
}


void CConfigSchemaHelper::stripXPathIndex(StringBuffer &strXPath)
{
    int nLen = strXPath.length()-3;

    while (nLen > 0)
    {
        if (strXPath[nLen] == '[')
        {
            strXPath.reverse().remove(0,strXPath.length()-nLen).reverse();
            return;
        }
        nLen--;
    }
}
