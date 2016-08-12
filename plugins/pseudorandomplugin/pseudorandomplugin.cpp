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

#include "platform.h"
#include "eclrtl.hpp"
#include "jstring.hpp"
#include "pseudorandomplugin.hpp"
#include "jutil.hpp"

#define PSEUDO_RANDOM_PLUGIN_VERSION "pseudorandom-plugin plugin 1.0.0"
ECL_PSEUDO_RANDOM_PLUGIN_API bool getECLPluginDefinition(ECLPluginDefinitionBlock *pb)
{
    if (pb->size != sizeof(ECLPluginDefinitionBlock))
        return false;

    pb->magicVersion = PLUGIN_VERSION;
    pb->version = PSEUDO_RANDOM_PLUGIN_VERSION;
    pb->moduleName = "lib_pseudorandom"
    pb->ECL = NULL;
    pb->flags = PLUGIN_IMPLICIT_MODULE;
    pb->description = "ECL plugin library for C++11 pseudo random number generators\n";
    return true;
}

namespace RandomPlugin {

ECL_PSEUDO_RANDOM_PLUGIN_API unsigned ECL_PSEUDO_RANDOM_PLUGIN_CALL prGetNextPseudoRandomNumberUniformDistribution(unsigned engine, unsigned lower_bound, unsigned upper_bound)
{
    return pseudo_pseudorandom->nextUniform(static_cast<IPseudoRandomNumberGenerator::ePseudoRandomNumberEngine>(engine), lower_bound, upper_bound);
}

}//close namespace
