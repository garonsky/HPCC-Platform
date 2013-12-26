//#ifdef CONFIGURATOR_STATIC_LIB

#include "ConfiguratorAPI.hpp"
#include "ConfiguratorMain.hpp"
#include "BuildSet.hpp"
#include "ConfigSchemaHelper.hpp"
#include "ConfiguratorMain.hpp"
#include "jstring.hpp"
#include "SchemaMapManager.hpp"
#include "SchemaEnumeration.hpp"
#include "SchemaCommon.hpp"
#include "ConfiguratorMain.hpp"
#include "EnvironmentModel.hpp"

namespace CONFIGURATOR_API
{

static CConfigSchemaHelper *s_pConfigSchemaHelper = NULL;

int getNumberOfAvailableComponents()
{
    assert(s_pConfigSchemaHelper != NULL);

    StringArray arrComps;

    CBuildSetManager::getInstance()->getBuildSetComponents(arrComps);

    return arrComps.length();
}

int getNumberOfAvailableServices()
{
    assert(s_pConfigSchemaHelper != NULL);

    StringArray arrServices;

    CBuildSetManager::getInstance()->getBuildSetServices(arrServices);

    return arrServices.length();
}

const char* getBuildSetServiceName(int idx, char *pName)
{
    assert(s_pConfigSchemaHelper != NULL);

    if (pName != NULL)
    {
        strncpy(pName, CBuildSetManager::getInstance()->getBuildSetServiceName(idx), CBuildSetManager::getInstance()->getBuildSetServiceName(idx) == NULL ? 0 : strlen(CBuildSetManager::getInstance()->getBuildSetServiceName(idx)));
    }

    return CBuildSetManager::getInstance()->getBuildSetServiceName(idx);
}

const char* getBuildSetComponentName(int idx, char *pName)
{
    assert(s_pConfigSchemaHelper != NULL);

    if (pName != NULL)
    {
        strncpy(pName, CBuildSetManager::getInstance()->getBuildSetComponentName(idx), CBuildSetManager::getInstance()->getBuildSetComponentName(idx) == NULL ? 0 : strlen(CBuildSetManager::getInstance()->getBuildSetComponentName(idx)));
    }

    return CBuildSetManager::getInstance()->getBuildSetComponentName(idx);
}


#ifdef CONFIGURATOR_STATIC_LIB

int initialize(int argc, char *argv[])
{
    assert(s_pConfigSchemaHelper == NULL);

    InitModuleObjects();

    //ConfiguratorMain(argc, argv);

    s_pConfigSchemaHelper = CConfigSchemaHelper::getInstance();

    return 1;
}

int initialize()
{
    assert(s_pConfigSchemaHelper == NULL);

    InitModuleObjects();

    s_pConfigSchemaHelper = CConfigSchemaHelper::getInstance();

    s_pConfigSchemaHelper->populateSchema();

    return 1;
}

#endif // CONFIGURATOR_STATIC_LIB

int getValue(const char *pXPath, char *pValue)
{
    int counter = 0;
    itoa(counter, pValue, 10);
    counter++;

    CAttribute *pAttribute = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getAttributeFromXPath(pXPath);

    assert(pAttribute != NULL);

    if (pAttribute->isInstanceValueValid() == true)
    {
        strcpy(pValue, pAttribute->getEnvValueFromXML());
    }
    else
    {
        pValue = NULL;
    }
    return true;
}

void setValue(const char *pXPath, const char *pValue)
{
    assert(pXPath != NULL && pXPath[0] != 0);
    assert(pValue != NULL);

    CAttribute *pAttribute = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getAttributeFromXPath(pXPath);

    assert(pAttribute != NULL);

    pAttribute->setEnvValueFromXML(pValue);
    pAttribute->setInstanceAsValid();

    CConfigSchemaHelper::getInstance()->setEnvTreeProp(pXPath, pValue);
}

int getIndex(const char *pXPath)
{
    CRestriction *pRestriction = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getRestrictionFromXPath(pXPath);

    assert(pRestriction != NULL);
    assert(pRestriction->getEnumerationArray() != NULL);

    return pRestriction->getEnumerationArray()->getEnvValueNodeIndex();
}

void setIndex(const char *pXPath, int newIndex)
{
    assert(newIndex >= 0);

    CRestriction *pRestriction = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getRestrictionFromXPath(pXPath);

    assert(pRestriction != NULL);
    assert(pRestriction->getEnumerationArray() != NULL);

    pRestriction->getEnumerationArray()->setEnvValueNodeIndex(newIndex);

    CConfigSchemaHelper::getInstance()->setEnvTreeProp(pXPath, pRestriction->getEnumerationArray()->item(newIndex).getValue());
}

const char* getTableValue(const char *pXPath, int nRow)
{
    assert(pXPath != NULL && *pXPath != 0);

    CAttribute *pAttribute = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getAttributeFromXPath(pXPath);
    CElement *pElement = NULL;

    if (pAttribute == NULL)
    {
        pElement =  CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getElementFromXPath(pXPath);

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

            pAttribute =  CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getAttributeFromXPath(strXPath.str());

            assert(pAttribute != NULL);

            return pAttribute->getEnvValueFromXML();
        }
    }
}

void setTableValue(const char *pXPath, int index, const char *pValue)
{
    assert(false);  // NOT IMPLEMENTED
}


int getNumberOfUniqueColumns()
{
    return CConfigSchemaHelper::getInstance()->getEnvironmentXPathSize();
}

const char* getColumnName(int idx)
{
    if (idx < CConfigSchemaHelper::getInstance()->getEnvironmentXPathSize())
    {
        return CConfigSchemaHelper::getInstance()->getEnvironmentXPaths(idx);
    }
    else
    {
        return NULL;
    }
}

int getNumberOfRows(const char* pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    return CConfigSchemaHelper::getInstance()->getElementArraySize(pXPath);
}

int getNumberOfTables()
{
    return CConfigSchemaHelper::getInstance()->getNumberOfTables();
}

const char* getServiceName(int idx, char *pName)
{
    if (pName != NULL)
    {
        strcpy (pName, CBuildSetManager::getInstance()->getBuildSetComponentName(idx));
    }
    return CBuildSetManager::getInstance()->getBuildSetComponentName(idx);
}

const char* getComponentName(int idx, char *pName)
{
    if (pName != NULL)
    {
        strcpy (pName, CBuildSetManager::getInstance()->getBuildSetComponentName(idx));
    }
    return CBuildSetManager::getInstance()->getBuildSetComponentName(idx);
}

int openConfigurationFile(const char* pFile)
{
    CConfigSchemaHelper::getInstance()->loadEnvFromConfig(pFile);

    return 1;
}

/*const char* getComponentNameInConfiguration(int idx, char *pName)
{
    if (idx < 0)
    {
        return NULL;
    }

    if (pName != NULL)
    {
        strcpy (pName, CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx)->getName());
    }

    return CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx)->getName();
}*/

int getNumberOfComponentsInConfiguration(void *pData)
{
    if (pData == NULL)
    {
        return CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getNumberOfComponents();
    }
    else
    {
        CElement *pElement = static_cast<CElement*>(pData);

        assert(pElement->getNodeType() == XSD_ELEMENT);

        //int index = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getIndexOfElement(pElement);

        //CElementArray *pElementArray = (static_cast<CElementArray*>(CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(index)->getParentNode()));

        CElementArray *pElementArray = static_cast<CElementArray*>(pElement->getParentNode());

        assert(pElementArray->getNodeType() == XSD_ELEMENT_ARRAY);

        int nLength = pElementArray->length();

        return nLength;
    }
}

void* getComponentInConfiguration(int idx)
{
    assert(idx < CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getNumberOfComponents());

    CElement *pElement = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx);

    return pElement;
}

void* getComponentInstance(int idx, void *pData)
{
    assert(pData != NULL);
    assert(((static_cast<CElement*>(pData))->getNodeType()) == XSD_ELEMENT);

    CElement *pElement = static_cast<CElement*>(pData);

    CElementArray *pElementArray = static_cast<CElementArray*>(pElement->getParentNode());

    //assert(pElementArray->length() > idx);

    if (pElementArray->length() >= idx)
        idx = 0;

    CElement *pElement2 = &(pElementArray->item(idx));

    return pElement2;
}

const char* getComponentNameInConfiguration(int idx, void *pData)
{
    if (pData == NULL)
    {
        return CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx)->getName();
    }
    else
    {
        CElement *pElement = static_cast<CElement*>(pData);

        assert(pElement->getNodeType() == XSD_ELEMENT);

        pElement = &(dynamic_cast<const CElementArray*>(pElement->getConstParentNode())->item(idx));

        const CAttribute *pAttribute = NULL;

        if (pElement->getAttributeArray() != NULL)
        {
            pAttribute = pElement->getAttributeArray()->findAttributeWithName("name");

            return pAttribute->getName();
        }
        else
        {
            return NULL;
        }
    }

    assert(false);
    return NULL;
}


const void* getPointerToComponentInConfiguration(int idx, void *pData, int compIdx)
{
    if (pData == NULL)
    {
        const CElement *pElement = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx);

        assert(pElement != NULL);

        const CXSDNodeBase *pNodeBase = pElement->getConstParentNode();
        const CElementArray *pElementArray = dynamic_cast<const CElementArray*>(pNodeBase);

        assert(pElementArray != NULL);

        return pElementArray;
    }
    else
    {
        assert( compIdx >= 0);

        CElementArray *pElementArray = static_cast<CElementArray*>(pData);

        assert(pElementArray->getNodeType() == XSD_ELEMENT_ARRAY);

        const CXSDNodeBase *pNodeBase = &(pElementArray->item(compIdx+idx));

        const CElement *pReturnElement = dynamic_cast<const CElement*>(pNodeBase);

        return pReturnElement;
    }
}

const void* getPointerToComponentTypeInConfiguration(void *pData)
{
    assert (pData != NULL);

    CElement *pElement = static_cast<CElement*>(pData);

    assert (pElement->getNodeType() == XSD_ELEMENT);

    CElementArray *pElementArray = static_cast<CElementArray*>(pElement->getParentNode());

    pElement = &(pElementArray->item(0));

    return pElement;
}

int getIndexOfParent(void *pData)
{
    assert (pData != NULL);
    assert((static_cast<CElement*>(pData))->getNodeType() == XSD_ELEMENT);

    int nIndexOfParent = CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getIndexOfElement(static_cast<CElement*>(pData));

    assert(nIndexOfParent >= 0);

    return nIndexOfParent;
}

const void* getPointerToComponents()
{
    assert(CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(0)->getConstParentNode()->getNodeType() == XSD_ELEMENT_ARRAY);

    return (CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(0)->getConstParentNode());
}

int getNumberOfChildren(void *pData)
{
    int nRetVal = 0;

    if (pData == NULL)
    {
     //  CEnvironmentModel *pModel = CEnvironmentModel::getInstance();

//        nRetVal = pModel->getRoot()->getNumberOfChildren();
        return 1;
    }
    else
    {
        CEnvironmentModelNode *pNode = static_cast<CEnvironmentModelNode*>(pData);

        nRetVal = pNode->getNumberOfChildren();
    }

    return nRetVal;
}

const char* getData(void *pData)
{
    assert(pData != NULL);

    const char *p = CEnvironmentModel::getInstance()->getData(static_cast<CEnvironmentModelNode*>(pData));

    return p;
}

void* getParent(void *pData)
{
    //assert(pData != NULL);

    if (pData == NULL)
    {
        return NULL;
    }

    return (void*)(CEnvironmentModel::getInstance()->getParent(static_cast<CEnvironmentModelNode*>(pData)));
}

void* getChild(void *pData, int idx)
{
    if (pData == NULL)
    {
        assert(idx < CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getNumberOfComponents());

        return (void*)(CEnvironmentModel::getInstance()->getRoot());
    }
    else
    {
        void *pRetPtr = (void*)(CEnvironmentModel::getInstance()->getChild(static_cast<CEnvironmentModelNode*>(pData), idx));

        if (pRetPtr == NULL)
        {
            pRetPtr = pData;
        }

        return pRetPtr;
    }
}

int getIndexFromParent(void *pData)
{
    assert(pData != NULL);

    CEnvironmentModelNode *pNode = static_cast<CEnvironmentModelNode*>(pData);

    assert (pNode->getParent() != NULL);

    CEnvironmentModelNode *pGrandParent = pNode->getParent();

    int nChildren = pGrandParent->getNumberOfChildren();

    for (int idx = 0; idx < nChildren; idx++)
    {
        if (pNode == pGrandParent->getChild(idx))
        {
            return idx;
        }
    }

    assert(false);
    return 0;
}

/*void* getComponent(void *pComponent, int idx)
{
    assert(idx >= 0);

    if (pComponenet == NULL)
    {
        return CConfigSchemaHelper::getInstance()->getSchemaMapManager()->getComponent(idx)->getParentNode();
    }
    else
    {
        CElementArray *pElementArray = static_cast<CElementArray*>(pComponent);

        if (pElementArray->length() >= idx || idx < 0)
        {
            return NULL;
        }

        pElementArray->item()
    }
}*/


/*
void closeConfigurationFile()
{

}

bool saveConfigurationFile()
{
    return true;
}


const char* getComponentNameInConfiguration(int index, char *pName = 0)
{

}

int getNumberOfServicesInConfiguration()
{

}

const char* getServiceNameInConfiguration(int index, char *pName = 0)
{

}
*/

}
//#endif // CONFIGURATOR_STATIC_LIB
