#ifndef _DOJOJSMARKUP_HPP_
#define _DOJOJSMARKUP_HPP_

#include "jstring.hpp"
#include "jutil.hpp"
#include "jdebug.hpp"

static const char* DJ_START_TEST("define([\n\
                                 \"dojo/_base/declare\",\n\
                                 \"dojo/dom\",\n\
\n\
                                 \"dojox/layout/TableContainer\",\n\
\n\
                                 \"dijit/Tooltip\",\n\
                                 \"dijit/layout/TabContainer\",\n\
                                 \"dijit/layout/ContentPane\",\n\
                                 \"dijit/form/Form\",\n\
                                 \"dijit/form/TextBox\",\n\
                                 \"dijit/layout/_LayoutWidget\",\n\
                                 \"dijit/_TemplatedMixin\",\n\
                                 \"dijit/_WidgetsInTemplateMixin\",\n\
                                 \"dijit/form/Select\",\n\
                                 \"dijit/registry\",\n\
\n\
\n\
                                 \"dojo/text!../templates/GlebWidget3.html\"\n\
\n\
                             ], function (declare, dom,\n\
                                     TableContainer,\n\
                                 Tooltip, TabContainer, ContentPane, Form, TextBox,\n\
                                 _LayoutWidget, _TemplatedMixin, _WidgetsInTemplateMixin, Select, registry,\n\
                                     template) {\n\
\n\
                                 return declare(\"GlebWidget4\", [_LayoutWidget, _TemplatedMixin, _WidgetsInTemplateMixin], {\n\
                                     templateString: template,\n\
                                     baseClass: \"GlebWidget4\",\n\
                                 name: \"GlebWidget4\",\n\
\n\
\n\
                                     postCreate: function (args) {\n\
                                         this.inherited(arguments);\n\
                                     },\n\
\n\
                                     resize: function (args) {\n\
                                         this.inherited(arguments);\n\
                                     },\n\
\n\
                                     layout: function (args) {\n\
                                         this.inherited(arguments);\n\
                                     },\n\
\n\
                                     //  Implementation  ---\n\
                                     _initControls: function () {\n\
                                         var context = this;\n\
                                         this.targetSelectControl = registry.byId(this.id + \"TargetSelect\");\n\
                                     top.mystuff = this;\n\
                                     top.mystuff2 = registry.byId(\"tc1\");\n\
                                     top.registry = registry;\n\
                                     top.form = Form;\n\
\n\
");

static const char* DJ_FINISH_TEST("\n},\n        init: function (params) {\n\
                                         if (this.initalized)\n\
                                             return;\n\
                                         this.initalized = true;\n\
\n\
                                     this._initControls();\n\
                                     }\n\
                                 });\n\
                             });");




static const char* DJ_TAB_PART_1("\nvar cp = new ContentPane({\n\
title: \"");

static const char* DJ_TAB_PART_2("\",\n\
style: \"height: 50%; width: 90%x;\",\n \
cssText: \"width: 50%; height: 70%; showLabels: true; colspan: 1\",\n\
doLayout: \"true\",\n\
id: \"");


//static const char* DJ_TAB_PART_3("\", }).placeAt(\"stubTabContainer\");\n");
static const char* DJ_TAB_PART_3("\", });\n");



static const char* DJ_TABLE_PART_1("\nvar tc = new dojox.layout.TableContainer(\n\
{ cols: 2,\n\
\"labelWidth\" : \"50\" });");

static const char* DJ_TABLE_PART_2("if (tc != null) {cp.placeAt(\"stubTabContainer\");\ncp.addChild(tc);}\n else cp = null;\nvar tc = null; \n");

static const char* DJ_TABLE_ROW_PART_1("\nvar txt = new dijit.form.TextBox({label: \"");
static const char* DJ_TABLE_ROW_PART_PLACE_HOLDER("\", placeHolder: \"");
static const char* DJ_TABLE_ROW_PART_ID_BEGIN("\", id: \"");
static const char* DJ_TABLE_ROW_PART_ID_END("\"});\n");
static const char* DJ_TABLE_ROW_PART_2("\"});\n\
tc.addChild(txt);");

static const char* DJ_ADD_CHILD("\ntc.addChild(txt);");

static const char* DJ_TOOL_TIP_BEGIN("\nvar mytip = new dijit.Tooltip({");
static const char* DJ_TOOL_TIP_CONNECT_ID_BEGIN(" connectId: [\"");
static const char* DJ_TOOL_TIP_CONNECT_ID_END("\"], ");
static const char* DJ_TOOL_TIP_LABEL_BEGIN("label: \"");
static const char* DJ_TOOL_TIP_LABEL_END("\"");
static const char* DJ_TOOL_TIP_END("});");

static unsigned getRandomID()
{
    Owned<IRandomNumberGenerator> random = createRandomNumberGenerator();
    random->seed(get_cycles_now());

    return (random->next() % 1000000000);
}

static void genTabDojoJS(StringBuffer &strJS, const char *pName)
{
    assert(pName != NULL);

    if (pName == NULL)
    {
        return;
    }


    StringBuffer id;

    id.appendf("X%d",getRandomID());

    strJS.append(DJ_TAB_PART_1).append(pName).append(DJ_TAB_PART_2).append(id.str()).append(DJ_TAB_PART_3);
}

static void genTableRow(StringBuffer &strJS, const char* pName)
{

}




#endif // _DOJOJSMARKUP_HPP_
