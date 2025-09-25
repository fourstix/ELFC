


int strlen(char *s) {
	int len = 0;
	if (s) {
		asm("         gosub s_lget16  ; set the string pointer");
		asm("           dw 0          ; from argument stack");             
	  asm("         copy ra, rf     ; put source pointer into rf");
		asm("         ldi  0          ; clear counter");
		asm("         phi  rc         ; clear hi byte");
		asm("         plo  rc         ; clear lo byte");
    asm("loop:    lda  rf         ; get byte from string");
		asm("         lbz  done       ; jump if terminator found");
		asm("         inc  rc         ; increment count");
		asm("         lbr  loop       ; and keep looking for terminator");
    asm("done:    copy rc, ra     ; move count to return variable");
		asm("         gosub s_lset16  ; set the return value");
		asm("           dw -2         ; in the argument stack"); 
	}
	/*
	char	*p;

	for (p = s; *p; p++)
		;
	return p - s;
	*/
	return len;
}
