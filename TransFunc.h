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

#pragma once

#include "includes.h"

string ask_file_name();


struct Transaction
{
	std::string id;
	int value;
};

struct TransactionList
{
	static const int MAX_TRANSACTIONS{ 100 };

	Transaction transactions[MAX_TRANSACTIONS];
	int size;

	bool read_from_file(string r_file_name);
	int count() const;
};

struct Menu
{
	TransactionList transactionsList;

	void menu(string m_file_name);
	void print_count();
	void minimum_resource_size();
	void all_transactions();
	int transaction_of_id(string callingMode, string identifier);
	void sum_untill();
	void list_identifies();
	void validate();
	int resource_processing(int resource_arr[], string id_arr[], int value_arr[], int resource_arr_count);
};
