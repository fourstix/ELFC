
void *memset(void *p, int c, int n) {
	if (p) {
		asm("         call lget16     ; set the destination pointer");
		asm("           dw 0          ; from argument stack");      
		asm("         copy ra, rd     ; put destination pointer into rd");        
		asm("         call lget16     ; set the source pointer");
		asm("           dw 2          ; from argument stack");             
		asm("         copy ra, rf     ; put character into rf"); 
		asm("         call lget16     ; set the counter");
		asm("           dw 4          ; from argument stack");      
		asm("         copy ra, rc     ; put counter into rc");        
		asm("loop:    glo  rc         ; get low count byte");
		asm("         lbnz memset     ; jump if not zero");
		asm("         ghi  rc         ; get high count byte");
		asm("         lbz  done       ; return if zero");
		asm("memset:  glo  rf         ; get character from source");
		asm("         str  rd         ; store into destination");
		asm("         inc  rd         ; point to next destination position");
		asm("         dec  rc         ; decrement count");
		asm("         lbr  loop     ; and continue setting memory");
		asm("done:    adi  0          ; clear DF for return"); 				 
	}
	return p;
}

/*
void *memset(void *p, int c, int n) {
	char	*q;

	q = p;
	while (n--) *(char *)p++ = c;
	return q;
}
*/
