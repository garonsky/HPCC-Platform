#include "jstring.hpp"
#include "SchemaCommon.hpp"
#include "BuildSet.hpp"
#include "JSONMarkUp.hpp"
#include "ConfigSchemaHelper.hpp"

using namespace CONFIGURATOR;

void CJSONMarkUpHelper::createUIContent(::StringBuffer &strJSON, unsigned int &offset, const char *pUIType, const char* pLabel, const char* pKey, \
                                        const char *pToolTip, const char *pDefaultValue, const char *pValues)
{
    assert(pUIType);

    offset+= STANDARD_OFFSET_1;

    strJSON.appendf(" %s \"%s\",", JSON_LABEL, pLabel);
    strJSON.appendf(" %s \"%s\",", JSON_TYPE, pUIType);

    //strJSON.appendf(" %s \"%s\",", JSON_KEY, pKey);
    StringBuffer strKey(pKey);
    strKey.replace('/','_'); // for frontend
    strJSON.appendf(" %s \"%s\",", JSON_KEY, strKey.str());

    strJSON.appendf(" %s \"%s\",", JSON_TOOLTIP, pToolTip);
    strJSON.appendf(" %s \"%s\"", JSON_DEFAULT_VALUE, pDefaultValue);

    if (strcmp(pUIType, JSON_TYPE_DROP_DOWN) == 0 && pValues && *pValues)
    {
        strJSON.appendf(", %s [ \"%s\" ]", JSON_VALUES, pValues);
    }
    else if (strcmp(pUIType, JSON_TYPE_TABLE) == 0 && pValues && *pValues)
    {
        strJSON.appendf(", %s [ \"%s\" ]", JSON_COLUMN_NAMES_VALUE, pValues);
    }
}

void CJSONMarkUpHelper::getNavigatorJSON(::StringBuffer &strJSON)
{
    int nComponents = CBuildSetManager::getInstance()->getBuildSetComponentCount();

    if (nComponents == 0)
        return;

    strJSON.append(JSON_NAVIGATOR_BEGIN);
    strJSON.append(JSON_NAVIGATOR_TEXT).append("\"").append(CConfigSchemaHelper::getInstance()->getEnvFilePath()).append("\",").append("\n");
    strJSON.append(JSON_NAVIGATOR_KEY).append("\"").append(CConfigSchemaHelper::getInstance()->getEnvFilePath()).append("\",").append("\n");

    for (int i = 0; i < nComponents; i++)
    {
        if (i == 0)
        {
            strJSON.append("\n");
            strJSON.append(JSON_NAVIGATOR_NODES);
            strJSON.append(JSON_NAVIGATOR_NODE_BEGIN);
        }

        StringBuffer strComponentTypeName(CBuildSetManager::getInstance()->getBuildSetComponentTypeName(i));
        StringBuffer strComponentProcessName(CBuildSetManager::getInstance()->getBuildSetProcessName(i));

        strJSON.append(JSON_NAVIGATOR_TEXT).append("\"").append(strComponentTypeName.str()).append("\",").append("\n");
        strJSON.append(JSON_NAVIGATOR_KEY).append("\"").append(CBuildSetManager::getInstance()->getBuildSetComponentFileName(i)).append("\"");

        int nInstanceCount = CConfigSchemaHelper::getInstance()->getInstancesOfComponentType(strComponentTypeName.str());

        for (int ii = 0; ii < nInstanceCount; ii++)
        {
            if (ii == 0)
            {
                strJSON.append(",\n");
                strJSON.append(JSON_NAVIGATOR_NODES);
                strJSON.append(JSON_NAVIGATOR_NODE_BEGIN);
            }

            strJSON.append(JSON_NAVIGATOR_TEXT).append("\"").append(CConfigSchemaHelper::getInstance()->getInstanceNameOfComponentType(strComponentProcessName.str(),ii)).append("\",").append("\n");
            strJSON.append(JSON_NAVIGATOR_KEY).append("\"").append(strComponentProcessName.str()).append("[").append(ii+1).append("]").append("\"\n");

            if (ii+1 < nInstanceCount)
            {
                strJSON.append("},\n{");
            }
            else
            {
                strJSON.append("\n");
                strJSON.append(JSON_NAVIGATOR_NODE_END);
            }
        }

        if (i+1 < nComponents)
        {
            strJSON.append("},\n{");
        }
        else
        {
            strJSON.append("\n");
            strJSON.append(JSON_NAVIGATOR_NODE_END);
        }

    }
    strJSON.append(JSON_NAVIGATOR_END);
}
