#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <iomanip>
using namespace std;
class instructor
{
protected:
	char *name = new char;
	int ID;
	int numberofclients;

public:
	inline virtual void set()
	{
		cout << "enter employee name" << endl;
		fflush(stdin);
		cin.getline(name, 20);
		cout << "enter instructor id" << endl;
		cin >> ID;
	}
	inline virtual float calculate(char a[8])
	{
		return 0;
	}
};

class weights : virtual public instructor
{
protected:
	int w = 1000, tw = 1000;
};

class zumba : virtual public instructor
{
protected:
	int tz = 600;
};

class mma : virtual public instructor
{
protected:
	int m = 700, tm = 800;
};

class cardio : virtual public instructor
{
protected:
	int c = 500;
};
class client : public weights, public zumba, public mma, public cardio
{
protected:
	char *cname = new char;
	int membershipf = 0;

public:
	void set()
	{
		cout << "enter your name" << endl;
		fflush(stdin);
		cin.getline(cname, 20);
	}
	float calculate(char a[8]) // calculates fees
	{
		int k;
		for (int i = 0; i < 8; i++)
		{
			if (a[i] == '1')
			{
				membershipf += w;
				cout << "do you want a personal instructor for weights?" << endl
					 << "if yes enter 1 else enter 0" << endl;
				cin >> k;
				if (k == 1)
					membershipf += tw;
			}
			else if (a[i] == '2')
			{
				membershipf += tz;
			}
			else if (a[i] == '3')
			{
				membershipf += m;
				cout << "do you want a personal instructor for mma?" << endl;
				cout << "if yes enter1 else enter 0" << endl;
				cin >> k;
				if (k == 1)
					membershipf += tm;
			}
			else if (a[i] == '4')
				membershipf += c;
		}
		return membershipf;
	}

	void alter(int mode) // deletes membership
	{
		int flag = 0, result;
		string line, name;
		vector<string> lines;
		ifstream iofile("output.txt");
		if (iofile.fail())
		{
			cout << "unable to open file for reading" << endl;
			return;
		}
		while (getline(iofile, line))
		{
			lines.push_back(line);
		}
		iofile.close();
		cout << "enter your name:" << endl;
		fflush(stdin);
		cin.getline(cname, 30);
		name = cname;
		ofstream w("output.txt");
		if (w.fail())
		{
			cout << "unable to open file for writing" << endl;
			return;
		}
		for (int i = 0; i < lines.size(); i++)
		{
			if (name == lines[i].substr(0, name.length()))
			{
				if (mode == 1 && flag == 0)
				{
					flag = 1;
					cout << "choose your new facility" << endl;
					cout << "1:weights    2:zumba    3:mma    4:cardio" << endl;
					fflush(stdin);
					cin.getline(cname, 8);
					result = calculate(cname);
					w << lines[i].substr(0, name.length()) << " " << result << "\n";
					cout << "you're facility choice has been updated" << endl;
					continue;
				}
				if (mode == 2)
				{
					flag = 1;
					cout << "memebership deleted" << endl;
					continue;
				}
			}
			w << lines[i] << "\n";
		}
		w.close();
		if (flag == 0)
			cout << "INVALID NAME ENETERED" << endl;
	}
	void renew_membership(string &l) // renews membership for n months
	{
		string t;
		int flag = 0, months;
		ifstream read("output.txt");
		if (read.fail())
		{
			cout << "unable to open file" << endl;
			return;
		}
		while (getline(read, t))
		{
			if (t.substr(0, l.length()) == l)
			{
				flag = 1;
				t = t.substr(l.length(), t.length());
				cout << "By how many months do you want too extend your membership?" << endl;
				cin >> months;
				try
				{
					cout << "Your membership fees for " << months << " months is:" << renew(t, months) << endl;
				}
				catch (...)
				{
					cerr << "invalid name entered or an error has occurred" << endl;
				}
			}
		}
		read.close();
		if (flag == 0)
		{
			cout << "INVALID NAME ENTERED!!" << endl;
			return;
		}
	}
	int renew(string &t, int m) // renews gym membership
	{
		membershipf = stoi(t);
		membershipf = membershipf * m;
		if (m <= 3)
		{
			membershipf = membershipf - (membershipf * 20 / 100);
		}
		else if (m > 3 && m < 12)
		{
			membershipf = membershipf - (membershipf * 30 / 100);
		}
		else if (m == 12)
		{
			membershipf = membershipf - (membershipf * 40 / 100);
		}
		else if (m > 12)
		{
			membershipf = membershipf - (membershipf * 50 / 100);
		}
		return membershipf;
	}
	friend ostream &operator<<(ostream &out, client &c);
};

ostream &operator<<(ostream &out, client &c) // overloaded << operator for entering object directly to file
{
	out << c.cname << " ";
	out << c.membershipf << endl;
	return out;
}
class expense : public instructor // to calculate salary
{
	int e = 8000;

public:
	void salary() // calculates salary of instructor
	{
		int id, flag = 0;
		ifstream inputFile("instructors.txt");
		if (inputFile.fail())
		{
			cout << "unable to open file for reading" << endl;
			return;
		}
		cout << "enter instructor id" << endl;
		cin >> id;
		while (inputFile >> ID >> numberofclients)
		{
			if (id == ID)
			{
				flag = 1;
				inputFile.close();
				try
				{
					if (numberofclients != 0)
					{
						e = e + numberofclients * 500;
						display();
					}
					else
					{
						throw numberofclients;
					}
				}
				catch (int)
				{
					cout <<setw(40)<< "instructor has zero clients" << endl;
					cout << setw(34)<<"stipend is 8000" << endl;
				}
			}
		}
		if (flag == 0)
			cout << "invalid ID entered" << endl;
	}
	void instructors_list()
	{
		ifstream read("instructors.txt");
		if (read.fail())
		{
			cout << "unable to open file for reading" << endl;
			return;
		}
		cout << setw(5) << "ID" << setw(20) << "number of clients" << endl;
		while (read >> ID >> numberofclients)
		{
			cout << setw(6) << ID << setw(10) << numberofclients << endl;
		}
		read.close();
		cout << endl;
	}
	void display()
	{
		cout << "instructor salary is:" << e << endl;
	}
};

int main()
{
	ifstream openf("instructors.txt");
	if(openf){}
	else
	{
		ofstream wf("instructors.txt");
		wf.close();
	}
	openf.close();
	int ch;
	while (1)
	{
		cout << "1:create member" << endl;
		cout << "2:renew membership" << endl;
		cout << "3:change facility" << endl;
		cout << "4:cancel membership" << endl;
		cout << "5:instructor's list" << endl;
		cout << "6:calculate instructor salary" << endl;
		cout << "7:EXIT" << endl;
		cin >> ch;
		client cli;
		instructor *cl = &cli;
		expense E;
		char *a = new char;
		ofstream add("output.txt", ios::app);
		string s;
		switch (ch)
		{
		case 1:
			cl->set();
			cout << "Choose desired facility from following:" << endl;
			cout << "1:weights    2:zumba    3:mma    4:cardio" << endl;
			fflush(stdin);
			cin.getline(a, 8);
			cout << "your gym fees are:" << cl->calculate(a) << endl;
			delete a;
			add << cli;
			add.close();
			break;
		case 2:
			cout << "enter your name" << endl;
			fflush(stdin);
			cin.getline(a, 30);
			s = a;
			delete a;
			dynamic_cast<client *>(cl)->renew_membership(s);
			break;
		case 3:
			dynamic_cast<client *>(cl)->alter(1);
			break;
		case 4:
			cout << "do you really want to cancel your membership?enter 1 if yes else 0" << endl;
			cin >> ch;
			if (ch == 1)
				dynamic_cast<client *>(cl)->alter(2);
			break;
		case 5:
			cl = &E;
			dynamic_cast<expense *>(cl)->instructors_list();
			break;
		case 6:
			cl = &E;
			dynamic_cast<expense *>(cl)->salary();
			break;
		case 7:
			exit(1);
			break;
		default:
			cout << "Enter a valid option" << endl;
		}
	}
	return 0;
}