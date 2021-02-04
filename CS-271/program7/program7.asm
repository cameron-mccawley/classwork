TITLE Project 7   (program7.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_7        Date : 12 / 06 / 2020
;Description: Quiz the user on thier knowledge on combinatorics.  Uses recursion for calculations to check against user answer


INCLUDE c:\Irvine\irvine32.inc

MAX_N = 12
MIN_N = 3
MIN_R = 1

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
	header				BYTE	"Welcome to the Combinations Calculator", 10, 13
						BYTE	"Implemented by Cameron McCawley", 0
	instructions		BYTE	"I'll give you a combinations problem. You enter your answer, and I'll let you know if you're right.", 0
	
	problem				BYTE	"Problem:", 0
	prompt_n			BYTE	"Number of elements in the set: ", 0
	prompt_r			BYTE	"Number of elements to choose from the set: ", 0
	prompt_answer		BYTE	"How many ways can you choose? ", 0

	prompt_problem		BYTE	"Another problem? (y/n): ", 0

	correct				BYTE	"You are correct!", 0
	incorrect			BYTE	"You need more practice.", 0

	answer_1			BYTE	"There are ", 0
	answer_2			BYTE	" combinations of ", 0
	answer_3			BYTE	" items from a set of ", 0 

	yes					BYTE	"y", 0
	no					BYTE	"n", 0

	goodbye				BYTE	"OK ... goodbye.", 0

	error_msg			BYTE	"ERROR: You did not enter an unsigned number, or your number was too big.", 0
	error_msg_2			BYTE	"Please try again: ", 0

	invalid_res			BYTE	"Invalid response.  Another problem? (y/n): ", 0

	input				BYTE	300 DUP(0)
	temp_arr			DWORD	32 DUP(0)

	r					DWORD	?
	n					DWORD	?
	user_answer			DWORD	?
	result				DWORD	?
	continue_res		BYTE	32 DUP(0)
	

	
.code
main PROC
	call	introduction

	top:
		call	Crlf
		push	OFFSET temp_arr
		push	OFFSET n
		push	OFFSET r
		call	showProblem

		push	SIZEOF user_answer
		push	OFFSET user_answer
		call	getData

		push	n
		push	r
		push	OFFSET result
		call	combinations
			
		push	OFFSET temp_arr
		push	n
		push	r
		push	user_answer
		push	result
		call	showResults
		
		
		displayString prompt_problem						;This code is to prompt the user if they want another problem

		prompt:													
			getString OFFSET continue_res, SIZEOF continue_res	

			mov		esi, OFFSET continue_res				;Set up to compare strings
			mov		edi, OFFSET yes
			cmpsb											;Loop back to top?
			je		top

			mov		esi, OFFSET continue_res				;Set up to compare strings
			mov		edi, OFFSET no
			cmpsb
			je		quit
			jmp		error									;User didnt enter "y" or "n", so show error

		error:
			displayString invalid_res
			jmp		prompt

		quit:
			call	Crlf
			displayString goodbye							;Say goodbye and end the program


	INVOKE ExitProcess,0
main ENDP



;===============================================
;Pre: None
;Post: Header and intstructions are printed on the string
;Requires: nothing
;Returns: nothing
;Description: This uses the displaystring macro to print the header and instructions
;===============================================
introduction PROC
	displayString header									;Print the header
	call	Crlf
	call	Crlf

	displayString instructions								;Print the instructions
	call	Crlf

	ret
introduction ENDP



;===============================================
;Pre: Introduction called
;Post: Problem is displayed
;Requires: a temp_array, address of n, and address of r are pushed onto the stack
;Returns: n and r
;Description: Randomly creates a combinatorics problem within the valid range of numbers
;===============================================
showProblem PROC
	push	ebp
	mov		ebp, esp
	pushad													;Save registers
	
	mov		ebx, [ebp + 12]									;Address of n
	mov		ecx, [ebp + 8]									;Address of r

	call	Randomize										;Set random seed
	mov		eax, MAX_N
	sub		eax, MIN_N
	add		eax, 1

	call	RandomRange										;get a random number in range for n
	add		eax, MIN_N

	mov		[ebx], eax										;save value to n
		
	sub		eax, MIN_R
	add		eax, 1

	call	RandomRange										;get a random number in range for r
	add		eax, MIN_R

	mov		[ecx], eax										;save value to r
	

	displayString problem
	call	Crlf

	displayString prompt_n
	push	[ebx]											;Print randomly generated n
	push	[ebp+16]
	call	WriteVal
	call	Crlf
	
	displayString prompt_r
	push	[ecx]											;Print randomly generated r
	push	[ebp+16]
	call	WriteVal
	call	Crlf

	displayString prompt_answer
	
	popad
	pop		ebp
	ret		12												;Clean up the stack
showProblem ENDP



;===============================================
;Pre: Show problem has been called
;Post: User's answer is stored in user_answer
;Requires: The size of and the address of user_answer are pushed onto the stack
;Returns: Nothing
;Description: Uses readVal proc to get user's answer
;===============================================
getData PROC
	push	ebp
	mov		ebp, esp
	pushad

	push	[ebp + 8]										;Address to store input
	push	[ebp + 12]										;SIZEOF input
	call	readVal

	popad
	pop		ebp
	ret		8
getData ENDP



;===============================================
;Pre: getData has been called
;Post: the correct combinations has been calculated for the problem generated
;Requires: n and r have been generated and are pushed on the stack. Result is pushed on the stack.
;Returns: The answer to nCr
;Description: Uses sub procedure factorial to calculate nCr
;===============================================
combinations PROC
	push	ebp
	mov		ebp, esp
	pushad

	sub		esp, 16											;Make room for locals

	push	[ebp+16]										;Calculate n!
	push	[ebp+8]
	call	factorial

	mov		ebx, [ebp+8]
	mov		eax, [ebx]
	mov		DWORD PTR [ebp-4], eax							;sore n! in local variable

	push	[ebp+12]
	push	[ebp+8]
	call	factorial										;Calculate r!

	mov		ebx,[ebp+8]
	mov		eax,[ebx]
	mov		DWORD PTR[ebp-8],eax							;Store r! in local variable

	mov		eax, [ebp+16]
	mov		ebx, [ebp+12]
	sub		eax, ebx
	cmp		eax, 0											;Check so we dont div by 0

	je		one
	mov		DWORD PTR [ebp-12], eax

	push	[ebp-12]
	push	[ebp+8]
	call	factorial										;Calculate (n-r)!

	mov		ebx, [ebp+8]
	mov		eax, [ebx]
	mov		DWORD PTR [ebp-16], eax							;Store result of (n-r)! in local variable

	mov		eax, [ebp-8]
	mov		ebx, [ebp-16]
	mul		ebx												;Calculate r!(n-r)!

	mov		edx, 0
	mov		ebx, eax
	mov		eax, [ebp-4]
	div		ebx												;Calculate n!/(r!(n-r)!)

	mov		ebx, [ebp+8]
	mov		[ebx], eax										;Store final result
	jmp		done											;jump to end

	one:
		mov		eax, 1
		mov		ebx, [ebp+8]
		mov		[ebx], eax
		mov		eax, [ebx]

	done:
		popad
		add		esp, 16
		pop		ebp
		ret		12

combinations ENDP



;===============================================
;Pre: None
;Post: Factorial is calculated
;Requires: result and number to be calculated are pushed on the stack
;Returns: n!
;Description: Uses recursion to calculate the factorial of a number
;===============================================
factorial PROC
	push	ebp
	mov		ebp, esp
	pushad

	mov		eax, [ebp+12]
	mov		ebx, [ebp+8]
	cmp		eax, 0											;Has base case been met?
	jg		recurse											;Continue to do recursion
	mov		esi, [ebp+8]
	mov		eax, 1
	mov		[esi], eax										;Store result
	jmp		done
	
	recurse:
		dec		eax
		push	eax
		push	ebx
		call	factorial									;Recursion (n-1)

		mov		esi, [ebp+8]
		mov		ebx, [esi]
		mov		eax, [ebp+12]
		mul		ebx											;Multiply return value by base
		mov		[esi], eax									;Store result

	done:
		popad
		pop		ebp
		ret		8
	
factorial ENDP



;===============================================
;Pre: Result has been calculated
;Post: The user is informed if they are correct in their answer
;Requires: We have both user_data and result. temp_arr, n, r, user_data, and result are on stack
;Returns: Nothing
;Description: Tells the user if their answer was correct and then gives them the correct answer.
;===============================================
showResults PROC
	push	ebp
	mov		ebp, esp
	pushad
	
	call	Crlf
	displayString answer_1

	push	[ebp+8]
	push[ebp+24]
	call	writeVal										;print out actual answer

	displayString answer_2
	
	push	[ebp+16]										;print r
	push[ebp+24]
	call	writeVal

	displayString answer_2
	
	push	[ebp+20]
	push[ebp+24]
	call	writeVal										;print n

	mov		eax, [ebp+8]
	cmp		eax, [ebp+12]									;is user_answer == result?
	je		good_job	

	call	Crlf
	displayString incorrect									;Incorrect, so say so
	
	jmp		done
			
	good_job:
		call	Crlf
		displayString correct

	done:
		call	Crlf
		call	Crlf
		popad
		pop		ebp
		ret		20

		
showResults ENDP



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
		mov		ebx, [ebp+12]
		mov		[ebx], edx										;save the integer passed in
		popad
		pop		ebp
		ret		8
readVal ENDP



;===============================================
;Pre: Nothing
;Post: number is printed out to the console
;Requires: the number is pushed onto the stack
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