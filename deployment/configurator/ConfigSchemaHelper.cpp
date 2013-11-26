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
#include "SchemaMapManager.hpp"

#define LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET \
int nComponentCount = CBuildSetManager::getInstance()->getBuildSetComponentCount();         \
\
for (int idx = 0; idx < nComponentCount; idx++)


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

CConfigSchemaHelper::CConfigSchemaHelper(const char* pBuildSetFile, const char* pBuildSetDir, const char* pDefaultDirOverride) : m_pBasePath(NULL), m_nTables(0), m_pEnvPropertyTree(NULL), m_pSchemaMapManager(NULL)
{
    assert(pBuildSetFile != NULL);
    assert(pBuildSetDir != NULL);

    CBuildSetManager::getInstance(pBuildSetFile, pBuildSetDir);
    m_pSchemaMapManager = new CSchemaMapManager();
}

CConfigSchemaHelper::~CConfigSchemaHelper()
{
    delete m_pSchemaMapManager;
}

bool CConfigSchemaHelper::populateSchema()
{
    assert(m_pSchemaMapManager != NULL);

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pSchemaName != NULL)
        {
            CXSDNodeBase *pNull = NULL;
            CSchema *pSchema = CSchema::load(pSchemaName, pNull);

            m_pSchemaMapManager->setSchemaForXSD(pSchemaName, pSchema);
        }
    }

    populateEnvXPath();

    return true;
}

void CConfigSchemaHelper::printConfigSchema(StringBuffer &strXML) const
{
    assert(m_pSchemaMapManager != NULL);

    const char *pComponent = NULL;
    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pComponent == NULL || strcmp(pComponent, pSchemaName) == 0)
        {
            const char* pXSDSchema = pSchemaName;

            if (pXSDSchema == NULL)
            {
                continue;
            }

            pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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
    assert(comp != NULL && *comp != 0);
    assert(m_pSchemaMapManager != NULL);

    if (comp == NULL || *comp == 0)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;


    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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
    assert(comp != NULL && *comp != 0);
    assert(m_pSchemaMapManager != NULL);

    if (comp == NULL || *comp == 0)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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
    assert(comp != NULL && *comp != 0);
    assert(m_pSchemaMapManager != NULL);

    if (comp == NULL || *comp == 0)
    {
        return NULL;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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
    assert(comp != NULL && *comp != 0);
    assert(m_pSchemaMapManager != NULL);

    if (comp == NULL || *comp == 0)
    {
        return;
    }

    CSchema* pSchema = NULL;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pSchemaName != NULL && strcmp(comp, pSchemaName) == 0)
        {
             pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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
    assert (m_pSchemaMapManager != NULL);

    CAttributeArray *pAttributeArray = NULL;
    CElementArray *pElementArray = NULL;
    CSchema* pSchema = NULL;

    strXML.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Environment>\n\t<Software>");

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pComponent == NULL || strcmp(pComponent, pSchemaName) == 0)
        {

            if (pSchemaName == NULL)
            {
                continue;
            }

            pSchema =  m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

            if (pSchema != NULL)
            {
                strXML.append(pSchema->getXML(NULL));
            }
        }
    }

    strXML.append("\t</Software>\n</Environment>\n");

    return true;
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

            pNodeBase = m_pSchemaMapManager->getSimpleTypeWithName(pName) != NULL ? dynamic_cast<CSimpleType*>(m_pSchemaMapManager->getSimpleTypeWithName(pName)) : NULL;

            if (pNodeBase == NULL)
            {
                pNodeBase = m_pSchemaMapManager->getComplexTypeWithName(pName) != NULL ? dynamic_cast<CComplexType*>(m_pSchemaMapManager->getComplexTypeWithName(pName)) : NULL ;
            }

            assert(pNodeBase != NULL);

            if (pNodeBase != NULL)
            {
                Extension.setBaseNode(pNodeBase);
            }
        }
    }

    m_extensionArr.popAll(false);
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
            assert(m_pSchemaMapManager != NULL);

            CAttributeGroup *pAttributeGroup = m_pSchemaMapManager->getAttributeGroupFromXPath(pRef);

            assert(pAttributeGroup != NULL);

            if (pAttributeGroup != NULL)
            {
                AttributeGroup.setRefNode(pAttributeGroup);
            }
        }
    }

    m_attributeGroupArr.popAll(true);
}

void CConfigSchemaHelper::populateEnvXPath()
{
    CSchema* pSchema = NULL;
    StringBuffer strXPath;

    LOOP_THRU_BUILD_SET_MANAGER_BUILD_SET
    {
        pSchema = m_pSchemaMapManager->getSchemaForXSD(CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx));

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
        pSchema = m_pSchemaMapManager->getSchemaForXSD(CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx));

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
        const char *pSchemaName = CBuildSetManager::getInstance()->getBuildSetComponentFileName(idx);

        if (pComponent == NULL || strcmp(pComponent,pSchemaName) == 0)
        {
            if (pSchemaName == NULL || (pXSDName != NULL && strcmp(pXSDName, pSchemaName) != 0))
            {
                continue;
            }

            pSchema = m_pSchemaMapManager->getSchemaForXSD(pSchemaName);

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

void CConfigSchemaHelper::setEnvTreeProp(const char *pXPath, const char* pValue)
{
    assert(pXPath != NULL && pXPath[0] != 0);
    assert(m_pSchemaMapManager != NULL);

    CAttribute *pAttribute = m_pSchemaMapManager->getAttributeFromXPath(pXPath);

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
    assert(m_pSchemaMapManager != NULL);

    CAttribute *pAttribute = m_pSchemaMapManager->getAttributeFromXPath(pXPath);
    CElement *pElement = NULL;

    if (pAttribute == NULL)
    {
        pElement = m_pSchemaMapManager->getElementFromXPath(pXPath);

        assert(pElement != NULL);

        return pElement->getEnvValueFromXML();
    }
    else
    {
        assert(pAttribute != NULL);

        if (nRow == 1)
        {
            return pAttribute->getEnvValueFromXML();
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

            pAttribute = m_pSchemaMapManager->getAttributeFromXPath(strXPath.str());

            assert(pAttribute != NULL);

            return pAttribute->getEnvValueFromXML();
        }
    }
}

int CConfigSchemaHelper::getElementArraySize(const char *pXPath) const
{
    assert(pXPath != NULL);
    assert(m_pSchemaMapManager != NULL);

    CElementArray *pElementArray = m_pSchemaMapManager->getElementArrayFromXPath(pXPath);

    if (pElementArray == NULL)
    {
        return 0;
    }

    return pElementArray->getCountOfSiblingElements(pXPath);
}

const char* CConfigSchemaHelper::getAttributeXSDXPathFromEnvXPath(const char* pEnvXPath) const
{
    assert(pEnvXPath != NULL && *pEnvXPath != 0);
    assert(m_pSchemaMapManager != NULL);

    CAttribute *pAttribute = m_pSchemaMapManager->getAttributeFromXPath(pEnvXPath);

    assert(pAttribute != NULL);

    return pAttribute->getXSDXPath();
}

const char* CConfigSchemaHelper::getElementArrayXSDXPathFromEnvXPath(const char* pEnvXPath) const
{
    assert(pEnvXPath != NULL);
    assert(m_pSchemaMapManager != NULL);

    CElementArray *pElementArray = m_pSchemaMapManager->getElementArrayFromXPath(pEnvXPath);

    assert(pElementArray != NULL);

    return pElementArray->getXSDXPath();
}

void CConfigSchemaHelper::appendAttributeXPath(const char* pXPath)
{
    m_strArrayEnvXPaths.append(pXPath);
}

void CConfigSchemaHelper::appendElementXPath(const char* pXPath)
{
    m_strArrayEnvXPaths.append(pXPath);
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
