#ifndef EASY_ALGORITHM_ARRAY_H
#define EASY_ALGORITHM_ARRAY_H

#include <iosfwd>
#include <iostream>
#include "data_structure.h"
#include "iterator.h"

namespace easy_algorithm {

template <class Item>
class Array : public DataStructure {
public:
  friend class DataStructure;

  void insert(Item item, size_t index);         // �������� ������� elem � ������� index
  Iterator& begin() const;                               // ���������� �������� �� ������ ��������� ������
  Iterator& end() const;                                 // ���������� �������� �� ����� ��������� ������
  Item& operator [] (size_t index);                     // ���������� ������ �� ������� � �������� index
  const Item& operator [] (size_t index) const;


  bool checkIndex(size_t index);


private:
  std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const;
  const std::istream& vInput(const std::istream& is, DataStructure& ds);
  /////Array& vClone() const{ return Array<Item>(0); }
  void vInsert(Item item, size_t index);                    // ����������� ������� �������������
  void vSwap(size_t index1, size_t index2);               // �������� ���������� ������ (��� ��������� v)
  void vSwap(DataStructure& ds);                              // ������������ ����������� ��������� ��������
  void vReplace(size_t source, size_t dest) {}
  void vRemove(size_t index){}
  //Iterator vBegin() const{return Iterator();}
  //Iterator vEnd() const{return Iterator();}
  //  Elem& vGet(size_t index){}
  //  const Elem& vGet(size_t index) const{}
  const DataStructure& vAssign(const DataStructure& ds){ return Array<Item>(0); }
  virtual ~Array(){}
protected:
  Item* getPointer() const;
  void setPointer(Item*);
private:
  Array(size_t maxSize);
  Array(const DataStructure& array);

  Item* pArray;
};

template <class Item>
bool Array<Item>::checkIndex(size_t index) {
  return !(index >= size() || index < 0);
}

template <class Item>
Array<Item>::Array(size_t maxSize) : DataStructure(maxSize) {
  pArray = new Item[maxSize];
  /************/
  for (size_t i = 0; i < maxSize; ++i){
    pArray[i] = i;
    std::cout << pArray[i] << "\n";
  }
  /************/
}

template <class Item>
Array<Item>::Array(const DataStructure& array) : DataStructure(array.maxSize()) {
  pArray = new Item[array.maxSize()]; // maxSize �������� �� size
  for (size_t i = 0; i < array.maxSize(); ++i){
    pArray[i] = (((Array<Item>*)&array)->pArray)[i];
    /******/
    std::cout << pArray[i] << "\n";
    /******/
  }
}

template <class Item>
std::ostream& Array<Item>::vPrint(std::ostream& os, const DataStructure& ds) const {
  return os; // ��������
}

template <class Item>
const std::istream& Array<Item>::vInput(const std::istream& is, DataStructure& ds) {
  return is; // ��������
}

template <class Item>
void Array<Item>::insert(Item item, size_t index) {
  if (!checkIndex(index))
    throw std::out_of_range(IndexError);
  vInsert(item, index);
}

template <class Item>
void Array<Item>::vInsert(Item item, size_t index) {
  // ��������
}

template <class Item>
void Array<Item>::vSwap(size_t index1, size_t index2) {
  // ��������
}

template <class Item>
Item* Array<Item>::getPointer() const {
  return pArray;
}

template <class Item>
void Array<Item>::setPointer(Item* p) {
  pArray = p;
}

template <class Item>
void Array<Item>::vSwap(DataStructure& ds) {
  Item* temp = pArray;
  pArray = ((Array<int>*)(&ds))->getPointer();
  ((Array<int>*)(&ds))->setPointer(temp);
  //��� �������� _size � _maxSize
}

}

#endif