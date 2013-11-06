#ifndef _CONFIG_SCHEMA_HELPER_HPP_
#define _CONFIG_SCHEMA_HELPER_HPP_

#include "jiface.hpp"
#include "jutil.hpp"
#include "jarray.hpp"
#include "jhash.hpp"
#include "SchemaAttributes.hpp"
#include "SchemaAttributeGroup.hpp"
#include "SchemaElement.hpp"
#include "SchemaSchema.hpp"
#include "SchemaExtension.hpp"
#include "BuildSet.hpp"
//#include "XMLConfiguration.hpp"

class CSimpleType;

class CConfigSchemaHelper : public CInterface//, CXMLConfiguration
{
public:

    IMPLEMENT_IINTERFACE

    static CConfigSchemaHelper* getInstance(const char* pDefaultDirOverride =  NULL);
    static CConfigSchemaHelper* getInstance(const char* pBuildSetFileName, const char *pBaseDirectory, const char *pDefaultDirOverride = NULL);

    virtual ~CConfigSchemaHelper();

    void getBuildSetComponents(StringArray& buildSetArray) const;
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

    void setBuildSetArray(const StringArray &strArray);

    void addToolTip(const char *js);

    const char* getToolTipJS() const;

    const char* getBasePath() const
    {
        return m_pBasePath;
    }

    void setEnvTreeProp(const char *pXPath, const char* pValue);

    void addMapOfAttributeToXPath(const char*pXPath, CAttribute *pAttribute);
    void removeMapOfAttributeToXPath(const char*pXPath);

    void addMapOfRestrictionToXPath(const char*pXPath, CRestriction *pRestriction);
    void removeMapOfRestrictionToXPath(const char*pXPath);

    bool getValue(const char *pXPath, char *pValue);
    void setValue(const char *pXPath, const char *pValue);
    int getIndex(const char *pXPath);

protected:

    CConfigSchemaHelper(const char* pBuildSetFile = DEFAULT_BUILD_SET_XML_FILE, const char* pBuildSetDir = DEFAULT_BUILD_SET_DIRECTORY, const char* pDefaultDirOverride = NULL);

    Owned<IPropertyTree> m_buildSetTree;
    CIArrayOf<CBuildSet> m_buildSetArray;
    MapStringToMyClass<CSchema> m_schemaMap;
    MapStringTo<CSimpleType*> m_simpleTypePtrMap;
    MapStringTo<CComplexType*> m_complexTypePtrsMap;
    MapStringTo<CAttributeGroup*> m_attributeGroupTypePtrsMap;
    MapStringTo<CAttribute*> m_attributePtrsMap;
    MapStringTo<CRestriction*> m_restrictionPtrsMap;
    CIArrayOf<CExtension> m_extensionArr;
    CIArrayOf<CAttributeGroup> m_attributeGroupArr;
    StringBuffer m_buildSetPath;
    StringArray m_strToolTipsJS;

    IPropertyTree* getEnvPropertyTree()
    {
        return m_pEnvPropertyTree;
    }

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
    const char *m_pBasePath;

    StringBuffer m_strEnvFilePath;

    IPropertyTree *m_pEnvPropertyTree;

    void setBasePath(const char* pBasePath)
    {
        assert(m_pBasePath == NULL); // why ever set this twice?
        m_pBasePath = pBasePath;
    }
};

#endif // _CONFIG_SCHEMA_HELPER_HPP_
