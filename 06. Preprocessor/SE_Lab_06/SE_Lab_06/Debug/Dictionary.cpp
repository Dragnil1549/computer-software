#include "stdafx.h"

using namespace Dictionary;
using namespace std;


Instance Dictionary::Create(const char* name, int size)
{
	Instance NewDict;
	strlen(name) > ENTRYNAMEMAXSIZE ? throw THROW01 : strcpy_s(NewDict.name, name);
	NewDict.maxsize < size ? throw THROW02 : NewDict.size = size;
	NewDict.dictionary = new Entry[size];
	return NewDict;
}

void Dictionary:: AddEntry(Instance& inst, Entry ed) {
	
	int cnt = inst.cnt;
	cnt >= inst.size ? throw  THROW03 : inst.dictionary[cnt] = ed; //проверяем нет ли переполнения по количеству элементов словоря, если нет добавляем элемент
	for (int i=0; i < cnt; i++) { // дублирование индентификатора 
		if (inst.dictionary[cnt-1].id == ed.id)  //сравниваем если имя элемента совпадает с другими уже имеющимися именами выкидываем ошибку
			throw THROW04;
	}
	inst.cnt++; //увеличиваем количество ээлементов словаря 
}
void  Dictionary::DelEntry(Instance& inst, int id) {
	int tr = 0;
	cout << "Удаление id = " << id << endl;
	for (int i = 1; i <= inst.cnt; i++) {
		if (inst.dictionary[i].id == id) {
			tr = 1;
			for (int j = i; j < inst.cnt; j++) //переставляем все элементы на позицию +1 т.к. удалили один элемент
			{
				inst.dictionary[j] = inst.dictionary[j + 1];
			}
			inst.cnt--;
			break;
		}
	}
	if (tr == 0) //если нет элемента с таким индентифекатором
		throw THROW05;
}

Entry Dictionary::GetEntry(Instance& inst, int id) { // поиск по id и вывод имени найденного элемента
	int tr = 0;
	for (int i = 0; i < inst.cnt; i++)
	{
		if (inst.dictionary[i].id == id)
		{
			cout << inst.dictionary[i].id << " - " << inst.dictionary[i].name << endl;
			return inst.dictionary[i];
		}
	}
	if (tr == 0) //если нет элемента с таким индентифекатором
		throw THROW05;
}

void Dictionary::UpdEntry(Instance& inst, int id, Entry new_ed)  
{
	int a = 0;
	for (int i = 0; i < inst.cnt; i++)
	{
		if (inst.dictionary[i].id == id)  //нашли элемент который надо заменить 
		{
			for (int j = i + 1; j < inst.cnt; j++) //проверка на уникальность id
			{
				if (new_ed.id == inst.dictionary[j].id) throw THROW08;
			}
			a = 1;

			inst.dictionary[i].id = new_ed.id;    
			strcpy_s(inst.dictionary[i].name, new_ed.name);
			break;
		}
		else if (new_ed.id == inst.dictionary[i].id) throw THROW08;
	}
	if (a == 0) // не найден элемент
	{
		throw THROW07;
	}
}

void Dictionary::Print(Instance& d)
{
	cout << "---------" << d.name << "---------" << endl;
	for (int i = 0; i < d.cnt; i++)
	{
		cout << d.dictionary[i].id << " " << d.dictionary[i].name << endl;
	}
	cout << "-------------------------------" << endl;
}
void Dictionary::Delete(Instance& inst)
{
	delete[] inst.dictionary;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	try
	{
		Dictionary::Instance d1 = Dictionary::Create("Преподаватели", 5); // Cоздание словаря
		Dictionary::Entry e1 = { 1, "Гладкий" }, e2 = { 2, "Веялкин" }, e3 = { 3, "Cмелов" }, e4 = { 4, "Урбанович" };


		Dictionary::AddEntry(d1, e1); // Добавление элемента словаря 
		Dictionary::AddEntry(d1, e2); // Добавление элемента словаря 
		Dictionary::AddEntry(d1, e3); // Добавление элемента словаря 
		Dictionary::AddEntry(d1, e4); // Добавление элемента словаря

		Dictionary::Print(d1);

		Dictionary::Entry ex2 = Dictionary::GetEntry(d1, 4); // найти элемент словаря по индентификатору

		Dictionary::DelEntry(d1, 2); // Удалить элемент из словаря по индентификатору

		Dictionary::Entry newentry1 = { 6, "Гурин" };

		Dictionary::UpdEntry(d1, 3, newentry1);


		Dictionary::Print(d1);

		Dictionary::Instance d2 = Dictionary::Create("Студенты", 5);

	}
	catch (const char* e)
	{
		cout << e << endl;
	}
	system("pause");
}