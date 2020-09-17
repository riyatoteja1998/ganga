#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>


void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

void status(char *status){

static char *host = "localhost";
static char *user = "root";
static char *pass = "password";
static char *dbname ="esb_db";

unsigned int port =3306;
static char *unix_socket = NULL;
unsigned flag=0;

   MYSQL *con;
    con = mysql_init(NULL);
    if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
    {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
    }
    printf("Connection Successful!\n\n");

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