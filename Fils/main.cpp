#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
//#define READ_FROM_FILE
//#define HOME_WORK_T1

const char* UNITS[] = { "B", "kB", "MB", "GB" };

void main()
{
	setlocale(LC_ALL, "");
	//	std::cout << "Hello World";
	//	std::cout << endl;
		//https://legacy.cplusplus.com/doc/tutorial/files/

#ifdef WRITE_TO_FILE

	ofstream fout;			//1) ������� �����
	fout.open("File.txt", std::ios_base::app);	//2) ��������� �����
	fout << "Hello Files" << endl;//3) ����� � �����
	fout << "���� ������" << endl;
	fout.close();			//4) ����� ���� ��� ������ � ����� ���������, ��� ����������� ����� �������!!!
	system("notepad File.txt");

#endif // WRITE_TO_FILE
#ifdef READ_FROM_FILEDEBUG

	std::ifstream fin("File.txt");
	cout << "��������� ������� �������: " << fin.tellg() << endl;
	fin.seekg(0, ios::end);
	int i = 0;
	int filesize = fin.tellg();
	cout << "�������� ������� �������: " << filesize << endl;
	for (; filesize > 1024; i++, filesize /= 1024);
	cout << "������ �����: " << filesize << " " << UNITS[i] << endl;
	//fin.tellg() - tell get position (������� ������ ������������ �������)
	system("PAUSE");
	if (fin.is_open())
	{
		//TODO: ����� ������ �� �����
		const int SIZE = 1024 * 512;
		char sz_buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> sz_buffer;
			fin.getline(sz_buffer, SIZE);	//getline() ��������� ������ ������ � ���������, �� ��������� �����������
			//�� ���������, ������������ ��� fin.getline() �������� '\n'
			cout << sz_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}

#endif // READ_FROM_FILEDEBUG
#ifdef HOME_WORK_T1

	string fileName;
	cin >> fileName;

	fileName += ".txt";

	ofstream outfile(fileName);
	outfile << "Hello Files" << endl;
	outfile << "���� ������" << endl;
	outfile.close();
	ifstream infile(fileName);

#endif // HOME_WORK_T1
	
	streampos size;
	char* memblock;

	ifstream file("201 RAW.txt", ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		std::cout.write(memblock, size);

		delete[] memblock;
	}

}