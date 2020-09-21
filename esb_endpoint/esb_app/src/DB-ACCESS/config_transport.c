#include "db_connection.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include <stdbool.h>
    
#define CHECK_ID "select config_key,config_value from transport_config where route_id=?"  
#define STRING_SIZE 200



tp_data* get_tp_data(int route_id)
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
 MYSQL_BIND    bind[1];
 MYSQL_BIND   o_bind[2];
 MYSQL_RES     *prepare_meta_result;
 int            res;
 char          key_dat[STRING_SIZE];
 char          val_dat[STRING_SIZE];
 char          destination_data[STRING_SIZE];
 unsigned long str_length[5];
 unsigned long length[5];
 int           route_id_value;
 int           param_count;
 bool          is_null[5];
 
 stmt = mysql_stmt_init(con);
 if (!stmt)
 {
  fprintf(stderr, " mysql_stmt_init(), memory leaked\n");
  exit(0);
 }
  /* Prepare a SELECT query to fetch data from table */
 if (mysql_stmt_prepare(stmt, CHECK_ID, strlen(CHECK_ID)))
 {
  fprintf(stderr, " mysql_stmt_prepare(), select statement  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }


 /* Get the parameter count from the statement */
 param_count= mysql_stmt_param_count(stmt);


 if (param_count != 1) /* validate parameter count */
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

 /*  route_id INT */
 bind[0].buffer_type= MYSQL_TYPE_LONG;
 bind[0].buffer= &route_id_value;
 bind[0].is_null= 0;
 bind[0].length= 0;



 /* Bind the buffers */
 if (mysql_stmt_bind_param(stmt, bind))
 {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

  route_id_value = route_id;
 
 
 if (mysql_stmt_execute(stmt))
 {
  fprintf(stderr, " mysql_stmt_execute,  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Bind the result buffers */
 memset(o_bind, 0, sizeof(o_bind));
 
 /*id*/
 o_bind[0].buffer_type= MYSQL_TYPE_STRING;
 o_bind[0].buffer= (char *)&key_dat;
 o_bind[0].is_null= 0;
 o_bind[0].buffer_length= STRING_SIZE;
 o_bind[0].length= &str_length[0];

 o_bind[1].buffer_type= MYSQL_TYPE_STRING;
 o_bind[1].buffer= (char *)&val_dat;
 o_bind[1].is_null=0;
 o_bind[1].buffer_length= STRING_SIZE;
 o_bind[1].length= &str_length[1];

 /* Bind the result buffers */
 if (mysql_stmt_bind_result(stmt, o_bind))
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

 tp_data* node = (tp_data*)malloc(sizeof(tp_data));
 if(!mysql_stmt_fetch(stmt))
 {
    node->config_k = strdup(key_dat);
    node->config_v = strdup(val_dat);
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
/*
int main()
{
    tp_data* n = (tp_data*)malloc(sizeof(tp_data));
    n = get_tp_data(10);
    printf("%s\n",n->config_k);
    printf("%s\n",n->config_v);
}*/
