/*##############################################################################

    HPCC SYSTEMS software Copyright (C) 2016 HPCC Systems®.

    Licensed under the Apache License, Version 2.0 (the License);
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an AS IS BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
############################################################################## */


EXPORT randomplugin := SERVICE : plugin('randomlib'), namespace('nsRandomLib')
  UNSIGNED4 nextUniformRandom(CONST VARSTRING engine, UNSIGNED4 lower_bound, UNSIGNED4 upper_bound) : cpp,entrypoint='prGetNextPseudoRandomNumberUniformDistribution';
  UNSIGNED4 nextBinomialRandom(CONST VARSTRING engine, CONST REAL8 probability, UNSIGNED4 upper_bound) : cpp,entrypoint='prGetNextPseudoRandomNumberBinomialDistribution';
  UNSIGNED4 nextNegativeBinomialRandom(CONST VARSTRING engine, CONST REAL8 probability, UNSIGNED4 upper_bound) : cpp,entrypoint='prGetNextPseudoRandomNumberNegativeBinomialDistribution';
  UNSIGNED4 nextGeometricRandom(CONST VARSTRING engine, CONST REAL8 probability) : cpp,entrypoint='prGetNextPseudoRandomNumberGeometricDistribution';
  UNSIGNED4 nextPoissonRandom(CONST VARSTRING engine, CONST REAL8 mean) : cpp,entrypoint='prGetNextPseudoRandomNumberPoissonDistribution';
END;
