#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<mysql/mysql.h>
#include <stdbool.h>
/*
#define host "localhost"
#define user "root"
#define pass "riya"
#define dbname "esb_db"
#define port 0
#define unix_socket NULL
#define flag 0
*/
int check_all_routes(char *message_type,char *sender,char *destination);
int check_transport(int id);
int check_transform(int id);
int select_active_routes(char *message_type,char *sender,char *destination);
typedef struct {
     int id;
     char *Sender;
     char *Destination;
     char *MessageType;
     char *data_location;
     }task_list;
typedef struct {
  char *config_k;
  char *config_v;
  }tp_data;

typedef struct{
char *config_key;
char *config_value;
}tf_data;

void update_status(char *str,int ID);
tf_data* get_tf_data(int route_id);
tp_data* get_tp_data(int route_id);
task_list* fetch_data1(void);
void *poll_database_for_new_requests(void *vargp);
