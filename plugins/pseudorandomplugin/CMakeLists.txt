################################################################################
#    HPCC SYSTEMS software Copyright (C) 2016 HPCC Systems®.
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

# Component: pseudorandomplugin

#####################################################
# Description:
# ------------
#    Cmake Input File for pseudorandomplugin
#####################################################

project(pseudorandomplugin)

if(PSEUDO_RANDOMPLUGIN)
    ADD_PLUGIN(pseudorandomplugin PACKAGES PSEUDO_RANDOM_PLUGIN_DEP MINVERSION 0.1.0)

    if(MAKE_PSEUDO_RANDOMPLUGIN)
        set(
            SRCS
            pseudorandomplugin.hpp
            pseudorandomplugin.cpp)

        include_directories(
            ./../../system/include
            ./../../system/jlib
            ${PSEUDO_RANDOM_PLUGIN_DEP_INCLUDE_DIR})

        add_definitions(-D_USRDLL -DPSEUDO_RANDOM_PLUGIN_EXPORTS)

        HPCC_ADD_LIBRARY(pseudorandomplugin SHARED ${SRCS})
        if(${CMAKE_VERSION} VERSION_LESS "2.8.9")
            message(WARNING "Cannot set NO_SONAME. shlibdeps will give warnings when package is installed")
        elseif(NOT APPLE)
            set_target_properties(pseudorandomplugin PROPERTIES NO_SONAME 1)
        endif()

        install(
            TARGETS pseudorandomplugin
            DESTINATION plugins)

        target_link_libraries(
            pseudorandomplugin
            jlib
            ${PSEUDO_RANDOM_PLUGIN_DEP_LIBRARIES})
    endif()
endif()
