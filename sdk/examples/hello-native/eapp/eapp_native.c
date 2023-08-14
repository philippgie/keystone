//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "eapp_utils.h"
#include "string.h"
#include "edge_call.h"
#include <syscall.h>

//#define BUFSIZE 118
#define BUFSIZE 144

char* secret_global = "ANother secret secret secret char sequence!!!!";

#define OCALL_PRINT_STRING 1
#define OCALL_SCAN_STRING 2

unsigned long ocall_scan_print_string(char* string, unsigned char retbuf[], unsigned long* retval);

int main(){

  char* secret = "Super ultra duper secret enclave char sequence!!!!";
  unsigned char retbuf[1024*BUFSIZE];
  char secret_target[64];
  unsigned long retval;
  memcpy((char*)secret_target, secret, strlen(secret)+1);
  secret_target[12] = 's';
  ocall_scan_print_string("Hello World", retbuf, &retval);
  (void)secret;

  EAPP_RETURN(0);
}

unsigned long ocall_scan_print_string(char* string, unsigned char retbuf[], unsigned long *retval){
  //unsigned char retbuf[1024*80];
  memset(retbuf, (unsigned char)0x41, 1024*BUFSIZE);
  //ocall(OCALL_PRINT_STRING, string, strlen(string)+1, &retval ,sizeof(unsigned long));
  ocall(OCALL_SCAN_STRING, string, strlen(string)+1, retbuf , 1024* BUFSIZE * sizeof(unsigned char));
  ocall(OCALL_PRINT_STRING, retbuf, 1024*BUFSIZE, &retval , sizeof(unsigned long));
  return retbuf[0];
}
