#include <stdio.h>
#include <stdlib.h>

// Function called automatically when main finishes successfully
void trigger_segfault_on_exit(void) {
    printf("\n[Program execution complete. Triggering segmentation fault...]\n");
    
    int *ptr = NULL;
    *ptr = 42; // Dereferencing NULL pointer causes Segmentation Fault
}

int main(void) {
    // Register the exit handler
    if (atexit(trigger_segfault_on_exit) != 0) {
        fprintf(stderr, "Failed to register exit handler\n");
        return 1;
    }

    // Your main logic runs here
    printf("1. Initializing program...\n");
    printf("2. Performing operations...\n");
    printf("3. All operations finished successfully!\n");

    // Returning 0 signals successful completion to the exit handler
    return 0; 
}