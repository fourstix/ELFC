
int putch(int ch) {  
  asm("         call  lget16      ; get character to send");
  asm("           dw  0           ; from for arg 1 ");         
  asm("         glo  ra           ; ra holds character to send");
  asm("         call  o_type      ; send character to the terminal"); 
  return ch;
}
