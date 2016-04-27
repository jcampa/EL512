        TTL     "Automata celular"

******************************************************************
* Project name: Automata Celular
* Author(s): 	Jose de la Campa
* Date: 		20/04/2016
* Description: 	celular automata implementation based on the book
* 		"A new kind of science" by stephen Wolfram
*		for motorola 68HC11 procesor
******************************************************************

******************************************************************
* ASCII character definitions
EOT		EQU		4		;End Of Text
CR      EQU     $0d     ;ASCII Carriage Return
ESC		EQU		$1B		;ESCape
SPACE	EQU		$20		;Blanck space ' '
DOT		EQU		$23		;Black	space '#'

* Constants
N		EQU		127		;size
TRUE	EQU		1 		;true
FALSE	EQU		0 		;false

* BUFFALO monitor routines
OUTA    EQU     $FFB8   ;BUFFALO rtn to output acc A
OUTCRLF	EQU		$FFC4	;output CR-LF (carriage return and line feed)
OUTSTRG	EQU		$FFC7	;string output rtn.
OUTSTRG0	EQU	$FFCA	;same as OUTSTRG, wihout leading CR
INCHAR	EQU		$FFCD	;char input rtn.

* Program constants
VARS	EQU	$100	;where to locate variables
CODE	EQU	$2000	;where to locate code

* Program Variables
	ORG	VARS
mask 	RMB		1 	;Rule mask
aux		RMB		1	;
Rule 	RMB		1 	;Formation rule  
L1		FILL	FALSE,N		;memset with SPACE
L2		FILL	FALSE,N		;memset wiht DOT
sw 		RMB		1 	;flag
i 		RMB		1 	;Iterator
j 		RMB 	1 	;Iterator
******************************************************************

******************************************************************
* CODE SECCTION
        ORG     CODE
		
Main   
		jsr		Init
		jsr 	input
		
		jsr		call_show_line_L1
		jsr		OUTCRLF
		
do
		jsr 	evolve	
		jsr 	INCHAR 		;A = INCHAR()
		cmpa	#ESC		;escape char?
		beq		End_dowhile ;done if so
		jmp 	do
End_dowhile

        swi             	;return to BUFFALO monitor on HC11EVB


Init
		ldaa	#TRUE
		staa	sw
		
		jsr call_clear_line_L1
		jsr call_clear_line_L2
		
		clra 			; A = 0
		ldab	#N		; B = N
		ldx 	#2		; IX = 2
		idiv			; D/IX -> iX; r -> B
		xgdx			; swap (D, IX)
		ldx 	#L1		; x = L1
		abx				; x = L1 + N/2
		ldaa	#TRUE	; A = true
		staa	0,X 	; L1[N/2 + 1] = true
		rts	
		
call_clear_line_L1
		psha				; A
		pshb				; B
		pshx				; X
		pshy				; Y
		
		ldx		#L1
		pshx				;Stack L1
		jsr		clear_line
		ins					;Dealocate V
		ins					;Dealocate V
		
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts
		
call_clear_line_L2
		psha				; A
		pshb				; B
		pshx				; X
		pshy				; Y

		ldx		#L2
		pshx				;Stack L2
		jsr		clear_line
		ins					;Dealocate V
		ins					;Dealocate V
		
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts
		
clear_line		
		psha				; A
		pshb				; B
		pshx				; X
		pshy				; Y
		des 				; i
		tsx
		
* for (int i = 0; i < N_line; ++i)
		ldaa 	#0			;A = i
		staa	0,X 		;i = 0
		ldy 	9,X 		;Y = v
for_clear_line	
		ldaa    0,X    		;A = i
		cmpa    #N    		;i - N
        bge     end_for_clear_line ;>= 0 ? 

		ldaa 	#FALSE 		; A = FALSE
		staa 	0,Y 		; L1[i] = FALSE
		
		iny 				; Y points to the next element
		inc 	0,X			;i++
        jmp     for_clear_line
end_for_clear_line

		ins 			;Dealocate i
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts		
;//*< PILA >*///
;iX->|__i_| 0
;    |_RY_| 1
;    |_RY_| 2
;    |_RX_| 3
;    |_RX_| 4
;    |_RB_| 5
;    |_RA_| 6
;    |_RET| 7
;    |_RET| 8
;    |_*v_| 9
;    |_*v_| 10
		
input
		ldx	  	#GrtMsg
		jsr 	OUTSTRG
		jsr 	Read_rule
		jsr 	OUTCRLF
		ldx 	#Msg1
		jsr 	OUTSTRG
		jsr		show_rule
		jsr 	OUTCRLF
		rts
		
Read_rule
		jsr 	INCHAR 	; Read A
		suba 	#'0'	; A - '0'
		ldab	#10		; B = 10
		mul				; A x 10 -> B
		jsr 	INCHAR	; Read A
		suba	#'0'	; A - '0'
		aba				; A + B -> A
		tab				; A -> B
		ldab	#10		; B = 10
		mul				; A x B -> B
		jsr 	INCHAR	; Read A
		suba	#'0'	; A - '0'
		aba 			; A + B -> A
		staa 	Rule
		rts		
		

evolve	
		ldaa	sw
		cmpa 	#FALSE
		beq		else
		jsr		copy_L1_L2
		jmp 	end_if_evolve
else	jsr		copy_L2_L1

end_if_evolve
	; sw=!sw		
		ldaa 	sw
		eora 	#TRUE 		; Exclusive OR A with memory
		staa 	sw 
		rts
		
copy_L1_L2
		ldx		#L1
		pshx				;Stack L1
		ldx		#L2
		pshx				;Stack L2
		jsr		copy
		ins					;Dealocate L2
		ins					;Dealocate L2
		ins					;Dealocate L1
		ins					;Dealocate L1
		rts

copy_L2_L1
		ldx		#L2
		pshx				;Stack L2
		ldx		#L1
		pshx				;Stack L1
		jsr		copy
		ins					;Dealocate L1
		ins					;Dealocate L1
		ins					;Dealocate L2
		ins					;Dealocate L2
		rts
		
build_mask
		psha
		pshb
		pshx
		pshy 			;
		des 			; local n
		des 			; local i
		tsx
		
		ldaa 	#0 		; A = 0
		staa 	0,X 	; i = 0
		ldaa 	#1 		; A = 0x01
		staa  	1,X 	; n = 1
		
for_build_mask
		ldaa 	0,X 	; A = i
		cmpa 	mask	; i - mask
		beq 	end_for_build_mask

		asl 	1,X 	; n <<= 1

		inc		0,X
		jmp 	for_build_mask
end_for_build_mask

		ldaa 	1,X
		staa 	mask 	; mask = 0x01 << (a[i-2] << 2) + (a[i] << 1) + (a[i + 1])
		ins  			;Dealocate local i
		ins  			;Dealocate local n
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts
;//*< PILA >*///
;iX->|__i_| 0
; 	 |__n_| 1
;	 |_RY_| 2
;    |_RY_| 3
;    |_RX_| 4
;    |_RX_| 5
;    |_RB_| 6
;    |_RA_| 7
;    |_RET| 8
;    |_RET| 9		
		
copy
		psha
		pshb
		pshx
		pshy
		tsx
	; for (int i = 1; i < N_line - 1; ++i)
		ldaa 	#1		; A = 1
		staa	i		; i = 1
		
		;ldaa 	#1		; A = 1
		;staa 	mask	; mask = 1
for_copy
		tsx
		ldaa 	i		; A = i
		cmpa 	#N-1 	; i + 1 - N
		bge		end_for_copy ; >=?
	
	; mask = ((a[i - 1] << 2) + (a[i] << 1) + (a[i + 1]));
		ldab 	i		; B = i
		decb			; B = i - 1
		ldy 	10,X 	; Y = a	
		aby 			; Y = a + i - 1
		ldaa 	0,Y 	; A = a[i - 1]
		asla	 		; 
		asla 			; A = a[i-2] << 2
		iny 			; Y = a + i
		ldab 	0,Y		; B = a[i]
		aslb 	 		; B = a[i] << 1
		aba 			; A = (a[i-2] << 2) + (a[i] << 1)
		iny 			; Y = a + i + i
		ldab 	0,Y 	; A = a[i + 1]
		aba 			; A = (a[i-2] << 2) + (a[i] << 1) + (a[i + 1])
		staa 	mask 	; aux = A = (a[i-2] << 2) + (a[i] << 1) + (a[i + 1])
	
		jsr 	build_mask ;B = 0x01 << (a[i-2] << 2) + (a[i] << 1) + (a[i + 1])
		
		ldy 	8,X 	; Y = b
		ldab 	i		; B = i
		aby				; Y = b + i
		ldaa 	Rule	; A = rule
		anda 	mask 	; A = (rule & mask)
	
	; b[i] = (rule & mask);
		cmpa 	#FALSE 	
		beq 	else_for_copy
		ldaa 	#TRUE
		staa 	0,Y 	; b[i] = false
		jmp 	end_if_for_copy
else_for_copy
		ldaa 	#FALSE
		staa 	0,Y 	; b[i] = false
end_if_for_copy
		inc 	i 		; i++
		jmp for_copy
		
end_for_copy
		tsx
		ldx		8,X			; X = b 
		pshx				; Stack b
		jsr		show_line	; show(b)
		ins					;Dealocate b
		ins					;Dealocate b
		
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts		
;//*< PILA >*///
;iX->|_RY_| 0
;    |_RY_| 1
;    |_RX_| 2
;    |_RX_| 3
;    |_RB_| 4
;    |_RA_| 5
;    |_RET| 6
;    |_RET| 7
;    |_*b_| 8
;    |_*b_| 9
;    |_*a_| 10
;    |_*a_| 11
	
		
		
call_show_line_L1
		ldx		#L1
		pshx				;Stack L1
		jsr		show_line
		ins					;Dealocate V
		ins					;Dealocate V
		rts
		
call_show_line_L2
		ldx		#L2
		pshx				;Stack L2
		jsr		show_line
		ins					;Dealocate V
		ins					;Dealocate V
		rts
		
show_line		
		;jsr 	OUTCRLF
		psha
		pshb
		pshx
		pshy
		des 				;i
		tsx
* for (int i = 0; i < N_line; ++i)
		ldaa 	#0			;A = i
		staa	0,X 		;i = 0
for_show_line	
		ldaa    0,X    		;A = i
		cmpa    #N    		;i - N
        bge     end_for_show_line ;>= 0 ? 
 ;cout << v[i];
		pshx
		ldab 	0,X 		;B = i
		ldx 	9,X 		;X = L1 
		abx 				;X = L1 + i
		ldaa 	0,X 		;A = L1[i]
		
		cmpa 	#TRUE
		beq 	else_for_show_line
		ldaa 	#SPACE
		jsr 	OUTA
		jmp 	end_if_for_show_line
else_for_show_line
		ldaa 	#DOT
		jsr 	OUTA
end_if_for_show_line

		pulx
;//-----
		inc 	0,X			;i++
        jmp     for_show_line
end_for_show_line
*end loop for
		
		ins 			;Dealocate i
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts		
;//*< PILA >*///
;iX->|__i_| 0
;    |_RY_| 1
;    |_RY_| 2
;    |_RX_| 3
;    |_RX_| 4
;    |_RB_| 5
;    |_RA_| 6
;    |_RET| 7
;    |_RET| 8
;    |_*v_| 9
;    |_*v_| 10


show_aux	
		ldaa	aux
		psha				;Stack mask
		jsr		Show_3d_number
		ins					;Dealocate mask
		rts
		
show_mask	
		ldaa	mask
		psha				;Stack mask
		jsr		Show_3d_number
		ins					;Dealocate mask
		rts
		
show_i	
		ldaa	i
		psha				;Stack i
		jsr		Show_3d_number
		ins					;Dealocate i
		rts
		
show_rule	
		ldaa	Rule
		psha				;Stack Rule
		jsr		Show_3d_number
		ins					;Dealocate Rule
		rts

Show_3d_number
		psha			;stack A
		pshb			;stack B
		pshx			;stack X
		pshy			;stack Y
		tsx				;X points to the top of the stack
		
		clra 			; A = 0
		ldab	8,X		; B = Rule
		ldx 	#100	; IX = 100
		idiv			; D/IX -> iX; r -> B
		xgdx			; swap D, IX
		tba				; B -> A
		adda	#'0'	; A += '0'
		jsr 	OUTA	; first digit
		suba 	#'0'	; 
		ldab 	#100	; B = 100
		mul 			; B = A * B
		stab 	aux 	; aux = F00
		
		tsx
		clra 			; A = 0
		ldab	8,X		; B = Rule
		subb 	aux 	; B = Rule - aux
		ldx 	#10		; IX = 10
		idiv			; D/IX -> iX; r -> B
		xgdx			; swap D, IX
		tba				; B -> A
		adda	#'0'	; A += '0'
		jsr 	OUTA	; Second digit
		suba 	#'0'	;
		ldab 	#10		; B = 10
		mul 			; B = A * B = 0S0
		addb 	aux		; B = FS0
		stab 	aux 	; aux = FS0
		
		tsx
		ldaa	8,x		; A = Rule
		suba 	aux 	; A = Rule - FS0
		adda	#'0'	; A += '0'
		jsr 	OUTA	; Third digit		
		
		puly			;Dealocate Y
		pulx			;Dealocate X
		pulb			;Dealocate B
		pula			;Dealocate A
		rts
;//*< PILA >*///
;iX->|_RY_| 0
;    |_RY_| 1
;    |_RX_| 2
;    |_RX_| 3
;    |_RB_| 4
;    |_RA_| 5
;    |_RET| 6
;    |_RET| 7
;    |__n_| 8

******************************************************************

******************************************************************
* program output messages

GrtMsg	FCB	"Rule#: ",EOT
Msg1	FCB	"The rule you have chosen is: ",EOT
Msgmask	FCB	"mask: ",EOT
Msg_i	FCB	"i: ",EOT
Msg_aux FCB	"aux: ",EOT
Msg_L1 FCB	"L1: ",EOT
Msg_L2 FCB	"L2: ",EOT
;Msg2	FCB	"The string you entered was: ",EOT
;ByeMsg	FCB	CR,"End program",EOT
******************************************************************
; end of assembly source code
        END
		
