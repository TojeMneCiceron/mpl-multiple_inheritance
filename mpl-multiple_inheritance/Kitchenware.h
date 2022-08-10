#pragma once
#include <string>
using namespace std;

class Kitchenware
{
public:
	int i_number;
	string kw_type;
	Kitchenware(int i_number);
	virtual ~Kitchenware();
	virtual string Print();
	bool print;
};

class Stove : virtual public Kitchenware
{
public:
	string color;
	Stove(int i_number, string color);
	string Print() override;
};

class Pan : virtual public Kitchenware
{
public:
	int capacity;
	Pan(int i_number, int capacity);
	string Print() override;
};

class EStove : public Stove
{
public:
	int power;
	EStove(int i_number, string color, int power);
	string Print() override;
};

class GStove : public Stove
{
public:
	int gas_consumption;
	GStove(int i_number, string color, int gas_consumption);
	string Print() override;
};

class SlowCooker : public Pan, public EStove
{
public:
	bool pressure_cooker_f;
	SlowCooker(int i_number, string color, int capacity, int power, bool pressure_cooker_f);
	string Print() override;
};