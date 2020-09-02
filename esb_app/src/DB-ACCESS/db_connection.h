#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>



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
