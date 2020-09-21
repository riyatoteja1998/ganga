
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

void*  http_request(char* url)
{
 printf("in http request");
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);
    if(res!=CURLE_OK)
   {
	fprintf(stderr,"curl failed %s\n",curl_easy_strerror(res));
   }
    printf("%s\n", s.ptr);
    

    /* always cleanup */
    curl_easy_cleanup(curl);
    return (void*)s.ptr;
  }
   return NULL;
  
}



 int file_exist(char *file);
int file_exist(char *file)
{
  FILE *fp;

  char c;

  // Open file
  fp = fopen(file, "r");
  if (fp == NULL)
  {
    printf("Cannot open file \n");
    return 0;
  }

  // Read contents from file
  c = fgetc(fp);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(fp);
  }

  fclose(fp);
  return 1;
}

char* post_http(char* to_p,char* data_p)
{  printf("in post_https");

  char* to  = (char*)to_p;
  char* data = (char*)data_p;
  CURL *curl;
  CURLcode res;
  char *file = "/home/riya/ganga/esb_app/src/esb/data-Payload.json";

  FILE *fp = fopen(file, "wb");
  // In windows, this will init the winsock stuff 
  curl_global_init(CURL_GLOBAL_ALL);
 
  //get a curl handle 
  curl = curl_easy_init();
  if(curl) {
    // First set the URL that is about to receive our POST. This URL can
      // just as well be a https:// URL if that is what should receive the
       //data. 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_URL, to);
    // Now specify the POST data 
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS,data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
 
    // Perform the request, res will get the return code  
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 

    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  fclose(fp);
  return strdup((file));
  //return 0;
}


