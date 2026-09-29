#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *output_filename;
    FILE *fptr_out;
} DecodeInfo;

void do_decoding(DecodeInfo *decInfo) {
    // -------------------------------------------------------------------
    // 1. HEAP CORRUPTION (Writing past allocated buffer)
    // -------------------------------------------------------------------
    // We allocate 5 bytes for "data", but write 20 bytes into it.
    // The program will keep running fine for now, but glibc's heap
    // management metadata is now completely DESTROYED.
    char *secret_buffer = malloc(5);
    strcpy(secret_buffer, "This is 20 bytes of decoded secret data!");

    // -------------------------------------------------------------------
    // 2. INVALID FILE POINTER SETTINGS
    // -------------------------------------------------------------------
    decInfo->output_filename = "decoded.txt"; // String literal (Not heap memory!)
    decInfo->fptr_out = fopen(decInfo->output_filename, "w");

    if (decInfo->fptr_out != NULL) {
        fputs(secret_buffer, decInfo->fptr_out);
        // We close the file here, but DO NOT set fptr_out = NULL
        fclose(decInfo->fptr_out); 
    }

    printf("[SUCCESS] Steganography decoding completed successfully!\n");
    printf("[SUCCESS] Output saved to %s\n", decInfo->output_filename);
}

void cleanup_all(DecodeInfo *decInfo) {
    printf("[CLEANUP] Starting cleanup routine at end of program...\n");

    // ❌ BUG A: Double fclose() on the same file pointer
    // Calling fclose twice corrupts glibc file stream structures.
    fclose(decInfo->fptr_out); 

    // ❌ BUG B: Freeing non-heap memory or corrupted heap
    // Calling free() on a string literal OR on a corrupted heap chunk.
    free(decInfo->output_filename); 
}

int main() {
    DecodeInfo decInfo;
    decInfo.fptr_out = NULL;
    decInfo.output_filename = NULL;

    // Step 1: Program runs completely and looks 100% successful
    do_decoding(&decInfo);

    // Step 2: Program reaches the end, hits cleanup/exit, and CRASHES!
    cleanup_all(&decInfo);

    printf("This line will NEVER print because of the late SIGSEGV.\n");
    return 0;
}