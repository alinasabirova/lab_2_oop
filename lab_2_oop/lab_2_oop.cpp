#include <conio.h>
#include <iostream>

using namespace std;

class Room { //объявили класс
protected:
	int table_size, bed_size;
public:
	//int table_size, bed_size;
	Room() { //конструктор без параметров
		cout << "Room()" << endl;
		table_size = 0;
		bed_size = 0;
	}
	Room(int table_size, int bed_size) { //конструктор с параметрами
		cout << "Room(int table_size, int bed_size)" << endl;
		this->table_size = table_size;
		this->bed_size = bed_size;
	}
	Room(const Room& p) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "Room(const Room &p)" << endl;
		table_size = p.table_size;
		bed_size = p.bed_size;
	}
	~Room() { //деструктор
		cout << table_size << ", " << bed_size << endl;
		cout << "~Room()" << endl;
	}
	void change_size(int s1, int s2) { //метод 
		table_size = table_size + s1;
		bed_size = bed_size + s2;
	}
	void def_size();
};

void Room::def_size() {
	table_size = 2;
	bed_size = 3;
}

class BigRoom : public Room { //класс наследник
protected:
	int size;
public:
	//int table_size, bed_size;
	BigRoom() : Room() { //конструктор без параметров
		cout << "BigRoom()" << endl;
		size = 0;
	}
	BigRoom(int table_size, int bed_size, int size) : Room(table_size, bed_size) { //конструктор с параметрами
		cout << "BigRoom(int table_size, int bed_size)" << endl;
		this->size = size;
	}
	BigRoom(const BigRoom& p) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "BigRoom(const Room &p)" << endl;
		size = p.size;
		table_size = p.table_size;
		bed_size = p.bed_size;
	}
	~BigRoom() { //деструктор
		cout << table_size << ", " << bed_size << ", size - " << size << endl;
		cout << "~BigRoom()" << endl;
	}
	void change_room_size(int new_room_size) {
		size = new_room_size;
	}
};

class Floor {
protected:
	Room* r1;
	Room* r2;
public:
	//int table_size, bed_size;
	Floor() { //конструктор без параметров
		cout << "Floor()" << endl;
		r1 = new Room;
		r2 = new Room;
	}
	Floor(int table1_size, int bed1_size, int table2_size, int bed2_size) { //конструктор с параметрами
		cout << "Floor(int table1_size, int bed2_size, int table2_size, int bed2_size)" << endl;
		r1 = new Room(table1_size, bed1_size);
		r2 = new Room(table2_size, bed2_size);
	}
	Floor(const Floor& s) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "Floor(const Floor &p)" << endl;
		r1 = new Room(*(s.r1)); //копируем путем вызывания конструктора копирования точки
		r2 = new Room(*(s.r2)); //s-объект r1-указатель на point
	}
	~Floor() { //деструктор
		delete r1;
		delete r2;
		cout << "~Floor()" << endl;
	}

};

int main() {
	//статически созданные объекты и их удаление
	{
		Room a;
		Room b(3, 4);
		Room c(b);
	}
	cout << endl;

	Room* a1 = new Room(8, 8); //создается переменная-указатель на класс Room, выделяется память (в классе Room), переменной-указателю присваивается адрес в память 
	a1->def_size();
	a1->change_size(2, 2);
	delete a1; //удаляем явно, иначе объект останется в памяти (переменные-указатели удаляются после скобок)
	cout << endl;

	//динамически созданные объекты:
	Room* d = new Room;
	Room* e = new Room(5, 7);
	Room* f = new Room(*e);
	//удаление динамически созданных объектов
	delete d;
	delete e;
	delete f;
	cout << endl;

	BigRoom* g = new BigRoom(2, 3, 20);//создается объект класса BigRoom, вызывается сначала конструктор Room затем BigRoom
	delete g;
	cout << endl;


	//помещение объектов в переменные различных типов
   //если есть переменная-указатель на базовый класс, то в нее можно поместить объект потомка
	Room* w = new BigRoom(2, 3, 20); //создается объект класса BigRoom но у нас нет доступа к методам и свойствам класса BigRoom, вызыв констр Room затем BigRoom
	delete w; //неправильно удаляется, деструктор вызывается только для point()(базовово класса)
	cout << endl;
							//композиция
	Floor* h = new Floor;
	Floor* y = new Floor(*h);
	delete h;
	delete y;
	cout << endl;

	return 0;
}