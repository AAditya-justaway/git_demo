#ifndef PUBLICATION_LIST_H
#define PUBLICATION_LIST_H

#include "Publication.h"

class PublicationList {
private:
    Publication* publications;
    int count;
    int capacity;
    void resize();

public:
    PublicationList();
    ~PublicationList();
    PublicationList(const PublicationList& other) = delete;
    PublicationList& operator=(const PublicationList& other) = delete;

    bool parseFile(const char* filename);
    void addPublication(const Publication& pub);
    void sort();
    void printAll() const;

    int getCount() const;
    const Publication& getPublication(int index) const;
};

PublicationList* operator+(const PublicationList& lhs, const PublicationList& rhs);

#endif // PUBLICATION_LIST_H