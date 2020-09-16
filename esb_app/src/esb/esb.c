//#include "email.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
//#include "../BMD/xml_header.h"
#include <libxml/parser.h>
#include "xml_header.h"
//#include "esb.h"


int queue_the_request(bmd *b,char *file)
{
    int success = 1; // 1 => OK, -1 => Error cases
    int failure=-1;
    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */
     int var = insert_esbrequest(b->envelop_value->Sender,b->envelop_value->Destination,b->envelop_value->MessageType,b->envelop_value->ReferenceID,b->envelop_value->MessageID,file,"file_received","1");
     if(var){
    return success;
    }
    return failure; 
    
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* file) {
    int status = 1; // 1 => OK, -ve => Errors
  //  printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd *b = bmd_main_parse(file);

    // Step 2:
    if (request_validation(b)==0)
    {
        //TODO: Process the error case
        
        printf("BMD is invalid!\n");
        status = -2;
        return -1;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b,file);
    }
    
    return status;
}

int main()
{
     char  file[100];
    scanf("%s",file);
    printf("%d",process_esb_request(file));
    return 0;
}

