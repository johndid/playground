; Zero byte free hello world assembly
global start
	
section .data
hello_world: db "Hello World!", 0x0a ; Defining the string to output
.len: equ $ - hello_world            ; Calculating the length of the helloworld string. 
                                     ; $ denotes the current address subtracting hello_world
                                     ; will produce the length of the hello_world+0x0a string.
section .text

start:
mov r8b, 0x02                        ; Unix system call class = 2
shl r8, 24                           ; Moving from 0x02 to 0x2000000 with left shift 24 times.
or r8, 0x04                          ; Adding the actual system call to the call class 0x2000000 to 0x2000004
                                     ; the 3 instructions above removes any zeros in the 0x200000 address and
                                     ; effectively places the 0x2000004 systemcall number in r8
jmp in                               ; trick to push the string address into rdi, eliminating the 2000 zeros
	
out:
pop rdi                              ; get the address of the helloworld string
mov rsi, rdi	                     ; put hello world to the correct register for the syscall
mov rax, r8                          ; setting the system call 
xor rdi,rdi                          ; zeroing out rdi for setting the std write handle
inc rdi                              ; applying the write handle using no zero bytes

xor edx,edx	                     ; zeroing out edx before setting the length of the string
mov dl, hello_world.len              ; Add the length of the string to write  
syscall                              ; using the calculated length from the .len definition above

sub r8, 0x3                          ; as r8 contain the latest syscall 0x2000004 so subtracting 3 will produce                                                        ; 0x2000001, which is the syscall for exit
mov rax, r8                          ; setting the system call 
xor rdi, rdi                         ; zeroing out rdi for the return value of the exit system call
syscall

in:	
call out                             ; Call out labes as a function forcing the string below 
db "Hello World!", 0x0a              ; to be pushed into rdi
