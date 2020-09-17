#include "db_connection.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
    
#define SELECT_DATA "select id,sender_id,dest_id,message_type from esb_request where status ='received'"  
#define STRING_SIZE 200



task_list* fetch_data()
{
   MYSQL *con;
   con = mysql_init(NULL);
   if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
   {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
   }
   printf("Connection Successful!\n\n");
    
 MYSQL_STMT    *stmt;
 //MYSQL_BIND    bind[3];
 MYSQL_BIND   out_bind[4];
 MYSQL_RES     *prepare_meta_result;
 int            id_data;
 char          sender_data[STRING_SIZE];
 char          destination_data[STRING_SIZE];
 char          message_type_data[STRING_SIZE];
 unsigned long str_length[3];
 unsigned long length[1];
 int           param_count;
 bool          isnull[4];
 
 stmt = mysql_stmt_init(con);
 if (!stmt)
 {
  fprintf(stderr, " mysql_stmt_init(), memory leaked\n");
  exit(0);
 }
  /* Prepare a SELECT query to fetch data from table */
 if (mysql_stmt_prepare(stmt, SELECT_DATA, strlen(SELECT_DATA)))
 {
  fprintf(stderr, " mysql_stmt_prepare(), select statement  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }


 /* Get the parameter count from the statement */
 param_count= mysql_stmt_param_count(stmt);
 printf("%d",param_count);

 if (param_count != 0) /* validate parameter count */
 {
  fprintf(stderr, " not valid parameter count returned by mysql\n");
  exit(0);
 }


/* Fetch result set meta information */
 prepare_meta_result = mysql_stmt_result_metadata(stmt);
 if (!prepare_meta_result)
 {
  fprintf(stderr," mysql_stmt_result_metadata(), returned no meta DATA\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

if (mysql_stmt_execute(stmt))
 {
  fprintf(stderr, " mysql_stmt_execute,  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }


 /* Bind the result buffers */
 memset(out_bind, 0, sizeof(out_bind));
 
 /*id*/
 out_bind[0].buffer_type= MYSQL_TYPE_LONG;
 out_bind[0].buffer= &id_data;
 out_bind[0].is_null= 0;
 out_bind[0].buffer_length= 200;
 
 out_bind[1].buffer_type= MYSQL_TYPE_STRING;
 out_bind[1].buffer= (char *)&sender_data;
 out_bind[1].is_null= 0;
 out_bind[1].buffer_length= STRING_SIZE;
 out_bind[1].length= &str_length[0];

 out_bind[2].buffer_type= MYSQL_TYPE_STRING;
 out_bind[2].buffer= (char *)&destination_data;
 out_bind[2].is_null=0;
 out_bind[2].buffer_length= STRING_SIZE;
 out_bind[2].length= &str_length[1];

 out_bind[3].buffer_type= MYSQL_TYPE_STRING;
 out_bind[3].buffer= (char *)&message_type_data;
 out_bind[3].is_null= 0;
 out_bind[3].buffer_length= STRING_SIZE;
 out_bind[3].length= &str_length[2];

 /* Bind the result buffers */
 if (mysql_stmt_bind_result(stmt, out_bind))
 {
  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Now buffer all results to client */
 if (mysql_stmt_store_result(stmt))
 {
  fprintf(stderr, " mysql_stmt_store_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }
 
 task_list* node = (task_list*)malloc(sizeof(task_list));
 if(!mysql_stmt_fetch(stmt))
 {
    node->id = id_data;
    node->Sender = sender_data;
    node->Destination = destination_data;
    node->MessageType = message_type_data;
     mysql_free_result(prepare_meta_result);

 /* Close the statement */
 if (mysql_stmt_close(stmt))
 {
  fprintf(stderr, " error while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }
 
 mysql_close(con); 
 return node;
 }
 else
 {
  printf("no data found");
 }
 /* Free the result metadata */
 mysql_free_result(prepare_meta_result);

 /* Close the statement */
 if (mysql_stmt_close(stmt))
 {
  fprintf(stderr, " error while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }
 
 mysql_close(con);  
  return NULL;
}

/*int main()
{
    task_list* n = (task_list*)malloc(sizeof(task_list));
    n = fetch_data();
    //printf("%d\n",n->id);
    //printf("%s\n",n->Sender);

}*/

