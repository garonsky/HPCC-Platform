project ( configurator )

set ( SRCS QMLMarkup.cpp QMLMarkup.hpp ConfiguratorMain.cpp ConfigFileComponentUtils.cpp ConfigFileUtils.cpp ConfigFileUtilsObservable.cpp
      ConfigFileUtilsObserver.cpp EnvironmentConfiguration.cpp WizardBase.cpp ConfigSchemaHelper.cpp
      SchemaAttributes.cpp SchemaComplexType.cpp SchemaSequence.cpp SchemaElement.cpp
      SchemaAppInfo.cpp SchemaAnnotation.cpp SchemaComplexContent.cpp SchemaComplexType.cpp SchemaDocumentation.cpp
      SchemaExtension.cpp SchemaChoice.cpp SchemaInclude.cpp SchemaSchema.cpp SchemaSimpleType.cpp SchemaRestriction.cpp NodeHandlerDocumentation.cpp DojoHelper.cpp
      SchemaEnumeration.cpp SchemaCommon.cpp ExceptionStrings.cpp SchemaEnumeration.cpp SchemaAttributeGroup.cpp DocumentationMarkup.hpp DojoJSMarkup.hpp
      SchemaCommon.hpp BuildSet.cpp ConfiguratorAPI.cpp)

include_directories (
         ./../../system/include
         ./../../system/jlib
         ./../deploy/

         /opt/Qt/5.1.1/gcc_64/mkspecs/linux-g++
         /opt/Qt/5.1.1/gcc_64/include
         /opt/Qt/5.1.1/gcc_64/include/QtQuick
         /opt/Qt/5.1.1/gcc_64/include/QtQml
         /opt/Qt/5.1.1/gcc_64/include/QtNetwork
         /opt/Qt/5.1.1/gcc_64/include/QtGui
         /opt/Qt/5.1.1/gcc_64/include/QtCore
         ./../configurator_ui
         ./../configurator_app

)


# STATIC LIBRARY (.a)
ADD_DEFINITIONS( -D_USRDLL -DCONFIGURATOR_STATIC_LIB)
HPCC_ADD_LIBRARY ( configurator  ${SRCS} )

# APPLICATION
#ADD_DEFINITIONS ( -D_CONSOLE )
#link_directories(../configurator_ui /opt/Qt/5.1.1/gcc_64/lib/ )
#HPCC_ADD_EXECUTABLE ( configurator  ${SRCS} )
#target_link_libraries ( configurator jlib ConfiguratorUI )

# QT APPLICATION
#link_directories(../configurator_ui /opt/Qt/5.1.1/gcc_64/lib/ ../build-configurator_app-Desktop-Debug )
#target_link_libraries ( configurator jlib ConfiguratorUI configurator_app )

install ( TARGETS configurator DESTINATION sbin )
