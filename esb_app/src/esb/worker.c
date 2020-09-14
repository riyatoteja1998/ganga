#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "../DB-ACCESS/db_connection.h"

int fetch_new_request_from_db(task_list *request)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
    if(request!=NULL)
    return 0;
    //printf("Checking for new requests in esb_requests table.\n");
    return 1; // 1 => OK, -1 => Errors
}

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{
    // Step 1: Open a DB connection
    int i = 0;
    while (i < 99)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
          task_list* req = (task_list*)malloc(sizeof(task_list));
          req = fetch_data();
        /**
         * Step 3:
         */
        if (fetch_new_request_from_db(&req))
        {
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
              update_status(req->id,"processing");
              tp_data* n1 = (tp_data*)malloc(sizeof(tp_data));
              tf_data* n2 = (tf_data*)malloc(sizeof(tf_data));
              n1 = config_transport(req->id);
              n2 = config_transform(req->id);
              

              

            printf("Applying transformation and transporting steps.\n");
        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
}
