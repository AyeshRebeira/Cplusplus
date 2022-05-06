#include <iostream>
using namespace std;
#include "newArray.h"
using namespace arrayspace;

int main(){
    
    cout << "Trying to create an array of size 0:" << endl;
    list<int> list1(0); //throwing an error
    
    cout << endl << "Creating an array named list2" << endl;
    list<int> list2(3);

    cout << "Adding elements to list2" << endl;
    list2.add(6);
    list2.add(4);
    list2.add(5);
    cout << "Attempting to add an element that exceeds the size of list2:" << endl;
    list2.add(2);
    
    cout << endl << "Creating a new list, list3" << endl;
    list<int> list3(20);
    cout << "Adding two elements to list3" << endl;
    list3.add(13);
    list3.add(15);
    
    cout << endl << "Attempting to remove more elements than are present in list3: " << endl;
    list3.remove();
    list3.remove();
    
    
    cout << endl << "The item at index 1 for list2: " << list2[1] << endl;
    
    cout << endl << "Copied the contents of list2 to new list4" << endl;
    list<int> list4(3);
    list4 = list2;
    cout << "The item at index 1 for list4: " << list4[1] << endl;
    
    list<int> list5(20);
    cout<< endl << "Enter a number to add to new list, list5: ";
    int input;
    cin >> input;
    list5[0] = input;
    cout << "Item " << list5[0] << " has been added to list5" << endl;
    
    cout << endl << "End program" << endl;
    
    return 0;
    
}
