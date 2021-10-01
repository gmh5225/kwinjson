#include "../cJSON/cJSON.h"
#include "../libcjson/crt.h"
//#include "test.h"


#pragma warning(disable:4559) 
#pragma warning(disable:4189) 

#define EXIT_FAILURE 0

#define fprintf(...) 
#define printf(...) 

//;$(DDK_LIB_PATH)\stdunk.lib
//#pragma comment(lib, "legacy_stdio_definitions.lib")


//////////////////////////////////////////////////////////////////////////////////////////////////


char * create_monitor(void)
//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
{
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

    for (index = 0; index < 3; ++index) {
        resolution = cJSON_CreateObject();
        if (resolution == NULL) {
            goto end;
        }
        cJSON_AddItemToArray(resolutions, resolution);

        width = cJSON_CreateString("test");
        if (width == NULL) {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "width", width);

        height = cJSON_CreateString("test");
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


char * create_monitor_with_helpers(void)
//NOTE: Returns a heap allocated string, you are required to free it after use.
{
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

    for (index = 0; index < 3; ++index) {
        cJSON * resolution = cJSON_CreateObject();

        if (cJSON_AddStringToObject(resolution, "width", "test") == NULL) {
            goto end;
        }

        if (cJSON_AddStringToObject(resolution, "height", "test") == NULL) {
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
