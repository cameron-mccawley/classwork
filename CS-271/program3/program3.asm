TITLE Project 3   (program3.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_3        Date : 10 / 18 / 2020
;Description: Average calculator

INCLUDE c:\Irvine\irvine32.inc

UPPER_LIMIT		equ		-1
LOWER_LIMIT		equ		-100
MAX_NAME_LENGTH	equ		64

.data

header_1		BYTE	"Assignment 3 (program3.asm)",0
header_2		BYTE	"Welcome to the Integer Accumulator by Cameron McCawley",0
prompt_name		BYTE	"What is your name? ",0
hello			BYTE	"Hello, ",0
instructions_1	BYTE	"Please enter numbers in [-100, -1].",0
instructions_2	BYTE	"Enter a non-negative number when you are finished to see results.",0
prompt_num		BYTE	"Enter number: ",0
entered_1		BYTE	"You entered ",0
entered_2		BYTE	" valid numbers.",0
sum_string		BYTE	"The sum of your valid numbers is ",0
round_string	BYTE	"The rounded average is ",0
goodbye			BYTE	"Thank you for playing Integer Accumulator! It's been a pleasure to meet you, ",0
error_message	BYTE	"Error: Not in range",0 
no_input		BYTE	"Error: Did not input any numbers", 0

username		BYTE	MAX_NAME_LENGTH+1 DUP (? )	;Stores username
sum				SDWORD	0
num_count		DWORD	0



.code
main PROC

;print headers
mov		edx,OFFSET header_1
call	WriteString
call	Crlf
mov		edx,OFFSET header_2
call	WriteString
call	Crlf
call	Crlf

;get username
mov		edx,OFFSET prompt_name
call	WriteString
mov		edx,OFFSET username
mov		ecx,MAX_NAME_LENGTH
call	ReadString
call	Crlf

;say hello
mov		edx,OFFSET hello
call	WriteString
mov		edx,OFFSET username
call	WriteString
call	Crlf
call	Crlf

;give instructions
mov		edx,OFFSET instructions_1
call	WriteString
call	Crlf
mov		edx,OFFSET instructions_2
call	WriteString
call	Crlf

;gets numbers from user, if out of range, reprompt for input
get_numbers:
	mov		edx,OFFSET prompt_num
	call	WriteString
	call	ReadInt						;read user input into eax
	call	Crlf
	cmp		eax,LOWER_LIMIT
	jl		error
	cmp		eax,UPPER_LIMIT
	jg		calculate

	;add input to sum
	mov		ebx,eax
	mov		eax,sum
	add		eax,ebx
	mov		sum,eax
	inc		num_count					;increment number of valid inputs entered
	jmp		get_numbers

;called when user doesnt enter any numbers to calculate, prints special message
display_no_input:
	mov		edx, OFFSET no_input
	call	WriteString
	jmp		ending

;Display error and jump back up to get_numbers section to reprompt
error:
	mov		edx,OFFSET error_message
	call	WriteString
	call	Crlf
	call	Crlf
	jmp		get_numbers

;do all of the average calculations as well as print the results to the screen
calculate:
	cmp		num_count, 0
	jz		display_no_input
	mov		edx,OFFSET entered_1
	call	WriteString
	mov		eax,num_count
	call	WriteDec
	mov		edx,OFFSET entered_2
	call	WriteString
	call	Crlf

	;print sum of numbers
	mov		edx,OFFSET sum_string
	call	WriteString
	mov		eax,sum
	call	WriteInt
	call	Crlf

	;divisionand printing it out
	mov		eax,num_count
	cmp		eax,0
	je		ending
	mov		eax,sum
	cdq										;Prep for div instruction
	mov		ebx,num_count
	neg		eax
	div		ebx								;result stored in eax
	push	eax								;save result on the stack
	mov		eax, 2
	mul		edx								;if you divide X by Y and get "A remainder B", then if 2B>=Y, round up
	cmp		edx, num_count					
	jl		write_round
	pop		eax								;restore eax register
	dec		eax

;Prints the rounded average to the screen
write_round:
	neg		eax
	mov		edx,OFFSET round_string			;overwrites remainder,but thats ok
	call	WriteString
	call	WriteInt

;says goodbye to the user
ending:
	call	Crlf
	mov		edx, OFFSET goodbye
	call	WriteString
	mov		edx, OFFSET username
	call	WriteString
	call	Crlf
	call	Crlf



INVOKE ExitProcess,0
main ENDP
END main