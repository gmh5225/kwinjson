#include "test.h"
#include "cJSON.h"


#pragma warning(disable:4559) 
#pragma warning(disable:4189) 


//;$(DDK_LIB_PATH)\stdunk.lib
//#pragma comment(lib, "legacy_stdio_definitions.lib")


#define fprintf(...) 
#define printf(...) 


//////////////////////////////////////////////////////////////////////////////////////////////////


//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
char * create_monitor(void)
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

    XSTATE_SAVE SaveState;
    NTSTATUS Status = KeSaveExtendedProcessorState(XSTATE_MASK_LEGACY, &SaveState);
    if (NT_SUCCESS(Status)) {
        __try {
            string = cJSON_Print(monitor);
            if (string == NULL) {
                fprintf(stderr, "Failed to print monitor.\n");
            }
        } __finally {
            KeRestoreExtendedProcessorState(&SaveState);
        }
    }

end:
    cJSON_Delete(monitor);
    return string;
}


//NOTE: Returns a heap allocated string, you are required to free it after use.
char * create_monitor_with_helpers(void)
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

    XSTATE_SAVE SaveState;
    NTSTATUS Status = KeSaveExtendedProcessorState(XSTATE_MASK_LEGACY, &SaveState);
    if (NT_SUCCESS(Status)) {
        __try {
            string = cJSON_Print(monitor);
            if (string == NULL) {
                fprintf(stderr, "Failed to print monitor.\n");
            }
        } __finally {
            KeRestoreExtendedProcessorState(&SaveState);
        }
    }

end:
    cJSON_Delete(monitor);
    return string;
}


/* return 1 if the monitor supports full hd, 0 otherwise */
int supports_full_hd(const char * const monitor)
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

    //const char * string = "XXX";
    //cJSON * json = cJSON_Parse(string);
    //char * string2 = cJSON_Print(json);

    char* monitor = create_monitor();

    char* monitor_with_helpers = create_monitor_with_helpers();

    int ret = supports_full_hd(monitor);

    cJSON_free(monitor);
    cJSON_free(monitor_with_helpers);
}


_Function_class_(DRIVER_UNLOAD)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
VOID Unload(_In_ struct _DRIVER_OBJECT * DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE();
}


EXTERN_C DRIVER_INITIALIZE DriverEntry;
//#pragma INITCODE
#pragma alloc_text(INIT, DriverEntry)
_Function_class_(DRIVER_INITIALIZE)
_IRQL_requires_same_
_IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    NTSTATUS status = STATUS_SUCCESS;

    UNREFERENCED_PARAMETER(RegistryPath);

    if (!KD_DEBUGGER_NOT_PRESENT) {
        KdBreakPoint();//__debugbreak();
    }

    //if (*InitSafeBootMode) {
    //    return STATUS_ACCESS_DENIED;
    //}

    PAGED_CODE();

    DriverObject->DriverUnload = Unload;

    JsonTest();

    return status;
}
