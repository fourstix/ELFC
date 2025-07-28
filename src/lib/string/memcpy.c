
 void *memcpy(void *d, void *s, int n) {
 if (d && s) {
	 asm("         call lget16     ; set the destination pointer");
	 asm("           dw 0          ; from argument stack");      
	 asm("         copy ra, rd     ; put destination pointer into rd");        
	 asm("         call lget16     ; set the source pointer");
	 asm("           dw 2          ; from argument stack");             
	 asm("         copy ra, rf     ; put source pointer into rf"); 
	 asm("         call lget16     ; set the counter");
	 asm("           dw 4          ; from argument stack");      
	 asm("         copy ra, rc     ; put counter into rc");        
	 asm("         call f_memcpy   ; call bios strcpy function");
 }
 return d;
}
/*
void *memcpy(void *d, void *s, int n) {
	char	*p;

	p = d;
	while (n--) *p++ = *(char *)s++;
	return d;
}
*/
