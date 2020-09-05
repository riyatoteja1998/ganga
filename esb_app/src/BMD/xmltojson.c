#include<stdio.h>
#include<stdlib.h>
void xmltojson(char *payload)
{
     char doc[] = "/home/harshal/Desktop/payload.json";
     FILE *file;
     file = fopen(doc,"w");

    if(file == NULL)
    {
      	printf("Writing Failed");
        exit(0);
    }

    fprintf(file,"{\n \"Payload\":\"%s\"\n}",payload);

    fseek(file, 0L, SEEK_END);

    // calculating the size of the file
    long int filesize = ftell(file);
    if(filesize > 4000000){
    printf("\nPayload size error\n");
    }
    else{
    printf("\nJson File Created Successfully\n");
    }
    fclose(file);
    return;
}
