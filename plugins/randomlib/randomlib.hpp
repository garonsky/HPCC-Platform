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

#ifndef RANDOMLIB_INCL
#define RANDOMLIB_INCL

#ifdef _WIN32
#define RANDOMLIB_CALL _cdecl
#ifdef RANDOMLIB_EXPORTS
#define RANDOMLIB_API __declspec(dllexport)
#else
#define RANDOMLIB_API __declspec(dllimport)
#endif
#else
#define RANDOMLIB_CALL
#define RANDOMLIB_API
#endif

#include "hqlplugins.hpp"

extern "C" {
RANDOMLIB_API bool getECLPluginDefinition(ECLPluginDefinitionBlock *pb);
RANDOMLIB_API void setPluginContext(IPluginContext * _ctx);
}

extern "C++"
{
RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberUniformDistribution(const char *engine, unsigned lower_bound, unsigned upper_bound);
RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberBinomialDistribution(const char *engine, const double probability, unsigned upper_bound);
RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberNegativeBinomialDistribution(const char *engine, const double probability, unsigned upper_bound);
RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberGeometricDistribution(const char *engine, const double probability);
RANDOMLIB_API unsigned RANDOMLIB_CALL prGetNextPseudoRandomNumberPoissonDistribution(const char *engine, const double mean);
}

#endif
