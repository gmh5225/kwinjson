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
    //free(out);//DLL的方式禁止使用free。
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


char * create_monitor(void)
//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char * string = NULL;
    cJSON * name = NULL;
    cJSON * resolutions = NULL;
    cJSON * resolution = NULL;
    cJSON * width = NULL;
    cJSON * height = NULL;
    size_t index = 0;

    cJSON * monitor = cJSON_CreateObject();
    if (monitor == NULL) {
        goto end;
    }

    name = cJSON_CreateString("Awesome 4K");
    if (name == NULL) {
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */
    cJSON_AddItemToObject(monitor, "name", name);

    resolutions = cJSON_CreateArray();
    if (resolutions == NULL) {
        goto end;
    }
    cJSON_AddItemToObject(monitor, "resolutions", resolutions);

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index) {
        resolution = cJSON_CreateObject();
        if (resolution == NULL) {
            goto end;
        }
        cJSON_AddItemToArray(resolutions, resolution);

        width = cJSON_CreateNumber(resolution_numbers[index][0]);
        if (width == NULL) {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "width", width);

        height = cJSON_CreateNumber(resolution_numbers[index][1]);
        if (height == NULL) {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "height", height);
    }

    string = cJSON_Print(monitor);
    if (string == NULL) {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    return string;
}


char * create_monitor_with_helpers(void)
//NOTE: Returns a heap allocated string, you are required to free it after use.
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char * string = NULL;
    cJSON * resolutions = NULL;
    size_t index = 0;

    cJSON * monitor = cJSON_CreateObject();

    if (cJSON_AddStringToObject(monitor, "name", "Awesome 4K") == NULL) {
        goto end;
    }

    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
    if (resolutions == NULL) {
        goto end;
    }

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index) {
        cJSON * resolution = cJSON_CreateObject();

        if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL) {
            goto end;
        }

        if (cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL) {
            goto end;
        }

        cJSON_AddItemToArray(resolutions, resolution);
    }

    string = cJSON_Print(monitor);
    if (string == NULL) {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    return string;
}


int supports_full_hd(const char * const monitor)
/* return 1 if the monitor supports full hd, 0 otherwise */
{
    const cJSON * resolution = NULL;
    const cJSON * resolutions = NULL;
    const cJSON * name = NULL;
    int status = 0;
    cJSON * monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL) {
        const char * error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("Checking monitor \"%s\"\n", name->valuestring);
    }

    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
    cJSON_ArrayForEach(resolution, resolutions)
    {
        cJSON * width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON * height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height)) {
            status = 0;
            goto end;
        }

        if ((width->valuedouble == 1920) && (height->valuedouble == 1080)) {
            status = 1;
            goto end;
        }
    }

end:
    cJSON_Delete(monitor_json);
    return status;
}


void JsonTest()
{
    const char * ver = cJSON_Version();

    char * monitor = create_monitor();

    char * monitor_with_helpers = create_monitor_with_helpers();

    int ret = supports_full_hd(monitor);

    cJSON_free(monitor);
    cJSON_free(monitor_with_helpers);
}


int main()
{
    write();
    read();
    JsonTest();
}
