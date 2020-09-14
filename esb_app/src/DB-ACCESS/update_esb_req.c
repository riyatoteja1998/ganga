/*
 Including necessery header files 
*/
#include <stdio.h>
#include <string.h>
#include <mysql.h>

/*adding db_connector external header file where the user,password,port and socket stored*/

#include "db_connector.h"
#define STRING_SIZE 100

//error will be printed with the mysql_con
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);
  exit(1);        
}

/* Updateing the esb_request */
#define UPDATE_QUERY "UPDATE esb_request SET status = ? WHERE id = ? "
int update_esb_request(char *status, int id)
{
  printf("Updating esb_request status...\n")
  MYSQL_STMT *stmt;
  MYSQL_BIND bind[2];
  my_ulonglong affected_rows;
  int param_count;
  int id_data;
  char status_data[STRING_SIZE];
  unsigned long str_length;
  bool is_null;

/* database connection handle */
  MYSQL *con;

/* mysql Connection initialization */
  con = mysql_init(NULL);

  if (con == NULL)
  {

    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

/* checks the connectivity with these parameters
con,host,user_name,password,port,unix_socket,flag
 */
  if (mysql_real_connect(con,host,user,pass,
                         db_name,port,unix_socket,flag) == NULL)
  {
    finish_with_error(con);
  }
  /* Prepare an UPDATE query with 3 parameters */
  stmt = mysql_stmt_init(con);
  if (!stmt)
  {
    fprintf(stderr, " mysql_stmt_init(), out of memory\n");
    exit(0);
  }

  if (mysql_stmt_prepare(stmt, UPDATE_QUERY, strlen(UPDATE_QUERY)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), UPDATE failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }
  //fprintf(stdout, "Successful\n");

  /* Get the parameter count from the statement */
  param_count = mysql_stmt_param_count(stmt);
  //fprintf(stdout, " total parameters in UPDATE: %d\n", param_count);


  if (param_count != 2)
  {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    exit(0);
  }

  /* Bind the data for 2 parameters */
  memset(bind, 0, sizeof(bind));

  /* STRING PARAMETER */
  bind[0].buffer_type = MYSQL_TYPE_STRING;
  bind[0].buffer = (char *)&status_data;
  bind[0].is_null = 0;
  bind[0].length = &str_length;
  bind[0].buffer_length = STRING_SIZE;

  /* INTEGER id PARAMETER */
  bind[1].buffer_type = MYSQL_TYPE_LONG;
  bind[1].buffer = (char *)&id_data;
  bind[1].is_null = 0;
  bind[1].length = 0;

  /* Bind the buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }

  id_data = id;
  strncpy(status_data, status, STRING_SIZE);
  str_length = strlen(status_data);

  /* Execute the UPDATE statement*/
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute, failed\n");
    fprintf(stderr, " [%d]%s\n", mysql_stmt_errno(stmt),
            mysql_stmt_error(stmt));
    exit(0);
  }

  /* 
  Get the total rows affected 
  affected_rows = mysql_stmt_affected_rows(stmt);
  fprintf(stdout, " total affected rows(UPDATE 2): %lu\n",
  (unsigned long)affected_rows);
   */


  /*if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
   }*/

  /* Close the statement */
  if (mysql_stmt_close(stmt))
  {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
  }
  mysql_close(con);
  return 1;
}

/*int main() {
  char *s;
  s = "done";
 update_esb_request(&s,1);
 return 0;
}*/
