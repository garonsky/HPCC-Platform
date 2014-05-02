<Archive>
<!--

    HPCC SYSTEMS software Copyright (C) 2014 HPCC Systems.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
-->
 <OnWarning value="2131=error"/>
 <Query>
//Command line maps it to an error, but #ONWARNING maps it to just log the information
#ONWARNING(2131, LOG);
idRec := { unsigned id; };
inRec := { unsigned id, dataset(idRec) ids; };
d := DATASET('in', inRec, thor);
output(SORT(d, id).ids);
 </Query>
</Archive>
