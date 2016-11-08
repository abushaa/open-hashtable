#include <iostream>
using namespace std;

struct Pair       //Структура являющаяся звеном списка
{
    int key;
    Pair()
    {
        x = 0;
        y = 0;
        next = nullptr;
        prev = nullptr;
    }
    Pair(int a, int b)
    {
        x = a;
        y = b;
        next = nullptr;
        prev = nullptr;
    }
    int x;
    int y;     //Значение x будет передаваться в список
    Pair *next,*prev; //Указатели на адреса следующего и предыдущего элементов списка
    void print_pair(){
        cout << "{" << key << ": " << "(" << x << ", " << y << ")"<< "} ";
    }
};


struct List   //Создаем тип данных Список
{
    Pair *head;
    Pair *tail;  //Указатели на адреса начала списка и его конца
    List() {
        head = tail = nullptr;
    }


    void add(const int _key, const int x, const int y) {
        Pair *temp = new Pair(); // Выделение памяти под новый элемент структуры
        temp->key = _key;
        //temp->next = nullptr;       // Указываем, что изначально по следующему адресу пусто
        temp->x = x;
        temp->y = y;             // Записываем значение в структуру

        if (head) // Если список не пуст
        {
            temp->prev = tail; // Указываем адрес на предыдущий элемент в соотв. поле
            tail->next = temp; // Указываем адрес следующего за хвостом элемента
            tail = temp;       //Меняем адрес хвоста
        } else //Если список пустой
        {
            temp->prev = nullptr; // Предыдущий элемент указывает в пустоту
            head = tail = temp;    // Голова=Хвост=тот элемент, что сейчас добавили
        }
    }


    void print() {
        Pair *temp = head;  // Временно указываем на адрес первого элемента
        while (temp)      // Пока не встретим пустое значение
        {
            temp->print_pair();
            temp = temp->next;     //Смена адреса на адрес следующего элемента
        }
        cout << endl;
    }


    Pair *search_pair(const int s_key)  // 3
    {
        Pair *temp = head;
        while (temp) {
            if (temp->key == s_key) {
                return temp;
            }
            temp = temp->next;
        }
        cerr << "Key error!";
        return temp;
    }


    void delete_pair(int d_key)  // 5
    {
        Pair *temp = search_pair( d_key);
        if (temp != head and temp != tail) {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        } else if (temp == tail) {
            tail = temp->prev;
            tail->next = nullptr;
        } else if (temp == head) {
            head = temp->next;
            head->prev = nullptr;
        }
        delete temp;
    }
};

int hash_(int key){
    return key%10;
}

struct hash_table
{
    List *keys = new List[10];

    void add_(int key, int x, int y)
    {
        int hs = hash_(key);
        keys[hs].add(key, x, y);
    }

    Pair *search_(int key)
    {
        int hs = hash_(key);
        return keys[hs].search_pair(key);
    }
    void delete_(int key)
    {
        int hs = hash_(key);
        keys[hs].delete_pair(key);
    }
};


int main ()
{
    hash_table new_table;
    for(int i=0; i<20; i++)
    {
        new_table.add_(i, i+1, i+2);
    }
    for(int i = 0; i < 10; i++)
    {
        new_table.keys[i].print();
    }
    cout << endl;
    cout << endl;
    new_table.delete_(10);
    new_table.keys[0].print();
    cout << endl;
    Pair *s_pair = new_table.search_(15);
    s_pair->print_pair();
    return 0;
}