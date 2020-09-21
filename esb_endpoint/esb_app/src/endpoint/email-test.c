#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#define FROM_ADDR    "riyatoteja1998@gmail.com"
#define CC_ADDR      "riyatoteja1998@gmail.com"

int sendemail(char *To, char *path_p) { 
 
    char *to = (char*)To;
    char *file_path = (char*)path_p;
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
  
  curl = curl_easy_init();
  if(curl) {
    /* This is the URL for your mailserver */ 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_USERNAME, "riyatoteja1998@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "8p26aa0026");

    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
 
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
 
    recipients = curl_slist_append(recipients, to);
    recipients = curl_slist_append(recipients, CC_ADDR);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
 
    /*json file*/
    FILE *fd = fopen(file_path, "r");
//         curl_easy_setopt(curl, CURLOPT_READDATA, fp);
    curl_easy_setopt(curl, CURLOPT_READDATA,fd);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
 
    /* Send message */ 
    res = curl_easy_perform(curl);
 
    /* errors checks */ 
    if(res != CURLE_OK)
     { fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              return -1;
     }
    /* deallocate the list of recipients */ 
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
  }
 return 1;
}
/*
int main()
{

    printf("%d",sendemail("testgangahv@gmail.com","/home/harshal/Desktop/payload.json"));

}*/
