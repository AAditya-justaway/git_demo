#include "Publication.h"

// Helper function to safely allocate and copy a C-style string
void Publication::safe_strcpy(char*& dest, const char* src) {
    delete[] dest;
    dest = lowlevel::my_strdup(src);
}

// Constructor: Initialize all pointers to nullptr
Publication::Publication() : 
    entryType(nullptr), key(nullptr), title(nullptr), author(nullptr), 
    booktitle(nullptr), year(nullptr), doi(nullptr), pdf(nullptr), 
    ppt(nullptr), code(nullptr), source(nullptr), preprint(nullptr), 
    video(nullptr), abbr(nullptr) {}

// Copy Constructor: Use the assignment operator for a deep copy
Publication::Publication(const Publication& other) : 
    entryType(nullptr), key(nullptr), title(nullptr), author(nullptr), 
    booktitle(nullptr), year(nullptr), doi(nullptr), pdf(nullptr), 
    ppt(nullptr), code(nullptr), source(nullptr), preprint(nullptr), 
    video(nullptr), abbr(nullptr) {
    *this = other;
}

// Destructor: Free all allocated memory
Publication::~Publication() {
    delete[] entryType; delete[] key;     delete[] title; 
    delete[] author;    delete[] booktitle; delete[] year;
    delete[] doi;       delete[] pdf;     delete[] ppt;
    delete[] code;      delete[] source;  delete[] preprint;
    delete[] video;     delete[] abbr;
}

// Public getter for the year field
const char* Publication::getYear() const {
    return year;
}

// Assignment Operator: Perform a deep copy of all members
Publication& Publication::operator=(const Publication& other) {
    if (this == &other) return *this;
    safe_strcpy(entryType, other.entryType);
    safe_strcpy(key, other.key);
    safe_strcpy(title, other.title);
    safe_strcpy(author, other.author);
    safe_strcpy(booktitle, other.booktitle);
    safe_strcpy(year, other.year);
    safe_strcpy(doi, other.doi);
    safe_strcpy(pdf, other.pdf);
    safe_strcpy(ppt, other.ppt);
    safe_strcpy(code, other.code);
    safe_strcpy(source, other.source);
    safe_strcpy(preprint, other.preprint);
    safe_strcpy(video, other.video);
    safe_strcpy(abbr, other.abbr);
    return *this;
}

// setField: Now recognizes all new fields from the bib file
void Publication::setField(const char* fieldKey, const char* fieldValue) {
    using lowlevel::my_strcmp;
    if (my_strcmp(fieldKey, "entryType") == 0) safe_strcpy(entryType, fieldValue);
    else if (my_strcmp(fieldKey, "key") == 0) safe_strcpy(key, fieldValue);
    else if (my_strcmp(fieldKey, "title") == 0) safe_strcpy(title, fieldValue);
    else if (my_strcmp(fieldKey, "author") == 0) safe_strcpy(author, fieldValue);
    else if (my_strcmp(fieldKey, "booktitle") == 0) safe_strcpy(booktitle, fieldValue);
    else if (my_strcmp(fieldKey, "journal") == 0) safe_strcpy(booktitle, fieldValue); // Treat journal as booktitle
    else if (my_strcmp(fieldKey, "year") == 0) safe_strcpy(year, fieldValue);
    else if (my_strcmp(fieldKey, "doi") == 0) safe_strcpy(doi, fieldValue);
    else if (my_strcmp(fieldKey, "pdf") == 0) safe_strcpy(pdf, fieldValue);
    else if (my_strcmp(fieldKey, "ppt") == 0) safe_strcpy(ppt, fieldValue);
    else if (my_strcmp(fieldKey, "code") == 0) safe_strcpy(code, fieldValue);
    else if (my_strcmp(fieldKey, "source") == 0) safe_strcpy(source, fieldValue);
    else if (my_strcmp(fieldKey, "preprint") == 0) safe_strcpy(preprint, fieldValue);
    else if (my_strcmp(fieldKey, "video") == 0) safe_strcpy(video, fieldValue);
    else if (my_strcmp(fieldKey, "abbr") == 0) safe_strcpy(abbr, fieldValue);
}

// print: Rewritten to match your desired output format precisely
void Publication::print() const {
    using lowlevel::my_printf;
    my_printf("---\n");
    if (title) { my_printf("Title: ", title); my_printf("\n"); }
    if (author) { my_printf("Author(s): ", author); my_printf("\n"); }
    if (booktitle) { my_printf("Booktitle: ", booktitle); my_printf("\n"); }
    if (year) { my_printf("Year: ", year); my_printf("\n"); }
    if (doi) { my_printf("DOI: ", doi); my_printf("\n"); }
    if (pdf) { my_printf("PDF: ", pdf); my_printf("\n"); }
    if (ppt) { my_printf("PPT: ", ppt); my_printf("\n"); }
    if (code) { my_printf("Code: ", code); my_printf("\n"); }
    if (source) { my_printf("Source: ", source); my_printf("\n"); }
}

// operator< for sorting: No changes needed here
bool operator<(const Publication& lhs, const Publication& rhs) {
    int year_lhs = lhs.year ? lowlevel::my_atoi(lhs.year) : 0;
    int year_rhs = rhs.year ? lowlevel::my_atoi(rhs.year) : 0;
    if (year_lhs != year_rhs) {
        return year_lhs > year_rhs; // Descending year sort
    }
    if (lhs.author && rhs.author) {
        return lowlevel::my_strcmp(lhs.author, rhs.author) < 0; // Ascending author sort
    }
    return lhs.author != nullptr;
}