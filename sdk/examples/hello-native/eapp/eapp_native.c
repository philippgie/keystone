//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "eapp_utils.h"
#include "string.h"
#include "edge_call.h"
#include <syscall.h>

//#define BUFSIZE 118
#define BUFSIZE 1024 * 154

char* s = "random string";

#define OCALL_PRINT_STRING 1
#define OCALL_SCAN_STRING 2

unsigned long ocall_scan_data(char* string, unsigned char retbuf[], size_t retbuflen);
unsigned long ocall_print_data(unsigned char buf[], size_t buflen);

int main(){

  //char* secret = "Super ultra duper secret enclave char sequence!!!!";
  char* secret = "\x12\x34\x31\x24\x33\x61\x22\x2e\x2f\x27\x28\x25\x24\x2f\x35\x28\x20\x2d\x61\x24\x2f\x22\x2d\x20\x37\x24\x61\x32\x24\x22\x33\x24\x35\x60\x60\x60";
  unsigned char retbuf[BUFSIZE];
  memset(retbuf, (unsigned char)0x41, BUFSIZE);
  char secret_target[64];
  for (size_t i = 0; i < strlen(secret); i++)
  {
    secret_target[i] = secret[i] ^ 'A';
  }
  
  ocall_scan_data("Input data:\n", retbuf, BUFSIZE);
  ocall_print_data(retbuf, BUFSIZE);
  (void)secret_target;

  EAPP_RETURN(0);
}

unsigned long ocall_scan_data(char* string, unsigned char retbuf[], size_t retbuflen){
  ocall(OCALL_SCAN_STRING, string, strlen(string)+1, retbuf , retbuflen);
  return retbuf[0];
}

unsigned long ocall_print_data(unsigned char buf[], size_t buflen){
  unsigned long retval;
  ocall(OCALL_PRINT_STRING, buf, buflen, &retval , sizeof(unsigned long));
  return retval;
}
