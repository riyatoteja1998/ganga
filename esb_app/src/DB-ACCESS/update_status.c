#include"db_connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>


#define STRING_SIZE 500

#define UPDATE "update esb_request SET status  = ? where id = ?"
void update_status(char **str,int ID)
{                              
MYSQL_STMT    *stmt;
MYSQL_BIND    bind[2];
uint64_t      affected_rows;
int           param_count;
short         id;
int           int_data;
char          status_data[STRING_SIZE];
unsigned long str_length;
bool          is_null;

 MYSQL *con;
    con = mysql_init(NULL);
    if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
    {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
    }
    printf("Connection Successful!\n\n");



stmt = mysql_stmt_init(con);
if (!stmt)
{
  fprintf(stderr, " mysql_stmt_init(), MEMORY LEAK\n");
  exit(0);
}
if (mysql_stmt_prepare(stmt, UPDATE, strlen(UPDATE)))
{
  fprintf(stderr, " mysql_stmt_prepare(), update failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, updated query successful\n");

/* Fetch the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in update: %d\n", param_count);

if (param_count != 2) /* validate parameter count */
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
}

/* Bind the parameters */

memset(bind, 0, sizeof(bind));




/* STRING PARAMETERS */
bind[0].buffer_type= MYSQL_TYPE_STRING;
bind[0].buffer= (char *)status_data;
bind[0].buffer_length= STRING_SIZE;
bind[0].is_null= 0;
bind[0].length= &str_length;

/* id INT PARAM */
bind[1].buffer_type= MYSQL_TYPE_SHORT;
bind[1].buffer= (char *)&id;
bind[1].is_null= 0;
bind[1].length= 0;

/* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind))
{
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

 id = ID;
strncpy(status_data, *str, STRING_SIZE); /* string  */
str_length= strlen(status_data);



/* Process the update statement 1*/
if (mysql_stmt_execute(stmt))
{
  fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* Get the number of affected rows */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows(UPDATE 2): %lu\n",
                (unsigned long) affected_rows);

if (affected_rows != 1) /* validate affected rows */
{
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}

/* Close the statement */
if (mysql_stmt_close(stmt))
{
  /* mysql_stmt_close() invalidates stmt, so call          */
  /* mysql_error(mysql) rather than mysql_stmt_error(stmt) */
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_error(con));
  exit(0);
}
  mysql_close(con);
}
/*
 int main()
 {
      char *status;
      status = "processing";
      update_status(&status,1); 
 }
*/










