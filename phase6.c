#include <stdio.h>

struct Node {
    int value;
    int index;
    struct Node *next;
};


void read_six_numbers(char *argv,int param_2){
  int i;
  
  i = sscanf(argv,"%d %d %d %d %d %d",
                 param_2,
                 param_2 + 4,
                 param_2 + 8,
                 param_2 + 12,
                 param_2 + 16,
                 param_2 + 20);
  if (i < 6) {
     printf("booooom !!!!!\n");
  }
  return;



void phase_6(int *param_1)
{
  int *piVar1;
  int j;
  int *tab_int;
  int i;
  Node *list;
  int *local_34 [6];
  int input [6];
  
  list = node1;
  read_six_numbers(param_1,input);
  i = 0;
  do {
    j = i;
    if (5 < input[i] - 1U) {
      printf("BOOM    1!!!!!!!\n)"
    }
    while (j = j + 1, j < 6) {
      if (input[i] == input[j]) {
        printf("BOOM!!!!!!!       2\n)"
      }
    }
    i = i + 1;
  } while (i < 6);
  i = 0;
  do {
    j = 1;
    tab_int = (int *)list;
    if (1 < input[i]) {
      do {
        tab_int = (int *)tab_int[2];
        j = j + 1;
      } while (j < input[i]);
    }
    local_34[i] = tab_int;
    i = i + 1;
  } while (i < 6);
  i = 1;
  tab_int = local_34[0];
  do {
    piVar1 = local_34[i];
    tab_int[2] = (int)piVar1;
    i = i + 1;
    tab_int = piVar1;
  } while (i < 6);
  piVar1[2] = 0;
  i = 0;
  do {
    if (*local_34[0] < *(int *)local_34[0][2]) {
      printf("BOOM!!!!!!! 3\n)"
    }
    local_34[0] = (int *)local_34[0][2];
    i = i + 1;
  } while (i < 5);
  return;
}


/*
                        node6                                           XREF[1]:     Entry Point(*)  
0804b230 b0 01 00        undefine
         00 06 00 
         00 00 00 
                        node5                                           XREF[1]:     Entry Point(*)  
0804b23c d4 00 00        undefine
         00 05 00 
         00 00 30 
                        node4                                           XREF[1]:     Entry Point(*)  
0804b248 e5 03 00        undefine
         00 04 00 
         00 00 3c 
                        node3                                           XREF[2]:     Entry Point(*), 0804b268(*)  
0804b254 2d 01 00        undefine
         00 03 00 
         00 00 48 
    0804b254 2d              undefined12Dh                     [0]                               XREF[2]:     Entry Point(*), 0804b268(*)  
    0804b255 01              undefined101h                     [1]
    0804b256 00              undefined100h                     [2]
    0804b257 00              undefined100h                     [3]
    0804b258 03              undefined103h                     [4]
    0804b259 00              undefined100h                     [5]
    0804b25a 00              undefined100h                     [6]
    0804b25b 00              undefined100h                     [7]
    0804b25c 48              undefined148h                     [8]           ?  ->  0804b248
    0804b25d b2              undefined1B2h                     [9]
    0804b25e 04              undefined104h                     [10]
    0804b25f 08              undefined108h                     [11]
                        node2                                           XREF[5]:     Entry Point(*), 
                                                                                    phase_6:08048e3b(*), 
                                                                                    phase_6:08048e47(*), 
                                                                                    phase_6:08048e6c(*), 
                                                                                    phase_6:08048e73(R)  
0804b260 d5 02 00 00     undefined4 000002D5h
0804b264 02              ??         02h
0804b265 00              ??         00h
0804b266 00              ??         00h
0804b267 00              ??         00h
                        PTR_node3_0804b268                              XREF[4]:     phase_6:08048e30(R), 
                                                                                    phase_6:08048e55(W), 
                                                                                    phase_6:08048e70(R), 
                                                                                    phase_6:08048e7e(R)  
0804b268 54 b2 04 08     addr       node3
                        node1[8]                                        XREF[4,1]:   Entry Point(*), 
                        node1                                                        phase_6:08048da4(*), 
                                                                                    phase_6:08048e29(*), 
                                                                                    phase_6:08048e3b(*), 
                                                                                    phase_6:08048e30(R)  
0804b26c fd 00 00        undefine
            00 01 00 
            00 00 60 
    0804b26c fd              undefined1FDh                     [0]                               XREF[4]:     Entry Point(*), 
                                                                                                                phase_6:08048da4(*), 
                                                                                                                phase_6:08048e29(*), 
                                                                                                                phase_6:08048e3b(*)  
    0804b26d 00              undefined100h                     [1]
    0804b26e 00              undefined100h                     [2]
    0804b26f 00              undefined100h                     [3]
    0804b270 01              undefined101h                     [4]
    0804b271 00              undefined100h                     [5]
    0804b272 00              undefined100h                     [6]
    0804b273 00              undefined100h                     [7]
    0804b274 60              undefined160h                     [8]           ?  ->  0804b260     XREF[1]:     phase_6:08048e30(R)  
    0804b275 b2              undefined1B2h                     [9]
    0804b276 04              undefined104h                     [10]
    0804b277 08              undefined108h                     [11]

    node1 {
    fd 00 00  00000fd  =  253
   00 01 00 =   1
   00 00 60 =   next
    }
   node2 {
    d5 02 00 00     undefined4 000002D5h   = 725
    02 
    00
   }
    node3 {
        2d 01 00        12d = 301
        00 03 00 
        00 00 48
   }
  node4 {
        e5 03 00  ---> 3e5 = 997
        00 04 00
        00 00 3c
    }
    node5{
        d4 00 00 ----> d4 = 212
        00 05 00
        00 00 30
    }
    node6{
        b0 01 00 ----> 1b0 = 432
        00 06 00
        00 00 00
    }
*/