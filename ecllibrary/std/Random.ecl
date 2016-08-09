/*##############################################################################
## HPCC SYSTEMS software Copyright (C) 2016 HPCC Systems®.  All rights reserved.
############################################################################## */


//EXPORT Random := MODULE

IMPORT lib_randomlib;

//EXPORT UNSIGNED4 nextUniformRandom(UNSIGNED4 engine, UNSIGNED4 lower_bound, UNSIGNED4 upper_bound) :=
//    lib_randomlib.GetNextPseudoRandomNumberUniformDistribution(engine, lower_bound, upper_bound);
    //lib_randomlib.StringFilterOut(engine, lower_bound, upper_bound);

//END;


EXPORT Random := SERVICE : plugin('randomplugin'), namespace('nsRandomLib')
  UNSIGNED4 nextUniformRandom(UNSIGNED4 engine, UNSIGNED4 lower_bound, UNSIGNED4 upper_bound) : cpp,action,context,entrypoint='prGetNextPseudoRandomNumberUniformDistribution';
END;
