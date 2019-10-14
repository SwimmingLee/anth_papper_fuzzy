#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>


 
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int getRest_A053Sensor(void) //main
{
  struct curl_slist *headers = NULL;
  CURL *curl_handle;
  CURLcode res;

  char *url = "https://api.artik.cloud/v1.1/messages/snapshots?includeTimestamp=true&sdids=5b0b6de1d0ad438199ea7b79e95e36fe";
  
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
  chunk.size = 0;    /* no data at this point */ 
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl_handle = curl_easy_init();

  headers = curl_slist_append(headers, "Postman-Token: ec4596e3-e4ac-488b-ada4-9221f171b82b");
  headers = curl_slist_append(headers, "Cache-Control: no-cache");
  headers = curl_slist_append(headers, "Authorization: Bearer bf95691253114af68020c4458ac3d8a5");
  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
  
  /* specify URL to get */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */ 
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */ 
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */ 
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {//수신시 이곳에서 처리해야한다.
    //printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
//--------------------------------------------------------------------------
    printf("%s \n",chunk.memory);  //chunk.memory가 받아온 json

//--------------------------------------------------------------------------
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
 
  /* we're done with libcurl, so clean it up */ 
  curl_global_cleanup();
 
  return 0;
}




