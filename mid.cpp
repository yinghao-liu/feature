#include "member.h"
void mid(void)
{
	bank_account a;
	a.show_balance();
	a.show_num();

	bank_account b;
	b.add(10);
	b.show_balance();
	b.show_num();
}
