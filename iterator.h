#ifndef EASY_ALGORITHM_ITERATOR_H
#define EASY_ALGORITHM_ITERATOR_H

#include <iosfwd>
#include <cstddef>
#include <stdexcept>

namespace easy_algorithm {

template <class Item>
class Iterator {
public:
  template <class Elem>
  friend std::ostream& operator << (std::ostream& os, Iterator<Elem>& iter);        // Вывод значения элемента в поток
  template <class Elem>
  friend const std::istream& operator >> (const std::istream& is, Iterator<Elem>& iter);  // Ввод значения элемента из потока
  Iterator() : _pItem(0) {}/******/
  Iterator(const Iterator& iter);                               // Конструктор копирования. Создает итератор идентичный iter
  virtual ~Iterator() {}                                        // Виртуальный деструктор позволяет полиморфное удаление объектов

  Iterator& operator ++ ();                                     // Префиксный инкремент итератора
  Iterator& operator -- ();                                     // Префиксный декремент итератора
  const Iterator& operator += (ptrdiff_t diff);                 // Изменить позицию итератора на diff вперед
  const Iterator& operator -= (ptrdiff_t diff);                 // Изменить позицию итератора на diff назад
  const Iterator& operator = (const Iterator& iter);            // Делает итератор идентичным iter
  const Iterator& operator = (const Item& item);
  //Iterator& insert(Item item);                                  // Вставить элемент в позицию итератора
                                                                // (возвращает позицию вставленного элемента)
  void swap(Iterator& iter);                                    // Поменять значения, на которые указывают 2 итератора
//  Iterator& replace(Iterator& iter);                            // Переместить значение, на которое указывает итератов позицию iter
//  Iterator& remove();                                           // Удалить элемент, на который указывает итератор
  ptrdiff_t operator - (const Iterator& iter);            // Возвращает количество элементов между двумя итераторами

  Item& operator * () const;                                    // Разыменование итератора
  Item* operator -> () const;                                   // Выбор члена элемента _pItem
  Item* getPointer() const;                                     // Возвращает указатель на элемент (_pItem)
  bool operator < (const Iterator& iter) const;                 // Сравнение значений, на которые указывают 2 итератора
  void checkPointer() const;
  bool operator == (const Iterator& iter) const;
  bool operator != (const Iterator& iter) const;

private:
  virtual std::ostream& vPrint(std::ostream& os, Iterator& iter) = 0;         // Вывод значения элемента в поток
  virtual const std::istream& vInput(const std::istream& is, Iterator& ds) = 0;     // Ввод значения элемента из потока

  //virtual Iterator& vClone() = 0;                               // Возвращает ссылку на копию итератора (для конструктора копирования)

  virtual Iterator& vIncrease() = 0;                            // Соответствует operator ++
  virtual Iterator& vDecrease() = 0;                            // Соответствует operator --
  virtual const Iterator& vSeekIter(ptrdiff_t diff) = 0;        // Соответствует operator +=, operator -=
  virtual const Iterator& vAssign(const Iterator& iter) = 0;    // Соответствует =
  virtual Iterator& vInsert(const Item& item) = 0;                     // Виртуальные функции соответствуют
  virtual void vSwap(Iterator& iter) = 0;                       // функциям интерфейса класса (без приставки v)
//  virtual Iterator& vReplace(Iterator& iter) = 0;               // Обеспечивают полиморфное поведение объектов
//  virtual Iterator& vRemove() = 0;
  virtual ptrdiff_t vDiff(const Iterator& iter) = 0;            // Соответствует operator -

protected:
  Item* _pItem;
};

template <class Item>
std::ostream& operator << (std::ostream& os, Iterator<Item>& iter) {
  iter.checkPointer();
  return iter.vPrint(os, iter);
}

template <class Item>
const std::istream& operator >> (const std::istream& is, Iterator<Item>& iter) {
  iter.checkPointer();
  return iter.vInput(is, iter);
}

template <class Item>
bool Iterator<Item>::operator == (const Iterator& iter) const {
  return _pItem == iter.getPointer();
}

template <class Item>
bool Iterator<Item>::operator != (const Iterator& iter) const {
  return !operator ==(iter);
}

template <class Item>
void Iterator<Item>::checkPointer() const {
  if (!_pItem)
    throw std::exception();
}

template <class Item>
Iterator<Item>::Iterator(const Iterator<Item>& iter)
: _pItem(iter.getPointer()) {}

template <class Item>
Item& Iterator<Item>::operator * () const {
  checkPointer();
  return *_pItem;
}

template <class Item>
Item* Iterator<Item>::operator -> () const {
  checkPointer();
  return _pItem;
}

template <class Item>
Item* Iterator<Item>::getPointer() const {
  return _pItem;
}

template <class Item>
bool Iterator<Item>::operator < (const Iterator<Item>& iter) const {
  checkPointer();
  iter.checkPointer();
  return *(*this) < *iter ? true : false;
}

template <class Item>
const Iterator<Item> operator + (const Iterator<Item>& iter, ptrdiff_t diff) {
  iter.checkPointer();
  return Iterator<Item>(iter) += diff;
}

template <class Item>
const Iterator<Item> operator + (ptrdiff_t diff, const Iterator<Item>& iter) {
  iter.checkPointer();
  return iter + diff;
}

template <class Item>
const Iterator<Item> operator - (const Iterator<Item>& iter, ptrdiff_t diff) {
  iter.checkPointer();
  return Iterator<Item>(iter) -= diff;
}

template <class Item>
const Iterator<Item> operator ++ (Iterator<Item>& iter, int) {
  iter.checkPointer();
  Iterator<Item> ret(iter);
  ++iter;
  return ret;
}

template <class Item>
const Iterator<Item> operator -- (Iterator<Item>& iter, int) {
 iter.checkPointer();
  Iterator<Item> ret(iter);
  --iter;
  return ret;
}


template <class Item>
Iterator<Item>& Iterator<Item>::operator ++ () {
  checkPointer();
  return vIncrease();
}

template <class Item>
Iterator<Item>& Iterator<Item>::operator -- () {
  checkPointer();
  return vDecrease();
}

template <class Item>
const Iterator<Item>& Iterator<Item>::operator += (ptrdiff_t diff) {
  checkPointer();
  return vSeekIter(diff);
}

template <class Item>
const Iterator<Item>& Iterator<Item>::operator -= (ptrdiff_t diff) {
  checkPointer();
  return vSeekIter(-diff);
}

template <class Item>
const Iterator<Item>& Iterator<Item>::operator = (const Iterator<Item>& iter) {
  return vAssign(iter);
}

template <class Item>
const Iterator<Item>& Iterator<Item>::operator = (const Item& item) {
  checkPointer();
  return vInsert(item);
}

/*template <class Item>
Iterator<Item>& Iterator<Item>::insert(Item item) {
  return vInsert(item);
}*/

template <class Item>
void Iterator<Item>::swap(Iterator<Item>& iter) {
  checkPointer();
  iter.checkPointer();
  vSwap(iter);
}

/*template <class Item>
Iterator<Item>& Iterator<Item>::replace(Iterator<Item>& iter) {
  return vReplace(iter);
}*/

/*template <class Item>
Iterator<Item>& Iterator<Item>::remove() {
  return vRemove();
}*/

template <class Item>
ptrdiff_t Iterator<Item>::operator - (const Iterator<Item>& iter) {
  checkPointer();
  iter.checkPointer();
  return vDiff(iter);
}

}

#endif
