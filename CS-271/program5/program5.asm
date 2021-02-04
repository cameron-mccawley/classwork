TITLE Project 5   (program5.asm)

;Author: Cameron McCawley
;Course / Project ID : CS271 / Project_5        Date : 11 / 08 / 2020
;Description: Sorts an array of random numbers and finds median and average of it

INCLUDE c:\Irvine\irvine32.inc
INCLUDE	input_output.inc
INCLUDE math.inc


MIN_INPUT				equ					16
MAX_INPUT				equ					256
MIN_RANDOM				equ					64
MAX_RANDOM				equ					1024

NUM_COLUMNS				equ					5

.data
header_title			BYTE				"Sorting Random Integers               Programmed by Cameron McCawley", 0
description				BYTE				"This program generates random numbers in the range [64, 1024], displays ", 13, 10
						BYTE				"the original list, sorts the list, and calculates the median value and the ", 13, 10
						BYTE				"average value. Finally, it displays the list sorted in descending order.", 0
prompt					BYTE				"How many numbers should be generated? [16, 256]: ", 0
error					BYTE				"Error: Out of range!", 0

unsorted				BYTE				"The unsorted random numbers: ", 0
median					BYTE				"The median is: ", 0
average					BYTE				"The average is: ", 0
sorted					BYTE				"The sorted list: ", 0

request					DWORD				?								;Stores number of elements to be generated
array					DWORD				MAX_INPUT	DUP(?)				;the array


.code
main PROC

	push	OFFSET header_title
	push	OFFSET description
	call	introduction													

	push	OFFSET prompt
	push	OFFSET error
	push	OFFSET request
	call	getData

	push	OFFSET array
	push	request
	call	fillArray

	push	OFFSET array
	push	request
	push	OFFSET unsorted
	call	displayList

	push	OFFSET array
	push	request
	call	sortList

	push	OFFSET array
	push	request
	push	OFFSET median
	call	displayMedian

	push	OFFSET array
	push	request
	push	OFFSET average
	call	displayAverage

	push	OFFSET array
	push	request
	push	OFFSET sorted
	call	displayList

	INVOKE ExitProcess,0
main ENDP

END main