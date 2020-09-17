#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
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
{

  char* to  = (char*)to_p;
  char* data = (char*)data_p;
  CURL *curl;
  CURLcode res;
  char *file = "/home/harshal/Desktop/checkhttp.json";

  FILE *fp = fopen(file, "wb");
  /* In windows, this will init the winsock stuff */ 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
    curl_easy_setopt(curl, CURLOPT_URL, to);
    /* Now specify the POST data */ 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  fclose(fp);
  return strdup((file));
  //return 0;
}
