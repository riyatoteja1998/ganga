#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include<mysql/mysql.h>

#include "db_connection.h"


#define STRING_SIZE 200
#define SELECT_QUERY "SELECT id,sender_id, dest_id, message_type,   \
                       data_location FROM esb_request               \
                       WHERE status = 'received' "


task_list *fetch_data1()
{
       MYSQL *con;
   con = mysql_init(NULL);
   if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
   {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
   }
   printf("Connection Successful!\n\n");
    
  
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    MYSQL_RES *prepare_meta_result;
    unsigned long length[5];
    int param_count, column_count, row_count;
    int id_data; /* For id */
    //char str_data[4][STRING_SIZE];
    char sender_id[STRING_SIZE];
    char dest_id[STRING_SIZE];
    char message_type[STRING_SIZE];
    char data_location[STRING_SIZE];
    bool is_null[5];
    bool error[5];

    /* Prepare a SELECT query to fetch data from esb_request */
    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(0);
    }
    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    //fprintf(stdout, " prepare, SELECT successful\n");

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);
    //fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

    if (param_count != 0) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }

    /* Execute the SELECT query */
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        fprintf(stderr,
                " mysql_stmt_result_metadata(), \
           returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Get total columns in the query */
    column_count = mysql_num_fields(prepare_meta_result);
    /*fprintf(stdout,
            " total columns in SELECT statement: %d\n",
            column_count);*/

    if (column_count != 5) /* validate column count */
    {
        fprintf(stderr, " invalid column count returned by MySQL\n");
        exit(0);
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /* ROUTE ID COLUMN */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char *)&id_data;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];
    bind[0].error = &error[0];

    /* Sender_id */
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)sender_id;
    bind[1].buffer_length = STRING_SIZE;
    bind[1].is_null = &is_null[1];
    bind[1].length = &length[1];
    bind[1].error = &error[1];

    /* dest_id */
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)dest_id;
    bind[2].buffer_length = STRING_SIZE;
    bind[2].is_null = &is_null[2];
    bind[2].length = &length[2];
    bind[2].error = &error[2];

    /* message_type */
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)message_type;
    bind[3].buffer_length = STRING_SIZE;
    bind[3].is_null = &is_null[3];
    bind[3].length = &length[3];
    bind[3].error = &error[3];

    /* Data Location */
    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)data_location;
    bind[4].buffer_length = STRING_SIZE;
    bind[4].is_null = &is_null[4];
    bind[4].length = &length[4];
    bind[4].error = &error[4];

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Now buffer all results to client (optional step) */
    if (mysql_stmt_store_result(stmt))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    task_list *node = (task_list *)malloc(sizeof(task_list));
    /* Fetch all rows */
    row_count = 0;
   
    while (!mysql_stmt_fetch(stmt))
    {
        row_count++;
        //fprintf(stdout, "  row %d\n", row_count);

        /* Column 1 */
    
        if (is_null[0])
        {
            fprintf(stdout, "Id is NULL (fetching request)\n");
        }
        else
        {
            
            node->id = id_data;
        }

        /* Column 2 */

        if (is_null[1])
        {
            fprintf(stdout, " NULL\n");
        }

        else
        {
            node->Sender = strdup(sender_id);
        }

        /* Column 3 */
       
        if (is_null[1])
        {
            fprintf(stdout, " NULL\n");
        }

        else
        {

            node->Destination = strdup(dest_id);
        }

        /* Column 4 */
    
        if (is_null[1])
        {
            fprintf(stdout, " NULL\n");
        }

        else
        {
            
            node->MessageType = strdup(message_type);
        }

        
        if (is_null[1])
        {
            fprintf(stdout, " NULL\n");
        }

        else
        {
        
            node->data_location = strdup(data_location);
        }

        return node;
    }

    /* Validate rows fetched */
    fprintf(stdout, " total rows fetched: %d\n", row_count);
    /*if (row_count= 2)
    {
        fprintf(stderr, " MySQL failed to return all rows\n");
        exit(0);
    }*/

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        /* mysql_stmt_close() invalidates stmt, so call          */
        /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_error(con));
        exit(0);
    }

    /*closes the database connection*/
    mysql_close(con);
    /* returns number of rows in result */
    return NULL;
}

/*int main()
{
  task_list* n = (task_list*)malloc(sizeof(task_list));
  n = fetch_data1();
  printf("%s",n->MessageType);
}*/