#ifndef _CONFIG_SCHEMA_HELPER_HPP_
#define _CONFIG_SCHEMA_HELPER_HPP_

#include "jiface.hpp"
#include "jptree.hpp"
#include "jutil.hpp"
#include "jarray.hpp"
#include "jhash.hpp"
#include "SchemaAttributes.hpp"
#include "SchemaAttributeGroup.hpp"
#include "SchemaElement.hpp"
#include "SchemaSchema.hpp"
#include "SchemaExtension.hpp"
#include "BuildSet.hpp"

class CSimpleType;

#define MAX_ARRAY_X 10
#define MAX_ARRAY_Y 128

const char modelNames[MAX_ARRAY_X][MAX_ARRAY_Y] = {"tableDataModel0",
                                                   "tableDataModel1",
                                                   "tableDataModel2",
                                                   "tableDataModel3",
                                                   "tableDataModel4",
                                                   "tableDataModel5",
                                                   "tableDataModel6",
                                                   "tableDataModel7",
                                                   "tableDataModel8",
                                                   "tableDataModel9" };


class CConfigSchemaHelper : public CInterface
{
public:

    IMPLEMENT_IINTERFACE

    static CConfigSchemaHelper* getInstance(const char* pDefaultDirOverride =  NULL);
    static CConfigSchemaHelper* getInstance(const char* pBuildSetFileName, const char *pBaseDirectory, const char *pDefaultDirOverride = NULL);

    virtual ~CConfigSchemaHelper();

    bool populateBuildSet();
    bool populateSchema();
    void printConfigSchema(StringBuffer &str) const;

    CSchema* getSchemaForXSD(const char* pComponent);

    void setSchemaForXSD(const char* pComponent, CSchema *pSchema);

    CSimpleType* getSimpleTypeWithName(const char* pName);
    void setSimpleTypeWithName(const char* pName, CSimpleType *pSimpleType);

    CComplexType* getComplexTypeWithName(const char* pName);
    void setComplexTypeWithName(const char* pName, CComplexType *pComplexType);

    CAttributeGroup *getAttributeGroup(const char* pName);
    void setAttributeGroupTypeWithName(const char* pName, CAttributeGroup *pAttributeGroup);

    void addExtensionToBeProcessed(CExtension *pExtension);
    void addAttributeGroupToBeProcessed(CAttributeGroup *pAttributeGroup);

    //test purposes
    bool getXMLFromSchema(StringBuffer& strXML, const char* pXSD);

    IPropertyTree* getSchema(const char* );

    void processExtensionArr();
    void processAttributeGroupArr();
    void populateEnvXPath();
    void loadEnvFromConfig(const char *pEnvFile);

    void traverseAndProcessArray(const char *pXSDName = NULL);

    const char* printDocumentation(const char* comp);
    const char* printDojoJS(const char* comp);
    const char* printQML(const char* comp) const;
    void printDump(const char* comp) const;
    void dumpStdOut() const;

    void addToolTip(const char *js);

    const char* getToolTipJS() const;

    const char* getBasePath() const
    {
        return m_pBasePath;
    }

    void setEnvTreeProp(const char *pXPath, const char* pValue);

    void addMapOfXPathToAttribute(const char*pXPath, CAttribute *pAttribute);
    void removeMapOfXPathToAttribute(const char*pXPath);

    void addMapOfXPathToRestriction(const char*pXPath, CRestriction *pRestriction);
    void removeMapOfXPathToRestriction(const char*pXPath);

    void addMapOfXPathToElementArray(const char*pXPath, CElementArray *pElementArray);
    void removeMapOfXPathToElementArray(const char*pXPath);

    void addMapOfXPathToElement(const char*pXPath, CElement *pElement);
    void removeMapOfXPathToElement(const char*pXPath);

    bool getValue(const char *pXPath, char *pValue);
    void setValue(const char *pXPath, const char *pValue);
    int getIndex(const char *pXPath);
    void setIndex(const char *pXPath, int newIndex);

    const char* getTableValue(const char* pXPath, int nRow = 1) const;

    int getEnvironmentXPathSize() const
    {
        return m_strArrayEnvXPaths.length();
    }

    const char* getEnvironmentXPaths(int idx) const
    {
        assert(idx >= 0);
        assert(m_strArrayEnvXPaths.length() > idx);

        return m_strArrayEnvXPaths.item(idx);
    }

    int getElementArraySize(const char *pXPath) const;

    const char* getAttributeXSDXPathFromEnvXPath(const char* pEnvXPath) const;
    const char* getElementArrayXSDXPathFromEnvXPath(const char* pEnvXPath) const;

    static void stripXPathIndex(StringBuffer &strXPath);

    IPropertyTree* getEnvPropertyTree()
    {
        return m_pEnvPropertyTree;
    }

    int getNumberOfTables() const
    {
        return m_nTables;
    }

    void incTables()
    {
        m_nTables++;
    }

protected:

    CConfigSchemaHelper(const char* pBuildSetFile = DEFAULT_BUILD_SET_XML_FILE, const char* pBuildSetDir = DEFAULT_BUILD_SET_DIRECTORY, const char* pDefaultDirOverride = NULL);

    MapStringToMyClass<CSchema> m_schemaMap;
    MapStringTo<CSimpleType*> m_simpleTypePtrMap;
    MapStringTo<CComplexType*> m_complexTypePtrsMap;
    MapStringTo<CAttributeGroup*> m_attributeGroupTypePtrsMap;
    MapStringTo<CAttribute*> m_attributePtrsMap;
    MapStringTo<CRestriction*> m_restrictionPtrsMap;
    MapStringTo<CElementArray*> m_elementArrayPtrsMap;
    MapStringTo<CElement*> m_elementPtrsMap;
    CIArrayOf<CExtension> m_extensionArr;
    CIArrayOf<CAttributeGroup> m_attributeGroupArr;
    StringArray m_strToolTipsJS;
    StringArray m_strArrayEnvXPaths;

    void setEnvPropertyTree(IPropertyTree *pEnvTree)
    {
        m_pEnvPropertyTree =  pEnvTree;
    }

    void setEnvFilePath(const char* pEnvFilePath)
    {
        assert(pEnvFilePath != NULL);

        m_strEnvFilePath.set(pEnvFilePath);
    }

    const char* getEnvFilePath() const
    {
        return m_strEnvFilePath.str();
    }

private:

    static CConfigSchemaHelper* s_pCConfigSchemaHelper;
    int m_nTables;
    const char *m_pBasePath;

    StringBuffer m_strEnvFilePath;

    IPropertyTree *m_pEnvPropertyTree;
};

#endif // _CONFIG_SCHEMA_HELPER_HPP_
