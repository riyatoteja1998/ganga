
#include "../DB-ACCESS/db_connection.h"
#include "../BMD/xml_header.h"
#include "../endpoint/transform.h"

int queue_the_request(bmd *b,char *path);
int process_esb_request(char* path);
void *poll_database_for_new_requests(void *vargp);


/*int process_esb_request(char* bmd_file_path);

typedef struct {
    char* sender_id;
    char* destination_id;
    char* message_type;
    // TODO: Other fields
} bmd_envelop;

typedef struct {
    bmd_envelop envelop;
    char* payload;
} bmd;
*/