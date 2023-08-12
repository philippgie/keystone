//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#include "eapp_utils.h"
#include "string.h"
#include "edge_call.h"
#include <syscall.h>

char* secret_global = "ANother secret secret secret char sequence!!!!";

#define OCALL_PRINT_STRING 1

unsigned long ocall_print_string(char* string);

int main(){

  char* secret = "Super ultra duper secret enclave char sequence!!!!";
  ocall_print_string("Hello World");
  (void)secret;

  EAPP_RETURN(0);
}

unsigned long ocall_print_string(char* string){
  //unsigned char retbuf[1024*80];
  unsigned char retbuf[1024*118];
  //ocall(OCALL_PRINT_STRING, string, strlen(string)+1, &retval ,sizeof(unsigned long));
  ocall(OCALL_PRINT_STRING, string, strlen(string)+1, retbuf , 1024* 118 * sizeof(unsigned char));
  ocall(OCALL_PRINT_STRING, retbuf, 1024*118, retbuf , 1024* 118 * sizeof(unsigned char));
  return retbuf[0];
}
