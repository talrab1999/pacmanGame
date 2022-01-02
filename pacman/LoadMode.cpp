#include "LoadMode.h"

void LoadMode::gameLoop(bool silent) {
	cout << "this is load mode game loop print" << endl;
	if (silent)
		cout << "silent mode" << endl;
	system("pause");
}
