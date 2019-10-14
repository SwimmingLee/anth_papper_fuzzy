

#ifndef __GET_MIDDLE_WEATHER_H__
#define __GET_MIDDLE_WEATHER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
#include <expat.h>
#include <curl/curl.h>	

#include <time.h>	



struct MemoryStruct {
  char *memory;
  size_t size;
};
 
struct ParserStruct {
  int ok;
  size_t tags;
  size_t depth;
  struct MemoryStruct characters;
};
 
int getMiddle_Weather();












int order=0;
int count=0;
int n=0;
int m=0;
int i;
int l = 0;

char * tmp[16];
char * weather[13];
char result[12];
char* newstrptr;


static void startElement(void *userData, const XML_Char *name,
                         const XML_Char **atts)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  state->tags++;
  state->depth++;
 
  /* Get a clean slate for reading in character data. */ 
  free(state->characters.memory);
  state->characters.memory = NULL;
  state->characters.size = 0;
}
 
static void characterDataHandler(void *userData, const XML_Char *s, int len)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  struct MemoryStruct *mem = &state->characters;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + len + 1);
  if(mem->memory == NULL) {
    /* Out of memory. */ 
    fprintf(stderr, "Not enough memory (realloc returned NULL).\n");
    state->ok = 0;
    return;
  }
 
  memcpy(&(mem->memory[mem->size]), s, len);
  mem->size += len;
  mem->memory[mem->size] = 0;
}
 
static void endElement(void *userData, const XML_Char *name)
{
  struct ParserStruct *state = (struct ParserStruct *) userData;
  state->depth--;	
  count++;
  //printf("%d ",count++);
  //printf("%s \n",state->characters.memory);
  //printf("%5lu   %10lu   %s\n", state->depth, state->characters.size, name);
  
  if(order==0){
	if((count>4)&&(count<18))
	{
		//printf("%s : ",name);
		//printf("%d ",count);
  		//printf("%s \n",state->characters.memory);
		l = strlen(state->characters.memory); 
		newstrptr = (char*)malloc(sizeof(char) * (l + 1));
       	strcpy(newstrptr, state->characters.memory);
        weather[n++] = newstrptr;
		//printf("%s\n",weather[n++]);		
  	}	
  }else{
	if((count>4)&&(count<21)){
		//printf("%d ",count);
		//printf("%s : ",name);
  		//printf("%s \n",state->characters.memory);
		l = strlen(state->characters.memory); 
		newstrptr = (char*)malloc(sizeof(char) * (l + 1));
       	strcpy(newstrptr, state->characters.memory);
        tmp[m++] = newstrptr;
		//printf("%s\n",tmp[m++]);		
  	}
  }
  
}
 
static size_t parseStreamCallback(void *contents, size_t length, size_t nmemb,
                                  void *userp)
{
  XML_Parser parser = (XML_Parser) userp;
  size_t real_size = length * nmemb;
  struct ParserStruct *state = (struct ParserStruct *) XML_GetUserData(parser);
 
  /* Only parse if we're not already in a failure state. */ 
  if(state->ok && XML_Parse(parser, (const char*)contents, real_size, 0) == 0) {
    int error_code = XML_GetErrorCode(parser);
    fprintf(stderr, "Parsing response buffer of length %lu failed"
            " with error code %d (%s).\n",
            real_size, error_code, XML_ErrorString((XML_Error)error_code));
    state->ok = 0;
  }
 
  return real_size;
}

//--------------------------------------------------------------------------------------
int getMiddle_Weather() {
	CURL *curl_handle;
  	CURLcode res;
  	XML_Parser parser;
	struct ParserStruct state;

	/* Initialize the state structure for parsing. */
  	memset(&state, 0, sizeof(struct ParserStruct));
  	state.ok = 1;

	char *url = (char*)malloc(sizeof(char) * 512);
	char *http = (char*)malloc(sizeof(char) * 255);
	char *ServiceKey_val = (char*)malloc(sizeof(char) * 255);
	char *regId_val = (char*)malloc(sizeof(char) * 8);
	char *tmFc_val = (char*)malloc(sizeof(char) * 12);
	char *numOfRows_val = (char*)malloc(sizeof(char) * 2);
	char *pageNo_val = (char*)malloc(sizeof(char) * 5);
	const char *ServiceKey = "?ServiceKey=";
	const char *regId = "&regId=";
	const char *tmFc = "&tmFc=";
	const char *numOfRows = "&numOfRows=";
	const char *pageNo = "&pageNo=";
	const char *startPage = "&startPage=1";
//--------------------------time-------------------------------------------현재시간의 것을 가져오자--------------------------------
	time_t t = time(NULL);
	struct tm time = *localtime(&t);

	int year = time.tm_year+1900;
	int month = time.tm_mon+1;
	int day = time.tm_mday;
	int hour = time.tm_hour;
	//9.14 day bug clear if 201810010300 ?? yes boom! but clear~
	if(hour<6){
		if(day==1){
			switch(month){
				case 1:{
					month=12;
					day=31;
				}
				break;
				case 2:{
					month=1;
					day=31;				
				}
				break;
				case 3:{
					month=2;
					if(year%4!=0){
					  day=28;
					}else{
					  day=29;					
					}					
				}
				break;
				case 4:{
					month=3;
					day=31;				
				}
				break;
				case 5:{
					month=4;
					day=30;				
				}
				break;
				case 6:{
					month=5;
					day=31;				
				}
				break;
				case 7:{
					month=6;
					day=30;				
				}
				break;
				case 8:{
					month=7;
					day=31;				
				}
				break;
				case 9:{
					month=8;
					day=31;				
				}
				break;
				case 10:{
					month=9;
					day=30;				
				}
				break;
				case 11:{
					month=10;
					day=31;				
				}
				break;
				case 12:{
					month=11;
					day=30;				
				}
				break;						
			}			
		}
 		day-=1;
	}	
	if(month>9){
		if(day>9){
			sprintf(result,"%d%d%d0600",year,month,day);
			//printf("%s\n",result);
		}else{
			sprintf(result,"%d%d0%d0600",year,month,day);
			//printf("%s\n",result);
		}
	}else{
		if(day>9){
			sprintf(result,"%d0%d%d0600",year,month,day);
			//printf("%s\n",result);
		}else{
			sprintf(result,"%d0%d0%d0600",year,month,day);
			//printf("%s\n",result);
		}
	}	
 //--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	strcpy(ServiceKey_val, "8YTY69H8vs%2BtoxKvsA8aRD93DxmjeIk3ugVN%2Bs4A%2F2%2FHCFXQT%2BO9KUoD%2Fnhf%2BidN0rn%2BbN4rqzUtIeDvEWbFag%3D%3D");
	strcpy(tmFc_val, result);
	strcpy(numOfRows_val, "10");
	strcpy(pageNo_val, "1");
	for(i=0;i<2;i++)
	{
		if(order==0){//first middle land weather
			strcpy(http, "http://newsky2.kma.go.kr/service/MiddleFrcstInfoService/getMiddleLandWeather");
			strcpy(regId_val, "11B00000"); //later need select do(ex choongchungnamdo) change ga nueng
		}else{//second middle temperature
			strcpy(http, "http://newsky2.kma.go.kr/service/MiddleFrcstInfoService/getMiddleTemperature");
			strcpy(regId_val, "11B10101"); //later need select do(ex choongchungnamdo) change ga nueng		
		}
		sprintf(url, "%s%s%s%s%s%s%s%s%s%s%s%s",http, ServiceKey, ServiceKey_val, regId, regId_val, tmFc, tmFc_val, numOfRows, numOfRows_val, pageNo, pageNo_val, startPage);
  		/* Initialize a namespace-aware parser. */ 
  		parser = XML_ParserCreateNS(NULL, '\0');
  		XML_SetUserData(parser, &state);
		XML_SetElementHandler(parser, startElement, endElement);
	  	XML_SetCharacterDataHandler(parser, characterDataHandler);

		//printf("%s \n", url);
  		/* Initialize a libcurl handle. */ 
  		curl_global_init(CURL_GLOBAL_DEFAULT);
  		curl_handle = curl_easy_init();
  		curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
  		curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, parseStreamCallback);
  		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)parser);
 
  		res = curl_easy_perform(curl_handle);
  		if(res != CURLE_OK) {
    			fprintf(stderr, "curl_easy_perform() failed: %s\n",
            		curl_easy_strerror(res));
  		}	
  		else if(state.ok) 
		{
    			/* Expat requires one final call to finalize parsing. */ 
    			if(XML_Parse(parser, NULL, 0, 1) == 0) 
			{
      				int error_code = XML_GetErrorCode(parser);
      				fprintf(stderr, "Finalizing parsing failed with error code %d (%s).\n",
              			error_code, XML_ErrorString((XML_Error)error_code));
    			}
			else 
			{		
			}
  		}
		order++;
		count=0;
		n=0;
		m=0;
	}//for end
	
//-----------------------------------------------------------------------------------------------------------------------------------------------
	
	int i;
	int rainy_count = 0;

	for(i=1;i<11;i++){
		//printf("%s \n",weather[i]);
		if(strstr(weather[i], "구름많음") != NULL) rainy_count++;
		
		if(strstr(weather[i], "흐리고 비") != NULL) rainy_count++;
		else if(strstr(weather[i], "구름많고 비") != NULL) rainy_count++;

	}
        //printf("탄저병 위험수치 %d 입니다. 탄저병 예방조치를 취하시는것을 권고드립니다. \n",rainy_count*10);	
	if(rainy_count>=4){
		printf("탄저병 위험수치 %d 입니다. 탄저병 예방조치를 취하시는것을 권고드립니다. \n",rainy_count*10);	
	}
 
	free(url);
	free(http);
	free(ServiceKey_val);
	free(regId_val);
	free(tmFc_val);
	free(numOfRows_val);
	free(pageNo_val);



  return 0;


}


#endif
