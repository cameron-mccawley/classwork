TITLE Project
INCLUDE	c:\Irvine\irvine32.inc

.data
k SDWORD 10
n SDWORD 12
yes BYTE "Yes", 0
no BYTE "no", 0
maybe BYTE "maybe", 0

.code
main PROC

;----------------------------------------
;Q2
mov		eax, k
mov		ebx, n
mov		edx, OFFSET yes
top_1:
cmp		eax, ebx
jg		endBlock
call	WriteString
add		eax, 2
mov		k, eax
jmp		top_1
endBlock:

;Q3
mov		eax, k
mov		ebx, n
mov		edx, OFFSET maybe
top_2:
call	WriteString
sub		eax,1
mov		k,eax
cmp		eax,ebx
jg		top_2

;Q4
mov		k, 14
mov		ecx, k
sub		ecx, 1
top_3:
mov		eax,k
sub		eax,1
call	WriteDec
mov		k, eax
loop	top_3

;Q5
mov		k, 10
mov		ecx, n
mov		eax, k
sub		ecx, eax
top_4:
mov		edx,OFFSET no
call	WriteString
loop	top_4

;Q6
for(i = 5; i > 0; i--){
	for(int k = 5; k > 0; k--){
		if(k >= i){
			cout << k;
		}
		else{
			cout << "*";
		}
	}
	cout << "\n";
}

mov		ecx, 5 
L1:
mov		count, ecx
mov		ecx, 5
L2:
cmp		ecx, count
jl		falseBlock
mov		eax, ecx
call	WriteDec
jmp		endBlock
falseBlock:
mov		edx, OFFSET star
call	WriteString
endBlock:
loop	L2
mov		edx,OFFSET newLine
call	WriteString
mov		ecx,count
loop	L1

;Q13
mov		eax, k
mov		ebx, n
cmp		eax, ebx
jg		falseBlock
mov		edx, OFFSET yes
call	WriteString
jmp		endBlock
falseBlock:
mov		edx,OFFSET no
call	WriteString
endBlock:

;Q14
mov		eax, k
mov		ebx, n
cmp		eax, ebx
jl		trueBlock1
cmp		eax, ebx
jg		trueBlock2
jmp		falseBlock
trueBlock1:
mov		edx, OFFSET maybe
call	WriteString
jmp		endBlock
trueBlock2:
mov		edx, OFFSET no
call	WriteString
jmp		endBlock
falseBlock:
mov		edx, OFFSET yes
call	WriteString
endBlock:

;Q15
mov		eax,x
mov		ebx,y
mov		ecx,z
cmp		eax,ebx
jle		falseBlock
cmp		ebx,ecx
jge		falseBlock
mov		edx,OFFSET yes
call	WriteString
jmp		endBlock
falseBlock:
mov		edx, OFFSET no
call	WriteString
endBlock:

;Q16
mov		eax,x
mov		ebx,y
mov		ecx,z
cmp		eax,ebx
jl		trueBlock1
cmp		eax,ecx
jg		trueBlock1
;code for falseblock
mov		edx,OFFSET maybe
call	WriteString
cmp		eax,ebx
jg		trueBlock2
cmp		eax,ecx
jl		trueBlock2
;falseBlock2
mov		edx, OFFSET yes
call	WriteString
jmp		endBlock
trueBlock2:
mov		edx, OFFSET no
call	WriteString
jmp		endBlock
trueBlock1:
mov		edx, OFFSET no
call	WriteString
endBlock:

INVOKE ExitProcess, 0
main ENDP
END main