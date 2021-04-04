/******************************************************************************
*                                                                             *
*   Program : Transactions Lists & Claims                                     *
*                                                                             *
*                                                                             *
*                                                                             *
*   Programmer : Nikita Seliverstov (nikselko)                                *
*                                                                             *
*                                                                             *
******************************************************************************/

#include "TransFunc.h"

string ask_file_name()
{
	string tmp_input;
	cout << "Enter file name: ";
	cin >> tmp_input;
	return tmp_input;
}


void Menu::menu(string m_file_name)
{
	auto choise = 0;
	auto exitStatus = false;

	while (!exitStatus)
	{
		system("cls");
		cout << "Opened: " << m_file_name << endl << endl << endl
			<< "Select an Option: " << endl
			<< "1.		Count of transactions" << endl
			<< "2.		Minimum resource size" << endl
			<< "3.		All transactions" << endl
			<< "4.		Transactions of ID" << endl
			<< "5.		Sum of claims untill N" << endl
			<< "6.		List identifiers" << endl
			<< "7.		Validate" << endl
			<< "8.		Quit" << endl << endl << endl
			<< "-> ";
		cin >> choise;

		if (choise > 0 && choise < 9)
		{
			switch (choise)
			{
			case 1:
				print_count();
				cout << endl;
				system("pause");
				break;
			case 2:
				minimum_resource_size();
				cout << endl;
				system("pause");
				break;
			case 3:
				all_transactions();
				cout << endl;
				system("pause");
				break;
			case 4:
				transaction_of_id("user", " ");
				cout << endl;
				system("pause");
				break;
			case 5:
				sum_untill();
				cout << endl;
				system("pause");
				break;
			case 6:
				list_identifies();
				cout << endl;
				system("pause");
				break;
			case 7:
				validate();
				cout << endl;
				system("pause");
				break;
			case 8:
				exitStatus = true;
			}
		}
		else
		{
			system("cls");
			cout << "ERROR: Wrong menu choise! Try typing 1-8" << endl;
			system("pause");
			break;
		}
	}
}

void Menu::print_count()
{
	cout << endl << endl
		<< "There are: " 
		<< transactionsList.count() 
		<< " transactions" << endl;
}

void Menu::minimum_resource_size()
{
	int* min_res_array = new int[transactionsList.count()];

	for (auto i = 0; i < transactionsList.count(); i++)
	{
		if (transactionsList.transactions[i].value == 0)
		{
			min_res_array[i] = min_res_array[i - 1];

			for (auto j = 0; j < i; j++)
			{				
				if (transactionsList.transactions[i].id == transactionsList.transactions[j].id)
					min_res_array[i] -= transactionsList.transactions[j].value;
			}
		}
		else if (i == 0)
			min_res_array[i] = transactionsList.transactions[i].value;
		else 
		{
			min_res_array[i] = min_res_array[i - 1];
			min_res_array[i] = min_res_array[i] + transactionsList.transactions[i].value;
		}
	}
	
	int min_res_size;
	min_res_size = min_res_array[0];

	for (auto j = 1; j < transactionsList.count(); j++)
		if (min_res_size < min_res_array[j])
			min_res_size = min_res_array[j];
	
	cout << endl << endl
		<< "Minimum pool for resources is: "
		<< min_res_size
		<< " memmory units" << endl;

	delete [] min_res_array;
}

void Menu::all_transactions()
{
	int* all_res_array = new int[transactionsList.count()];
	string* all_id_array = new string[transactionsList.count()];
	int* all_value_array = new int[transactionsList.count()];

	for (auto i = 0; i < transactionsList.count(); i++)
	{
		all_res_array[i] = transactionsList.transactions[i].value;
		all_id_array[i] = transactionsList.transactions[i].id;
		all_value_array[i] = transactionsList.transactions[i].value;
	}

	resource_processing(all_res_array, all_id_array, all_value_array, transactionsList.count());

	delete[] all_res_array;
	delete[] all_id_array;
	delete[] all_value_array;
}

int Menu::transaction_of_id(string callingMode, string identifier)
{
	string tmp_input_id;

	if (callingMode == "user")
	{
		cout << endl << "ID: ";
		cin >> tmp_input_id;
	}
	else if (callingMode == "auto")
	{
		tmp_input_id = identifier;
	}

	auto tmp_count = 0;

	for (auto i = 0; i < transactionsList.count(); i++)
		if (transactionsList.transactions[i].id == tmp_input_id)
			tmp_count++;

	int* ofid_res_array = new int[tmp_count];
	string* ofid_id_array = new string[tmp_count];
	int* ofid_value_array = new int[tmp_count];

	tmp_count = 0;

	for (auto i = 0; i < transactionsList.count(); i++)
	{
		if (transactionsList.transactions[i].id == tmp_input_id)
		{
			ofid_res_array[tmp_count] = transactionsList.transactions[i].value;
			ofid_id_array[tmp_count] = transactionsList.transactions[i].id;
			ofid_value_array[tmp_count] = transactionsList.transactions[i].value;
			tmp_count++;
		}
	}

	auto returnValue = resource_processing(ofid_res_array, ofid_id_array, ofid_value_array, tmp_count);

	delete[] ofid_res_array;
	delete[] ofid_id_array;
	delete[] ofid_value_array;

	return returnValue;
}

void Menu::sum_untill()
{
	int tmp_input_count;

	cout << endl << "Untill n = ";
	cin >> tmp_input_count;

	if (tmp_input_count > transactionsList.count())
	{
		system("cls");
		cout << "ERROR WRONG COUNT!!!" << endl;
	}
	else
	{
		int* untill_res_array = new int[tmp_input_count];
		string* untill_id_array = new string[tmp_input_count];
		int* untill_value_array = new int[tmp_input_count];

		for (auto i = 0; i < tmp_input_count; i++)
		{
			untill_res_array[i] = transactionsList.transactions[i].value;
			untill_id_array[i] = transactionsList.transactions[i].id;
			untill_value_array[i] = transactionsList.transactions[i].value;
		}

		resource_processing(untill_res_array, untill_id_array, untill_value_array, tmp_input_count);

		delete[] untill_res_array;
		delete[] untill_id_array;
		delete[] untill_value_array;
	}
}

void Menu::list_identifies()
{
	string* unique_list_identifiers = new string[transactionsList.MAX_TRANSACTIONS];
	auto tmp_count = 0;

	for (auto i = 0; i < transactionsList.count(); i++)
	{
		if (tmp_count != 0)
		{
			auto matches_count = 0;

			for (auto j = 0; j < tmp_count; j++)
				if (unique_list_identifiers[j] != transactionsList.transactions[i].id)
					matches_count++;

			if (matches_count == tmp_count)
			{
				unique_list_identifiers[tmp_count] = transactionsList.transactions[i].id;
				tmp_count++;
			}
		}
		else
		{
			unique_list_identifiers[tmp_count] = transactionsList.transactions[i].id;
			tmp_count++;
		}
	}

	for (auto i = 0; i < tmp_count; i++)
		cout << unique_list_identifiers[i] << endl;
	
	delete[] unique_list_identifiers;
}

void Menu::validate()
{
	string* validate_list_identifiers = new string[transactionsList.MAX_TRANSACTIONS];
	auto tmp_count = 0;

	for (auto i = 0; i < transactionsList.count(); i++)
	{
		if (tmp_count != 0)
		{
			auto matches_count = 0;

			for (auto j = 0; j < tmp_count; j++)
				if (validate_list_identifiers[j] != transactionsList.transactions[i].id)
					matches_count++;

			if (matches_count == tmp_count)
			{
				validate_list_identifiers[tmp_count] = transactionsList.transactions[i].id;
				tmp_count++;
			}
		}
		else
		{
			validate_list_identifiers[tmp_count] = transactionsList.transactions[i].id;
			tmp_count++;
		}
	}

	int validation = 0;

	for (auto i = 0; i < tmp_count; i++)
	{
		cout << endl << "-VALIDATION OF (" << validate_list_identifiers[i] << ')' << endl;
		auto res = transaction_of_id("auto", validate_list_identifiers[i]);
		cout << endl << "-Resources count for " << validate_list_identifiers[i];
		if (res >= 0)
		{
			cout << " is postitve at the end (" << res << ") ";
			validation++;
		}
		else
			cout << " is NEGATIVE at the end(" << res << ")! ";
		cout << validation << " / " << tmp_count << endl << endl;
	}

	if (validation == tmp_count)
		cout << endl << "-LIST VALID!!";
	else
		cout << endl << "-LIST NOT VALID!!";

}

int Menu::resource_processing(int resource_arr[], string id_arr[], int value_arr[], int resource_arr_count)
{
	int resource_res = 0;

	for (auto i = 0; i < resource_arr_count; i++)
	{
		if (resource_arr[i] == 0)
		{
			cout << endl << '*' << id_arr[i] << ' '
				<< value_arr[i];

			resource_arr[i] = resource_arr[i-1];

			for (auto j = 0; j < i; j++)
				if (id_arr[i] == id_arr[j])
					resource_arr[i] = resource_arr[i] - value_arr[j];

			cout << ", resources needed: " << resource_arr[i] << endl;
		}
		else if (i == 0)
		{
			resource_arr[i] = value_arr[i];

			cout << endl << '*' << id_arr[i] << ' '
				<< value_arr[i]
				<< ", resources needed: " << resource_arr[i] << endl;
		}
		else
		{
			auto tmp_buffer = resource_arr[i - 1];
			resource_arr[i] = resource_arr[i] + tmp_buffer;

			cout << endl << '*' << id_arr[i] << ' '
				<< value_arr[i]
				<< ", resources needed: " << resource_arr[i] << endl;
		}

		resource_res = +resource_arr[i];
	}

	return resource_res;
}

bool TransactionList::read_from_file(string r_file_name)
{
	
	if (ifstream input{ r_file_name })
	{
		int transactionNumber = 0;
		string line{};

		while (getline(input, line))
		{
			size_t tmp_pos = line.find(' ');

			auto tmp_id = line.substr(0, tmp_pos);
			auto tmp_value = line.substr(tmp_pos, line.length());

			transactions[transactionNumber].id = tmp_id;
			transactions[transactionNumber].value = stoi(tmp_value);

			transactionNumber++;
		}

		size = transactionNumber;
		return true;
	}
	else
		return false;
}

int TransactionList::count() const
{
	return  size;
}