//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include <edge_call.h>
#include <keystone.h>

unsigned long
print_string(char* str);
void
print_string_wrapper(void* buffer);
#define OCALL_PRINT_STRING 1
#define OCALL_SCAN_STRING 2

#define BUFSIZE 142
//#define BUFSIZE 118

/***
 * An example call that will be exposed to the enclave application as
 * an "ocall". This is performed by an edge_wrapper function (below,
 * print_string_wrapper) and by registering that wrapper with the
 * enclave object (below, main).
 ***/
unsigned long
print_string(char* str) {
  //return printf("Enclave said: \"%s\"\n", str);
printf("\n******************************************\n");

  //return_ptr=0xffffffff40000000;
  for (unsigned int i = 0; i < 1024*BUFSIZE; i+=64)
  {
    printf("\n%p: ", str+i);
    for (unsigned int j = i; j < i+64 && j < 1024*BUFSIZE; j++)
    {
    printf("%c", ((char*)str)[j]);
    }
  }
  printf("\n******************************************\n");


}

int
main(int argc, char** argv) {
  Keystone::Enclave enclave;
  Keystone::Params params;
  puts("Beginning main");

  params.setFreeMemSize(1024 * 128);
  //params.setFreeMemSize(1024 * 128);
  //params.setUntrustedMem(DEFAULT_UNTRUSTED_PTR, 1024 * 1024);
  params.setUntrustedMem(0xffffffff00000000 - 1024 * 1024, 1024 * 1024);

  puts("Set mem utm and fre");

  enclave.init(argv[1], argv[2], params);

  puts("initialized enclave");

  enclave.registerOcallDispatch(incoming_call_dispatch);

  /* We must specifically register functions we want to export to the
     enclave. */
  register_call(OCALL_PRINT_STRING, print_string_wrapper);
  register_call(OCALL_SCAN_STRING, print_string_wrapper);

  edge_call_init_internals(
      (uintptr_t)enclave.getSharedBuffer(), enclave.getSharedBufferSize());

  puts("About to run enclave");
  enclave.run();

  return 0;
}

/***
 * Example edge-wrapper function. These are currently hand-written
 * wrappers, but will have autogeneration tools in the future.
 ***/
void
print_string_wrapper(void* buffer) {
  /* Parse and validate the incoming call data */
  struct edge_call* edge_call = (struct edge_call*)buffer;
  uintptr_t call_args;
  unsigned long ret_val;
  size_t arg_len;
  if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
    edge_call->return_data.call_status = CALL_STATUS_BAD_OFFSET;
    return;
  }

  /* Pass the arguments from the eapp to the exported ocall function */
  ret_val = print_string((char*)call_args);

  /* Setup return data from the ocall function */
  uintptr_t data_section = edge_call_data_ptr();
  memcpy((void*)data_section, &ret_val, sizeof(unsigned long));
  if (edge_call_setup_ret(
          edge_call, (void*)72057593896374272, 0)) {
          //edge_call, (void*)data_section, sizeof(unsigned long))) {
    edge_call->return_data.call_status = CALL_STATUS_BAD_PTR;
    puts("edge_call_setup_ret BAD");
  } else {
    edge_call->return_data.call_status = CALL_STATUS_OK;
    puts("edge_call_setup_ret OK");
  }

  /* This will now eventually return control to the enclave */
  return;
}
