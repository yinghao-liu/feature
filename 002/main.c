static int global_static_non_inited;
static int global_static_inited = 0;

int global_ext_non_inited;
int global_ext_inited = 0;


static int global_static_fun(void)
{
	return 0;
}

int global_ext_fun(void)
{
	return 0;
}

int main(void)
{
	static int local_static_non_inited;
	static int local_static_inited = 0;

	int local_inited = 0;
	int local_non_inited;
	return 0;
}
