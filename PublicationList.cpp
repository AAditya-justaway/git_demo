#include "PublicationList.h"

// Helper function to trim whitespace and bib chars from a string in-place
void trim_bib_inplace(char* str) {
    if (!str) return;
    char* start = str;
    // Trim leading characters
    while (*start && (*start == ' ' || *start == '\t' || *start == '{' || *start == ',' || *start == '=' || *start == '"')) {
        start++;
    }

    char* end = start + lowlevel::my_strlen(start) - 1;
    // Trim trailing characters
    while (end > start && (*end == ' ' || *end == '\t' || *end == '}' || *end == ',' || *end == '"')) {
        *end = '\0';
        end--;
    }
    
    // Move the trimmed string to the beginning of the buffer
    if (str != start) {
        char* p = str;
        while ((*p++ = *start++));
    }
}

// Constructor
PublicationList::PublicationList() : publications(nullptr), count(0), capacity(10) {
    publications = new Publication[capacity];
}

// Destructor
PublicationList::~PublicationList() {
    delete[] publications;
}

// Resize internal array
void PublicationList::resize() {
    capacity *= 2;
    Publication* new_publications = new Publication[capacity];
    for (int i = 0; i < count; ++i) {
        new_publications[i] = publications[i];
    }
    delete[] publications;
    publications = new_publications;
}

// Add a publication
void PublicationList::addPublication(const Publication& pub) {
    if (count == capacity) {
        resize();
    }
    publications[count++] = pub;
}

// Sort the list
void PublicationList::sort() {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (!(publications[j] < publications[j + 1])) {
                Publication temp = publications[j];
                publications[j] = publications[j + 1];
                publications[j + 1] = temp;
            }
        }
    }
}

// printAll: REWRITTEN to print with year-based group headings
void PublicationList::printAll() const {
    if (count == 0) return;

    char* last_year_printed = nullptr;

    for (int i = 0; i < count; ++i) {
        const char* current_year = publications[i].getYear();
        
        // Check if the year has changed from the last entry
        if (current_year && (last_year_printed == nullptr || lowlevel::my_strcmp(last_year_printed, current_year) != 0)) {
            lowlevel::my_printf("\n### **Year: ");
            lowlevel::my_printf(current_year);
            lowlevel::my_printf("**\n");
            
            // Update the last year printed
            delete[] last_year_printed;
            last_year_printed = lowlevel::my_strdup(current_year);
        }
        
        publications[i].print();
    }

    delete[] last_year_printed; // Final cleanup
}

// Getters
int PublicationList::getCount() const { return count; }
const Publication& PublicationList::getPublication(int index) const { return publications[index]; }

// parseFile: No changes needed
bool PublicationList::parseFile(const char* filename) {
    lowlevel::File bib_file;
    if (!bib_file.open(filename)) {
        lowlevel::my_printf("Error: Could not open file ", filename);
        lowlevel::my_printf("\n");
        return false;
    }

    char line[2048]; // Increased buffer size for long abstract lines
    Publication currentPub;
    bool inEntry = false;

    while (bib_file.get_line(line, 2048)) {
        if (line[0] == '@') {
            if (inEntry) addPublication(currentPub);
            currentPub = Publication(); // Reset for new entry
            inEntry = true;
            
            char* type = lowlevel::my_strtok(line, "{");
            char* key = lowlevel::my_strtok(nullptr, ",");
            if (type) currentPub.setField("entryType", type + 1);
            if (key) currentPub.setField("key", key);

        } else if (inEntry && lowlevel::my_strstr(line, "=")) {
            char* key = lowlevel::my_strtok(line, "=");
            char* value = lowlevel::my_strtok(nullptr, "}");
            
            if (key && value) {
                trim_bib_inplace(key);
                trim_bib_inplace(value);
                currentPub.setField(key, value);
            }
        } else if (inEntry && line[0] == '}') {
            addPublication(currentPub);
            inEntry = false;
        }
    }
    if (inEntry) addPublication(currentPub);

    bib_file.close();
    return true;
}

// operator+: No changes needed
PublicationList* operator+(const PublicationList& lhs, const PublicationList& rhs) {
    PublicationList* result = new PublicationList();
    for (int i = 0; i < lhs.getCount(); ++i) {
        result->addPublication(lhs.getPublication(i));
    }
    for (int i = 0; i < rhs.getCount(); ++i) {
        result->addPublication(rhs.getPublication(i));
    }
    return result;
}