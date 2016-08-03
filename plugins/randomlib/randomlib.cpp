#include <cassert>
#include <cstdlib>
#include <cstring>
#include "randomlib.hpp"
#include "jutil.hpp"

#define RANDOMLIB_VERSION "RANDOMLIB 1.0.00"

static const char * EclDefinition =
"export RandomLib := SERVICE\n"
"  unsigned GetNextPseudoRandomNumberUniformDistribution(unsigned engine, unsigned lower_bound, unsigned upper_bound) : c, pure,fold,entrypoint='prGetNextPseudoRandomNumberUniformDistribution'; \n"
"END;";

RANDOMLIB_API bool getECLPluginDefinition(ECLPluginDefinitionBlock *pb)
{
    if (pb->size != sizeof(ECLPluginDefinitionBlock))
        return false;

    pb->magicVersion = PLUGIN_VERSION;
    pb->version = RANDOMLIB_VERSION " $Revision: 62376 $";
    pb->moduleName = "lib_randomlib";
    pb->ECL = EclDefinition;
    pb->flags = PLUGIN_IMPLICIT_MODULE;
    pb->description = "C++11 Random Library (partial)";
    return true;
}

extern "C"
{
namespace nsRandomLib
{
    IPluginContext * parentCtx = NULL;
}

using namespace nsRandomLib;
thread_local Owned<IPseudoRandomNumberGenerator> pseudo_random_ = createPseudoRandomNumberGenerator();

RANDOMLIB_API void setPluginContext(IPluginContext * _ctx) { parentCtx = _ctx; }

RANDOMLIB_API unsigned prGetNextPseudoRandomNumberUniformDistribution(enum IPseudoRandomNumberGenerator::ePseudoRandomNumberEngine engine, unsigned lower_bound, unsigned upper_bound)
{
    return pseudo_random_->nextUniform(static_cast<IPseudoRandomNumberGenerator::ePseudoRandomNumberEngine>(engine), lower_bound, upper_bound);
}
} // extern "C++"
