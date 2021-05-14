#include<Windows.h>
#include<fileapi.h>
#include<winbase.h>
#include<stdio.h>
#include<stdlib.h>
#include<WINNT.H>
#include<stdlib.h>
#include<string.h>

#define db(x) __asm _emit x
__declspec(naked) ShellcodeStart(VOID){
    __asm {
        pushad
        call    routine

    routine:
        pop ebp
        sub ebp, offset routine
        push 0 // MB_OK
        lea eax, [ebp+szCaption]
        push eax
        lea eax, [ebp+szText]
        push eax
        push 0
        mov eax, 0xAAAAAAAA
        call eax

        popad
        push 0xAAAAAAAA
        ret
    
    szCaption:
        db('F') db('e') db('i') db('t') db('a') db('n') db(00)

    szText:
        db('b') db('y') db(' ') db('k') db('a') db('r') db('a') db('n') db(00)
    }
}

void ShellcodeEnd(){

}
