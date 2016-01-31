#include <iostream>
#include <string>
using namespace std;

template <class T>
class NodeType {
public:
	int position;
	T info;
	NodeType<T>* link;
	NodeType<T>* prev;
};

template <class T>
class LinkedList {
public:
	NodeType<T>* head;
	NodeType<T>* tail;
	int size;

	LinkedList(){
		this->size = 0;
		this->head = NULL;
		this->tail = NULL;
	}

	~LinkedList(){
		//cout << "Going to delete all " << size << " elements of the list." << endl;
		clear();
	}
	
	LinkedList(LinkedList & other){
		copy(other);
	}

	void copy(LinkedList & other){
		NodeType<T> * rNodePtr = other.head;
		if (rNodePtr){
			head = new NodeType <T>(*rNodePtr);
			/*head = new NodeType <T>;
			*head = *rNodePtr;*/
			if (rNodePtr->link == NULL) tail = head;
			NodeType<T>* ptr = head;
			while (rNodePtr = rNodePtr->link){
				ptr->link = new NodeType<T>(*rNodePtr);
				/*if (rNodePtr != NULL)
					ptr = ptr->link;
				else{
					tail = ptr;
					tail->link = nullptr;
				}*/
				ptr = ptr->link;
				tail = ptr;
				tail->link = nullptr;
			}
		}
		else{
			head = tail = nullptr;
		}
		this->size = other.size;
	}

	LinkedList& operator=(LinkedList<T>& rhs)
	{
		if (this->head != rhs.head)
		{
			clear();
			copy(rhs);
		}
		return *this;
	}

	void clear(){
		NodeType<T> * current = head;
		while (head != NULL){
			current = current->link;
			delete head;
			head = current;
		}
		tail = NULL;
		size = 0;
	}

	void insertAtBeginning(int position, T value){
		NodeType<T> * newNode = new NodeType < T >;
		newNode->position = position;
		newNode->info = value;
		newNode->link = head;
		newNode->prev = NULL;
		head = newNode;
		size++;

		if (tail == NULL)
			tail = newNode;
		else
			newNode->link->prev = newNode;
	}

	void insertAtEnd(int position, T value){
		NodeType<T> * newNode = new NodeType < T >;
		newNode->position = position;
		// For LinkedList, use overriden assign operator 
		newNode->info = value;
		newNode->link = NULL;
		newNode->prev = tail;
		if (head == NULL)
			head = tail = newNode;
		else{
			tail->link = newNode;
			tail = newNode;
			//newNode->prev->link = newNode;
		}
		size++;
	}

	void insertWithSort(int position, T value){
		if (head == NULL){
			insertAtBeginning(position, value);
		}
		else{
			if (position < head->position){
				insertAtBeginning(position, value);
			}
			else if (position > tail->position){
				insertAtEnd(position, value);
			}
			else{
				NodeType<T> * newNode = new NodeType <T>;
				newNode->position = position;
				newNode->info = value;
				newNode->link = NULL;
				newNode->prev = NULL;
				NodeType<T> * current = head;
				for (int i = 0; i < size; i++){
					if (current->position == position){
							current->info = newNode->info;
						break;
					}
					else if (position > current->position && position < current->link->position){
						newNode->link = current->link;
						newNode->prev = current;
						current->link->prev = newNode;
						current->link = newNode;
						size++;
						break;
					}
					else{
						current = current->link;
					}
				}

			}

		}
	}
	
	void insertItemAt(int index, T value){
		if (index <= size){//else, may want to give a message or error 
			if (index == 0)
				insertAtBeginning(value);
			else if (index == size)
				insertAtEnd(value);
			else{
				NodeType<T> * newNode = new NodeType < T >;
				newNode->info = value;
				NodeType<T> * prev = head;
				for (int i = 0; i < index - 1; i++)
					prev = prev->link;

				newNode->link = prev->link;
				prev->link = newNode;
				size++;
			}
		}
	}

	int getSize(){
		return size;
	}

	// Count: number of columns 
	void print(int count){
		NodeType<T> * current = head;
		/*for (int i = 0; i < count; i++){
			if (current != NULL && current->position == i){
				cout << current->info << "\t";
				current = current->link;
			}
			else{
				cout << "0" << "\t";
			}
		}*/
		
		//start and end column index
		int start = 0;
		int end = current->position;
		for (int i = 0; i <= size; i++){
			if (i != size){
				for (int j = start; j < end; j++){
					cout << "0" << "\t";
				}
				cout << current->info << "\t";
				start = (current->position) + 1;
				if (current->link != NULL) {
					end = current->link->position;
					current = current->link;
				}
			}
			else{
				// If position of last node in list is not last element of column
				// start is then made the next position of last node's position 
				// end is the position of last node in column
				// Approach with only one compare
				if (current->position != count){
					start = current->position + 1;
					end = count;
					for (int i = start; i < end; i++){
						cout << "0" << "\t";
					}
				}
				// If position of last node in list is last node of column
				// end
				else{
					break;
				}
			}
		}
		cout << endl;
	}

	void addLinkedList(LinkedList<int>& other){
		//Swap from smaller linkedlist to larger one, increase efficiency
		LinkedList<int> larger_linkedlist, smaller_linkedlist;
		if (this->size < other.size){
			larger_linkedlist = other;	smaller_linkedlist = *this;
		}
		else{
			larger_linkedlist = *this;	smaller_linkedlist = other;
		}

		//larger_linkedlist_head = larger_linkedlist.head;
		//smaller_linkedlist_head = smaller_linkedlist.head;
		NodeType<int> * current_smaller = smaller_linkedlist.head;
		NodeType<int> * current_larger = larger_linkedlist.head;

		// When last node of smaller ll is smaller than first node of larger ll
		if (smaller_linkedlist.tail->position == larger_linkedlist.head->position){
			current_smaller = smaller_linkedlist.tail;
			larger_linkedlist.head->info = smaller_linkedlist.tail->info + larger_linkedlist.head->info;
			while (current_smaller = current_smaller->prev){
				larger_linkedlist.insertAtBeginning(current_smaller->position, current_smaller->info);
			}
			/*while (current_larger = current_larger->link){
				smaller_linkedlist.insertAtEnd(current_larger->position, current_larger->info);
			}
			larger_linkedlist = smaller_linkedlist;*/
		}
		else if (smaller_linkedlist.tail->position < larger_linkedlist.head->position){
			current_smaller = smaller_linkedlist.tail;
			while (current_smaller != NULL){
				larger_linkedlist.insertAtBeginning(current_smaller->position, current_smaller->info);
				current_smaller = current_smaller->prev;
			}
			/*while (current_larger != NULL){
				smaller_linkedlist.insertAtEnd(current_larger->position, current_larger->info);
				current_larger = current_larger->link;
			}
			larger_linkedlist = smaller_linkedlist;*/
		}
		else{
			while (current_smaller != NULL){
				// When node is larger than last node of larger ll 
				if (current_smaller->position == larger_linkedlist.tail->position){
					larger_linkedlist.tail->info = larger_linkedlist.tail->info + current_smaller->info;
					while (current_smaller = current_smaller->link){
						larger_linkedlist.insertAtEnd(current_smaller->position, current_smaller->info);
					}
					break;
				}
				else if (current_smaller->position > larger_linkedlist.tail->position){
					while (current_smaller != NULL){
						larger_linkedlist.insertAtEnd(current_smaller->position, current_smaller->info);
						current_smaller = current_smaller->link;
					}
					break;
				}
				else if (current_smaller->position < current_larger->position){
					larger_linkedlist.insertWithSort(current_smaller->position, current_smaller->info);
					current_smaller = current_smaller->link;
				}
				else if (current_smaller->position == current_larger->position){
					current_larger->info = current_smaller->info + current_larger->info;
					current_smaller = current_smaller->link;
					current_larger = current_larger->link;
				}
				else if (current_smaller->position > current_larger->position && current_smaller->position < current_larger->link->position){
					NodeType<T> * newNode = new NodeType <T>;
					newNode->position = current_smaller->position;
					newNode->info = current_smaller->info;
					newNode->link = current_larger->link;
					current_larger->link = newNode;

					larger_linkedlist.size++;
					current_smaller = current_smaller->link;
					current_larger = current_larger->link->link;
				}
				else{
					current_larger = current_larger->link;
				}
			}	
		}
		*this = larger_linkedlist;
	}

	//not used
	bool search(T & value){
		NodeType<T> * current = head;
		while (current != NULL)
			if (current->info == value) //check this in object's case
				return true;
			else
				current = current->link;
		return false;
	}

	T& getItemAt(int index){
		if (index < 0 || index >= size){
			cout << "Index out of bound.\n";
			abort();
		}
		NodeType<T> * current = head;
		for (int i = 0; i < index; i++)
			current = current->link;
		return (current->info);
	}

	NodeType<T>* getNodeAt(int index){
		if (index < 0 || index >= size){
			cout << "Index out of bound.\n";
			abort();
		}
		NodeType<T>* current = head;
		for (int i = 0; i < index; i++)
			current = current->link;
		return current;
	}

	//not used
	void setItemAt(int index, T & value){
		if (index < 0 || index >= size){
			cout << "Index out of bound.\n";
			abort();
		}
		NodeType<T> * current = head;
		for (int i = 0; i < index; i++)
			current = current->link;
		current->info = value;
	}

	//not used
	void deleteFirst(){
		if (size > 0){
			NodeType<T> * toBeDeleted = head;
			head = head->link;
			delete toBeDeleted;
			size--;

			if (head == NULL)
				tail = NULL;
		}
	}

	//not used
	void deleteLast(){
		if (size > 0){//else, may want to give a message or error 
			if (size == 1){//list has only one item 
				delete head;
				tail = head = NULL;
			}
			else{
				NodeType<T> * beforeLast = head;
				while (beforeLast->link->link != NULL)
					beforeLast = beforeLast->link;
				delete beforeLast->link;
				beforeLast->link = NULL;
				tail = beforeLast;
			}
			size--;
		}
	}

	//not used
	void deleteItemAt(int index){
		if (index < size){//else, may want to give a message or error 
			if (index == 0)
				deleteFirst();
			else{
				NodeType<T> * prev = NULL, *toDelete = head;
				for (int i = 0; i < index; i++){
					prev = toDelete;
					toDelete = toDelete->link;
				}
				prev->link = toDelete->link; //NULL also OK for last item
				if (toDelete == tail)
					tail = prev;
				delete toDelete;
				size--;
			}
		}
	}

};

class SM{
	int rows; int columns;
	LinkedList<LinkedList<int>> linkedListMatrix;

public:
	SM(){}

	SM(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
	}

	~SM(){

	}

	SM(SM& sm){
		rows = sm.rows;
		columns = sm.columns;
		LinkedList<LinkedList<int>> linkedListMatrix;
		linkedListMatrix = sm.linkedListMatrix;
	}

	void readElements(){
		bool stop = false;
		int row, column, value;

		cout << "Please enter row index, column index and value sequencially. Example: 1 1 1 or 1 22 -1" << endl;
		cout << "Enter 0 for value to stop input. Example: 0 0 0 or 1 1 0" << endl;
		while (stop == false){
			cin >> row >> column >> value;
			if (value == 0){
				stop = true;
				cout << "Finish initiating matrix." << endl;
			}
			else{
				// Check if user input is valid
				if (row >= rows || column >= columns){
					cout << "Invalid row index or column index." << endl;
					abort();
				}
				else{
					if (linkedListMatrix.getSize() == 0){
						LinkedList<int> newLinkedList;
						newLinkedList.insertWithSort(column, value);
						linkedListMatrix.insertWithSort(row, newLinkedList);
						//newLinkedList.insertAtBeginning(column, value);
						//linkedListMatrix.insertAtBeginning(row, newLinkedList);
					}
					else{
						for (int i = 0; i < linkedListMatrix.getSize(); i++){
							NodeType<LinkedList<int>>* nodeTypeLinkedList = linkedListMatrix.getNodeAt(i);
							if (nodeTypeLinkedList->position > row){
								LinkedList<int> newLinkedList;
								newLinkedList.insertWithSort(column, value);
								linkedListMatrix.insertWithSort(row, newLinkedList);
								break;
							}
							else if (nodeTypeLinkedList->position == row){
								nodeTypeLinkedList->info.insertWithSort(column, value);
								break;
							}
							else if (i == linkedListMatrix.getSize() - 1 && nodeTypeLinkedList->position < row){
								LinkedList<int> newLinkedList;
								newLinkedList.insertWithSort(column, value);
								linkedListMatrix.insertAtEnd(row, newLinkedList);
								break;
							}
						}
					}
				}
			}
		}
	}

	void printMatrix(){
		NodeType<LinkedList<int>>* current = linkedListMatrix.getNodeAt(0);
		int size = linkedListMatrix.getSize();
		//start and end column index
		int start = 0;
		int end = current->position;
		for (int i = 0; i <= size; i++){
			if (i != size){
				// Print empty rows
				for (int j = start; j < end; j++){
					for (int k = 0; k < columns; k++) cout << "0" << "\t";
					cout << endl;
				}
				current->info.print(columns);
				start = (current->position) + 1;
				if (current->link != NULL) {
					end = (current->link->position) + 0;
					current = current->link;
				}
			}
			else{
				// If position of last node in list is not last element of column
				// start is then made the next position of last node's position 
				// end is the position of last node in column
				// Approach with only one compare
				if (current->position != rows){
					start = current->position + 1;
					end = rows;
					for (int i = start; i < end; i++){
						for (int k = 0; k < columns; k++) cout << "0" << "\t";
						cout << endl;
					}
				}
				// If position of last node in list is last node of column
				// end
				else{
					break;
				}
			}
		}
	}

	void addSM(SM & other){
		if (rows == other.rows && columns == other.columns){
			LinkedList<LinkedList<int>> larger_linkedlist, smaller_linkedlist;
			if (linkedListMatrix.size < other.linkedListMatrix.size){
				larger_linkedlist = other.linkedListMatrix;	smaller_linkedlist = linkedListMatrix;
			}
			else{
				larger_linkedlist = linkedListMatrix;	smaller_linkedlist = other.linkedListMatrix;
			}

			NodeType<LinkedList<int>>* current_smaller = smaller_linkedlist.head;
			NodeType<LinkedList<int>>* current_larger = larger_linkedlist.head;

			if (smaller_linkedlist.tail->position == larger_linkedlist.head->position){
				current_smaller = smaller_linkedlist.tail;
				current_larger->info.addLinkedList(current_smaller->info);
				while (current_smaller = current_smaller->prev){
					larger_linkedlist.insertAtBeginning(current_smaller->position, current_smaller->info);
				}
			}
			else if (smaller_linkedlist.tail->position < larger_linkedlist.head->position){
				current_smaller = smaller_linkedlist.tail;
				while (current_smaller != NULL){
					larger_linkedlist.insertAtBeginning(current_smaller->position, current_smaller->info);
					current_smaller = current_smaller->prev;
				}
			}
			else{
				while (current_smaller != NULL){
					// When node is larger than last node of larger ll 
					if (current_smaller->position == larger_linkedlist.tail->position){
						larger_linkedlist.tail->info.addLinkedList(current_smaller->info);
						while (current_smaller = current_smaller->link){
							larger_linkedlist.insertAtEnd(current_smaller->position, current_smaller->info);
						}
						break;
					}
					else if (current_smaller->position > larger_linkedlist.tail->position){
						while (current_smaller != NULL){
							larger_linkedlist.insertAtEnd(current_smaller->position, current_smaller->info);
							current_smaller = current_smaller->link;
						}
						break;
					}
					else if (current_smaller->position < current_larger->position){
						larger_linkedlist.insertWithSort(current_smaller->position, current_smaller->info);
						current_smaller = current_smaller->link;
					}
					else if (current_smaller->position == current_larger->position){
						current_larger->info.addLinkedList(current_smaller->info);
						current_smaller = current_smaller->link;
						current_larger = current_larger->link;
					}
					else if (current_smaller->position > current_larger->position && current_smaller->position < current_larger->link->position){
						NodeType<LinkedList<int>> * newNode = new NodeType <LinkedList<int>>;
						newNode->position = current_smaller->position;
						newNode->info = current_smaller->info;
						newNode->link = current_larger->link;
						current_larger->link = newNode;

						larger_linkedlist.size++;
						//larger_linkedlist.insertWithSort(current_smaller->position, current_smaller->info);
						current_smaller = current_smaller->link;
						current_larger = current_larger->link->link;
					}
					else{
						current_larger = current_larger->link;
					}
				}
			}
			this->linkedListMatrix = larger_linkedlist;
		}
		else{

		}
	}

};


void main(){
	string yOrn;
	LinkedList<SM> sms;
	int rows, columns;
	/*LinkedList<int> a, b, c;
	//a.insertWithSort(3,100);
	a.insertWithSort(4, 100);
	//a.insertWithSort(1,2);
	//a.insertWithSort(4, 100);
	//b.insertWithSort(1,2);
	//b.insertWithSort(2,3);
	b.insertWithSort(0,4);
	b.insertWithSort(4, 4);
	//b.insertWithSort(2, 4);
	a.print(5);
	b.print(5);
	a.addLinkedList(b);
	a.print(5);*/

	cout << "Enter number of rows of matrix: ";
	cin >> rows; cout << endl;
	cout << "Enter number of columns of matrix: ";
	cin >> columns; cout << endl;
	SM sm1(rows, columns);
	sm1.readElements();
	sm1.printMatrix();

	cout << "Enter number of rows of matrix: ";
	cin >> rows; cout << endl;
	cout << "Enter number of columns of matrix: ";
	cin >> columns; cout << endl;
	SM sm2(rows, columns);
	sm2.readElements();
	sm2.printMatrix();

	sm1.addSM(sm2);
	sm1.printMatrix();
	//sms.insertWithSort(0,sm);
	/*LinkedList<SM> sms;
	
	int count=1;
	do{
		int rows, columns;
		cout << "Enter number of rows of matrix: ";
		cin >> rows; cout << endl;
		cout << "Enter number of columns of matrix: ";
		cin >> columns; cout << endl;
		cout << "fuck";
		SM sm(rows, columns);
		sm.readElements();
		//sm.printMatrix();
		sms.insertWithSort(count, sm);
		count++;
		cout << "Do you want to add more sprase matrices? (y/n)" << endl;	
		cin >> yOrn;
	} while (yOrn == "y");

	for (int i = 0; i < count; i++){
		cout << "Matrix " << i + 1<<endl;
		sms.getItemAt(i).printMatrix();
	}*/
	cin >> yOrn;
}