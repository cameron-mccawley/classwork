TITLE Project 4   (program4.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_4        Date : 10 / 25 / 2020
;Description: Displays n number of composite numbers

INCLUDE c:\Irvine\irvine32.inc

MIN_VALUE			equ			1
MAX_VALUE			equ			400

.data
header				BYTE		"Composite Number      Programmed by Cameron McCawley", 0
instructions		BYTE		"Enter the number of composite numbers you would like to see.", 0Ah, 0Dh
					BYTE		"I'll accept orders for up to 400 composites.", 0
prompt				BYTE		"Enter the number of composites to display [1 .. 400]: ", 0
error				BYTE		"Error: Out of range.", 0
goodbye				BYTE		"Results certified by Cameron McCawley.  Goodbye.", 0
space				BYTE		"   ", 0
input				DWORD		?											;Stores inputed number


.code
main PROC

	call	introduction
	call	getUserData
	call	showComposites
	call	farewell

	INVOKE ExitProcess,0
main ENDP




;===============================================
introduction PROC USES edx

;Pre: Nothing
;Post: Introduction and header are printed
;Requires: Variables declared globally
;Registers changed: edx
;Returns: Nothing
;Description: Prints header and instructions
;===============================================

																			;Print header
	mov		edx, OFFSET header
	call	WriteString
	call	CrLF
	call	CrLF
																			;Print instructions
	mov		edx, OFFSET instructions
	call	WriteString
	call	CrLF
	call	CrLF
	ret

introduction ENDP




;===============================================
getUserData PROC USES edx

;Pre: Instructions function called
;Post: User data is stored in input
;Requires: text variables declared
;Registers changed: edx, ebx
;Returns: input
;Description: Gets and validates user input
;===============================================
	
	mov		ebx, 0

	input_top:
		mov		edx, OFFSET prompt
		call	WriteString
		call	ReadInt
		call	validate
		cmp		ebx, 0														;check if input was valid
		je		input_top

		ret
		
getUserData ENDP




;===============================================
validate PROC

;Pre: User input is in EAX
;Post: EBX is changed if input is in range
;Requires:getUserData provides input
;Registers changed: eax, ebx, edx
;Returns: ebx
;Description: Validates that user input is in range
;===============================================

	cmp		eax, MIN_VALUE
	jl		display_error
	cmp		eax, MAX_VALUE
	jg		display_error
	mov		input, eax
	mov		ebx, 1															;input is valid, so change ebx and return
	ret

	display_error:
		mov		edx, OFFSET error
		call	WriteString
		call	CrLF
		ret

validate ENDP




;===============================================
showComposites PROC

;Pre: user input has been obtained
;Post: Composites are printed
;Requires: input to be defined
;Registers changed: eax, ebx, ecx, edx
;Returns: Nothing
;Description: Prints up to and including n composites
;===============================================

	mov		eax, 0
	mov		ebx, 3															;ebx has current number to check, first is 3
	mov		ecx, input														;ecx has number of entries, this will be used for loop
	mov		edx, 0															;line count

	top:
		inc		ebx
		nested_top:
			call	isComposite												;check if the next num is composite
			cmp		eax, 1
			je		composite_found
			inc		ebx
			jmp		nested_top

		composite_found:
			cmp		edx,7													;If 8 nums have printed, add a newline
			jle		print_num
			call	Crlf
			mov		edx, 0													;reset newline count
			
		print_num:
			mov		eax, ebx
			call	WriteDec
			inc		edx
			mov		al, 9h
			call	WriteChar												;print tab character
			loop	top														;dec ecx, jmp to top

	ret

showComposites ENDP




;===============================================
isComposite PROC USES ebx ecx edx

;Pre: ebx has current num
;Post: eax will be 1 or 0 depending on if composite
;Requires: number in ebx
;Registers changed: eax, ebx, edx, edx
;Returns: eax
;Description: Checks if the current number is composite, it does this
;			by dividing it by all numbers up to n, for checking if
;			n is composite
;===============================================

	mov		ecx, ebx
	dec		ecx																;first divisor

	top_comp:
		cmp		ecx, 2
		jl		ret_neg															
		cdq																	;prep for division
		mov		eax, ebx
		div		ecx
		cmp		edx, 0														;check for remainder
		je		ret_pos
		dec		ecx
		jmp		top_comp
																			;Number is not composite
		ret_neg:
			mov		eax, 0
			ret
																			;Number is composite
		ret_pos:
			mov		eax, 1
			ret

isComposite ENDP




;===============================================
farewell PROC

;Pre: Program complete
;Post: Goodbye printed
;Requires:Test segments defined
;Registers changed: edx
;Returns: Nothing
;Description: Says goodbye to the user
;===============================================
	
	call	CrLF
	call	CrLF
	mov		edx, OFFSET goodbye
	call	WriteString
	call	CrLF
	call	CrLF
	ret

farewell ENDP



END main