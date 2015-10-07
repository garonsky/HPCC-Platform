################################################################################
#    HPCC SYSTEMS software Copyright (C) 2014 HPCC Systems.
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

project (ws_configurator)

include(${HPCC_SOURCE_DIR}/esp/scm/additional.cmake)

set 	( 	SRCS
		${HPCC_SOURCE_DIR}/esp/scm/ws_configurator.ecm
		${ESPSCM_GENERATED_DIR}/ws_configurator_esp.cpp
		./ws_configurator.cpp
		./ws_configurator_plugin.cpp
	)

include_directories (
         ${HPCC_SOURCE_DIR}/esp/esplib
         ${HPCC_SOURCE_DIR}/esp/platform
         ${HPCC_SOURCE_DIR}/system/jlib
         ${HPCC_SOURCE_DIR}/common/environment
         ${HPCC_SOURCE_DIR}/esp/services
         ${HPCC_SOURCE_DIR}/common
         ${HPCC_SOURCE_DIR}/system/security/securesocket
         ${HPCC_SOURCE_DIR}/system/security/shared
         ${HPCC_SOURCE_DIR}/system/include
         ${HPCC_SOURCE_DIR}/common/remote
         ${HPCC_SOURCE_DIR}/clients
         ${HPCC_SOURCE_DIR}/dali/base
         ${HPCC_SOURCE_DIR}/common/dllserver
         ${HPCC_SOURCE_DIR}/esp/bindings
         ${HPCC_SOURCE_DIR}/esp/bindings/SOAP/xpp
         ${HPCC_SOURCE_DIR}/esp/bindings/http/client
         ${HPCC_SOURCE_DIR}/esp/http/platform
         ${HPCC_SOURCE_DIR}/system/mp
         ${HPCC_SOURCE_DIR}/system/xmllib
         ${HPCC_SOURCE_DIR}/configuration/configurator
         ${CMAKE_BINARY_DIR}
         ${CMAKE_BINARY_DIR}/oss
         ${CMAKE_BINARY_DIR}/esp/services/ws_configurator
    )

ADD_DEFINITIONS( -D_USRDLL )

HPCC_ADD_LIBRARY( ws_configurator SHARED ${SRCS}  )
add_dependencies (ws_configurator ws_configuratorespscm)
install ( TARGETS ws_configurator RUNTIME DESTINATION ${EXEC_DIR} LIBRARY DESTINATION ${LIB_DIR} )
target_link_libraries ( ws_configurator
         jlib
         xmllib
         esphttp
         environment
         dllserver
         securesocket
    )

