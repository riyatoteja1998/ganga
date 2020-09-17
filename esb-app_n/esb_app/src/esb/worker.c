#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
//#include "esb.h"
#include "../DB-ACCESS/db_connection.h"

#include<mysql/mysql.h>
#include "../BMD/xml_header.h"
//#include "db_connection.h"
#include "../endpoint/transform.h"
#include <pthread.h>
//int fetch_new_request_from_db(task_list *request)
//{
  //  /** 
    // * TODO: query the DB for this, and populate the 
     //* request pointer with the requests.
   //  */
   // if(request!=NULL)
    //return 0;
    //printf("Checking for new requests in esb_requests table.\n");
   // return 1; // 1 => OK, -1 => Errors
//}
//void *poll_database_for_new_requets(void *vargp);
/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{
    // Step 1: Open a DB connection
    int i = 0;
    while (i < 1)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
       task_list* req = fetch_data1();
         if(req==NULL)
        {
            printf("no req");
        }
 
        /**
         * Step 3:
         */
        
            /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
             if (req!=NULL)
        {
        
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
          int route_id = select_active_routes(req->MessageType,req->Sender,req->Destination);
              bmd* b = bmd_main_parse(req->data_location);
              //printf("%s",b->payload);
              tp_data* n1 = get_tp_data(route_id);
              //tf_data* n2 = get_tf_data(route_id);
              char* transport_key = strdup(n1->config_k);
              char *transport_value = strdup(n1->config_v);
              printf("%s\n",n1->config_k);
              printf("%s\n",n1->config_v);
              free(n1);
             // printf("%s\n",n2->config_key);
             // printf("%s\n",n2->config_value);
             tf_data* n2 = get_tf_data(route_id);
             char* transform_key = strdup(n2->config_key);
             char *transform_value = strdup(n2->config_value);
              printf("%s",transform_key);
              printf("%s\n",transform_value);
              free(n2);
              char url[200];
              strcat(transport_key,transport_value);
              strcat(url,transport_key);
              puts(url);
              char *data = get_payload(url);
              //if(transform_key=="http")
            // {
                  char* httpres;
                  httpres = (char*)post_http(url,"name=harsh&job=T");
                  puts(httpres);
                  if(httpres==NULL)
                  {
                      printf("Connection Failed");
                      update_status("received",req->id);
                  }
                  else
                  {
                       printf("http post successfull");
                       if(file_exist(httpres)==0)
                       {
                           printf("reponse not recieved\n");

                       }
                       else
                       {
                           update_status("done",req->id);
                       }
                       
                  }

                  int x = sendemail("testgangahv@gmail.com",data);
                  if(x==1)
                  {
                      printf("mail sent successfully");
                  }

             //}

            printf("Applying transformation and transporting steps.\n");
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
        }
    }
}
