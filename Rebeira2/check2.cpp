//AyeshRebeira 
//CSIS 252 
//Assignment2
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int main(int argc, char *argv[])
{
	ifstream fileName;

	// variable storing hte file name entered by user
	string promptFile;
	cout << "Enter the name of the file: ";
	cin >> promptFile;
	
	fileName.open(promptFile);
	
	string unit, type;
	string unitArray[10000]; 
	string typeArray[10000];
	int count = 0;
	
	// bool to end loop
	bool endP = false;

		
	// check the file name exists.
	if(!fileName)
		cerr << "Invalid File" << endl;
	else
	{
		cout << "Your file exist" << endl;
		cout << "\n-------0--------\n" << endl;

		while (fileName >> unit >> type)
		{

			cout << unit << "---" << type << endl;
			unitArray[count] = unit;
			typeArray[count] = type;
			count ++;
		}							
	}
	
		
	string type1, type2;

	
	int countUnit1 = -1, countUnit2 = -1;
		
	while (!endP)
	{	
		cout << "Enter two units to convert: ";
		cin >> unit >> type;
		
		for (int i=0; i < count; i++)
		{
			if (unit == unitArray[i]){
				countUnit1 = i;}
			if (type == unitArray[i]){
				countUnit2 = i;}
		}
		
		if (countUnit1 == -1 || countUnit2 == -1)
		{	cerr << "Invalid units" << endl;}
		else
		{
			type1 = typeArray[countUnit1];
			type2 = typeArray[countUnit2];
			
			if (type1 == type2)
			{
				cout << "They are convertible" << endl;
			}
			else
			{
				cerr << "They are not convertible" << endl;
			}
		}
		countUnit1 = -1;
		countUnit2 = -1;
		
		int finishP;
		cout << "Press '0' to terminate your program or '1' to continue: ";
		cin >> finishP;
		
		if (finishP == 0)
		{
			endP = true;
		}
	}

	return 0;

}
