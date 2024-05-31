#include <iostream > 
#include <string>
#include<process.h>
#include<fstream>
#include <stdlib.h>
using namespace std;

struct Person
{
	string name;
	int totalitems;
	char Iname[50][50];
	float Qty[3];
	float price[3];
	float tprice[3];
	float vats;
	int vatprice[3];

} p1;

void inputs()
{
	cout << "\nEnter number of items= ";
	cin >> p1.totalitems;
	cout << p1.totalitems;
	for (int i = 0; i < p1.totalitems; i++)
	{
		cout << "\nEnter name of item " << i + 1 << ": ";
		cin >> p1.Iname[i];
		cout << "Enter quantity: ";
		cin >> p1.Qty[i];
		cout << "Enter price of item " << i + 1 << ": ";
		cin >> p1.price[i];
		p1.tprice[i] = p1.Qty[i] * p1.price[i];

		cout << p1.tprice[i];
	}

}

void output()
{
	int a;

	ifstream infile("COUNT.TXT");
	infile >> a;

	ofstream outfile("COUNT.TXT");
	a += 1;
	outfile << a;
	outfile.close();

	{ofstream outfile("HIS.TXT", ios::app);
	outfile << endl << "Bill No.: " << a << endl;
	outfile << "------------------------------------------------------------------------" << endl;
	cout << "\n";
	cout << "Name of Item\tQuantity   Price  Total Price\n";
	for (int i = 0; i < p1.totalitems; i++)
	{
		outfile << "Name: " << p1.Iname[i] << " Qty: " << p1.Qty[i] << " Price: " << p1.tprice[i] << endl;
		cout << p1.Iname[i] << "\t\t" << p1.Qty[i] << "\t   " << p1.price[i] << "\t   " << p1.tprice[i] << '\n';
	}

	outfile << "------------------------------------------------------------------------" << endl;
	outfile.close();
	}
}

void vatcal()
{
	inputs();
	for (int i = 0; i < p1.totalitems; i++)
	{
		if (p1.price[i] <= 100.00)
		{
			p1.vatprice[i] = p1.tprice[i] + (0.03 * p1.tprice[i]);
		}
		else
		{
			p1.vatprice[i] = p1.tprice[i] + (0.1 * p1.tprice[i]);
		}
	}
}

void outputs()
{
	output();

	float cash = 0, sum = 0, qty = 0, sumt = 0;

	for (int i = 0; i < p1.totalitems; i++)
	{
		sumt += p1.tprice[i];
		sum += p1.vatprice[i];
		qty += p1.Qty[i];
	}
	cout << "\nTotal:";
	cout << "\n------------------------------------------------------------------------------";
	cout << "\n\tQuantity= " << qty << "\t\t Sum= " << sumt << "\tWith Vat:" << sum;
	cout << "\n------------------------------------------------------------------------------";

pay:

	cout << "\n\n\t\t\t***PAYMENT SUMMARY*\n";
	cout << "\n\t\t\tTotal cash given: ";
	cin >> cash;

	if (cash >= sum)
		cout << "\n\t\t\tTotal cash returned: " << cash - sum << '\n';

	else
	{
		cout << "\n\t\t\tCash given is less than total amount!!!";

		goto pay;
	}
}





int passwords()
{

	char p1, p2, p3;

	cout << "\n\n\n\n\n\n\t\t\tENTER THE PASSWORD: ";

	cin >> p1;
	cout << "*";
	cin >> p2;
	cout << "*";
	cin >> p3;
	cout << "*";

	if ((p1 == 's' || p1 == 'S') && (p2 == 'i' || p2 == 'I') && (p3 == 'd' || p3 == 'D'))

		return 1;

	else
		return 0;
}



int main()
{

	char opt, ch;
	int a = 1;
	ifstream fin;

	a == passwords();
	if (!a)
	{
		for (int i = 0; i < 2; i++)
		{
			cout << "\nWrong password try once more\n";
			if (passwords())
			{
				goto last;
			}
			else
			{
				cout << "\n\n\t\t\t all attempts failed.....";
				cout << "\n\n\n\t\t\t see you.................. ";
				exit(0);
			}

		}
		cout << "\t\t\t sorry all attempts failed............. \n \t\t\tinactive";
	}
	else {
	last:;


		do
		{
		start:
			system("PAUSE");
			system("CLS");
			cout << "\n\n\t\t\t------------------------------";
			cout << "\n\t\t\tShop Billing Management System";
			cout << "\n\t\t\t------------------------------";
			cout << "\n\n\t\t\tWhat you want to do?";
			cout << "\n\t\t\t1.\tTo enter new entry\n\t\t\t2.\tTo view previous entries\n\t\t\t3.\tExit\n";
			cout << "\n\nEnter your option: ";
			cin >> opt;
			switch (opt)
			{
			case'1':
				vatcal();

				outputs();
				goto start;
			case'2':

				fin.open("HIS.TXT", ios::in);
				while (fin.get(ch))
				{
					cout << ch;
				}
				fin.close();

				goto start;
			case'3':
				exit(0);
			default:
				cout << "\a";
			}

		} while (opt != 3);
	}
	return 0;
}
