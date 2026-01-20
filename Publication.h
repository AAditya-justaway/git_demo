#ifndef PUBLICATION_H
#define PUBLICATION_H

#include "Syscalls.h"

class Publication {
private:
    // Original fields
    char* entryType;
    char* key;
    char* title;
    char* author;
    char* booktitle; // Changed from journal to be more generic
    char* year;

    // New potential fields from your bib file
    char* doi;
    char* pdf;
    char* ppt;
    char* code;
    char* source;
    char* preprint;
    char* video;
    char* abbr;

    // Helper for safe memory management
    void safe_strcpy(char*& dest, const char* src);

public:
    Publication();
    Publication(const Publication& other);
    Publication& operator=(const Publication& other);
    ~Publication();

    // Public method to set any field by its key
    void setField(const char* fieldKey, const char* fieldValue);

    // Public method to print in the desired format
    void print() const;

    // Getter needed for the new grouped printing function
    const char* getYear() const;

    // Friend declaration for the sorting operator
    friend bool operator<(const Publication& lhs, const Publication& rhs);
};

bool operator<(const Publication& lhs, const Publication& rhs);

#endif // PUBLICATION_H