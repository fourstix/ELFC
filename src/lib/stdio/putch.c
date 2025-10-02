
int putch(int ch) {  
  asm("         gosub s_lget16    ; get character to send");
  asm("           dw  0           ; from for arg 1 ");         
  asm("         glo  ra           ; ra holds character to send");
  asm("         call  O_TYPE      ; send character to the terminal"); 
  return ch;
}
