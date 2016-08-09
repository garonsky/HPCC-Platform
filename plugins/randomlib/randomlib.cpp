/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems®.

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

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "randomlib.hpp"
#include "jutil.hpp"

#define RANDOMLIB_VERSION "RANDOMLIB 1.0.00"

static const char * HoleDefinition = NULL;

static const char * EclDefinition =
"export RandomLib := SERVICE\n"
"  unsigned4 GetNextPseudoRandomNumberUniformDistribution(unsigned4 engine, unsigned4 lower_bound, unsigned4 upper_bound) : cpp, pure,fold,entrypoint='prGetNextPseudoRandomNumberUniformDistribution'; \n"

"END;";

RANDOMLIB_API bool getECLPluginDefinition(ECLPluginDefinitionBlock *pb) 
{
    //  Warning:    This function may be called without the plugin being loaded fully.  
    //              It should not make any library calls or assume that dependent modules
    //              have been loaded or that it has been initialised.
    //
    //              Specifically:  "The system does not call DllMain for process and thread 
    //              initialization and termination.  Also, the system does not load 
    //              additional executable modules that are referenced by the specified module."

    if (pb->size != sizeof(ECLPluginDefinitionBlock))
        return false;

    pb->magicVersion = PLUGIN_VERSION;
    pb->version = RANDOMLIB_VERSION " $Revision: 62376 $";
    pb->moduleName = "lib_randomlib";
    pb->ECL = EclDefinition;
    //pb->Hole = HoleDefinition;
    pb->flags = PLUGIN_IMPLICIT_MODULE;
    pb->description = "RandomLib random services library";
    return true;
}

namespace nsRandomlib {
    IPluginContext * parentCtx = NULL;
}
using namespace nsRandomlib;

RANDOMLIB_API void setPluginContext(IPluginContext * _ctx) { parentCtx = _ctx; }

//-------------------------------------------------------------------------------------------------------------------------------------------

namespace nsRandomLib
{

thread_local Owned<IPseudoRandomNumberGenerator> pseudo_random_ = createPseudoRandomNumberGenerator();

inline enum IPseudoRandomNumberGenerator::ePseudoRandomNumberEngine getEngineType(const char *engine)
{
    if (!stricmp(engine, "MINSTD_RAND"))
        return IPseudoRandomNumberGenerator::MINSTD_RAND;
    else if (!stricmp(engine, "MT19937"))
        return IPseudoRandomNumberGenerator::MT19937;
    else if (!stricmp(engine, "RANLUX24_BASE"))
        return IPseudoRandomNumberGenerator::RANLUX24_BASE;
    else if (!stricmp(engine, "RANLUX48_BASE"))
        return IPseudoRandomNumberGenerator::RANLUX48_BASE;
    else if (!stricmp(engine, "RANLUX48_BASE"))
        return IPseudoRandomNumberGenerator::RANLUX48_BASE;
    else // default
        return IPseudoRandomNumberGenerator::MINSTD_RAND0;
}


RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberUniformDistribution(const char *engine, unsigned lower_bound, unsigned upper_bound)
{
    return pseudo_random_->nextUniform(getEngineType(engine), lower_bound, upper_bound);
}

RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberBinomialDistribution(const char *engine, const double probability, unsigned upper_bound)
{
    return pseudo_random_->nextBinomial(getEngineType(engine), probability, upper_bound);
}

RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberNegativeBinomialDistribution(const char *engine, const double probability, unsigned upper_bound)
{
    return pseudo_random_->nextNegativeBinomial(getEngineType(engine), probability, upper_bound);
}

RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberGeometricDistribution(const char *engine, const double probability)
{
    return pseudo_random_->nextGeometric(getEngineType(engine), probability);
}

RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberPoissonDistribution(const char *engine, const double mean)
{
    return pseudo_random_->nextPoisson(getEngineType(engine), mean);
}
}
