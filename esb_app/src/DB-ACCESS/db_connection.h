#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>

#define host "localhost"
#define user "root"
#define pass "password"
#define dbname "esb_db"
#define port 3306
#define unix_socket NULL
#define flag 0

int check_all_routes(char *message_type,char *sender,char *destination);
int check_transport(int id);
int check_transform(int id);

typedef struct {
     int id;
     char *Sender;
     char *Destination;
     char *MessageType;
     }task_list;
typedef struct {
  char *config_key;
  char *config_value;
  }tp_data;
typedef struct{
char *config_key;
char *config_value;
}tf_data;
int select_active_routes(char *message_type,char *sender,char *destination);
