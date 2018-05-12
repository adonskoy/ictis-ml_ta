#include <iostream>
#include<fstream>
using namespace std;

struct parametry
{
	int count1;
	int count2;
	int *arrayA;
	int *arrayX;
	int *arrayY;
};

void read(const char *file_name, parametry &data)
{
	ifstream in(file_name, ios::in);
	in>> data.count1;
	in >> data.count2;
	data.arrayA = new int[data.count1];
	data.arrayX = new int[data.count2];

	for (int i = 0; i < data.count1; i++) 
	{
		in >> data.arrayA[i];
	}
	for (int i = 0; i < data.count2; i++)
	{
		in >> data.arrayX[i];
	}

	in.close();
}

void found_Y(parametry &data)
{
	data.arrayY = new int[data.count2];
	for (int i = 0; i < data.count2; i++)
	{
		int degree = data.count1 - 1;
		int result = 0;
		for (int j = 0; j < data.count1; j++)
		{
			result += data.arrayA[j] * data.arrayX[i] ^ degree;
			degree--;
		}
		data.arrayY[i] = result;
	}
}
void write_results(const char *file_name, parametry data)
{
	ofstream out(file_name, ios::out);
	out << data.count2 << endl;
	for (int i = 0; i<data.count2; i++) 
	{
		out << data.arrayX[i] << " "<<data.arrayY[i]<<endl;
	}
	delete [] data.arrayA;
	delete [] data.arrayX;
	delete [] data.arrayY;
	out.close();
}
int main()
{
	parametry func1;
//-------------------------------------------
	read("input.txt", func1);
//-------------------------------------------
	found_Y(func1);
//-------------------------------------------
	write_results("output.txt",func1);
	return 0;
}
