
int getch(void) {
  int ch;
  
  asm("         call  o_readkey     ; read a character from input");
  asm("         plo ra              ; save in return register");
  asm("         ldi 0               ; pad register with zero");
  asm("         phi ra              ");
  asm("         call lset16         ; set the local variable"); 
  asm("           dw -2             ; with the return value");

  return ch;
}
