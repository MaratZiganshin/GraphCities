#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <iostream>

template <class T, class Comparator = std::less<typename T>> class PriorityQueue
{
public:

    PriorityQueue() : _storage() {}

    void push(const T& newElement)
    {
        int size = _storage.size();
        int index = 0;
        std::list<T>::const_iterator i;
        Comparator comparator;
        for (i = _storage.begin(); i != _storage.end(); ++i)
            if (comparator(*i,newElement))
                break;
        _storage.insert(i, newElement);
    }

    T pop()
    {
        T temp = _storage.front();
        _storage.pop_front();
        return temp;
    }

    T top()
    {
        return _storage.front();
    }

    size_t size() const
    {
        return _storage.size();
    }

    bool isEmpty() const
    {
        return _storage.empty();
    }

    bool isFull() const
    {
        return false;
    }
private:

    std::list<T> _storage;

};
// TODO: Напишите здесь СОБСТВЕННУЮ реализацию шаблонного класса PriorityQueue (название д.б. строго таким!) — 
// очередь с приоритетами, удовлетворяющего следующему концепту:
//
//1)  Шаблон определения очереди должен быть строго представлен в настояем файле `priority_queue.h` полностью без разделения на h/hpp;
//    определение — в глобальном пространстве имен.
//
//2)  Шаблон имеет два параметра: <T> определяет тип элементов, хранящихся в очереди; <Comparator> задает тип (для создания 
//    объекта-компаратора) для сравнения элементов для получения порядка, по умолчанию 
//    Comparator = std::less<typename T>.
//   
//3)  Шаблон определяет следующие основные операции над очередью:

//    а)  Помещение нового элемента в очередь:
//        void push(const T& newElement);
//        Способ реорганизации/переупорядочивания очереди (ленивый/отложенный или немедленный) определяется самостоятельно.
//        Если конкретная (ваша) реализация очереди подразумевает максимальный размер, то при превышении (помещением очередного
//        элемента) максимального размера, генерируется исключение std::out_of_range.
//        
//    б)  Извлечение "максимального" элемента из начала очереди (в соответствии с порядком, определяемым компаратором):
//        T pop();
//        Если очередь пуста, генерируется исключение std::out_of_range.
//        
//    в)  Получение "максимального" элемента из начала очереди без удаления его из очереди:
//        T top();
//        Если очередь пуста, генерируется исключение std::out_of_range.
//
//    г)  Получение размера очереди:
//        size_t size() const;
//        
//    д)  Определения, является ли очередь пустой; является ли очередь заполненной:
//        bool isEmpty() const;
//        bool isFull() const;
//        Если реализация не подразумевает ограничение на число хранимых в очереди элементов,
//        метод isFull() всегда возвращает false.
//    
//    е)  Конструкторы: по умолчанию, инициализация размером очереди (если известен). Деструктор, если нужен, КК и ОП для соответствия
//        правило большой тройки (если применимо).
//        
//4)  Шаблон реализации класса определяется самостоятельно. Тестирование будет осуществляться на предмет соответствия указанному 
//    концепту. Также при review кода будет приниматься во внимания особенно важные имлементационные моменты.
//    Выбор подлежащей структуры (вектор, лист, куча, дерева...) на оценку большого влияния не окажет.
//    Проксирование (использование стандартного контейнера std::priority_queue) не разрешено.
//
//5)  При необходимости можно доопределить вспомогательные классы внутри шаблона очереди или вне его. При этом
//    их определение не должно влечь за собой дополнительных ограничений на использование типа
//    PriorityQueue<T, Comparator> за пределами данного модуля.
//
//6)  При желании можно реализовать итератор(ы) для перебора элементов очереди в порядке, определяемом компаратором.
//    В этом случае следует дополнить семантику класса соответствующими методами: begin(), end() и т.д.

#endif // 
