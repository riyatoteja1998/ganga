#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>


static char *host = "localhost";
static char *user = "root";
static char *pass = "password";
static char *dbname ="esb_db";

unsigned int port =3306;
static char *unix_socket = NULL;
unsigned flag=0;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}
int main()
{
    MYSQL *con;
    con = mysql_init(NULL);
    if(!(mysql_real_connect(con,host,user,pass,dbname,port,unix_socket,flag)))
    {
        fprintf(stderr,"\nError : %s [%d]\n",mysql_error(con),mysql_errno(con));
        exit(1);
    }
    printf("Connection Successful!\n\n");

    //if (mysql_query(con, "SELECT * FROM esb_request"))
   // {
    //    finish_with_error(con);
   // }
    char sender_id[50];
    char dest_id[50];
    char message_type[50];
    char message_id[50];
    char data_location[50];
    char status[50];
    char status_details[50];

    printf("Enter sender id\n");
    scanf("%s",sender_id);
    printf("Enter dest id\n");
    scanf("%s",dest_id);
    printf("Enter msg type\n");
    scanf("%s",message_type);
    printf("Enter msg id\n");
    scanf("%s",message_id);
    printf("Enter data location\n");
    scanf("%s",data_location);
    printf("Enter status\n");
    scanf("%s",status);
    printf("Enter status details\n");
    scanf("%s",status_details);

    if (mysql_query(con, "INSERT INTO esb_request(sender_id, dest_id, message_type, message_id, data_location, status, status_details) VALUES(sender_id,dest_id,message_type,message_id,data_location, status, status_details)")) {
        finish_with_error(con);
    }

    mysql_close(con);

    exit(0);

    return EXIT_SUCCESS;
}
