#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>
#include <stdbool.h>

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void status(char *status){

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



char query[500];

/*Send data*/
sprintf(query,"select * from esb_request where status= %s",status);
 

  /*checks if statements executes properly*/
  if (mysql_query(con, query)) {
      finish_with_error(con);
  }

  MYSQL_RES *result;

  /*stores the result */
  result = mysql_store_result(con); 
  
  /* report error if result is NULL*/
  if (result == NULL) {
      finish_with_error(con);
  }

  /* shows number of fields*/ 
  int num_fields = mysql_num_fields(result);

  
  MYSQL_ROW row;

  /*it holds field value*/
  MYSQL_FIELD *field;
      
      while(field = mysql_fetch_field(result)) {
       printf(" %s ||",field->name);
    } 
      printf("\n");
    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
            printf(" || ");        }
        printf("\n");
    }

 
  mysql_free_result(result);
  /*it closes the db connection*/
  mysql_close(con);  
}
/*
int main() {

   
   char* get_status="1";
   status(get_status);
   return 0;
}   
*/
