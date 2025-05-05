#include <windows.h>
#include <stdio.h>
#include <oleauto.h>
#include "SimaticManager.h"
#include <initguid.h>  // Only in *one* .c file before using DEFINE_GUID
DEFINE_GUID(IID_IDispatch, 0x00020400, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

HRESULT hr;
CLSID clsid;
ITypeLib *pTypeLib = NULL;
IDispatch *pDispatch = NULL;
DISPID dispid;
DISPPARAMS dispParams = { NULL, NULL, 0, 0 };
VARIANT result;
const wchar_t *tlbPath = L"C:/Program Files (x86)/Siemens/Step7/S7BIN/S7ABATCX.TLB";

int main(void){
    LoadInterface();
    // Execute here....

    UnloadInterface();
    return 0;
}

int LoadInterface(void) {
    // Step 1: Initialize COM
    printf("Starting load interface.\n");
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        printf("Failed to initialize COM.\n");
        return 1;
    }

    // Step 2: Get CLSID from ProgID "Simatic.Simatic.1"
    printf("Starting Simatic.Simatic.1 loading...\n");
    hr = CLSIDFromProgID(L"Simatic.Simatic.1", &clsid);
    if (FAILED(hr)) {
        printf("Failed to get CLSID from ProgID.\n");
        CoUninitialize();
        return 1;
    }

    // Step 3: Create COM instance and load library enums
    printf("Creating COM Instance\n");
    hr = CoCreateInstance(&clsid, NULL, CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER, &IID_IDispatch, (void**)&pDispatch);
    if (FAILED(hr)) {
        printf("Failed to create COM instance.\n");
        CoUninitialize();
        return 1;
    }
    // Load interface Enum
    printf("Loading ENUM Libraries\n");
    //pTypeLib->lpVtbl->Release(pTypeLib);


    printf("COM object created successfully!\n");
    return 0;
}

void UnloadInterface(void){
    // Cleanup
    if (pDispatch) pDispatch->lpVtbl->Release(pDispatch);
    CoUninitialize();
}

int CallFunction(void){
    // 4. Get DISPID for "Test"
    LPOLESTR methodName = L"Test";
    hr = pDispatch->lpVtbl->GetIDsOfNames(pDispatch, &IID_NULL, &methodName, 1, LOCALE_USER_DEFAULT, &dispid);
    if (FAILED(hr)) {
        printf("Method 'Test' not found.\n");
        pDispatch->lpVtbl->Release(pDispatch);
        CoUninitialize();
        return 1;
    }

    // 5. Call the "Test" method
    VariantInit(&result);
    hr = pDispatch->lpVtbl->Invoke(
        pDispatch,
        dispid,
        &IID_NULL,
        LOCALE_USER_DEFAULT,
        DISPATCH_METHOD,
        &dispParams,
        &result,
        NULL,
        NULL
    );

    if (SUCCEEDED(hr)) {
        printf("Method 'Test' called successfully.\n");
        // You can inspect result.vt and result contents if Test returns a value
    } else {
        printf("Invoke failed. HRESULT: 0x%lx\n", hr);
    }

    return 0;
}