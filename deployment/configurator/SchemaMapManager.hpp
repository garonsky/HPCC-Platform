#include "jhash.hpp"

#ifndef _SCHEMA_MAP_MANAGER_HPP_
#define _SCHEMA_MAP_MANAGER_HPP_

class CSchema;
class CAttribute;
class CAttributeGroup;
class CSimpleType;
class CComplexType;
class CAttributeGroup;
class CAttribute;
class CRestriction;
class CElementArray;
class CElement;

class CSchemaMapManager
{

public:

    CSchemaMapManager();
    virtual ~CSchemaMapManager();

    CSchema* getSchemaForXSD(const char* pComponent);
    void setSchemaForXSD(const char* pComponent, CSchema *pSchema);

    CSimpleType* getSimpleTypeWithName(const char* pName);
    void setSimpleTypeWithName(const char* pName, CSimpleType *pSimpleType);

    CComplexType* getComplexTypeWithName(const char* pName);
    void setComplexTypeWithName(const char* pName, CComplexType *pComplexType);
    CComplexType* getComplexTypeFromXPath(const char *pXPath);

    CAttributeGroup *getAttributeGroup(const char* pName);
    void setAttributeGroupTypeWithName(const char* pName, CAttributeGroup *pAttributeGroup);
    CAttributeGroup* getAttributeGroupFromXPath(const char *pXPath);
//    void clearAttributeGroupMap(bool nodestruct = false);

    void addMapOfXPathToAttribute(const char* pXPath, CAttribute *pAttribute);
    void removeMapOfXPathToAttribute(const char* pXPath);
    CAttribute* getAttributeFromXPath(const char* pXPath);

    void addMapOfXPathToRestriction(const char*pXPath, CRestriction *pRestriction);
    void removeMapOfXPathToRestriction(const char*pXPath);
    CRestriction* getRestrictionFromXPath(const char* pXPath);

    void addMapOfXPathToElementArray(const char* pXPath, CElementArray *pElementArray);
    void removeMapOfXPathToElementArray(const char* pXPath);
    CElementArray* getElementArrayFromXPath(const char* pXPath);

    void addMapOfXPathToElement(const char* pXPath, CElement *pElement, bool bIsTopLevelElement = false);
    void removeMapOfXPathToElement(const char* pXPath);
    CElement* getElementFromXPath(const char *pXPath);

    int getNumberOfComponents() const;
    CElement* getComponent(int index);
    int getIndexOfElement(const CElement *pElem);

protected:

    MapStringTo<CSchema*> m_schemaPtrMap;
    MapStringTo<CSimpleType*> m_simpleTypePtrMap;
    MapStringTo<CComplexType*> m_complexTypePtrsMap;
    MapStringTo<CAttributeGroup*> m_attributeGroupTypePtrsMap;
    MapStringTo<CAttribute*> m_attributePtrsMap;
    MapStringTo<CRestriction*> m_restrictionPtrsMap;
    MapStringTo<CElementArray*> m_elementArrayPtrsMap;
    MapStringTo<CElement*> m_elementPtrsMap;

private:

};

#endif // _SCHEMA_MAP_MANAGER_HPP_
