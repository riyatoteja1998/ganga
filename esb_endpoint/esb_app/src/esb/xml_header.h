//int process_esb_request(char* bmd_file_path);

typedef struct {
    char *MessageID;
    char *MessageType;
    char *Sender;
    char *Destination;
    char *CreationDateTime;
    char *Signature;
    char *ReferenceID;
} bmd_envelop;

typedef struct {
    bmd_envelop* envelop_value;
    char* payload;
} bmd;

bmd_envelop *extract_envelop(char *doc);
char *extract_payload(char *doc);
int is_bmd_valid(bmd* b);
int request_validation(bmd *b);
bmd *bmd_main_parse(char * file);
int file_exist(char *f);

