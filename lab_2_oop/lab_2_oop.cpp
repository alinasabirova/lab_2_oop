#include <conio.h>
#include <iostream>

using namespace std;

class Floor { //объявили класс
protected:
	int lenght, width; //атрибуты
public:
	//int lenght, width;
	Floor() { //конструктор без параметров
		cout << "Floor()" << endl;
		lenght = 0;
		width = 0;
	}
	Floor(int lenght, int width) { //конструктор с параметрами
		cout << "Floor(int lenght, int width)" << endl;
		this->lenght = lenght;
		this->width = width;
	}
	Floor(const Floor& p) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "Floor(const Floor &p)" << endl;
		lenght = p.lenght;
		width = p.width;
	}
	~Floor() { //деструктор
		cout << lenght << ", " << width << endl;
		cout << "~Floor()" << endl;
	}
	void change_size(int s1, int s2) { //метод 
		lenght = lenght + s1;
		width = width + s2;
	}
	void def_size();
};

void Floor::def_size() {
	lenght = 2;
	width = 3;
}

class laminate : public Floor { //класс наследник
protected:
	string color;
public:
	laminate() : Floor() { //конструктор без параметров
		cout << "laminate()" << endl;
		color = "";
	}
	laminate(int lenght, int width, string color) : Floor(lenght, width) { //конструктор с параметрами
		cout << "laminate(int lenght, int width)" << endl;
		this->color = color;
	}
	laminate(const laminate& p) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "laminate(const Floor &p)" << endl;
		color = p.color;
		lenght = p.lenght;
		width = p.width;
	}
	~laminate() { //деструктор
		cout << lenght << ", " << width << ", color - " << color << endl;
		cout << "~laminate()" << endl;
	}
	void change_color(int new_color) {
		color = new_color;
	}
};

class Room {
protected:
	Floor* r1;
	Floor* r2;
public:
	Room() { //конструктор без параметров
		cout << "Room()" << endl;
		r1 = new Floor;
		r2 = new Floor;
	}
	Room(int lenght1, int width1, int lenght2, int width2) { //конструктор с параметрами
		cout << "Room(int lenght1, int width2, int lenght2, int width2)" << endl;
		r1 = new Floor(lenght1, width1);
		r2 = new Floor(lenght2, width2);
	}
	Room(const Room& s) { //конструктор копирования - переносит все свойства из того объекта, который передали
		cout << "Room(const Room &p)" << endl;
		r1 = new Floor(*(s.r1)); //копируем путем вызывания конструктора копирования точки
		r2 = new Floor(*(s.r2)); //s-объект r1-указатель на point
	}
	~Room() { //деструктор
		delete r1;
		delete r2;
		cout << "~Room()" << endl;
	}
};

int main() {
	{
		Floor a;
		Floor b(3, 4);
		Floor c(b);
	}
	cout << endl;
	                        
	Floor* a1 = new Floor(8, 8); 
	a1->def_size();
	a1->change_size(2, 2);
	delete a1; 
	cout << endl;

	Floor* d = new Floor;
	Floor* e = new Floor(5, 7);
	Floor* f = new Floor(*e);
	delete d;
	delete e;
	delete f;
	cout << endl;

	laminate* l = new laminate();
	laminate* g = new laminate(2, 3, "black");
	laminate* n = new laminate(*g);
	delete l; 
	delete g;
	delete n;
	cout << endl;

	Floor* w = new laminate(2, 3, "white"); 
	delete w; 
	cout << endl;
					
	Room* h = new Room;
	Room* y = new Room(*h);
	delete h;
	delete y;
	cout << endl;

	return 0;
}