#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include "xml_header.h"
#include <libxml/parser.h>

bmd *bmd_main_parse(char * file)
{
    bmd * b = (bmd*) malloc (sizeof(bmd));
    b->envelop_value=  extract_envelop(file);
    b->payload= extract_payload(file);
    return b;
}
