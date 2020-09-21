
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define STRING_SIZE 100
struct string
{
  char *ptr;
  size_t len;
};
/*
void init_string(struct string *s)
{ 
  printf("string initialisation\n");
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}
*/
size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s)
{ 
  printf("Callback is called\n");
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size * nmemb;
}

void* get_call_destination(void *urlp,void *apip)
{
  /* Converting URL to string */
  char *url = (char*) urlp;
  char *api = (char*) apip;
  CURL *curl;
  CURLcode result;


  curl = curl_easy_init();
  struct string s;
  init_string(&s);
  /* Checks if curl is initialised properly and 
   * performs required operations */

  if (curl)
  {
    printf("Checking Destination Connection %s\n",api);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    /* Verbose is to check what happens within curl */
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    result = curl_easy_perform(curl);

    if (result != CURLE_OK)
    {
      fprintf(stderr, "Connection failed.");
      exit(0);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  printf("%s\n",s.ptr);
  return (void*)s.ptr;
}

char *get_payload(char *url)
{
      
    /*Creates file name of json as per bmd name*/
    char doc[100]="/home/riya/ganga/esb_app/src/esb/data-Payload.json";

    /* Get data from destination service 
        that should be sent */
    char *data = get_call_destination(url,"ifsc");

    FILE *fp;
    fp = fopen(doc, "w");
    if (fp == NULL)
    {
        printf("file opening failed");
        exit(0);
    }
    /* Writes into json file */
    fprintf(fp, "\n%s\n", data);
    /* Closes file */
    fclose(fp);
    /* returns json filename */
    return strdup(doc);
}
