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



