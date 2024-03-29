#include <iostream>
#include <fstream>

class Shape {
public:
    enum Color { WHITE, RED, GREEN };
    virtual ~Shape() {}
    virtual Shape* clone() const { return nullptr; }
    virtual void print(std::ostream& os) const {}
    virtual bool operator==(const Shape& other) const { return false; }
    virtual bool operator>(const Shape& other) const { return false; }
};

class Circle : public Shape {
public:
    int X;
    int Y;
    int Radius;
    Color color;

    Circle(int xCoord = 0, int yCoord = 0, int radius = 0, Color col = WHITE)
        : X(xCoord), Y(yCoord), Radius(radius), color(col) {}

    Shape* clone() const override {
        return new Circle(*this);
    }

    void print(std::ostream& os) const override {
        os << "Circle (" << X << "," << Y << "," << Radius << ")";
    }

    bool operator==(const Shape& other) const override {
        if (const Circle* circle = dynamic_cast<const Circle*>(&other)) {
            return X == circle->X && Y == circle->Y && Radius == circle->Radius;
        }
        return false;
    }

    bool operator>(const Shape& other) const override {
        if (const Circle* circle = dynamic_cast<const Circle*>(&other)) {
            return Radius > circle->Radius;
        }
        return false;
    }
};

class Rect : public Shape {
public:
    int X;
    int Y;
    int Width;
    int Height;
    Color color;

    Rect(int xCoord = 0, int yCoord = 0, int width = 0, int height = 0, Color col = WHITE)
        : X(xCoord), Y(yCoord), Width(width), Height(height), color(col) {}

    Shape* clone() const override {
        return new Rect(*this);
    }

    void print(std::ostream& os) const override {
        os << "Rect (" << X << "," << Y << "," << Width << "," << Height << ")";
    }

    bool operator==(const Shape& other) const override {
        if (const Rect* rect = dynamic_cast<const Rect*>(&other)) {
            return X == rect->X && Y == rect->Y && Width == rect->Width && Height == rect->Height;
        }
        return false;
    }

    bool operator>(const Shape& other) const override {
        if (const Rect* rect = dynamic_cast<const Rect*>(&other)) {
            return Width * Height > rect->Width * rect->Height;
        }
        return false;
    }
};

class Node {
public:
    Shape* data;
    Node* prev;
    Node* next;

    Node() : next(nullptr), prev(nullptr), data(nullptr) {}
    Node(Node* pr, const Shape& d) : next(pr->next), prev(pr) {
        pr->next = this;
        next->prev = this;
        data = d.clone();

        std::cout << "Node created with data: ";
        data->print(std::cout);
        std::cout << std::endl;
    }


    ~Node() {
        delete data;
    }
};

class List {
private:
    Node head;
    Node tail;
    size_t m_size;

public:
    List() : head(), tail(), m_size(0) {
        head.next = &tail;
        tail.prev = &head;
    }

    ~List() {
        while (head.next != &tail) {
            Node* temp = head.next;
            head.next = temp->next;
            delete temp;
        }
    }

    enum SortType { AREA, COLOR };

    void AddToTail(const Shape& data) {
        Node* newNode = new Node{ tail.prev, data };
        m_size++;
    }

    void AddToHead(const Shape& data) {
        Node* newNode = new Node{ &head, data };
        m_size++;
    }

    void Remove(const Shape& target) {
        Node* curr = head.next;
        while (curr != &tail) {
            if (*(curr->data) == target) {
                Node* temp = curr;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr = curr->next;
                delete temp;
                m_size--;
            }
            else {
                curr = curr->next;
            }
        }
    }

 

    void SortListByArea() {
        Node* i = head.next->next;
        while (i != &tail) {
            Node* j = i;
            while (j != &head && *(j->prev->data) > *(j->data)) {
                std::swap(j->prev->data, j->data);
                j = j->prev;
            }
            i = i->next;
        }
    }

    void SortListByColor() {
        Node* i = head.next->next;
        while (i != &tail) {
            Node* j = i;
            while (j != &head && (dynamic_cast<Circle*>(j->prev->data))->color > (dynamic_cast<Circle*>(j->data))->color) {
                std::swap(j->prev->data, j->data);
                j = j->prev;
            }
            i = i->next;
        }
    }

    void SortList(SortType sortType) {
        switch (sortType) {
        case AREA:
            SortListByArea();
            break;
        case COLOR:
            SortListByColor();
            break;
        default:
            std::cerr << "Invalid sort type\n";
            break;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const List& list) {
        Node* current = list.head.next;
        while (current != &(list.tail)) {
            current->data->print(os);
            os << std::endl;
            current = current->next;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, List& list) {
        //Pass
        return is;
    }
};





const char* sep = "------------------------------------\n";



int main()
{
    //
    // 1. Создаем список
    //
    List ls1;

    ls1.AddToTail(Circle(1, 1, 1, Shape::WHITE));	//добавляем элементы в список
    ls1.AddToTail(Circle(5, 5, 5, Shape::RED));
    ls1.AddToTail(Rect(2, 3, 4, 5, Shape::RED));
    ls1.AddToTail(Rect(4, 6, 8, 10, Shape::GREEN));
    ls1.AddToTail(Circle(2, 2, 2, Shape::WHITE));
    ls1.AddToTail(Rect(3, 5, 6, 7, Shape::GREEN));
    std::cout << ls1;								//выводим список	

    ls1.Remove(Circle(5, 5, 5, Shape::RED));		// удаляем первый элемент, равный заданному
    std::cout << ls1;
    ls1.Remove(Rect(4, 6, 8, 10, Shape::GREEN));
    std::cout << ls1;

    //
    // 2. Приведенный ниже код должен выполняться корректно	
    //
    List ls2 = ls1;
    List ls3 = ls2;
    std::cout << ls2;

    ls2.AddToHead(Circle(5, 5, 5, Shape::RED));
    ls2.AddToHead(Rect(5, 7, 9, 11, Shape::WHITE));

    std::cout << ls2;
    ls1 = ls2;			// из "большого" списка в "маленький"
    std::cout << ls1;

    ls1 = ls3;			// из "маленького" списка в "большой"
    std::cout << ls1 << sep;
    //
    // 3. Вспоминаем про семантику перемещения	
    //
    List ls4 = std::move(ls2);
    std::cout << ls4;
    std::cout << ls2;

    ls3 = std::move(ls4);
    std::cout << ls3;
    std::cout << ls4 << sep;
    //
    //4.  Сортировка по возрастанию площади кружка
    //
    std::cout << ls3;
    ls3.SortList(AREA);
    std::cout << ls3 << sep;

    ls3.SortList(COLOR);
    std::cout << ls3 << sep;

    //
    // 5. Файловый ввод/вывод
    //
    std::ofstream fout("list.txt");
    fout << ls3;	// выводим список в файл
    fout.close();

    std::ifstream fin("list.txt");
    List ls5;		// читаем список из файла
    fin >> ls5;
    fin.close();

    std::cout << ls5;


    return 0;
}