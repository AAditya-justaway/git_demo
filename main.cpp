#include "PublicationList.h"
#include "Syscalls.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        lowlevel::my_printf("Usage: ", argv[0]);
        lowlevel::my_printf(" <bibfile1> [bibfile2]\n");
        return 1;
    }

    lowlevel::my_printf("--> Parsing first file: ", argv[1]);
    lowlevel::my_printf("\n");
    PublicationList list1;
    if (!list1.parseFile(argv[1])) {
        return 1;
    }

    lowlevel::my_printf("\n*** Unsorted List 1 ***\n");
    list1.printAll();

    lowlevel::my_printf("\n--> Sorting list 1...\n");
    list1.sort();

    lowlevel::my_printf("\n*** Sorted List 1 (Year Desc, Author Asc) ***\n");
    list1.printAll();

    if (argc > 2) {
        lowlevel::my_printf("\n--> Parsing second file: ", argv[2]);
        lowlevel::my_printf("\n");
        PublicationList list2;
        list2.parseFile(argv[2]);
        
        lowlevel::my_printf("\n--> Merging lists using '+' operator...\n");
        PublicationList* mergedList = list1 + list2;
        
        lowlevel::my_printf("\n*** Merged List (Unsorted) ***\n");
        mergedList->printAll();

        lowlevel::my_printf("\n--> Sorting merged list...\n");
        mergedList->sort();

        lowlevel::my_printf("\n*** Merged List (Sorted) ***\n");
        mergedList->printAll();

        delete mergedList; // Clean up memory from '+' operation
    }

    return 0;
}