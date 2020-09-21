#include "db_connection.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include <stdbool.h>
    
#define SELECT_ID "select route_id from routes where message_type = ? and sender = ? and destination = ?  and is_active=1"  
#define STRING_SIZE 200



int select_active_routes(char *message_type,char *sender,char *destination)
{   
  MYSQL *con;
  char *server = "localhost";
  char *user = "root";
  char *password = "riya"; /* set me first */
  char *database = "esb_db";
	
  con = mysql_init(NULL);
	
  /* Connect to database */
  if (!mysql_real_connect(con, server, user, password, database, 0, NULL, 0)) {
	fprintf(stderr, "%s\n", mysql_error(con));
	return 0;
  }

    
 MYSQL_STMT    *stmt;
 MYSQL_BIND    bind[3];
 MYSQL_BIND   out_bind[1];
 MYSQL_RES     *prepare_meta_result;
 char          message_data[STRING_SIZE];
 char          sender_data[STRING_SIZE];
 char          destination_data[STRING_SIZE];
 unsigned long str_length[3];
 unsigned long length[1];
 int           id;
 int           param_count;
 bool          is_null[3];
 
 stmt = mysql_stmt_init(con);
 if (!stmt)
 {
  fprintf(stderr, " mysql_stmt_init(), memory leaked\n");
  exit(0);
 }
  /* Prepare a SELECT query to fetch data from table */
 if (mysql_stmt_prepare(stmt, SELECT_ID, strlen(SELECT_ID)))
 {
  fprintf(stderr, " mysql_stmt_prepare(), select statement  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }


 /* Get the parameter count from the statement */
 param_count= mysql_stmt_param_count(stmt);


 if (param_count != 3) /* validate parameter count */
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


 memset(bind, 0, sizeof(bind));

 /*  Message_type STRING */
 bind[0].buffer_type= MYSQL_TYPE_STRING;
 bind[0].buffer= (char *)&message_data;
 bind[0].buffer_length= STRING_SIZE;
 bind[0].is_null= 0;
 bind[0].length= &str_length[0];

 /* sender STRING */
 bind[1].buffer_type= MYSQL_TYPE_STRING;
 bind[1].buffer= (char *)&sender_data;       
 bind[1].is_null= 0;
 bind[1].length= &str_length[1];
 bind[1].buffer_length= STRING_SIZE;
 
 /* destination */
 bind[2].buffer_type= MYSQL_TYPE_STRING;
 bind[2].buffer= (char *)&destination_data;       
 bind[2].is_null= 0;
 bind[2].length= &str_length[2];
 bind[2].buffer_length= STRING_SIZE;



 /* Bind the buffers */
 if (mysql_stmt_bind_param(stmt, bind))
 {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 strncpy(message_data, message_type, STRING_SIZE);
 strncpy(sender_data, sender, STRING_SIZE);
 strncpy(destination_data, destination, STRING_SIZE);
 str_length[0]= strlen(message_data);
 str_length[1]=strlen(sender_data);
 str_length[2]=strlen(destination_data);
 
 
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
 out_bind[0].buffer= &id;
 out_bind[0].is_null= 0;
 out_bind[0].buffer_length= 200;

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

 if(!mysql_stmt_fetch(stmt))
 {
    return id;
 }
 else
 {
  printf("no route found");
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
 
 return 0; 
}

/*int main()
{
   char *sender = "a";
   char *message_type = "sample";
   printf("%d",select_active_routes(message_type,sender,"z"));
   return 0;
}*/
