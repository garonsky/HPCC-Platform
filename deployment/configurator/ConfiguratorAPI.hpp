#ifndef _CONFIGURATOR_API_HPP_
#define _CONFIGURATOR_API_HPP_

namespace CONFIGURATOR_API
{

#ifdef CONFIGURATOR_STATIC_LIB
extern "C" int initialize(int argc, char *argv[]);
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

}


#endif // _CONFIGURATOR_API_HPP_
