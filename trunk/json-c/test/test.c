#include "test.h"

#include "../json-c/json_object.h"
#include "../json-c/json_object_iterator.h"
#include "../json-c/json_tokener.h"

#define fprintf(...) 
#define printf(...) 


void JsonTest()
{
	const char * input = "{\n\
		\"string_of_digits\": \"123\",\n\
		\"regular_number\": 222,\n\
		\"decimal_number\": 99.55,\n\
		\"boolean_true\": true,\n\
		\"boolean_false\": false,\n\
		\"big_number\": 2147483649,\n\
		\"a_null\": null,\n\
		}";

	struct json_object * new_obj;
	struct json_object_iterator it;
	struct json_object_iterator itEnd;

	it = json_object_iter_init_default();
	new_obj = json_tokener_parse(input);
	it = json_object_iter_begin(new_obj);
	itEnd = json_object_iter_end(new_obj);

	while (!json_object_iter_equal(&it, &itEnd)) {
		printf("%s\n", json_object_iter_peek_name(&it));
		printf("%s\n", json_object_to_json_string(json_object_iter_peek_value(&it)));
		json_object_iter_next(&it);
	}

	json_object_put(new_obj);
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
