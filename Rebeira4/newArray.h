#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
namespace arrayspace
{

template <class T>
class list
{
   public:
      explicit list(int size=99);
      ~list(); // destructor
      list (const list&); // copy constructor
      const list& operator = (const list&); // operator =

      T& operator[](int index);
      const T& operator[](int index) const;
      void traversal(void (*) (T&));
      
      //int getSize(); // returns the set size of the array
      void add(T num); // add to end of the list
      T remove();      // remove and return the last int in the list
   private:
      int size;          // size of dynamically allocated array
      int count;         // current number of ints in the array
      T *thelist;      // dynamically allocated array
};
 
template <class T>
void list<T>::traversal(void (*f)(T&))
{
   for (int i=0; i<count; i++)
      f(thelist[i]);
}

template <class T>
T& list<T>::operator[](int index)
{
   return thelist[index];
}

template <class T>
const T& list<T>::operator[](int index) const
{
   return thelist[index];
}

template <class T>
list<T>::list(int s)
{
   try
   {
       if (s > 0){
           thelist = new T[s];
           count=0;
           size = s;
       }else{
           throw s;
       }
   }
   
   catch (int x)
   {
       cout << "Size for the array has to be greater than 0. Size has been set to 15." << endl;
       thelist = new T[15];
       count=0;
       size=15;
       
   }
}

template <class T>
list<T>::~list()
{
   delete [] thelist;
   thelist = NULL;
}

template <class T>
list<T>::list(const list<T>& list) //copy constructor
{
   thelist = new T[list.size];
   count = list.count;
   size = list.size;
   for (int i=0; i<count; i++)
      thelist[i] = list.thelist[i];
}

template <class T>
const list<T>& list<T>::operator = (const list<T>& list) //overloaded assignment operator
{
   if (&list != this)
   {
      delete [] thelist;
      thelist = new T[list.size];
      count = list.count;
      size = list.size;
      for (int i=0; i<count; i++)
         thelist[i] = list.thelist[i];
   }
   return *this;
}

template <class T>
void list<T>::add(T num)
{
   int temp;
   temp = count + 1;
   try
   {
       if (temp <= size){
           thelist[count] = num; 
           count++;
       }else{
           throw 0;
       }
   }
   catch (int)
   {
       cout << "Element " << num << " exceeds bounds. Cannot add." << endl; 
       
   }
   
}

template <class T>
T list<T>::remove()
{
    int temp;
    temp = count - 1;
   try
   {
       if (temp <= 0){
           throw 0;
       }
       count--;
       return thelist[count];
   }
   catch (int)
   {
       cout << "Array is empty, cannot delete an element." << endl;
       
   }
}

}

#endif
