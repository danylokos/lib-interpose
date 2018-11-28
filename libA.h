// libA

// C function
extern "C" {
	int add(int a, int b);

//C struct function pointer
extern "C" typedef struct AStruct {
	int (*sub)(AStruct *pAStruct, int a, int b);
} AStruct;

extern "C" AStruct * AStruct_new();

extern "C" void AStruct_free(AStruct *pAStruct);
}
// C++

class BClass {
	public:
		// C++ static method
		static int multi(int a, int b);
		// C++ method
		double div(int a, int b);
};
