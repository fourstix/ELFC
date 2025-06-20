
#ifndef _STDLIB_
#define _STDLIB_
#pragma .link .library stdlib.lib
#pragma             extrn Cabort
#pragma             extrn Cabs
#pragma             extrn Cexit            


#ifndef EOF
#define  EOF  (-1)
#endif 

#ifndef NULL
#define  NULL (void*)0
#endif 


void abort(void);
int abs(int n);
void exit(int n);

#endif
