#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
char res[10][500];
int k=0;

struct data {
    char messageid[50];
    char msgtype[50];
    char sender[50];
    char destination[50];
    char createdate[50];
    char signature[50];
    char ref_id[50];
    };

void parse (xmlDocPtr doc, xmlNodePtr cur) {

	xmlChar *key;
	xmlNodePtr curr;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"MessageID"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("MessageID : %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"MessageType"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("MessageType: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	     if ((!xmlStrcmp(cur->name, (const xmlChar *)"Sender"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("Sender: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	     if ((!xmlStrcmp(cur->name, (const xmlChar *)"Destination"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("Destination: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	     if ((!xmlStrcmp(cur->name, (const xmlChar *)"CreationDateTime"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("CreationDateTime: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	     if ((!xmlStrcmp(cur->name, (const xmlChar *)"Signature"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("Signature: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	    if ((!xmlStrcmp(cur->name, (const xmlChar *)"ReferenceID"))) {
		    key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("Signature: %s\n", key);
		    strncpy(res[k++],key,100);
		    xmlFree(key);
 	    }
 	     if ((!xmlStrcmp(cur->name, (const xmlChar *)"UserProperties"))) {
	           for (curr = cur->children; curr != NULL; curr = curr->next)
	           {
	              if (curr->type != XML_ELEMENT_NODE)
                          continue;
                     key = xmlNodeGetContent(curr);
                     strncpy(res[k++], key, 100);
                     printf("Content : %s\n", key);
                          k++;
                    // printf("value of k is %d\n",k);
                               xmlFree(key);
		   // key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    //printf("MessageID : %s\n", key);
		    //strncpy(res[k++],key,100);
		    //xmlFree(key);
 	    }


	}

	cur = cur->next;
	}

}

static struct data *parseDoc(char *docname) {

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);

	if (doc == NULL ) {
		fprintf(stderr,"Document is not parsed successfully. \n");
		//return;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr,"document is empty\n");
		xmlFreeDoc(doc);
		//return;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "BMD")) {
		fprintf(stderr,"document of the wrong type, main root != BMD");
		xmlFreeDoc(doc);
		//return;
	}

	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"Envelop"))){
			parse (doc, cur);
		}

	cur = cur->next;
	}

	xmlFreeDoc(doc);
	struct data *p2;
	 p2 = malloc(sizeof(struct data));
	 strcpy(p2->messageid, res[0]);
	 strcpy(p2->msgtype, res[1]);
	 strcpy(p2->sender, res[2]);
	 strcpy(p2->destination, res[3]);
	 strcpy(p2->createdate, res[4]);
	 strcpy(p2->signature, res[5]);
	 strcpy(p2->ref_id, res[6]);


    return p2;

}

int main(int argc, char **argv) {

	char *docname;


	struct data* temp = parseDoc ("/home/harshal/Desktop/bmd.xml");
	int x;
	for(x=0;x<k;x++)
	{
	  printf("%s\n",res[x]);
	}
	//printf("%d\n",k);
	printf("%s\n",temp->messageid);
	printf("%s\n",temp->msgtype);
        printf("%s\n",temp->sender);
	return (1);
}
