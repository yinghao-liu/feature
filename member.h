#ifndef _MEMBER_H_
#define _MEMBER_H_

class bank_account{
public:
	bank_account(void);
	~bank_account(void);
	void show_balance(void);
	void show_num(void);
	void add(int incre);

private:
	int balance;
	static int *num;
};



#endif
