//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "eapp_utils.h"
#include "string.h"
#include "edge_call.h"
#include <syscall.h>

//#define BUFSIZE 118
#define BUFSIZE 142

char* s = "random string";

#define OCALL_PRINT_STRING 1
#define OCALL_SCAN_STRING 2

unsigned long ocall_scan_print_string(char* string, unsigned char retbuf[], unsigned long* retval);

int main(){

  //char* secret = "Super ultra duper secret enclave char sequence!!!!";
  char* secret = "\x12\x34\x31\x24\x33\x61\x22\x2e\x2f\x27\x28\x25\x24\x2f\x35\x28\x20\x2d\x61\x24\x2f\x22\x2d\x20\x37\x24\x61\x32\x24\x22\x33\x24\x35\x60\x60\x60";
  unsigned char retbuf[1024*BUFSIZE];
  memset(retbuf, (unsigned char)0x00, 1024*BUFSIZE);
  char secret_target[64];
  for (size_t i = 0; i < strlen(secret); i++)
  {
    secret_target[i] = secret[i] ^ 'A';
  }
  
  unsigned long retval;
  ocall_scan_print_string("Hello World", retbuf, &retval);
  (void)secret_target;

  EAPP_RETURN(0);
}

unsigned long ocall_scan_print_string(char* string, unsigned char retbuf[], unsigned long *retval){
  ocall(OCALL_SCAN_STRING, string, strlen(string)+1, retbuf , 1024* BUFSIZE * sizeof(unsigned char));
  ocall(OCALL_PRINT_STRING, retbuf, 1024*BUFSIZE, &retval , sizeof(unsigned long));
  return retbuf[0];
}
