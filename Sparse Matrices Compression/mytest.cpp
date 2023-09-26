#include <iostream>
#include <cassert>
#include "csr.h"

class Tester {
public:
	// Test functions for CSR class
	bool testCompressNormal() {
		CSR csr;
		int array[] = { 10, 20, 0, 0, 0, 0, 
						0, 30, 0, 40, 0, 0, 
						0, 0, 50, 60, 70, 0, 0, 0, 0, 0, 0, 80 };
		//csr.compress(4, 6, array, 24);

		// Check if csr is populated correctly
		bool passed = true;
		//passed = passed && (csr.getAt(0, 0) == 10);
		//passed = passed && (csr.getAt(2, 4) == 70);
		return passed;
	}
	int test = 0;
	bool testCompressErrorLessData() {
		CSR csr;
		int array[6] = { 10, 20, 30, 40 }; // Data is less than matrix size
		csr.compress(2, 3, array, 4); // The matrix size is 2x3
		int test = -1;
		// Check if csr is populated correctly
		bool passed = true;
		passed = passed && (csr.getAt(0, 0) == 10);
		passed = passed && (csr.getAt(0, 1) == 20);
		passed = passed && (csr.getAt(0, 2) == 30);
		passed = passed && (csr.getAt(1, 0) == 40);
		passed = passed && (csr.getAt(1, 1) == 0); // Missing data, expect 0
		if (passed == false)
			cout << "false at getAt(1, 1) == 0";
		test = csr.getAt(1, 2);
		passed = passed && (csr.getAt(1, 2) == 0); // Missing data, expect 0
		if (passed == false)
			cout << "false at getAt(1, 2) == 0";
		return passed;
	}

	bool testCompressErrorZeroMatrix() {
		CSR csr;
		int array[1] = {}; // Empty data, should create a 0x0 matrix
		csr.compress(0, 0, array, 0);

		// Check if csr is empty
		return csr.empty();
		//return false;
	}

	bool testEqualityOperator() {
		CSR csr1, csr2;
		int array1[] = { 10, 20, 30, 40, 50, 60, 70, 80 };
		int array2[] = { 10, 20, 30, 40, 50, 60, 70, 80 };

		csr1.compress(2, 4, array1, 8);
		csr2.compress(2, 4, array2, 8);

		// Check if csr1 and csr2 are equal
		return csr1 == csr2;
	}

	bool testEqualityOperatorEmpty() {
		CSR csr1, csr2; // Both empty

		// Check if csr1 and csr2 are equal
		return csr1 == csr2;
	}

	bool testGetAtException() {
		CSR csr;
		bool exceptionThrown = false;
		try {
			int value = csr.getAt(1, 2); // Accessing an empty matrix
		}
		catch (const std::runtime_error& e) {
			exceptionThrown = true;
		}
		return exceptionThrown;
	}

	// Test functions for CSRList class
	bool testAssignmentOperator() {
		CSRList list1, list2;
		CSR csr1, csr2;
		int array1[] = { 10, 20, 30, 40, 50, 60, 70, 80 };
		int array2[6] = { 100, 200, 300 };

		csr1.compress(2, 4, array1, 8);
		csr2.compress(3, 3, array2, 9);

		list1.insertAtHead(csr1);
		list2 = list1; // Assignment

		// Check if list2 is an exact deep copy of list1
		return list1 == list2;
	}

	bool testAssignmentOperatorEmpty() {
		CSRList list1, list2; // Both empty

		list2 = list1; // Assignment

		// Check if list2 is an empty list
		//if (list2.empty())
			//cout << "   Empty  ";
		return list2.empty();
	}

	bool testGetAtExceptionEmptyList() {
		CSRList list;
		bool exceptionThrown = false;
		try {
			int value = list.getAt(0, 1, 1); // Accessing an empty list
		}
		catch (const std::runtime_error& e) {
			exceptionThrown = true;
		}
		return exceptionThrown;
	}
};

int main() {
	Tester tester;

	//if (tester.testCompressNormal()) {
	//	std::cout << "Test testCompressNormal: Passed" << std::endl;
	//}
	//else {
	//	std::cout << "Test testCompressNormal: Failed" << std::endl;
	//}

	if (tester.testCompressErrorLessData()) {
		std::cout << "Test testCompressErrorLessData: Passed" << std::endl;
	}
	else {
		std::cout << "Test testCompressErrorLessData: Failed" << std::endl;
	}

	if (tester.testCompressErrorZeroMatrix()) {
		std::cout << "Test testCompressErrorZeroMatrix: Passed" << std::endl;
	}
	else {
		std::cout << "Test testCompressErrorZeroMatrix: Failed" << std::endl;
	}

	if (tester.testEqualityOperator()) {
		std::cout << "Test testEqualityOperator: Passed" << std::endl;
	}
	else {
		std::cout << "Test testEqualityOperator: Failed" << std::endl;
	}

	if (tester.testEqualityOperatorEmpty()) {
		std::cout << "Test testEqualityOperatorEmpty: Passed" << std::endl;
	}
	else {
		std::cout << "Test testEqualityOperatorEmpty: Failed" << std::endl;
	}

	if (tester.testGetAtException()) {
		std::cout << "Test testGetAtException: Passed" << std::endl;
	}
	else {
		std::cout << "Test testGetAtException: Failed" << std::endl;
	}

	if (tester.testAssignmentOperator()) {
		std::cout << "Test testAssignmentOperator: Passed" << std::endl;
	}
	else {
		std::cout << "Test testAssignmentOperator: Failed" << std::endl;
	}

	if (tester.testAssignmentOperatorEmpty()) {
		std::cout << "Test testAssignmentOperatorEmpty: Passed" << std::endl;
	}
	else {
		std::cout << "Test testAssignmentOperatorEmpty: Failed" << std::endl;
	}

	if (tester.testGetAtExceptionEmptyList()) {
		std::cout << "Test testGetAtExceptionEmptyList: Passed" << std::endl;
	}
	else {
		std::cout << "Test testGetAtExceptionEmptyList: Failed" << std::endl;
	}

	std::cout << "All tests completed!" << std::endl;

	return 0;
}
