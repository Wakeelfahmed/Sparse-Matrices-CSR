// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"

class Tester {

};
// this program presents a sample usage of project 1
int main()
{
	try {
		Tester tester;
		CSR aCSR, b, c, d, e;
		int array1[] = { 10,20,0 ,0 ,0 ,0,
						 0 ,30,0 ,40,0 ,0,
						 0 ,0 ,50,60,70,0,
						 0 ,0 ,0 ,0 ,0 ,80 };
		aCSR.compress(4, 6, array1, 24);//initialize object aCSR

		//cout << "******* testing of Array 1 A *******\n";
		//aCSR.dump();
		//cout << "******* End testing of Array 1 A *******\n\n";
		CSR bCSR(aCSR);//create bCSR using copy constructor
		//cout << "******* testing of Array 1 B *******\n";
		//bCSR.dump();
		//cout << "******* End testing of Array 1 B *******\n\n";
		//cout << "******* End of Array 1 *******\n";
		CSR cCSR;
		int array2[] = { 0,0,0,0,100,200,0,0,300 };
		cCSR.compress(3, 3, array2, 9);//initialize object cCSR
		//cout << "******* testing of Array 2 C *******\n";
		//cCSR.dump();
		//cout << "******* End testing of Array 2 C *******\n\n";
		//cout << "******* testing of Array 2 D *******\n";
		CSR dCSR(cCSR);//create dCSR using copy constructor
		//cout << "******* End testing of Array 2 D *******\n\n";
		//cout << "******* End of Array 2 *******\n";

		CSRList aCSRList;//create aCSRList
		aCSRList.insertAtHead(aCSR);
		aCSRList.insertAtHead(cCSR);
		CSRList bCSRList;//create bCSRList
		bCSRList.insertAtHead(dCSR);
		bCSRList.insertAtHead(bCSR);

		cout << endl << "Dumping aCSRList:" << endl;
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
		b.compress(5, 5, array3, 5*5);//initialize object aCSR
		
		int array4[] = { 0, 0, 0, 0
						,0, 0, 0, 0
						,0, 7, 0, 0
						,0, 0, 0, 0 };
		c.compress(4, 4, array4, 4*4);//initialize object aCSR
		
		b.dump();
		c.dump();

		int array5[] = { 1, 0, 2
						,2, 1, 0
						,0, 1, 3 };
		d.compress(3, 3, array5, 3 * 3);//initialize object aCSR
		d.dump();

	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
