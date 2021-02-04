
INCLUDE c:\Irvine\irvine32.inc
INCLUDE	input_output.inc

MIN_INPUT				equ					16
MAX_INPUT				equ					256
MIN_RANDOM				equ					64
MAX_RANDOM				equ					1024

NUM_COLUMNS				equ					5

.code

;===============================================
;Pre: Nothing
;Post: Introduction and headers are printed
;Requires: title and desctiption are pushed on the stack
;Registers changed: edx
;Stack (In order pushed):
;	OFFSET header_title
;	OFFSET introduction
;Returns: nothing
;Description: Prints to the screen the title of the program
;			  and the introduction.
;===============================================
introduction PROC

	push	ebp								
	mov		ebp, esp

	mov		edx, [ebp + 12]													;move header string to be printed
	call	WriteString
	call	Crlf
	call	Crlf

	mov		edx, [ebp + 8]													;move description to be printed
	call	WriteString
	call	Crlf
	call	Crlf

	pop		ebp
	ret		8
introduction ENDP



;===============================================
;Pre: Introduction has been printed
;Post: length of array is requested
;Requires: prompt, error message, and result on the stack
;Registers changed: edx, ebx, eax
;Stack (In order pushed):
;	OFFSET prompt
;	OFFSET error
;	OFFSET request
;Returns: Length of array to be generated
;Description: Prompts the user for length of array to be
;			  generated and handles any errors
;===============================================
getData PROC
	push	ebp
	mov		ebp, esp

	mov		ebx, [ebp + 8]													;user input var is in ebx

	top:
		mov		edx, [ebp + 16]												;Print out the prompt for input
		call	WriteString
		call	ReadInt
		cmp		eax, MIN_INPUT												;Validate input is within range
		jl		display_error
		cmp		eax, MAX_INPUT
		jg		display_error

		mov		[ebx], eax													;input is valid, so store it
		pop		ebp
		ret		12

	display_error:
		call	Crlf
		mov		edx, [ebp + 12]												;Print error on screen and reprompt for input
		call	WriteString
		call	Crlf
		jmp		top

getData ENDP



;===============================================
;Pre: Array was sorted
;Post: Median is displayed on screen
;Requires: Array is sorted and array, request, and median text is on the stack
;Registers changed: edx, eax, ebx
;Stack (In order pushed):
;	OFFSET array
;	request
;	OFFSET displayMedian
;Returns: The median of the array
;Description: This takes the sorted array and finds its median, 
;			  If the length is even, it will take the address of the middle two
;===============================================
displayMedian PROC
	
	push	ebp
	mov		ebp, esp

	mov		edx, [ebp+8]													;print out median title
	call	Crlf
	call	Crlf
	call	WriteString

	mov		esi, [ebp + 16]													;Get first element of arrray
	mov		eax, [ebp + 12]													;get length of array
	mov		edx, 0

	mov		ebx, 2
	div		ebx
	cmp		edx, 0															;Is the length of the array even?
	je		getMedian

	mov		ebx, 4															;Find the halfway point, since length is odd
	mul		ebx
	add		esi, eax
	mov		eax, [esi]

	jmp		print

	getMedian:
		mov		ebx, 4														;Get higher number in array
		mul		ebx
		add		esi, eax
		mov		edx, [esi]

		mov		eax, esi													;Get lower num in array
		sub		eax, 4
		mov		esi, eax
		mov		eax, [esi]

		add		eax, edx													;Get average of low and high
		mov		edx, 0
		mov		ebx, 2
		div		ebx

	print:
		call	WriteDec
		call	Crlf
		call	Crlf

	pop		ebp
	ret		12
displayMedian ENDP



;===============================================
;Pre: Median was displayed
;Post: Average is displayed
;Requires: Array to be sorted and array, request, and average text on stack
;Registers changed: eax, ecx, edx
;Stack (In order pushed):
;	OFFSET array
;	request
;	OFFSET displayAverage
;Returns: The average of the array
;Description: Finds the average of the array list, rounds up to nearest integer
;===============================================
displayAverage PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 4															;this will hold the sum of our elements
	
	mov		DWORD PTR [ebp-4], 0
	mov		eax, [ebp-4]
	mov		esi, [ebp+16]													;store location of array
	mov		ecx, [ebp+12]													;set counter to length of array
				
	mov		edx, [ebp+8]													;write average title
	call	WriteString

	top:
		add		eax, [esi]									
		add		esi, 4														;add up all the numbers
		loop	top
	
	mov		edx, 0
	cdq
	mov		ecx, [ebp+12]
	div		ecx																;divide sum by length of array
	
	push	eax																;save average to the stack
	mov		eax, 2
	mul		edx
	mul		edx
	cmp		edx, ecx														;if you divide X by Yand get "A remainder B",then if 2B>=Y,round up
	pop		eax
	jl		write_num														
	inc		eax																;Rounds number up!

	write_num:
		call	WriteDec													;print the number
		call	Crlf

	mov		esp, ebp
	pop		ebp
	ret
displayAverage ENDP



;===============================================
;Pre: Array is filled
;Post: current contents of array are printed
;Requires: Array to be filled
;Registers changed: ebx, ecx, edx
;Stack (In order pushed):
;	OFFSET array
;	request
;	OFFSET title
;Returns: nothing
;Description: Displays the current contents of the array to the screen
;===============================================
displayList PROC
	push	ebp
	mov		ebp, esp

	mov		ebx, 0
	mov		esi, [ebp + 16]												;Get pointer to array
	mov		ecx, [ebp + 12]												;get number of elements to display
	mov		edx, [ebp + 8]												;Print out the title of the display
	
	call	Crlf
	call	WriteString
	call	Crlf
	top:
		cmp		ebx, NUM_COLUMNS										;Check to see if we need to create a new line
		jge		print_newline
		inc		ebx
		mov		eax, [esi]
		call	WriteDec
		add		esi, 4													;Move to next elem in array
		mov		al,9h
		call	WriteChar												;print tab character
		loop	top														;dec ecx,jmp to top

		pop		ebp
		ret		10

	print_newline:
		call	Crlf
		mov		ebx, 0													;create new row
		jmp		top
	
displayList ENDP


END