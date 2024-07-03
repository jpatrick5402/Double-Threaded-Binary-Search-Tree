/*
This files serves as a way to test the functionality of the BST
This tests the functions:
1.insert()
2.size()
3.print()
4.printinorder()
5.printreverse()

*/
#include "BST.h"

void main()
{
    cout << "\nJoseph Patirck -- Project 2 -- Double Threaded Binary Search Tree\n\n";

    BST<int, string> myBST;

    myBST.insert(77, "seventy-seven");
    myBST.insert(70, "seventy");
    myBST.insert(75, "seventy-five");
    myBST.insert(66, "sixty-six");
    myBST.insert(79, "seventy-nine");
    myBST.insert(68, "sixty-eight");
    myBST.insert(67, "sixty-seven");
    myBST.insert(69, "sixty-nine");
    myBST.insert(90, "ninety");
    myBST.insert(85, "eighty-five");
    myBST.insert(83, "eighty-three");
    myBST.insert(87, "eighty-seven");
    myBST.insert(65, "sixty-five");

    cout << "BST size: " << myBST.size() << "\n\n";

    cout << "print() function: \n";
    myBST.print();
    cout << "\n";

    cout << "printinorder() function: \n";
    myBST.printinorder();
    cout << "\n\n";

    cout << "printreverse() function: \n";
    myBST.printreverse();
    cout << "\n\n";
}