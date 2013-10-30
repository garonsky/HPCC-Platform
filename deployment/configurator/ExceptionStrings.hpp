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
    EX_STR_UNKNOWN,

    EX_STR_LAST_ENTRY
};


const char pExceptionStringArray[EX_STR_LAST_ENTRY][MAX_EXCEPTION_STRING_LENGTH] = { /*** ALWAYS AT TO THE END OF THE ARRAY!!! ***/
                                                                                     "can not open xsd file",
                                                                                     "simple type already defined",
                                                                                     "complex type already defined",
                                                                                     "attribute group already defined"
                                                                                     /*** ADD CORRESPONDING ENTRY TO pExceptionStringActionArray ***/
                                                                                    };

const char pExceptionStringActionArray[EX_STR_LAST_ENTRY][MAX_EXCEPTION_STRING_LENGTH] = {  /*** ALWAYS AT TO THE END OF THE ARRAY!!! ***/
                                                                                            "Ensure that input xsd files exist and that it's permissions are set properly",
                                                                                            "Multiple xs:simpleType tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing." ,
                                                                                            "Multiple xs:complexType tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing.",
                                                                                            "Multiple xs:attributeGroup tags with the same name defined in xsd files. Try processing xsd files using -use parameter and only specify 1 xsd file for processing."
                                                                                            /*** ADD CORRESPONDING ENTRY TO pExceptionStringActionArray ***/
                                                                                        };

IException *MakeExceptionFromMap(int code, enum eExceptionCodes);
IException *MakeExceptionFromMap(enum eExceptionCodes);

#endif // _EXCEPTION_STRINGS_HPP_
