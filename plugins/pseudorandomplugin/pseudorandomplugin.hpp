/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2016 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */

#ifndef ECL_RANDOM_PLUGIN_SYNC_INCL
#define ECL_RANDOM_PLUGIN_SYNC_INCL

#ifdef _WIN32
#define ECL_RANDOM_PLUGIN_CALL _cdecl
#ifdef ECL_RANDOM_PLUGIN_EXPORTS
#define ECL_RANDOM_PLUGIN_API __declspec(dllexport)
#else
#define ECL_RANDOM_PLUGIN_API __declspec(dllimport)
#endif
#else
#define ECL_RANDOM_PLUGIN_CALL
#define ECL_RANDOM_PLUGIN_API
#endif

#include "hqlplugins.hpp"
#include "eclhelper.hpp"

extern "C"
{
    ECL_RANDOM_PLUGIN_API bool getECLPluginDefinition(ECLPluginDefinitionBlock *pb);
    ECL_RANDOM_PLUGIN_API void setPluginContext(IPluginContext * _ctx);
}

extern "C++"
{
namespace nsPseudoRandomPlugin {
    //--------------------------SET----------------------------------------
//    ECL_RANDOM_PLUGIN_API unsigned ECL_RANDOM_PLUGIN_CALL func1  (ICodeContext * _ctx, const char * param1, const char * param2, unsigned param3);
//    ECL_RANDOM_PLUGIN_API void ECL_RANDOM_PLUGIN_CALL func2 (ICodeContext * _ctx, size32_t & returnLength, char * & returnValue, const char * param1, const char * param2, size32_t param3ValueLength, const char * param3Value);

    ECL_RANDOM_PLUGIN_API unsigned ECL_RANDOM_PLUGIN_CALL prGetNextPseudoRandomNumberUniformDistribution(/*enum IPseudoRandomNumberGenerator::ePseudoRandomNumberEngine*/unsigned engine, unsigned lower_bound, unsigned upper_bound);

}
}
#endif
