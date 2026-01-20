#include "Syscalls.h"
#include <unistd.h> // For open, read, write, close system calls
#include <fcntl.h>  // For O_RDONLY

namespace lowlevel {

    // --- String Functions ---
    int my_strlen(const char* s) {
        int i = 0;
        if (!s) return 0;
        while (s[i]) i++;
        return i;
    }

    int my_strcmp(const char* s1, const char* s2) {
        if (!s1 && !s2) return 0;
        if (!s1) return -1;
        if (!s2) return 1;
        while (*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }

    char* my_strcpy(char* dest, const char* src) {
        if (!dest || !src) return nullptr;
        char* original_dest = dest;
        while ((*dest++ = *src++));
        return original_dest;
    }

    char* my_strdup(const char* s) {
        if (!s) return nullptr;
        int len = my_strlen(s);
        char* new_s = new char[len + 1];
        my_strcpy(new_s, s);
        return new_s;
    }
    
    const char* my_strstr(const char* haystack, const char* needle) {
        if (!needle || *needle == '\0') return haystack;
        const char* p1 = haystack;
        while (*p1) {
            const char* p1_begin = p1;
            const char* p2 = needle;
            while (*p1 && *p2 && *p1 == *p2) {
                p1++;
                p2++;
            }
            if (*p2 == '\0') return p1_begin;
            p1 = p1_begin + 1;
        }
        return nullptr;
    }

    char* my_strtok(char* str, const char* delim) {
        static char* last_token = nullptr;
        if (str != nullptr) {
            last_token = str;
        }
        if (last_token == nullptr || *last_token == '\0') {
            return nullptr;
        }
        char* token_start = last_token;
        while (*last_token != '\0') {
            const char* d = delim;
            while (*d != '\0') {
                if (*last_token == *d) {
                    *last_token = '\0';
                    last_token++;
                    return token_start;
                }
                d++;
            }
            last_token++;
        }
        return token_start;
    }
    
    // --- I/O Functions ---
    void my_printf(const char* s) {
        if (s) {
            write(STDOUT_FILENO, s, my_strlen(s));
        }
    }
    
    void my_printf(const char* s1, const char* s2) {
        if (s1) write(STDOUT_FILENO, s1, my_strlen(s1));
        if (s2) write(STDOUT_FILENO, s2, my_strlen(s2));
    }

    // --- Conversion Functions ---
    int my_atoi(const char* s) {
        if (!s) return 0;
        int res = 0;
        int sign = 1;
        int i = 0;
        if (s[0] == '-') {
            sign = -1;
            i++;
        }
        for (; s[i] != '\0'; ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                res = res * 10 + s[i] - '0';
            } else {
                break;
            }
        }
        return sign * res;
    }

    // --- File Class Implementation ---
    File::File() : fd(-1), buffer(nullptr), buffer_pos(0), bytes_in_buffer(0) {
        buffer = new char[BUFFER_SIZE];
    }
    
    File::~File() {
        close();
        delete[] buffer;
    }

    bool File::open(const char* filename) {
        fd = ::open(filename, O_RDONLY);
        return fd != -1;
    }

    void File::close() {
        if (fd != -1) {
            ::close(fd);
            fd = -1;
        }
    }

    bool File::get_line(char* line, int max_len) {
        int line_pos = 0;
        while (line_pos < max_len - 1) {
            if (buffer_pos >= bytes_in_buffer) {
                bytes_in_buffer = ::read(fd, buffer, BUFFER_SIZE);
                buffer_pos = 0;
                if (bytes_in_buffer <= 0) {
                    break;
                }
            }
            char c = buffer[buffer_pos++];
            if (c == '\n') {
                break;
            }
            line[line_pos++] = c;
        }
        line[line_pos] = '\0';
        return (line_pos > 0 || bytes_in_buffer > 0);
    }
}