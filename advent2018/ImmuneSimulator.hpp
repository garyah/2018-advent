#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

namespace Advent2018
{
	typedef enum
	{
		Cold = 1 << 0,
		Fire = 1 << 1,
		Radiation = 1 << 2,
		Bludgeoning = 1 << 3,
		Slashing = 1 << 4,
	} AttackType;
	typedef enum
	{
		ImmuneSystem = 0,
		Infection = 1,
		InvalidType
	} GroupType;
	typedef struct
	{
		unsigned numUnits;
		unsigned hitPoints;
		unsigned immunities;
		unsigned weaknesses;
		unsigned attackDamage;
		AttackType attackType;
		unsigned initiative;
	} Group;
	typedef vector<Group> Army;
	typedef unordered_set<unsigned> SomeSet;
	typedef unordered_map<unsigned, unsigned> SomeMap;

	struct ImmuneSimulator
	{
		ImmuneSimulator(unsigned field1 = 0,
			int field2 = 0,
			const char *field3 = "",
			int dummy = 0) :
			_field1(field1),
			_field2(field2),
			_field3(field3),
			_dummy(dummy)
		{
		}

		void addGroup(unsigned arg1 = 0u, int arg2 = 0, const char *arg3 = "")
		{
			_field1 = arg1;
			_field2 = arg2;
			_field3 = arg3;
		}

		void method2()
		{
		}

		void helper1(unsigned arg1, int arg2, unsigned& out1, string& out2)
		{
			out1 = 0;
			out2.empty();
		}

		void helper2()
		{
		}

		unsigned _field1;
		int _field2;
		string _field3;
		int _dummy;

		Army _immuneSystem;
		Army _infection;
		SomeSet _someSet;
		SomeMap _someMap;
	};
}
