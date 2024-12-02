#include "objPosArrayList.h"
#include <stdexcept>
// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
   listSize = 0;
   arrayCapacity = ARRAY_MAX_CAP;
   aList = new objPos[arrayCapacity];


}

objPosArrayList::~objPosArrayList()
{
   delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity) {
            throw std::overflow_error("Array is full");
        }
        for (int i = listSize; i > 0; i--) {
            aList[i] = aList[i - 1]; // Shift elements
        }
        aList[0] = thisPos;
        listSize++;

   
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity) {
            throw std::overflow_error("Array is full");
        }
        aList[listSize] = thisPos; // Insert at the end
        listSize++;
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) {
            throw std::underflow_error("Array is empty");
        }
        for (int i = 0; i < listSize - 1; i++) {
            aList[i] = aList[i + 1]; // Shift elements
        }
        listSize--;
}

void objPosArrayList::removeTail()
{
     if (listSize == 0) {
            throw std::underflow_error("Array is empty");
        }
        listSize--; // Simply decrease listSize

}

objPos objPosArrayList::getHeadElement() const
{
 if (listSize == 0) {
            throw std::underflow_error("Array is empty");
        }
        return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
   if (listSize == 0) {
            throw std::underflow_error("Array is empty");
        }
        return aList[listSize - 1];

}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize) {
            throw std::out_of_range("Index is out of range");
        }
        return aList[index];
}