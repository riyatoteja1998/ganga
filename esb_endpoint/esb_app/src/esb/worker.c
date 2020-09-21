#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "../DB-ACCESS/db_connection.h"

#include<mysql/mysql.h>
#include "../BMD/xml_header.h"
#include "../endpoint/transform.h"
#include <pthread.h>


void *poll_database_for_new_requests(void *vargp)
{


    // Step 1: Open a DB connection
    int i = 0;
    while (i < 1)
    {
        i++;
       
       task_list* req = fetch_data1();
         if(req==NULL)
        {
            printf("no req");
        }
 
       
             if (req!=NULL)
        {
        
       
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
              char *data =get_payload(url);
              //printf("\n%s\n\n",data);
              //if(transform_key=="http")
            // {  "name=riyaa&job=T"
                char* httpres;
                httpres = (char*)http_request(url);
                  //http_request("https://ifsc.razorpay.com/HDFC0CAGSBK");
                  //puts(httpres);
                  if(httpres==NULL)
                  {
                      printf("Connection Failed");
                      update_status("received",req->id);
                  }
                  else
                  {
                       printf("http post successfull");
                       /*if(file_exist(httpres)==0)
                       {
                           printf("reponse not recieved\n");

                       }
                       else
                       {
                           update_status("done",req->id);
                       }
                       */
                  }

                  int x = 1;//sendemail("riyatoteja1998@gmail.com",data);
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
