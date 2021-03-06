################################################################################
#    HPCC SYSTEMS software Copyright (C) 2012 HPCC Systems®.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
################################################################################


# Component: eclscheduler

#####################################################
# Description:
# ------------
#    Cmake Input File for eclscheduler
#####################################################


project( eclscheduler ) 

set (    SRCS 
         eclscheduler.cpp 
    )

set (    INCLUDES
    )

include_directories ( 
         ./../../common/remote 
         ./../../common/workunit 
         ./../../system/include 
         ./../../system/mp 
         ./../../dali/base 
         ./../../system/jlib 
         ./../../ecl/schedulectrl
    )

HPCC_ADD_EXECUTABLE ( eclscheduler ${SRCS} ${INCLUDES} )
install ( TARGETS eclscheduler RUNTIME DESTINATION ${EXEC_DIR} )

target_link_libraries ( eclscheduler 
         jlib
         schedulectrl
         workunit
    )

