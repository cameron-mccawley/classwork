TITLE Project 6   (program6.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_6        Date : 11 / 22 / 2020
;Description: gets 8 valid integers from the user and stores the numeric values in an array.
;			  The program then displays the integers,their sum,and their average.


INCLUDE c:\Irvine\irvine32.inc

MAX_INPUT = 8
;--------------------------------------
;Macro that reads input from the console
;--------------------------------------
getString		MACRO	address, length
	push	edx
	push	ecx
	mov		edx, address
	mov		ecx, length
	call	ReadString
	pop		ecx
	pop		edx
ENDM


;--------------------------------------
;Macro that prints a string to the console 
;--------------------------------------
displayString	MACRO	string
	push	edx
	mov		edx, OFFSET	string
	call	WriteString
	pop		edx
ENDM



.data
	header				BYTE	"PROGRAMMING ASSIGNMENT 6: Designing low-level I/O procedures", 10, 13
						BYTE	"Written by: Cameron McCawley", 0
	instructions		BYTE	"Please provide 8 unsigned decimal integers.", 10, 13
						BYTE	"Each number needs to be small enough to fit inside a 32-bit register.", 10, 13
						BYTE	"After you have finished inputting the raw numbers, I will display a list of the", 10, 13
						BYTE	"integers, their sum, and their average value.", 0
	prompt				BYTE	"Please enter an unsigned number: ", 0
	error_msg			BYTE	"ERROR: You did not enter an unsigned number, or your number was too big.", 0
	error_msg_2			BYTE	"Please try again: ", 0

	input				BYTE	300 DUP(0)
	array				DWORD	MAX_INPUT DUP(?)
	temp_arr			DWORD	32 DUP(0)

	sum					DWORD	?
	average				DWORD	?

	comma				BYTE	", ", 0

	entered_display		BYTE	"You entered the following numbers: ", 0
	sum_display			BYTE	"The sum of these numbers is: ", 0
	average_display		BYTE	"The average is: ", 0
	end_msg				BYTE	"Thanks for playing!", 0


	
.code
main PROC
	
	;--------------------------------------
	;Print header and give user instructions on how to use the program
	;--------------------------------------
	displayString header										;Displays header and instructions											
	call	Crlf
	call	Crlf
	displayString instructions
	call	Crlf
	call	Crlf

	mov		edi, OFFSET array									;Set up loop
	mov		ecx, MAX_INPUT
	
	;--------------------------------------
	;Prompt and get the input from the user and store in the array for processing
	;--------------------------------------
	get_input:
		displayString prompt									;Prompt user for input

		push	OFFSET input
		push	SIZEOF input
		call	readVal											;read value and convert to digit

		mov		eax, DWORD PTR input
		mov		[edi], eax
		add		edi, 4											;go to next digit
		loop	get_input										;Get the next input, loop back

	mov		ecx, MAX_INPUT										;Set up for loop to display nums entered
	mov		esi, OFFSET array
	call	Crlf
	displayString entered_display
	mov		ebx, 0

	;--------------------------------------
	;Display the nums entered in by the user in a comma seperated list
	;--------------------------------------
	display_nums:
		mov		eax, [esi]
		add		ebx, eax										;add value to ebx
		
		push	eax
		push	OFFSET temp_arr									
		call	writeVal										;Write the nums entered to the screen

		cmp		ecx, 1											;Check to see if we dont need to put anymore commas
		je		done
		displayString comma										;print out comma and spacing
		add		esi, 4											;go to next element in the array
		loop	display_nums
	
	done:
		call	Crlf

	;--------------------------------------
	;Print sum and calculate the average
	;--------------------------------------
	mov		eax, ebx											;Move sum to the accumulator
	mov		sum, eax											;store sum
	displayString	sum_display
	
	push	sum
	push	OFFSET temp_arr										;display the sum to the screen
	call	writeVal

	call	Crlf
	mov		ebx, MAX_INPUT										;Get the average of the list
	mov		edx, 0												
	div		ebx													;remainder in edx

	push	eax													;save average to the stack
	mov		eax, 2
	mul		edx
	mul		edx
	cmp		edx, ecx											;if you divide X by Yand get "A remainder B",then if 2B>=Y,round up
	pop		eax
	mov		average, eax
	jl		writeNum											;We dont need to round so just go straight to printing num
	inc		eax
	mov		average, eax

	;--------------------------------------
	;Print the average to the screen
	;--------------------------------------
	writeNum:
		displayString average_display							;Display the average to the screen

		push	average
		push	OFFSET temp_arr
		call	writeVal
		call	Crlf
		call	Crlf

	;--------------------------------------
	;Say goodbye to the user and end the program
	;--------------------------------------
	displayString end_msg										;Say goodbye to the user
	call	Crlf
	call	Crlf

	INVOKE ExitProcess,0
main ENDP



;===============================================
;Pre: Nothing
;Post: Values from console are stored in array
;Requires: address of input and length of string are pushed to the stack
;Returns: nothing
;Description: Gets a string of digits from the user, validates user inputs are digits and converts to numeric
;===============================================
readVal PROC
	push	ebp
	mov		ebp, esp
	pushad														;Save all the regs

	getNum:
		mov		edx, [ebp+12]									;get address of input
		mov		ecx, [ebp+8]									;store length of string
		getString edx, ecx
		
		mov		esi, edx										;Set up regs for conversion
		mov		ebx, MAX_INPUT
		cld
		mov		edx, 0
		mov		eax, 0

	load:
		
		lodsb													;load byte from esi to ax
		cmp		ax, 0
		je		endblock
		imul	edx,10
		jc		error
		cmp		ax, 48											;Check that num is ascii num
		jl		error
		cmp		ax, 57
		jg		error
		sub		al, 48											;Subtracting 48 will get us integer
		add		edx, eax
		loop	load


	error:
		displayString error_msg
		call	Crlf
		displayString error_msg_2
		jmp		getNum

	endBlock:
		mov		DWORD PTR input, edx							;save the integer passed in
		popad
		pop		ebp
		ret		8
readVal ENDP



;===============================================
;Pre: Nothing
;Post: number is printed out to the console
;Requires: the number and address to store string are pushed onto the stack
;Returns: nothing
;Description: Converts a numerical value to a string and prints it out to the console
;===============================================
writeVal PROC
	push	ebp
	mov		ebp, esp
	pushad

	mov		eax, [ebp+12]										;int to be converted
	mov		edi, [ebp+8]										;address to store string is in edi
	mov		ebx, 10												;10 will give us smallest digit when dividing
	push	0													;reset

	convert:
		mov		edx, 0
		div		ebx												;divide by 10 to get last digit
		add		edx, 48
		push	edx
		cmp		eax, 0											;null terminator reached?
		jne		convert											;convert next digit

	pop_array:
		pop		[edi]											;pop the nums off of the stack
		mov		eax, [edi]
		inc		edi												;inc counter
		cmp		eax, 0											;has null terminator been reached?
		jne		pop_array
			
	mov		edx, [ebp+8]										;use macro to write string
	displayString temp_arr

	popad
	pop		ebp
	ret		8
writeVal ENDP


END main