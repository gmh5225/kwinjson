#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <Windows.h>
#include "..\cJSON\cJSON.h"


#ifdef _WIN64  
#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\libjson.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\libjson.lib")
#endif
#else 
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\libjson.lib")
#else
#pragma comment(lib, "..\\Release\\libjson.lib")
#endif
#endif


void write()
{
    cJSON * root;

    root = cJSON_CreateObject();                     // 创建根数据对象
    cJSON_AddStringToObject(root, "name", "luffy");  // 添加键值对
    cJSON_AddStringToObject(root, "sex", "man");     // 添加键值对
    cJSON_AddNumberToObject(root, "age", 19);        // 添加键值对

    char * out = cJSON_Print(root);   // 将json形式转换成字符串
    printf("%s\n", out);

    cJSON_Delete(root);
    //free(out);//禁止使用free。
    cJSON_free(out);
}


void read()
{
    cJSON * json, * name, * sex, * age;
    const char * out = "{\"name\":\"luffy\",\"sex\":\"man\",\"age\":19}";

    json = cJSON_Parse(out);
    name = cJSON_GetObjectItem(json, "name"); 
    sex = cJSON_GetObjectItem(json, "sex");
    age = cJSON_GetObjectItem(json, "age");

    printf("name:%s,sex:%s,age:%d\n", name->valuestring, sex->valuestring, age->valueint);

    cJSON_Delete(json);
}


int main()
{
    write();
    read();
}
