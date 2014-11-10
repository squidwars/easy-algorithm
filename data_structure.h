#ifndef EASY_ALGORITHM_DATA_STRUCTURE_H
#define EASY_ALGORITHM_DATA_STRUCTURE_H

#include <iosfwd>
#include <vector>

namespace easy_algorithm {

template <class Item>  // Предварительное объявление классов, используемых в DataStructure
class Array;
template <class Item>
class VectorAdapter;

class DataStructure {     // Базовый класс структур данных
public:
  friend std::ostream& operator << (std::ostream& os, const DataStructure& ds);         // Вывод структуры данных в поток
  friend const std::istream& operator >> (const std::istream& is, DataStructure& ds);   // Ввод структуры данных из потока

  template <class Item>
  static DataStructure* createArray(size_t maxSize);                        // Производящая функция Array(size_t)
  template <class Item>
  static DataStructure* createArray(const DataStructure& array);            // Производящая функция Array(const DataStructure&)
  template <class Item>
  static DataStructure* createVectorAdapter(std::vector<Item>& array);      // Производящая функция VectorAdapter(std::vector<Item>&)
  
  virtual ~DataStructure();                             // Виртуальный деструктор позволяет полиморфное удаление объектов

  void swap(size_t index1, size_t index2);              // Поменять местами 2 элемента с индексами index1 и index2
  void swap(DataStructure& ds);                         // Поменять структуры данных
  void replace(size_t source, size_t dest);             // Переставить элемент с индексом source в позицию dest
  void remove(size_t index);                            // Удалить элемент с индексом index
  bool compare(size_t index1, size_t index2);           // Возвращает true, если элемент 1 меньше элемента 2
  const DataStructure& operator = (const DataStructure& ds);    // Делает содержание структуры данных идентичной ds
  
  size_t Size() const;                                  // Возвращает количество элементов
  size_t maxSize() const;                               // Возвращает максимальный размер структуры данных
  bool empty() const;                                   // Возвращает true, если елементов нет

  void swap();                                          // Поменять местами 2 элемента с индексами _cur1 и _cur2
  void replace();                                       // Переставить элемент с индексом _cur1 в позицию _cur2
  void remove();                                        // Удалить элемент с индексом _cur1
  void setCur1(size_t index);                           // Установить курсор _cur1 на позицию index
  void setCur2(size_t index);                           // Установить курсор _cur2 на позицию index
  bool compare();                                       // Возвращает true, если элемент _cur1 меньше элемента _cur2
  size_t getCur1();                                     // Возвращает индекс (курсор) _cur1
  size_t getCur2();                                     // Возвращает индекс (курсор) _cur2

protected:
  explicit DataStructure(size_t maxSize);                 // Конструктор, задающий максимальный размер структуры данных
                                                          // (не позволяет неявного преобразования)
  DataStructure(const DataStructure& ds);                 // Конструктор копирования
  
  void checkIndex(size_t index);                          // Проверка индекса (вызывает исключение при нарушении)
  void setSize(size_t size);                              // Устанавливает количество элементов
  void setMaxSize(size_t size);                           // Устанавливает максимальный размер структуры данных

private:
  virtual std::ostream& vPrint(std::ostream& os, const DataStructure& ds) const = 0;    // Вывод структуры данных в поток
  virtual const std::istream& vInput(const std::istream& is, DataStructure& ds) = 0;    // Ввод структуры данных из потока

  virtual void vSwap(DataStructure& ds) = 0;                            // Соответствует swap(DataStructure& ds)
  virtual const DataStructure& vAssign(const DataStructure& ds) = 0;    // Соответствует operator =             

  virtual void vSwap() = 0;                               // Виртуальные функции, соответствующие открытому интерфейсу класса
  virtual void vReplace() = 0;                            // Должны быть переопределены в производных классах
  virtual void vRemove() = 0;
  virtual void vSetCur1(size_t index) = 0;
  virtual void vSetCur2(size_t index) = 0;
  virtual bool vCompare() = 0;
  
  size_t _size;                                           // Количество элементов в структуре данных
  size_t _maxSize;                                        // Максимальное количество элементов в структуре данных
  size_t _cur1, _cur2;                                    // Курсоры - индексы элементов, над которыми производятся операции
};

template <class Item>
DataStructure* DataStructure::createArray(size_t maxSize) {   // Производящая функция Array(size_t)
  return new Array<Item>(maxSize);                            // Возвращается указатель DataStructure* на объект Array<Item>
}

template <class Item>
DataStructure* DataStructure::createArray(const DataStructure& array) {   // Производящая функция Array(const DataStructure&)
  return new Array<Item>(array);                                          // Возвращается указатель DataStructure* на объект Array<Item>
}

template <class Item>
DataStructure* DataStructure::createVectorAdapter(std::vector<Item>& array) {   // Производящая функция VectorAdapter(std::vector<Item>&)
  return new VectorAdapter<Item>(array);                                        // Возвращается указатель DataStructure* на объект Array<Item>
}

}

#endif
