/// prompt start
// Write a C program which momentarily increases user's permissions on a directory,
// does some operation, and lowers them again. Secure the program against cases when
// the decrease of permissions could be intercepted.
/// prompt end
#define _GNU_SOURCE // Required for setresuid and setresgid
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void increase_permissions(const char *dir_path, mode_t new_permissions) {
    // Get the current permissions of the directory
    struct stat st;
    if (stat(dir_path, &st) == -1) {
        perror("Error getting directory permissions");
        exit(EXIT_FAILURE);
    }

    // Increase user permissions
    int old_permissions = st.st_mode & 0777; // Mask out non-permission bits
    int final_permissions = old_permissions | new_permissions;
    if (chmod(dir_path, final_permissions) == -1) {
        perror("Error changing directory permissions");
        exit(EXIT_FAILURE);
    }

    printf("Directory permissions increased.\n");
}

void perform_operation(const char *dir_path) {
    // Replace this function with the specific operation you want to perform
    // For example, you can create, modify, or delete files in the directory.
    // Here, we'll just print a message.

    printf("Performing operation in directory: %s\n", dir_path);
}

void decrease_permissions(const char *dir_path, mode_t original_permissions) {
    // Lower the permissions back to the original state
    if (chmod(dir_path, original_permissions) == -1) {
        perror("Error changing directory permissions back to original");
        exit(EXIT_FAILURE);
    }

    printf("Directory permissions decreased.\n");
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Extract directory path from command-line arguments
    const char *dir_path = argv[1];

    // Get the original permissions of the directory
    struct stat st;
    if (stat(dir_path, &st) == -1) {
        perror("Error getting directory permissions");
        exit(EXIT_FAILURE);
    }

    mode_t original_permissions = st.st_mode & 0777; // Mask out non-permission bits

    // Elevate privileges using setuid and setgid
    if (setresuid(geteuid(), geteuid(), geteuid()) == -1 ||
        setresgid(getegid(), getegid(), getegid()) == -1) {
        perror("Error setting user and group IDs");
        exit(EXIT_FAILURE);
    }

    // Increase permissions momentarily
    increase_permissions(dir_path, S_IRWXU);

    // Perform the operation in the directory
    perform_operation(dir_path);

    // Lower permissions back to the original state
    decrease_permissions(dir_path, original_permissions);

    // Drop elevated privileges
    if (setresuid(getuid(), getuid(), getuid()) == -1 ||
        setresgid(getgid(), getgid(), getgid()) == -1) {
        perror("Error resetting user and group IDs");
        exit(EXIT_FAILURE);
    }

    return 0;
}