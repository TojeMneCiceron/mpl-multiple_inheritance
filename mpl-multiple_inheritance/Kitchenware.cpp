#include "Kitchenware.h"

Kitchenware::Kitchenware(int i_number)
{
	this->i_number = i_number;
}

Kitchenware::~Kitchenware()
{

}

string Kitchenware::Print()
{
	return "����������� �����: " + to_string(i_number) + ", " + kw_type;
}

Stove::Stove(int i_number, string color) : Kitchenware(i_number)
{
	this->color = color;
	this->kw_type = "�����";
	this->print = true;
}

string Stove::Print()
{
	string res = print ? Kitchenware::Print() : "";
	return res + ", ����: " + color;
}

Pan::Pan(int i_number, int capacity) : Kitchenware(i_number)
{
	this->capacity = capacity;
	this->kw_type = "��������";
	this->print = true;
}

string Pan::Print()
{
	return Kitchenware::Print() + ", �����: " + to_string(capacity);
}

EStove::EStove(int i_number, string color, int power) : Kitchenware(i_number), Stove(i_number, color)
{
	this->power = power;
	this->kw_type = "������������� �����";
	this->print = true;
}

string EStove::Print()
{
	return Stove::Print() + ", ��������: " + to_string(power);
}

GStove::GStove(int i_number, string color, int gas_consumption) : Kitchenware(i_number), Stove(i_number, color)
{
	this->gas_consumption = gas_consumption;
	this->kw_type = "������� �����";
	this->print = true;
}

string GStove::Print()
{
	return Stove::Print() + ", ������ ����: " + to_string(gas_consumption);
}

SlowCooker::SlowCooker(int i_number, string color, int capacity, int power, bool pressure_cooker_f) : Kitchenware(i_number), Pan(i_number, capacity), EStove(i_number, color, power)
{
	this->pressure_cooker_f = pressure_cooker_f;
	this->kw_type = "�����������";
	this->print = false;
}

string SlowCooker::Print()
{
	string psf = pressure_cooker_f ? "��" : "���";
	return Pan::Print() + EStove::Print() + ", ������� ����������: " + psf;
}
