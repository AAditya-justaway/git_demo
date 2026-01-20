#ifndef SYSCALLS_H
#define SYSCALLS_H

// A namespace to hold all our custom low-level functions.
namespace lowlevel {
    // String functions (replaces <cstring>)
    int my_strlen(const char* s);
    int my_strcmp(const char* s1, const char* s2);
    char* my_strcpy(char* dest, const char* src);
    char* my_strdup(const char* s);
    const char* my_strstr(const char* haystack, const char* needle);
    char* my_strtok(char* str, const char* delim);

    // I/O functions (replaces <cstdio>)
    void my_printf(const char* s);
    void my_printf(const char* s1, const char* s2);

    // Conversion functions (replaces <cstdlib>)
    int my_atoi(const char* s);

    // A simple buffered file reader using system calls
    class File {
    private:
        int fd; // file descriptor
        char* buffer;
        int buffer_pos;
        int bytes_in_buffer;
        static const int BUFFER_SIZE = 4096;

    public:
        File();
        ~File();
        bool open(const char* filename);
        void close();
        bool get_line(char* line, int max_len);
    };
}

#endif // SYSCALLS_H