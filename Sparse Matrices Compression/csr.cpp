// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"
///////////////CSR Class Implementation///////////////

CSR::CSR() : m_values(nullptr), m_col_index(nullptr), m_row_index(nullptr), m_nonzeros(0), m_m(0), m_n(0), m_next(nullptr) {}
CSR::~CSR() { clear(); }
CSR::CSR(const CSR& rhs) : m_values(nullptr), m_col_index(nullptr), m_row_index(nullptr),
m_nonzeros(0), m_m(0), m_n(0), m_next(nullptr) {
	// Create a deep copy of rhs
	m_m = rhs.m_m;
	m_n = rhs.m_n;
	m_nonzeros = rhs.m_nonzeros;

	// Allocate memory for arrays
	m_values = new int[m_nonzeros];
	m_col_index = new int[m_nonzeros];
	m_row_index = new int[m_m + 1];

	// Copy data from rhs
	for (int i = 0; i < m_nonzeros; ++i) {
		m_values[i] = rhs.m_values[i];
		m_col_index[i] = rhs.m_col_index[i];
	}
	for (int i = 0; i <= m_m; ++i) {
		m_row_index[i] = rhs.m_row_index[i];
	}
}
void CSR::clear() {
	delete[] m_values;
	delete[] m_col_index;
	delete[] m_row_index;

	m_values = nullptr;
	m_col_index = nullptr;
	m_row_index = nullptr;
	m_nonzeros = 0;
	m_m = 0;
	m_n = 0;
}
bool CSR::empty() const { return (m_m == 0 || m_n == 0); }
void CSR::compress(int m, int n, int array[], int arraySize) {
	clear(); // Clear existing data

	if (m == 0 || n == 0 || arraySize == 0) {
		// Empty matrix or empty array
		m_m = m;
		m_n = n;
		return;
	}

	// Initialize member variables
	m_m = m;
	m_n = n;
	m_nonzeros = 0;

	// Count non-zero values
	for (int i = 0; i < arraySize; ++i) {
		if (array[i] != 0) {
			m_nonzeros++;
		}
	}
	//cout << "# of Non Zeros " << m_nonzeros << endl;
	//cout << "Array Size " << arraySize << endl;
	//cout << "Array Received in compress fln is ";
	//for (int i = 0; i < arraySize; i++)
	//{
	//	cout << array[i] << "\t";
	//	if (i % (m_n - 1) == 0 && i != 0)
	//		cout << "\n";
	//}cout << "\n";
	// Allocate memory for arrays
	m_values = new int[m_nonzeros];
	m_col_index = new int[m_nonzeros];
	m_row_index = new int[m_m + 1];

	int valueIndex = 0;
	m_row_index[0] = 0;

	// Populate arrays
	for (int i = 0; i < m_m; ++i) {
		for (int j = 0; j < m_n; ++j) {
			int index = i * m_n + j;
			if (array[index] != 0) {
				m_values[valueIndex] = array[index];
				m_col_index[valueIndex] = j;
				valueIndex++;
			}
		}
		m_row_index[i + 1] = valueIndex; // Updated row index properly
	}
}
int CSR::getAt(int row, int  col) const {
	if (row < 0 || row >= m_m || col < 0 || col >= m_n) {
		throw std::runtime_error("Index out of bounds");
	}

	for (int i = m_row_index[row]; i < m_row_index[row + 1]; ++i) {
		if (m_col_index[i] == col) {
			return m_values[i];
		}
	}
	throw std::runtime_error("Index does not exist");
}
bool CSR::operator==(const CSR& rhs) const {
	if (m_m != rhs.m_m || m_n != rhs.m_n || m_nonzeros != rhs.m_nonzeros) {
		return false;
	}

	for (int i = 0; i < m_nonzeros; ++i) {
		if (m_values[i] != rhs.m_values[i] || m_col_index[i] != rhs.m_col_index[i]) {
			return false;
		}
	}
	return true;
}
int CSR::sparseRatio() {
	if (empty()) {
		return 0; // Empty matrix, so ratio is 0%
	}
	return (m_nonzeros * 100) / (m_m * m_n);
}
void CSR::dump() {
	cout << endl;
	if (!empty()) {
		for (int i = 0; i < m_nonzeros; i++)
			cout << m_values[i] << " ";
		cout << endl;
		for (int i = 0; i < m_nonzeros; i++)
			cout << m_col_index[i] << " ";
		cout << endl;
		for (int i = 0; i < m_m + 1; i++)
			cout << m_row_index[i] << " ";
	}
	else
		cout << "The object is empty!";
	cout << endl;
}

//////////////CSRList Class Implementation///////////////
CSRList::CSRList() : m_head(nullptr), m_size(0) {}
CSRList::CSRList(const CSRList& rhs) : m_head(nullptr), m_size(0) {
	CSR* rhsNode = rhs.m_head;
	while (rhsNode != nullptr) {
		CSR* newNode = new CSR(*rhsNode);
		insertAtHead(*newNode);
		rhsNode = rhsNode->m_next;
	}
}
CSRList::~CSRList() { clear(); }
bool CSRList::empty() const { return (m_size == 0); }
void CSRList::insertAtHead(const CSR& matrix) {
	CSR* newNode = new CSR(matrix);
	newNode->m_next = m_head;
	m_head = newNode;
	m_size++;
}
void CSRList::clear() {
	CSR* current = m_head;
	while (current != nullptr) {
		CSR* temp = current;
		current = current->m_next;
		delete temp;
	}
	m_head = nullptr;
	m_size = 0;
}
int CSRList::getAt(int CSRIndex, int row, int col) const {
	if (CSRIndex < 0 || CSRIndex >= m_size) {
		throw std::runtime_error("Object is not in the list!");
	}

	CSR* current = m_head;
	for (int i = 0; i < CSRIndex; ++i) {
		current = current->m_next;
	}

	return current->getAt(row, col);
}
bool CSRList::operator== (const CSRList& rhs) const {
	if (m_size != rhs.m_size) {
		return false;
	}

	CSR* leftNode = m_head;
	CSR* rightNode = rhs.m_head;

	while (leftNode != nullptr) {
		if (!(*leftNode == *rightNode)) {
			return false;
		}
		leftNode = leftNode->m_next;
		rightNode = rightNode->m_next;
	}

	return true;
}
const CSRList& CSRList::operator=(const CSRList& rhs) {
	if (this == &rhs) {
		return *this; // Self-assignment, no action needed
	}

	clear(); // Clear existing data

	CSR* rhsNode = rhs.m_head;
	while (rhsNode != nullptr) {
		CSR* newNode = new CSR(*rhsNode);
		insertAtHead(*newNode);
		rhsNode = rhsNode->m_next;
	}

	return *this;
}
int CSRList::averageSparseRatio() {
	if (empty()) {
		return 0; // No matrices in the list, so ratio is 0%
	}

	int totalRatio = 0;
	CSR* current = m_head;
	while (current != nullptr) {
		totalRatio += current->sparseRatio();
		current = current->m_next;
	}

	return totalRatio / m_size;
}
void CSRList::dump() {
	if (!empty()) {
		CSR* temp = m_head;
		while (temp != nullptr) {
			temp->dump();
			temp = temp->m_next;
		}
	}
	else
		cout << "Error: List is empty!" << endl;
}