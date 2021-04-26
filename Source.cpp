/*
* Andrew Menard
* 04 / 23 / 2021
* Project 3
* CS210
*
*This is the source C++ file for the grocery tracker program.
* The purpose of this application is to track how frequently grocery items
* are purchasedand see how frequently specific items are purchased.
* There is a histogram that is built from the input file of transactions.
* The user is given options with a menu selection.
*/

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
string CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// file stream function that prints histogram
// from frequency.dat file created in python function
int readFile() {

	ifstream inFS;
	string food;
	int foodFreq = 0;
	inFS.open("frequency.dat");
	if (!inFS.is_open()) {  // makes sure file opens properly
		cout << "could not open file frequency.dat." << endl;
		return 1;
	}
	while (inFS >> food >> foodFreq) {  // loop to print an * for every transaction of current item
		cout << left << setw(15) << food << " ";
		for (int i = 0; i <= foodFreq; i++) {
			cout << "*";
		}
		cout << endl;
	}
}
// menu function 
// prints user input options, takes input, and prints accordingly 
int menu() {
	int ch = 0;
	while (ch != 4) {
		cout << "1: List all items and frequency of each item\n";
		cout << "2: Show how many times a specific item was bought\n";
		cout << "3: Show Histogram of items bought\n";
		cout << "4: Exit\n";
		cout << "Enter your choice:\n";
		cin >> ch;
		switch (ch) {  // use switch statements instead of if/else to make code succinct 
		case 1: {  // call python function that opens data file, reads, makes list with frequency of each item, then prints
			CallProcedure("ListOccurances");
			menu();
			break;
		}
		case 2: {  // returns amount of transactions of particular item inputted by user
			string a;
			cout << "Enter item:";
			cin >> a;
			cout << callIntFunc("FrequencyOfItem", a);
			menu();
			break;
		}
		case 3: { // prints histogram

			CallProcedure("Histogram");  // call Histogram python function first to create frequency.dat file 
			cout << readFile() << endl;  // print readFile function that reads frequency.dat and creates Histogram from
			menu();
			break;
		}
		case 4: {  // Exit program
			cout << "Thank you\n";
			break;
		}
		default:   // Invalid input 
			printf("Wrong Input\n");
		}
	}

}

// keep main minimal by creating menu function and calling menu() in main()
int main()
{
	menu();
	
}