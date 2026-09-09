// void resetTime();
// int getTime();

void run_bench( void (*fun)(void *ptr), void *ptr,
			int tiempo_ref, int tolerancia, int nintentos );

void test_unitario(void);
void benchmark(int refs[], int n);
