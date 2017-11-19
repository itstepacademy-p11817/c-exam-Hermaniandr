#include <stdio.h>
#include <iostream>
#include <io.h>

using namespace std;

struct abonent
{
	char name[100];
	int mobile = -1;
	int home;
	int other;
};

int menu();
void show_contacts();
void search_by_name();
void search_by_number();
void add_contact();
void InsertionSort();

int N; //Текущее кол-во абонентов
abonent contact[100];
bool change = false; //Проверка на изменение списка контактов

int main()
{
	const int N0 = 100;//максимальное кол-во абонентов
	FILE *list;
	list = fopen("contacts", "rb");
	if (list == NULL)
	{
		list = fopen("contacts", "wb");
		fwrite(contact, sizeof(abonent), N0, list);

	}


	//считывание данных
	for (int i = 0; i < N0; i++)
		fread(&contact[i], sizeof(abonent), 1, list);

	for (int i = 0; i < N0; i++)
	{
		if (contact[i].mobile == 0 && contact[i].home == 0 && contact[i].other == 0) { N = i; break; }
	}
	cout << N << endl;
	fclose(list);

	system("cls");
	menu();

	if (change)
	{
		InsertionSort();
		fopen("contacts", "wb");
		fwrite(contact, sizeof(abonent), N0, list);
		fclose(list);
	}
	return 0;
}

//Меню 
//Чтобы начать работу непосредственно с контактами надо выбрать 1 пункт
int menu()
{
	cout << "\tMenu" << endl <<
		"1.Show contacts" << endl <<
		"2.Search by name" << endl <<
		"3.Search by number" << endl <<
		"4.Add contact" << endl <<
		"5.Call" << endl <<
		"6.Exit" << endl;
	int choise;
	//Такая вот забавная проверка на тип введённых данных(чтобы не крашилось при введение char/str) 
	if (scanf("%d", &choise) != 1) 
	{
		system("cls");
		cout << "You choosed wrong. \nEnter again please. \n\n";
		menu();
	}
	else{
		switch (choise)
		{
		case 1:
			system("cls");
			show_contacts(); break;
		case 2:
			system("cls");
			search_by_name(); break;
		case 3:
			system("cls");
			search_by_number(); break;
		case 4:
			system("cls");
			add_contact(); break;
		case 5:
			system("cls");
			search_by_number(); break;
		case 6:break;
		default:
		{
			system("cls");
			cout << "You choosed wrong. \nEnter again please. \n\n";
			menu();
		}
		}
		return 0;
	}

	
}

//Работа с контактами
void show_contacts()
{
	if (change) InsertionSort();
	for (int i = 0; i < N; i++)
	{
		cout << i << ". " << contact[i].name << endl;
		if (contact[i].mobile != 0)
			cout << "Mobile: " << contact[i].mobile << endl;
		if (contact[i].home != 0)
			cout << "Home: " << contact[i].home << endl;
		if (contact[i].other != 0)
			cout << "Other: " << contact[i].other << endl;
	}
	cout << "1.Show contact" << endl <<
		"2.Call a subscriber" << endl <<
		"3.Edit contact" << endl <<
		"4.Delete contact" << endl <<
		"5.Go to main menu" << endl;
	int choise;
	int number;
	if (scanf("%d", &choise) != 1)
	{
		system("cls");
		cout << "You choosed wrong. \nEnter again please. \n\n";
		show_contacts();
	}
	else
	{
		system("cls");
		switch (choise)
		{
			// Просмотр контакта (поиск по номеру контакта в телефонной книге, а не по его телефонному номеру)
		case 1:
		{
			cout << "Input the number of this contact" << endl;
			if (scanf("%d", &number) != 1)
			{
				system("cls");
				cout << "You choosed wrong. \nEnter again please. \n\n";
				show_contacts();
			}
			else {
				system("cls");
				cout << number << ". " << contact[number].name << endl;
				if (contact[number].mobile != 0)
					cout << "Mobile: " << contact[number].mobile << endl;
				if (contact[number].home != 0)
					cout << "Home: " << contact[number].home << endl;
				if (contact[number].other != 0)
					cout << "Other: " << contact[number].other << endl;

				cout << "Press Enter to Continue" << endl;
				while (getchar() != '\n');
				getchar();
				break;
			}
		}
		//Набор контакта по номеру
		//Несколько вариаций в зависимости от кол-ва номеров контакта
		case 2:
		{
			int quantity_of_numbers = 0;
			cout << "Input the number of this contact" << endl;
			if (scanf("%d", &number) != 1)
			{
				system("cls");
				cout << "You choosed wrong. \nEnter again please. \n\n";
				show_contacts();
			}
			else {
				if (contact[number].mobile != 0) quantity_of_numbers += 100;
				if (contact[number].home != 0) quantity_of_numbers += 10;
				if (contact[number].other != 0) quantity_of_numbers += 1;
				switch (quantity_of_numbers)
				{
				case 1: {cout << "Calling " << contact[number].name << endl; cin >> quantity_of_numbers; break; }
				case 10: {cout << "Calling " << contact[number].name << endl; cin >> quantity_of_numbers; break; }
				case 100: {cout << "Calling " << contact[number].name << endl; cin >> quantity_of_numbers; break; }
				case 11:
				{
					cout << "Call on the home(1) or other(2) number?";
					cin >> quantity_of_numbers;
					cout << "Calling " << contact[number].name << endl;
					cin >> quantity_of_numbers; break;
				}
				case 110:
				{
					cout << "Call on the home(1) or mobile(2) number?";
					cin >> quantity_of_numbers;
					cout << "Calling " << contact[number].name << endl;
					cin >> quantity_of_numbers; break;
				}
				case 101:
				{
					cout << "Call on the mobile(1) or other(2) number?";
					cin >> quantity_of_numbers;
					cout << "Calling " << contact[number].name << endl;
					cin >> quantity_of_numbers; break;
				}
				case 111:
				{
					cout << "Call on the home(1), mobile(2) or other(3) number?";
					cin >> quantity_of_numbers;
					cout << "Calling " << contact[number].name << endl;
					cin >> quantity_of_numbers; break;
				}

				}
				break;
			}
		}
		//Редактирование контакта
		case 3:
		{
			change = true;
			cout << "Input the number of this contact" << endl;
			if (scanf("%d", &number) != 1)
			{
				system("cls");
				cout << "You choosed wrong. \nEnter again please. \n\n";
				show_contacts();
			}
			else {
				cout << "Enter name" << endl;
				cin >> contact[number].name;
				cout << "Enter mobile number or '0' if you do not know it" << endl;
				cin >> contact[number].mobile;
				cout << "Enter home number or '0' if you do not know it" << endl;
				cin >> contact[number].home;
				cout << "Enter other number or '0' if you do not know it" << endl;
				cin >> contact[number].other;
				break;
			}

		}
		//Удаление контакта
		case 4:
		{
			change = true;
			cout << "Input the number of this contact" << endl;
			if (scanf("%d", &number) != 1)
			{
				system("cls");
				cout << "You choosed wrong. \nEnter again please. \n\n";
				show_contacts();
			}
			else {
				N--;
				for (int i = number; i < N; i++) contact[i] = contact[i + 1];
				for (int j = 0; j < 100; j++) contact[N].name[j] = ' ';
				contact[N].home = 0;
				contact[N].mobile = 0;
				contact[N].other = 0;

				break;
			}
		}
		//Выход в меню
		case 5: system("cls"); break;
		}
		menu();
	}
}

//Поиск по имени
void search_by_name()
{
	cout << "Enter the required name" << endl;
	char required[100];
	cin >> required;
	int lenght;
	for (int i = 0; i < 100; i++) if (required[i] == '\0')
	{
		lenght = i; break;
	}
	bool equal;
	for (int i = 0; i < N; i++)
	{
		equal = true;
		for (int j = 0; j < lenght; j++)
		{
			if (contact[i].name[j] != required[j])
			{
				equal = 0; break;
			}
		}
		if (equal)
		{
			cout << i << ". " << contact[i].name << endl;
			if (contact[i].mobile != 0)
				cout << "Mobile: " << contact[i].mobile << endl;
			if (contact[i].home != 0)
				cout << "Home: " << contact[i].home << endl;
			if (contact[i].other != 0)
				cout << "Other: " << contact[i].other << endl;
		}
	}
	menu();
}

//Поиск по номеру
void search_by_number()
{
	cout << "Enter the required number" << endl;
	int required, to_call = 3;
	int quantity_of_numbers = 0;
	if (scanf("%d", &required) != 1)
	{
		system("cls");
		cout << "You choosed wrong. \nEnter again please. \n\n";
		search_by_number();
	}
	else
	{
		for (int i = 0; i < N; i++)
			if (contact[i].home == required || contact[i].mobile == required || contact[i].other == required)
			{
				cout << i << ". " << contact[i].name << endl;
				if (contact[i].mobile != 0)
					cout << "Mobile: " << contact[i].mobile << endl;
				if (contact[i].home != 0)
					cout << "Home: " << contact[i].home << endl;
				if (contact[i].other != 0)
					cout << "Other: " << contact[i].other << endl;
				cout << "Would you like to call " << contact[i].name << "? (1/0)" << endl;
				cin >> to_call;
				if (to_call == 1)
				{
					cout << "Calling " << contact[i].name << endl;
					cin >> quantity_of_numbers; break;
				}
			}
		if (to_call != 3)
		{
			menu();
			return;
		}
		else
		{
			cout << "Calling " << required << ". Subscriber with this number wasn't found. Want to add a new contact? (1/0)" << endl;
			cin >> to_call;
		}
		if (to_call == 1) add_contact();
		else menu();
	}

}

//Добавление
void add_contact()
{
	change = true;
	N++;
	cout << "Enter name" << endl;
	cin >> contact[N - 1].name;
	cout << "Enter mobile number or '0' if you do not know it" << endl;
	cin >> contact[N - 1].mobile;
	cout << "Enter home number or '0' if you do not know it" << endl;
	cin >> contact[N - 1].home;
	cout << "Enter other number or '0' if you do not know it" << endl;
	cin >> contact[N - 1].other;
	menu();
}


//Сортировка
void InsertionSort()
{
	int location;
	abonent newElement;

	for (int i = 1; i < N; i++)
	{
		newElement = contact[i];
		location = i - 1;
		while (location >= 0 && contact[location].name[0] > newElement.name[0])
		{
			contact[location + 1] = contact[location];
			location = location - 1;
		}
		contact[location + 1] = newElement;
	}
}