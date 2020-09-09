#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include "xml_header.h"
#include <libxml/parser.h>
//Converts .xml file to .json file 
char * xmltojson(bmd *b)
{
     char doc[1000];
     sprintf(doc,"%s-Payload.json","data");
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
//check whether payload size is acceptable or not
int check_payload(bmd *b)
{
    
    char *load = xmltojson(b);
    FILE* fp = fopen(load, "r"); 
  
   
    if (fp == NULL) { 
        printf("Reading Failed!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
   
    long int len = ftell(fp); 
  
    fclose(fp); 
    
    if(len > 500000)
    return 0;
    return 1;
}
// check all possile validation request
int request_validation(bmd * b)
{
   if(is_bmd_valid(b)==0)
   {
      printf("\nValidation Failed\n");
      return 0;
   }
   int r_id = select_active_routes(b->envelop_value->MessageType,b->envelop_value->Sender,b->envelop_value->Destination);
   if(r_id && check_transport(r_id) && check_transform(r_id) && check_payload(b)) 
   {
      return 1;
   }
   return 0;
   
}
int main()
{  
    char  file[100];
    scanf("%s",file);
    bmd * b = (bmd*) malloc (sizeof(bmd));
    b->envelop_value=  extract_envelop(file);
    b->payload= extract_payload(file);
    printf("%d",request_validation(b));
    return 0;
}
