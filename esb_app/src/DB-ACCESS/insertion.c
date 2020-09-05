#include "db_connection.h"
#include <stdio.h>
#include <string.h>
#include<mysql/mysql.h>

#define INSERT "insert into esb_request(sender_id,dest_id,message_type,reference_id,      message_id,data_location,received_on,status,status_details) values(?,?,?,?,?,?,CURRENT_TIMESTAMP,?,?)" 

 #define STRING_SIZE 500
int insert_esbrequest(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details) 
{

MYSQL_STMT    *stmt;
my_ulonglong  affected_rows;
MYSQL_BIND    bind[8];
int           id;
int           param_count; 
char          message_type_value[STRING_SIZE];
char          sender_id_value[STRING_SIZE];
char          dest_id_value[STRING_SIZE];
char          reference_id_value[STRING_SIZE];
char          message_id_value[STRING_SIZE];
char          data_location_value[STRING_SIZE];
char          status_value[STRING_SIZE];
char          status_details_value[STRING_SIZE];
unsigned long str_length[8];
bool          is_null;

    MYSQL *con;
    con = mysql_init(NULL);
    if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
    {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
    }
    printf("Connection Successful!\n\n");
/*Processing an INSERT query with 8 parameters */
stmt = mysql_stmt_init(con);
if (!stmt) {
  fprintf(stderr, " mysql_stmt_init(), memory leak\n");
  exit(0);
}


if (mysql_stmt_prepare(stmt, INSERT, strlen(INSERT))) {
  fprintf(stderr, " mysql_stmt_prepare(), INSERT function failed to execute\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}

/* get all the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
/*fprintf(stdout, " Total Parameters in INSERT are: %d\n", param_count);*/

/* check parameter count */
if (param_count != 8) {
  fprintf(stderr, "  parameter count is not valid returned by mysql\n");
  exit(0);
}

/* Bind all the data for all 8 parameters */
memset(bind, 0, sizeof(bind));

/* Sender_ID */
bind[0].buffer_type= MYSQL_TYPE_STRING;
bind[0].buffer= (char *)&sender_id_value;
bind[0].is_null= 0;
bind[0].length= &str_length[0];
bind[0].buffer_length= STRING_SIZE;


/* destination_id */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)dest_id_value;
bind[1].buffer_length= STRING_SIZE;
bind[1].is_null= 0;
bind[1].length= &str_length[1];

/* Message_type */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)&message_type_value;
bind[2].is_null= 0;
bind[2].buffer_length= STRING_SIZE;
bind[2].length= &str_length[2];

/* Reference_id */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&reference_id_value;
bind[3].is_null= 0;
bind[3].buffer_length= STRING_SIZE;
bind[3].length= &str_length[3];

/* Message_ID  */
bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)&message_id_value;
bind[4].is_null= 0;
bind[4].buffer_length= STRING_SIZE;
bind[4].length= &str_length[4];

/*Data_location*/
bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)&data_location_value;
bind[5].is_null= 0;
bind[5].buffer_length= STRING_SIZE;
bind[5].length= &str_length[5];

/*Status*/
bind[6].buffer_type= MYSQL_TYPE_STRING;
bind[6].buffer= (char *)&status_value;
bind[6].is_null= 0;
bind[6].buffer_length= STRING_SIZE;
bind[6].length= &str_length[6];

/*Status Details*/
bind[7].buffer_type= MYSQL_TYPE_STRING;
bind[7].buffer= (char *)&status_details_value;
bind[7].is_null= 0;
bind[7].buffer_length= STRING_SIZE;
bind[7].length= &str_length[7];

/* Bind all the buffers */
if (mysql_stmt_bind_param(stmt, bind)) {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
strncpy(sender_id_value,sender_id, STRING_SIZE);
str_length[0]= strlen(sender_id_value);
strncpy(dest_id_value,dest_id, STRING_SIZE);
str_length[1]=strlen(dest_id_value);
strncpy(message_type_value,message_type,STRING_SIZE);        
str_length[2]=strlen(message_type_value);
strncpy(reference_id_value,reference_id,STRING_SIZE);        
str_length[3]=strlen(reference_id_value);
strncpy(message_id_value,message_id,STRING_SIZE);        
str_length[4]=strlen(message_id_value);
strncpy(data_location_value,data_location,STRING_SIZE);        
str_length[5]=strlen(data_location_value);
strncpy(status_value,status,STRING_SIZE);        
str_length[6]=strlen(status_value);
strncpy(status_details_value,status_details,STRING_SIZE);        
str_length[7]=strlen(status_details_value);

/* Process the INSERT statement*/
if (mysql_stmt_execute(stmt)) {
  fprintf(stderr, " mysql_stmt_execute, failed\n");
  fprintf(stderr, " [%d]%s\n",mysql_stmt_errno(stmt),
  mysql_stmt_error(stmt));
  exit(0);
}

/* find the total rows affected */
affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, "Total Affected rows(insert): %lu\n",
                (unsigned long) affected_rows);

/* Validate affected rows */ 
if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by mysql\n");
  exit(0);
}

/* Close the statement */
if (mysql_stmt_close(stmt)) {
  fprintf(stderr, "  it failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
} 

  /*insertion is successful*/
  return 1;
  mysql_close(con);
}

