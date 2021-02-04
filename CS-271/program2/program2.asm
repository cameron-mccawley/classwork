TITLE Project 2   (program2.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_2        Date : 10 / 11 / 2020
;Description: Write a program to calculate Fibonacci numbers.

INCLUDE c:\Irvine\irvine32.inc

UPPER_LIMIT		equ		46
LOWER_LIMIT		equ		1
MAX_NAME_LENGTH	equ		36

.data
fibnum_1		DWORD	1
fibnum_2		DWORD	1

header_1		BYTE	"Fibonacci Numbers",0
header_2		BYTE	"Programmed by Cameron McCawley",0
prompt_name		BYTE	"What's your name? ",0
prompt_num		BYTE	"How many Fibonacci terms do you want? ",0
hello			BYTE	"Hello, ",0
instructions	BYTE	"Enter the number of Fibonacci terms to be displayed... It should be an integer in the range [1, 46]...",0
out_of_range	BYTE	"Out of range. ",0
goodbye			BYTE	"Goodbye, ",0
nice_day		BYTE	"Have a nice day!",0
space			BYTE	"         ",0
period			BYTE	".",0

username		BYTE	MAX_NAME_LENGTH+1 DUP (? )	;Stores username
num_terms		SDWORD	?							;Stores number of terms user picked
nl_counter		DWORD	0							;dertermines when newline should be inserted

.code
main PROC

;Print the header information
mov		edx,OFFSET header_1
call	WriteString
call	Crlf
mov		edx,OFFSET header_2
call	WriteString
call	Crlf
call	Crlf

;Prompt for username
mov		edx,OFFSET prompt_name
call	WriteString

;Get username from user
mov		edx,OFFSET username
mov		ecx,MAX_NAME_LENGTH				;buffer size - 1
call	ReadString

;say hello and give instructions to user
mov		edx,OFFSET hello
call	WriteString
mov		edx,OFFSET username
call	WriteString
mov		edx,OFFSET period
call	WriteString
call	Crlf
mov		edx,OFFSET instructions
call	WriteString
call	Crlf

;get number of terms in Fib sequence[1-46]
;jump to error if not in range
get_terms_top:
	mov		edx,OFFSET prompt_num
	call	WriteString
	call	ReadInt
	mov		num_terms,eax
	call	Crlf
	cmp		eax, UPPER_LIMIT
	jg		error
	cmp		eax, LOWER_LIMIT
	jl		error
	jmp		set_up_fib

;Displays error and loops back to get_terms_top
error:
	mov		edx,OFFSET out_of_range
	call	WriteString
	call	Crlf
	jmp		get_terms_top

;set up registers for the fib algorithm and display the starting values
set_up_fib:
	call	Crlf
	mov		nl_counter,0				;set new line counter to 0
	mov		ecx,num_terms				;move number of iterations into loop counter
	mov		edx, OFFSET space			;saving for future use
	mov		eax,fibnum_1
	call	WriteDec
	call	WriteString
	dec		ecx
	cmp		ecx,0
	je		ending

;Main algorithm for fib sequence
;output is already "1     " for first round
fib_algorithm_loop:
	mov		eax,fibnum_1
	mov		ebx,fibnum_2
	xchg	eax,ebx						;switches regs so now eax has higher num
	add		ebx,eax						;adds them together
	mov		fibnum_1,eax
	mov		fibnum_2,ebx
	inc		nl_counter					;update newline count
	cmp		nl_counter,4
	je		add_newline
	jmp		print

;adds a newline to display and resets count
add_newline:
	call	Crlf
	mov		nl_counter,0				;reset counter

;prints fib term and space
print:		
	call	WriteDec					;prints term
	call	WriteString					;prints space
	loop	fib_algorithm_loop			;loops back to start of alg

;says goodbye to the user :)
ending:
	call	Crlf
	call	Crlf
	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET username
	call	WriteString
	mov		edx, OFFSET period
	call	WriteString
	call	Crlf
	mov		edx, OFFSET nice_day
	call	WriteString

INVOKE ExitProcess,0
main ENDP
END main