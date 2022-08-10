#include <iostream>
#include <Windows.h>
#include "Kitchenware.h"
using namespace std;

struct Tree
{
	Kitchenware* data;
	Tree* left;
	Tree* right;
	int height;

	Tree(Kitchenware* x)
	{
		data = x;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
};

Tree* Root = nullptr;

//функции дерева

int Height(Tree* p)
{
	return p ? p->height : 0;
}

int HeightDiff(Tree* p)
{
	return Height(p->right) - Height(p->left);
}

void NewHeight(Tree* p)
{
	int hl = Height(p->left);
	int hr = Height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}


Tree* R(Tree* p)
{
	Tree* q = p->left;
	p->left = q->right;
	q->right = p;
	NewHeight(p);
	NewHeight(q);
	return q;
}


Tree* L(Tree* q)
{
	Tree* p = q->right;
	q->right = p->left;
	p->left = q;
	NewHeight(q);
	NewHeight(p);
	return p;
}


Tree* Balance(Tree* p)
{
	NewHeight(p);
	if (HeightDiff(p) == 2)
	{
		if (HeightDiff(p->right) < 0)
			p->right = R(p->right);
		return L(p);
	}
	if (HeightDiff(p) == -2)
	{
		if (HeightDiff(p->left) > 0)
			p->left = L(p->left);
		return R(p);
	}
	return p;
}


Tree* Insert(Tree* Root, Tree* x)
{
	if (Root == nullptr)
		return x;
	if (x->data->i_number < Root->data->i_number)
		Root->left = Insert(Root->left, x);
	else
		Root->right = Insert(Root->right, x);
	return Balance(Root);
}

Tree* Min(Tree* p)
{
	return p->left ? Min(p->left) : p;
}

Tree* DelMin(Tree* p)
{
	if (p->left == 0)
		return p->right;
	p->left = DelMin(p->left);
	return Balance(p);
}

Tree* Delete(Tree* Root, int i_number)
{
	if (Root == nullptr)
		return nullptr;
	if (i_number < Root->data->i_number)
		Root->left = Delete(Root->left, i_number);
	else
		if (i_number > Root->data->i_number)
			Root->right = Delete(Root->right, i_number);
		else
		{
			Tree* q = Root->left;
			Tree* r = Root->right;
			delete Root->data;
			delete Root;
			if (r == nullptr)
				return q;
			Tree* min = Min(r);
			min->right = DelMin(r);
			min->left = q;
			return Balance(min);
		}
	return Balance(Root);
}

bool Find(Tree* Root, int i_number)
{
	if (Root == nullptr)
		return false;
	if (Root->data->i_number == i_number)
		return true;
	if (i_number < Root->data->i_number)
		return Find(Root->left, i_number);
	else
		return Find(Root->right, i_number);
}

void DeleteTree(Tree* Root)
{
	if (Root == nullptr)
		return;
	DeleteTree(Root->left);
	DeleteTree(Root->right);
	delete Root->data;
	delete Root;
}
//ввод инв. номера
int I_Num()
{
	int i_number;
	while (true)
	{
		string answer;
		cout << "\nВведите инвентарный номер\n";
		cin >> answer;
		try
		{
			i_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "\nВведен некорректный инвентарный номер\n";
			continue;
		}
		if (Find(Root, i_number))
		{
			cout << "\nИнвентарный номер занят\n";
			continue;
		}
		break;
	}
	return i_number;
}
//ввод объема
int Capacity()
{
	int capacity;
	while (true)
	{
		string answer;
		cout << "\nВведите объем\n";
		cin >> answer;
		try
		{
			capacity = stoi(answer);
		}
		catch (exception e)
		{
			cout << "\nНекорректный ввод\n";
			continue;
		}
		break;
	}
	return capacity;
}
//ввод мощности
int Power()
{
	int power;
	while (true)
	{
		string answer;
		cout << "\nВведите мощность\n";
		cin >> answer;
		try
		{
			power = stoi(answer);
		}
		catch (exception e)
		{
			cout << "\nНекорректный ввод\n";
			continue;
		}
		break;
	}
	return power;
}
//ввод расхода газа
int Gas_Consum()
{
	int gas_consumption;
	while (true)
	{
		string answer;
		cout << "\nВведите расход газа\n";
		cin >> answer;
		try
		{
			gas_consumption = stoi(answer);
		}
		catch (exception e)
		{
			cout << "\nНекорректный ввод\n";
			continue;
		}
		break;
	}
	return gas_consumption;
}
//ввод функции скороварки
bool P_Cooker_F()
{
	bool pressure_cooker_f;
	while (true)
	{
		string answer;
		cout << "\nИмеется ли функция скороварки? да/нет\n";
		cin >> answer;
		if (answer == "да")
		{
			pressure_cooker_f = true;
			break;
		}
		else
			if (answer == "нет")
			{
				pressure_cooker_f = false;
				break;
			}
			else
				cout << "\nНекорректный ввод\n";
	}
	return pressure_cooker_f;
}
//плита
void InsertStove()
{
	int i_number;
	string color;
	
	i_number = I_Num();

	cout << "\nВведите цвет\n";
	cin >> color;

	Kitchenware* x = new Stove(i_number, color);
	Root = Insert(Root, new Tree(x));
}
//кастрюля
void InsertPan()
{
	int i_number, capacity;

	i_number = I_Num();

	capacity = Capacity();

	Kitchenware* x = new Pan(i_number, capacity);
	Root = Insert(Root, new Tree(x));
}
//эл. плита
void InsertEStove()
{
	int i_number, power;
	string color;
	
	i_number = I_Num();

	cout << "\nВведите цвет\n";
	cin >> color;

	power = Power();

	Kitchenware* x = new EStove(i_number, color, power);
	Root = Insert(Root, new Tree(x));
}
//газ.плита
void InsertGStove()
{
	int i_number, gas_consumption;
	string color;
	
	i_number = I_Num();

	cout << "\nВведите цвет\n";
	cin >> color;

	gas_consumption = Gas_Consum();

	Kitchenware* x = new GStove(i_number, color, gas_consumption);
	Root = Insert(Root, new Tree(x));
}
//мультиварка
void InsertSlowCooker()
{
	int i_number, capacity, power;
	string color;
	bool pressure_cooker_f;
	
	i_number = I_Num();

	cout << "\nВведите цвет\n";
	cin >> color;

	capacity = Capacity();

	power = Power();

	pressure_cooker_f = P_Cooker_F();

	Kitchenware* x = new SlowCooker(i_number, color, capacity, power, pressure_cooker_f);
	Root = Insert(Root, new Tree(x));
}
//диалог добавления
void InsertDialog()
{
	while (true)
	{
		string answer;
		cout << "Выберите тип кухонной утвари\n1 - Плита\n2 - Кастрюля\n3 - Электрическая плита\n4 - Газовая плита\n5 - Мультиварка\n";
		cin >> answer;
		if (answer == "1")
		{
			InsertStove();
			break;
		}
		else
			if (answer == "2")
			{
				InsertPan();
				break;
			}
			else
				if (answer == "3")
				{
					InsertEStove();
					break;
				}
				else
					if (answer == "4")
					{
						InsertGStove();
						break;
					}
					else
						if (answer == "5")
						{
							InsertSlowCooker();
							break;
						}
						else
							cout << "\nНекорректный ввод\n";
	}
}
//диалог удаления
void DeleteDialog()
{
	int i_number;
	while (true)
	{
		string answer;
		cout << "\nВведите инвентарный номер\n";
		cin >> answer;
		try
		{
			i_number = stoi(answer);
		}
		catch (exception e)
		{
			cout << "\nВведен некорректный инвентарный номер\n";
			continue;
		}
		break;
	}
	if (Find(Root, i_number))
	{
		Root = Delete(Root, i_number);
		cout << "\nКухонная утварь успешно удалена\n";
	}
	else
		cout << "\nНет кухонной утвари с таким номером\n";
}
//прямой обход
void NLR(Tree* Root)
{
	if (Root == nullptr)
		return;
	cout << endl << Root->data->Print();
	NLR(Root->left);
	NLR(Root->right);
}
//обратный обход
void LRN(Tree* Root)
{
	if (Root == nullptr)
		return;
	LRN(Root->left);
	LRN(Root->right);
	cout << endl << Root->data->Print();
}
//симметричный обход
void LNR(Tree* Root)
{
	if (Root == nullptr)
		return;
	LNR(Root->left);
	cout << endl << Root->data->Print();
	LNR(Root->right);
}
//диалог вывода
void ShowDialog()
{
	while (true)
	{
		string answer;
		cout << "\nВыберите способ вывода данных\n1 - Прямой обход\n2 - Обратный обход\n3 - Симметричный обход\n";
		cin >> answer;
		if (answer == "1")
		{
			NLR(Root);
			break;
		}
		else
			if (answer == "2")
			{
				LRN(Root);
				break;
			}
			else
				if (answer == "3")
				{
					LNR(Root);
					break;
				}
				else
					cout << "\nНекорректный ввод\n";
	}
	cout << endl << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	while (true)
	{
		string answer;
		cout << "Выберите действие\n1 - Добавить\n2 - Удалить\n3 - Вывод данных\n4 - Выход\n";
		cin >> answer;
		if (answer == "1")
			InsertDialog();
		else
			if (answer == "2")
				DeleteDialog();
			else
				if (answer == "3")
					ShowDialog();
				else
					if (answer == "4")
						break;
					else
						cout << "Некорректный ввод\n";
	}
	DeleteTree(Root);
	return 0;
}