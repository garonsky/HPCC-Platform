#ifndef _EXCEPTION_STRINGS_HPP_
#define _EXCEPTION_STRINGS_HPP_

#include "jexcept.hpp"
#include <cstring>

#define MAX_EXCEPTION_STRING_LENGTH 2048

#define CATCH_EXCEPTION_AND_EXIT \
catch (IException *except) \
{\
    StringBuffer strErrMsg;\
    except->errorMessage(strErrMsg);\
    std::cout << std::endl << strErrMsg.str() << std::endl << std::endl;\
    exit(-1);\
}

enum eExceptionCodes
{
    EX_STR_CAN_NOT_OPEN_XSD  = 1,
    EX_STR_SIMPLE_TYPE_ALREADY_DEFINED,
    EX_STR_COMPLEX_TYPE_ALREADY_DEFINED,
    EX_STR_ATTRIBUTE_GROUP_ALREADY_DEFINED,
    EX_STR_CAN_NOT_PROCESS_ENV_XML,
    EX_STR_XPATH_DOES_NOT_EXIST_IN_TREE,
    EX_STR_MISSING_REQUIRED_ATTRIBUTE,
    EX_STR_UNKNOWN,
    EX_STR_LAST_ENTRY
};


const char pExceptionStringArray[EX_STR_LAST_ENTRY][MAX_EXCEPTION_STRING_LENGTH] = { /*** ALWAYS AT TO THE END OF THE ARRAY!!! ***/
                                                                                     "can not open xsd file",
                                                                                     "simple type already defined",
                                                                                     "complex type already defined",
                                                                                     "attribute group already defined",
                                                                                     "can not open/parse environment xml configuration",
                                                                                     "xpath does not exist in supplied tree",
                                                                                     "the xml file is missing a required attribute based on the xsd"
                                                                                     /*** ADD CORRESPONDING ENTRY TO pExceptionStringActionArray ***/
                                                                                    };

const char pExceptionStringActionArray[EX_STR_LAST_ENTRY][MAX_EXCEPTION_STRING_LENGTH] = {  /*** ALWAYS AT TO THE END OF THE ARRAY!!! ***/
                                                                                            "Ensure that input xsd files exist and that it's permissions are set properly",
                                                                                            "Multiple xs:simpleType tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing." ,
                                                                                            "Multiple xs:complexType tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing.",
                                                                                            "Multiple xs:attributeGroup tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing.",
                                                                                            "Failed to open/parss specified configuration file.  Verify file exits, permissions are set properly, and the file is valid.",
                                                                                            "The XML file may have errors.",
                                                                                            "The XML file may have errors.  An attribute marked as required in the XSD is missing in the xml file."
                                                                                            /*** ADD CORRESPONDING ENTRY TO pExceptionStringActionArray ***/
                                                                                        };

IException *MakeExceptionFromMap(int code, enum eExceptionCodes, const char* pMsg = NULL);
IException *MakeExceptionFromMap(enum eExceptionCodes, const char* pMsg = NULL);

#endif // _EXCEPTION_STRINGS_HPP_
