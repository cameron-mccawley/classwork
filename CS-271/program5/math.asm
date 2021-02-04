INCLUDE c:\Irvine\irvine32.inc
INCLUDE	math.inc

MIN_RANDOM				equ					64
MAX_RANDOM				equ					1024


.code

;===============================================
;Pre: Empty array
;Post: Filled array with random numbers
;Requires: User to specify number of elements, array and request are pushed on the stack
;Registers changed: esi, ecx, eax
;Stack (In order pushed):
;	OFFSET array
;	request
;Returns: n sized array filled with random numbers
;Description: Fills an array of user specified length 
;			  with random numbers between a certain range
;===============================================
fillArray PROC
	push	ebp
	mov		ebp, esp
	
	mov		esi, [ebp+12]													;Move array into esi
	mov		ecx, [ebp+8]													;number of elements to be in the array

	call	Randomize														;Set random seed (Irvine)
	top:
		mov		eax, MAX_RANDOM
		sub		eax, MIN_RANDOM
		add		eax, 1

		call	RandomRange													;Get a random number within range
		add		eax,MIN_RANDOM
		mov		[esi], eax													;Insert rand num in array
		add		esi, 4														;Move to the next element of array
		loop	top

	pop		ebp
	ret		8
fillArray ENDP


;===============================================
;Pre: Unsorted array
;Post: Sorted array
;Requires: Array var to be filled with random numbers, array and request are pushed on the stack
;Registers changed: ecx, eax, esi
;Stack (In order pushed):
;	OFFSET array
;	request
;Returns: Sorted array in descending order
;Description: Uses bubble sort to sort an array in 
;			  descending order
;===============================================
sortList PROC
	
	push	ebp
	mov		ebp, esp

	mov		ecx, [ebp+8]													;Move counter into ecx
	dec		ecx

	L1:
		push	ecx
		mov		esi, [ebp + 12]												;get first element of array

		L2:
			mov		eax, [esi]	
			cmp		[esi + 4], eax											;Do we need to swap?
			jl		L3
			xchg	eax, [esi+4]											;swaps adjacent elements
			mov		[esi], eax
		L3:
			add		esi, 4													;Go to next element in array
			loop	L2	

		pop		ecx
		loop	L1
		
		pop		ebp
		ret		8
sortList ENDP

END