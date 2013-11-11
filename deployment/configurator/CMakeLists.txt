project ( configurator )

set ( SRCS QMLMarkup.cpp QMLMarkup.hpp Main.cpp ConfigFileComponentUtils.cpp ConfigFileUtils.cpp ConfigFileUtilsObservable.cpp
      ConfigFileUtilsObserver.cpp EnvironmentConfiguration.cpp WizardBase.cpp ConfigSchemaHelper.cpp
      SchemaAttributes.cpp SchemaComplexType.cpp SchemaSequence.cpp SchemaElement.cpp
      SchemaAppInfo.cpp SchemaAnnotation.cpp SchemaComplexContent.cpp SchemaComplexType.cpp SchemaDocumentation.cpp
      SchemaExtension.cpp SchemaChoice.cpp SchemaInclude.cpp SchemaSchema.cpp SchemaSimpleType.cpp SchemaRestriction.cpp NodeHandlerDocumentation.cpp DojoHelper.cpp
      SchemaEnumeration.cpp SchemaCommon.cpp ExceptionStrings.cpp SchemaEnumeration.cpp SchemaAttributeGroup.cpp DocumentationMarkup.hpp DojoJSMarkup.hpp
      SchemaCommon.hpp )

include_directories (
         ./../../system/include
         ./../../system/jlib
         ./../deploy/
         /opt/Qt5.1.0/5.1.0/gcc_64/mkspecs/linux-g++
         /opt/Qt5.1.0/5.1.0/gcc_64/include
         /opt/Qt5.1.0/5.1.0/gcc_64/include/QtQuick
         /opt/Qt5.1.0/5.1.0/gcc_64/include/QtQml
         /opt/Qt5.1.0/5.1.0/gcc_64/include/QtNetwork
         /opt/Qt5.1.0/5.1.0/gcc_64/include/QtGui
         /opt/Qt5.1.0/5.1.0/gcc_64/include/QtCore

         /opt/Qt/5.1.1/gcc_64/mkspecs/linux-g++
         /opt/Qt/5.1.1/gcc_64/include
         /opt/Qt/5.1.1/gcc_64/include/QtQuick
         /opt/Qt/5.1.1/gcc_64/include/QtQml
         /opt/Qt/5.1.1/gcc_64/include/QtNetwork
         /opt/Qt/5.1.1/gcc_64/include/QtGui
         /opt/Qt/5.1.1/gcc_64/include/QtCore
         ./../configurator_ui

)

ADD_DEFINITIONS ( -D_CONSOLE )

link_directories(../configurator_ui /opt/Qt/5.1.1/gcc_64/lib/ /opt/Qt5.1.0/5.1.0/gcc_64/lib/ )

HPCC_ADD_EXECUTABLE ( configurator  ${SRCS} )
install ( TARGETS configurator DESTINATION sbin )
target_link_libraries ( configurator jlib ConfiguratorUI )
