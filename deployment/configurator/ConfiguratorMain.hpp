#ifndef _CONFIGURATOR_MAIN_HPP_
#define _CONFIGURATOR_MAIN_HPP_

#include "ConfiguratorAPI.hpp"
//#define MAX_ARRAY_X 10
//#define MAX_ARRAY_Y 128

/*const char modelNames[MAX_ARRAY_X][MAX_ARRAY_Y] = {"tableDataModel0",
                                                   "tableDataModel1",
                                                   "tableDataModel2",
                                                   "tableDataModel3",
                                                   "tableDataModel4",
                                                   "tableDataModel5",
                                                   "tableDataModel6",
                                                   "tableDataModel7",
                                                   "tableDataModel8",
                                                   "tableDataModel9" };
*/
void usage();

#ifdef CONFIGURATOR_STATIC_LIB

extern "C" int ConfiguratorMain(int argc, char* argv[]);

#endif // CONFIGURATOR_STATIC_LIB



#endif // _CONFIGURATOR_MAIN_HPP_
