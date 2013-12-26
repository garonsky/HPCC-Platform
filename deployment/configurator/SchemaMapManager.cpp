#include "SchemaMapManager.hpp"
#include "SchemaAll.hpp"

CSchemaMapManager::CSchemaMapManager()
{

}

CSchemaMapManager::~CSchemaMapManager()
{
    //  Does not delete data in maps!!!
}

CSchema* CSchemaMapManager::getSchemaForXSD(const char* pComponent)
{
    CSchema **pSchema = m_schemaPtrMap.getValue(pComponent);

    if (pSchema != NULL )
    {
        return *pSchema;
    }
    else
    {
        return NULL;
    }
}

void CSchemaMapManager::setSchemaForXSD(const char* pComponent, CSchema *pSchema)
{
    assert(pSchema != NULL);

    if (pSchema != NULL)
    {
        m_schemaPtrMap.setValue(pComponent, pSchema);
    }
}

CSimpleType* CSchemaMapManager::getSimpleTypeWithName(const char* pName)
{
    assert(pName != NULL);

    if (pName == NULL)
    {
        return NULL;
    }

    CSimpleType **ppSimpleType = NULL;

    ppSimpleType = m_simpleTypePtrMap.getValue(pName);

    if (ppSimpleType != NULL)
    {
        return *ppSimpleType;
    }
    else
    {
        return NULL;
    }
}

void CSchemaMapManager::setSimpleTypeWithName(const char* pName, CSimpleType *pSimpleType)
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

CComplexType* CSchemaMapManager::getComplexTypeWithName(const char* pName)
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

void CSchemaMapManager::setComplexTypeWithName(const char* pName, CComplexType *pComplexType)
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

CComplexType* CSchemaMapManager::getComplexTypeFromXPath(const char *pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    CComplexType** ppComplexType =  m_complexTypePtrsMap.getValue(pXPath);

    if (ppComplexType != NULL)
    {
        return *ppComplexType;
    }
    else
    {
        return NULL;
    }
}

CAttributeGroup* CSchemaMapManager::getAttributeGroup(const char* pName)
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

void CSchemaMapManager::setAttributeGroupTypeWithName(const char* pName, CAttributeGroup *pAttributeGroup)
{
    assert (pAttributeGroup != NULL);

    if (pName == NULL || pAttributeGroup == NULL)
    {
        return;
    }

    if (m_attributeGroupTypePtrsMap.getValue(pName) != NULL)
    {
        m_attributeGroupTypePtrsMap.remove(pName);
        //throw MakeExceptionFromMap(EX_STR_ATTRIBUTE_GROUP_ALREADY_DEFINED);
    }

    m_attributeGroupTypePtrsMap.setValue(pName, pAttributeGroup);
}

CAttributeGroup* CSchemaMapManager::getAttributeGroupFromXPath(const char *pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    if (pXPath == NULL || *pXPath == 0)
    {
        return NULL;
    }

    CAttributeGroup **ppAttributeGroup = m_attributeGroupTypePtrsMap.getValue(pXPath);

    assert(ppAttributeGroup != NULL);

    if (ppAttributeGroup != NULL)
    {
        return *ppAttributeGroup;
    }
    else
    {
        return NULL;
    }
}

void CSchemaMapManager::addMapOfXPathToAttribute(const char*pXPath, CAttribute *pAttribute)
{
    assert (pAttribute != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    // TODO:: throw exception if problems here

    assert(m_attributePtrsMap.find(pXPath) == NULL);

    // should I remove automatically?

    m_attributePtrsMap.setValue(pXPath, pAttribute);
}

void CSchemaMapManager::removeMapOfXPathToAttribute(const char*pXPath)
{
    assert (m_attributePtrsMap.find(pXPath) != NULL);

    m_attributePtrsMap.remove(pXPath);
}

CAttribute* CSchemaMapManager::getAttributeFromXPath(const char* pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    CAttribute **pAttribute = m_attributePtrsMap.getValue(pXPath);

    assert(pAttribute != NULL);

    return *pAttribute;
}

void CSchemaMapManager::addMapOfXPathToElementArray(const char*pXPath, CElementArray *pElementArray)
{
    assert (pElementArray != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    if (m_elementArrayPtrsMap.find(pXPath) != NULL)
    {
        return;  // already mapped, we must be dealing with live data
    }
    m_elementArrayPtrsMap.setValue(pXPath, pElementArray);
}

void CSchemaMapManager::removeMapOfXPathToElementArray(const char*pXPath)
{
    assert (m_elementArrayPtrsMap.find(pXPath) != NULL);
    m_elementArrayPtrsMap.remove(pXPath);
}

CElementArray* CSchemaMapManager::getElementArrayFromXPath(const char* pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    if (pXPath == NULL)
    {
        return NULL;
    }

    CElementArray** ppElementArray = m_elementArrayPtrsMap.getValue(pXPath);

    if (ppElementArray != NULL)
    {
        return *ppElementArray;
    }
    else
    {
        return NULL;
    }
}

void CSchemaMapManager::addMapOfXPathToElement(const char* pXPath, CElement *pElement,  bool bIsTopLevelElement)
{
    assert (pElement != NULL);
    assert(pXPath != NULL && *pXPath != 0);

    assert(m_elementPtrsMap.find(pXPath) == NULL);

    m_elementPtrsMap.setValue(pXPath, pElement);
}

void CSchemaMapManager::removeMapOfXPathToElement(const char*pXPath)
{
    assert (m_elementPtrsMap.find(pXPath) != NULL);
    m_elementPtrsMap.remove(pXPath);
}

CElement* CSchemaMapManager::getElementFromXPath(const char *pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    CElement **ppElement = m_elementPtrsMap.getValue(pXPath);

    assert(ppElement != NULL);

    if (ppElement != NULL)
    {
        return *ppElement;
    }
    else
    {
        return NULL;
    }
}

void CSchemaMapManager::addMapOfXPathToRestriction(const char*pXPath, CRestriction *pRestriction)
{
    assert (pRestriction != NULL);
    assert(pXPath != NULL && *pXPath != 0);
    assert(m_restrictionPtrsMap.find(pXPath) == NULL);

    m_restrictionPtrsMap.setValue(pXPath, pRestriction);
}

void CSchemaMapManager::removeMapOfXPathToRestriction(const char*pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    m_restrictionPtrsMap.remove(pXPath);
}

CRestriction* CSchemaMapManager::getRestrictionFromXPath(const char* pXPath)
{
    assert(pXPath != NULL && *pXPath != 0);

    CRestriction **ppRestriction = m_restrictionPtrsMap.getValue(pXPath);

    assert(ppRestriction != NULL);

    if (ppRestriction != NULL)
    {
        return *ppRestriction;
    }
    else
    {
        return NULL;
    }
}

int CSchemaMapManager::getNumberOfComponents() const
{
    HashIterator iter(m_elementPtrsMap);

    int nCount = 0;

    ForEach(iter)
    {
        CElement *pElement = *(m_elementPtrsMap.mapToValue(&iter.query()));

        if (pElement->isTopLevelElement() == true)
        {
            nCount++;
        }
    }

    return nCount;
}

CElement* CSchemaMapManager::getComponent(int index)
{
    assert(index >= 0 && index < getNumberOfComponents());

    HashIterator iter(m_elementPtrsMap);

    int nCount = 0;

    ForEach(iter)
    {
        CElement *pElement = *(m_elementPtrsMap.mapToValue(&iter.query()));

        if (pElement->isTopLevelElement() == true)
        {
            nCount++;
        }

        if (nCount == index)
        {
            return pElement;
        }
    }

    return NULL;
}

int CSchemaMapManager::getIndexOfElement(const CElement *pElem)
{
    int nCount = 0;

    HashIterator iter(m_elementPtrsMap);

    ForEach(iter)
    {
        CElement *pElement = *(m_elementPtrsMap.mapToValue(&iter.query()));

        if (pElement == pElem)
        {
            return nCount;
        }

        if (pElement->isTopLevelElement() == true)
        {
            nCount++;
        }
    }

    assert(false);
    return -1;
}
