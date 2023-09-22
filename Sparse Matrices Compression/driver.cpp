// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"

class Tester {

};
// this program presents a sample usage of project 1
int main()
{
	try {
		Tester tester;
		CSR aCSR, b, c, d, e, f;
		int array1[] = { 10, 20, 0 , 0 , 0 , 0,
						 0 , 30, 0 , 40, 0 , 0,
						 0 , 0 , 50, 60, 70, 0,
						 0 , 0 , 0 , 0 , 0 , 80 };
		aCSR.compress(4, 6, array1, 24);//initialize object aCSR

		CSR bCSR(aCSR);//create bCSR using copy constructor
		CSR cCSR;
		int array2[] = { 0, 0  , 0,
						 0, 100, 200,
						 0, 0  , 300 };
		cCSR.compress(3, 3, array2, 9);//initialize object cCSR
		CSR dCSR(cCSR);//create dCSR using copy constructor

		CSRList aCSRList;//create aCSRList
		aCSRList.insertAtHead(aCSR);
		aCSRList.insertAtHead(cCSR);
		CSRList bCSRList;//create bCSRList
		bCSRList.insertAtHead(dCSR);
		bCSRList.insertAtHead(bCSR);

		cout << "Dumping aCSRList:" << endl;
		aCSRList.dump();
		cout << endl << "Dumping bCSRList:" << endl;
		bCSRList.dump();

		cout << endl << aCSRList.getAt(1, 2, 4) << endl;//returns the value 70

		//cout << endl << aCSRList.getAt(5, 2, 2) << endl;//throws an exception
		int array3[] = { 1, 0, 0, 0, 0
					,0, 0, 2, 0, 0
					,0, 3, 0, 0, 0
					,0, 0, 0, 4, 0
					,0, 0, 0, 0, 5 };
		b.compress(5, 5, array3, 5 * 5);//initialize object aCSR

		int array4[] = { 0, 0, 0, 0
						,0, 0, 0, 0
						,0, 7, 0, 0
						,0, 0, 0, 0 };
		c.compress(4, 4, array4, 4 * 4);//initialize object aCSR

		//b.dump();
		//c.dump();

		int array5[] = { 1, 0, 2
						,2, 1, 0
						,0, 1, 3 };
		d.compress(3, 3, array5, 3 * 3);//initialize object aCSR
		//d.dump();
		int array6[] = { 0, 0, 0, 0, 0,
						 5, 8, 0, 0, 0,
						 0, 0, 0, 3, 0,
						 0, 0, 7, 0, 0 };
		e.compress(4, 5, array6, 4 * 5);//initialize object aCSR
		e.dump();
		int sparseMatrix[] = { 0, 0, 3, 0, 4,
							   0, 0, 5, 7, 0,
							   0, 0, 0, 0, 0,
							   0, 2, 6, 0, 0 };
		f.compress(4, 5, sparseMatrix, 4 * 5);//initialize object aCSR
		f.dump();
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
