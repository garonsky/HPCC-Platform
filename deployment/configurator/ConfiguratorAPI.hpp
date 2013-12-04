#ifndef _CONFIGURATOR_API_HPP_
#define _CONFIGURATOR_API_HPP_

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

namespace CONFIGURATOR_API
{

#ifdef CONFIGURATOR_STATIC_LIB
//extern "C" int initialize(int argc, char *argv[]);
extern "C" int initialize();
#endif // CONFIGURATOR_STATIC_LIB

extern "C" int getNumberOfAvailableComponents();
extern "C" int getNumberOfAvailableServices();
extern "C" const char* getServiceName(int idx, char *pName = 0);
extern "C" const char* getComponentName(int idx, char *pName = 0);

extern "C" int getValue(const char *pXPath, char *pValue);
extern "C" void setValue(const char *pXPath, const char *pValue);
extern "C" int getIndex(const char *pXPath);
extern "C" void setIndex(const char *pXPath, int newIndex);

extern "C" const char* getTableValue(const char *pXPath, int nRow);
extern "C" void setTableValue(const char *pXPath, int index, const char *pValue);
extern "C" int getNumberOfUniqueColumns();
extern "C" const char* getColumnName(int idx);
extern "C" int getNumberOfRows(const char* pXPath);
extern "C" int getNumberOfTables();

extern "C" int openConfigurationFile(const char* pFile);
extern "C" int getNumberOfComponentsInConfiguration();
extern "C" const char* getComponentNameInConfiguration(int idx, char *pName = 0);
/*extern "C" void closeConfigurationFile();
extern "C" bool saveConfigurationFile();

extern "C" const char* getComponentNameInConfiguration(int index, char *pName = 0);
extern "C" int getNumberOfServicesInConfiguration();
extern "C" const char* getServiceNameInConfiguration(int index, char *pName = 0);

extern "C" void setActiveView(int bIsService, int idx);*/

}


#endif // _CONFIGURATOR_API_HPP_
