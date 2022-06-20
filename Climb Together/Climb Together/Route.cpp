#include "Route.h"

double Route::MeasureTime()
{
	char temp;
	cout << "- - Press any key to start recording time - -\n";
	_getch();
	auto start = chrono::high_resolution_clock::now();
	cout << "- - Press any key to stop recording time OR press c, if user hasn't completed route.- -\n";
	temp = _getch();
	auto stop = chrono::high_resolution_clock::now();
	if (temp != 'c') {
		auto result = chrono::duration_cast<chrono::milliseconds> (stop - start);
		cin.clear();
		system("CLS");
		return result.count();
	}
	else
		return -1;

}
void Route::Animation()
{
	system("CLS");
	cout << "  ________                 \n";
	cout << "//       ||                \n";
	cout << "||   /---||  __________    \n";
	cout << "||  ||      |___    ___|   \n";
	cout << "||  ||          |  |       \n";
	cout << "||  ||          |  |       \n";
	cout << "||  ||___       |  |       \n";
	cout << "||       ||     |  |       \n";
	cout << "||_______||     |__|       \n";
	Sleep(50);
	system("CLS");

	cout << "  ________                 \n";
	cout << "//       ||                \n";
	cout << "||   /---||  __________    \n";
	cout << "||  ||      |___    ___|   \n";
	cout << "||  ||          |  |       \n";
	cout << "||  ||          |  |       \n";
	cout << "||  ||___       |  |       \n";
	cout << "||*******||     |**|       \n";
	cout << "||*******||     |**|       \n";
	Sleep(50);
	system("CLS");

	cout << "  ________                 \n";
	cout << "//       ||                \n";
	cout << "||   /---||  __________    \n";
	cout << "||  ||      |___    ___|   \n";
	cout << "||  ||          |  |       \n";
	cout << "||**||          |**|       \n";
	cout << "||**||___       |**|       \n";
	cout << "||*******||     |**|       \n";
	cout << "||*******||     |**|       \n";
	Sleep(50);
	system("CLS");

	cout << "  ________                 \n";
	cout << "//       ||                \n";
	cout << "||   /---||  __________    \n";
	cout << "||**||      |___    ___|   \n";
	cout << "||**||          |**|       \n";
	cout << "||**||          |**|       \n";
	cout << "||**||___       |**|       \n";
	cout << "||*******||     |**|       \n";
	cout << "||*******||     |**|       \n";
	Sleep(50);
	system("CLS");

	cout << "  ________                 \n";
	cout << "//*******||                \n";
	cout << "||** /---||  __________    \n";
	cout << "||**||      |**********|   \n";
	cout << "||**||          |**|       \n";
	cout << "||**||          |**|       \n";
	cout << "||**||___       |**|       \n";
	cout << "||*******||     |**|       \n";
	cout << "||*******||     |**|       \n";
	Sleep(50);
	system("CLS");
}