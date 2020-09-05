#include "xml_header.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <libxml/parser.h>
 
int is_leaf(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;
    child = child->next;
  }
  return 1;
}


void extract_attribute(xmlNode * node, bmd_envelop * b)
{
    int len;
    while(node!=NULL)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if(is_leaf(node))
            {     
                  /* Extracting MessageID*/
                 len= strlen((char*) xmlNodeGetContent(node));
                
                if((strcmp(((char *) node->name),"MessageID"))==0)
                {
                    b->MessageID = malloc((len+1)* sizeof(char));
                    strcpy(b->MessageID,(char *) xmlNodeGetContent(node));
                   
                }
                /* Extracting MesageType*/
                else if((strcmp(((char *) node->name),"MessageType"))==0)
	              {
	            b->MessageType =  (char *)malloc((len+1)* sizeof(char));
                    strcpy(b->MessageType ,(char *)xmlNodeGetContent(node));
                  
	              }
                /* Extracting Sender*/
                else if(strcmp(((char *) node->name), "Sender")==0)
	              {
		    b->Sender =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->Sender ,(char *)xmlNodeGetContent(node));
                 
	            	 }
                 /* Extracting Destination*/
                else if((strcmp(((char *) node->name),"Destination"))==0)
                {
		    b->Destination =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->Destination ,(char *)xmlNodeGetContent(node));
                 
	              }
                /* Extracting CreationDateTime*/
                else if((strcmp(((char *) node->name),"CreationDateTime"))==0)
	              {
		    b->CreationDateTime =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->CreationDateTime ,(char *)xmlNodeGetContent(node));
                
	               }
                 /* Extracting Signature*/
	              else  if((strcmp(((char *) node->name),"Signature"))==0)
            	  {
         	    b->Signature =  (char *)malloc((len+1)* sizeof(char));
                   strcpy(b->Signature ,(char *)xmlNodeGetContent(node));
                   
                }
                /* Extracting ReferenceID*/
                else if((strcmp(((char *) node->name),"ReferenceID"))==0)
	              {
		    b->ReferenceID =  (char *)malloc((len+1)* sizeof(char));
                    strcpy(b->ReferenceID ,(char *)xmlNodeGetContent(node));
                
                }
            }
        }
        extract_attribute(node->children,b);
        node = node->next;
    }
}


bmd_envelop *extract_envelop(char * filepath)
{
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;

  /*parse the file*/
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("not able to parse the XML file");
  }
  /*Fetch the root element node */
  root = xmlDocGetRootElement(doc);
  bmd_envelop * b =(bmd_envelop *) malloc(sizeof(bmd_envelop));
  extract_attribute(root,b);

   /*free the document */
    xmlFreeDoc(doc);

    xmlCleanupParser();
    return b;
}




char * extract_payload(char * file)
{
    char * payload;
    xmlNode *root = NULL;
    xmlDoc *doc = NULL;

  /*parse the file  */
  doc = xmlReadFile(file, NULL, 0);

  if (doc == NULL) {
    printf("XML file not parsed successfully");
  }
  int len;
  /*Get the root element node */
  root = xmlDocGetRootElement(doc);
  
  xmlNode * node = root->children;
  while(node!=NULL)
  {
    if(node->type==XML_ELEMENT_NODE)
    {
      if(is_leaf(node))
      {
        len = strlen((char*) xmlNodeGetContent(node));
        if((strcmp(((char *) node->name),"Payload"))==0)
	     {
            payload = (char *)malloc((len+1)* sizeof(char));
            strcpy(payload,(char *) xmlNodeGetContent(node));
            if(strcmp(payload, "") ==0){
                payload=NULL;  
            } 
            return payload;
        }
      } 
    }
    node = node->next;
  } 

  /*make document free*/
  xmlFreeDoc(doc);


  xmlCleanupParser();

  return NULL;     
}


int is_bmd_valid(bmd* b)
{
  /* Checking Whether MessageID is NULL */
  if(b->envelop_value->MessageID == NULL) {
    fprintf(stderr,"Message ID Not found in file");
    return 0;
  }

  /* Checking Whether MessageType is Valid */
  if(b->envelop_value->MessageType == NULL) {
    fprintf(stderr,"Message Type not found in file");
    return 0;
  }

  /* Checking Whether Sender is Valid */
  if(b->envelop_value->Sender == NULL) {
    fprintf(stderr,"Sender not found in file");
    return 0;
  }


  /* Checking Whether Destination is Valid */
  if(b->envelop_value->Destination == NULL) {
    fprintf(stderr,"Destination not found in file");
    return 0;
  }


  /* Checking Whether CreationDateTime is Valid */
  if(b->envelop_value->CreationDateTime == NULL) {
    fprintf(stderr,"CreationDateTime not found in file");
    return 0;
  }


  /*Checking Whether Signature is Valid*/
  if(b->envelop_value->Signature == NULL) {
    fprintf(stderr,"Signature not found in bmd");
    return 0;
  }

  /* Checking ReferenceID is Valid */
  if(b->envelop_value->ReferenceID == NULL) {
      fprintf(stderr,"ReferenceID not found in bmd");
      return 0;
  }

  /* Checking payload is Valid */
  if(b->payload == NULL) {
    fprintf(stderr,"Payload not found in bmd");
    return 0;
  }

  return 1;
}



int main()
{
    char  file[100];
    scanf("%s",file);
    bmd * b = (bmd*) malloc (sizeof(bmd));
    bd->envelop_value=  extract_envelop(filepath);
    bd->payload= extract_payload(filepath);
    printf("%d",is_bmd_valid(bd));
    printf("%s",bd->envelop_value->MessageType);
    printf("\n");
    printf("%s",xmltojson(bd->payload));
    return 0;
}

