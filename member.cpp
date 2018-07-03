#include <iostream>
#include "member.h"

using namespace std;
int g_number=0;
int *bank_account::num=new int();

bank_account::bank_account(void)
{
	if (nullptr == num){
		num = &g_number;
	}
	(*num)++;
	cout<<"init num is"<<num<<*num<<endl;
}
bank_account::~bank_account(void)
{
	(*num)--;
	cout<<"after destroy num is"<<num<<*num<<endl;
}
void bank_account::show_balance(void)
{
	cout<<"balance is "<<balance<<endl;
}
void bank_account::show_num(void)
{
	cout<<"total num is "<<num<<*num<<endl;
}

void bank_account::add(int incre)
{
	balance += incre;
}

