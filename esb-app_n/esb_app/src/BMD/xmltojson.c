#include<stdio.h>
#include<stdlib.h>
#include "xml_header.h"
#include<string.h>
#include<errno.h>
/*
char * xmltojson(bmd *b)
{
     char doc[1000];
     sprintf(doc,"Payload_%s.json",b->envelop_value->MessageID);
     FILE *file;
     char* data = b->payload;
     //printf("%s",data);
     file = fopen(doc,"w");
 
    if(file == NULL)
    {
      	printf("Writing Failed");
        exit(0);
    }

    fprintf(file,"{\n \"Payload\":\"%s\"\n}",data);
   
    fclose(file);
    //printf("%s",doc);
    printf("\nJson File Created Successfully\n");
    
    return strdup(doc);
}
*/