
void* malloc(int size) {
  void *p;
  asm("         call lget16     ; set the size value to allocate");
  asm("           dw 0          ; get size from argument stack");           
  asm("         copy ra, rc     ; set size for kernel function");
  asm("         push r7         ; save ESP on stack");
  asm("         load r7, 0      ; set flags to allocate temp non-aligned block");
  asm("         call O_ALLOC    ; call kernel alloc function");
  asm("         pop  r7         ; retore ESP to r7"); 
  asm("         copy rf, ra     ; copy pointer for return value");
  asm("         lbnf al_ok      ; df = 0 means allocated ok");
  asm("         load ra, 0      ; set return ptr to NULL");
  asm("al_ok:   call lset16    ; set pointer value for return");
  asm("           dw -2         ; set local variable on stack");           
  
  return p;
}
