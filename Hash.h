#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include "myVector.h"
//Implement a "chaining" hash table.Use your linked list class from homework 8.  You may use the "hello world" of hash functions, or a more advanced hash function of your choice.


class student
{
public:
	std::string name;
	unsigned int id;
	double gpa;

	student()
	{
		name = "ghost";
		id = 0;
		gpa = 0;
	}
	student(std::string _name, unsigned int _id, double _gpa)
	{
		id = _id;
		gpa = _gpa;
		name = _name;
	}
};
class studentList
{
private:
	//Implement a doubly linked list of students

	class node
	{
	public:
		student data;
		node * next;
		node * prev;

		node()
		{
			next = NULL;
			prev = NULL;
		}
		node(student x)
		{
			data = x;
			next = NULL;
			prev = NULL;
		}
	};

	node* head;
	node* tail;

	unsigned int numStudents;
	bool empty()
	{
		if (head == NULL && tail == NULL)
			return true;
		else
			return false;
	}

	bool isOnlyNode(node* input)
	{
		if (input->next == NULL && input->prev == NULL)
			return true;
		else
			return false;
	}

	bool isFirstNode(node* input)
	{
		if (input->next != NULL && input->prev == NULL)
			return true;
		else
			return false;
	}

	bool isLastNode(node* input)
	{
		if (input->next == NULL && input->prev != NULL)
			return true;
		else
			return false;
	}

	

	//complex, needs many cases
	/*void swapWholeNode(node* a, node* b)
	{

	}*/
	void swapNodeData(node* a, node* b)
	{
		student holder = a->data;
		a->data = b->data;
		b->data = holder;
	}

	
public:
	studentList()
	{
		head = NULL;
		tail = NULL;
		numStudents = 0;
	}
	/*copy constructor*/
	studentList(const studentList &otherList)
	{
		head = NULL;
		tail = NULL;
		for (node* tmp = otherList.head; tmp != NULL; tmp = tmp->next)
		{
			insert(tmp->data);
		}
	}
	~studentList()
	{
		while (!empty())
		{
			remove(tail);
		}
	}
	void remove(node* doomed)
	{
		if (doomed == NULL)
		{
			//do nothing
		}
		else if (isOnlyNode(doomed))
		{
			head = NULL;
			tail = NULL;
		}
		else if (isFirstNode(doomed))
		{
			head = doomed->next;
			head->prev = NULL;
		}
		else if (isLastNode(doomed))
		{
			tail = doomed->prev;
			tail->next = NULL;
		}
		else //general case
		{
			doomed->prev->next = doomed->next;
			doomed->next->prev = doomed->prev;
		}

		delete doomed;
		numStudents--;
	}
	//add a student to the list.
	//Must run in O(1) time.
	void insert(student s)
	{/*add data to back using tail*/
	 /*list is empty*/
		if (empty())
		{
			/*make head and tail point to only node in list*/
			tail = new node;
			head = tail;

			/*assign data member of node to the desired data value.
			since only 1 node, both pointers point to NULL*/
			tail->data = s;

			/*default constructor makes next and prev NULL*/
		}
		/*list !empty*/
		else
		{
			/*create a new node. set prev and tail correctly (next = NULL
			via node constructor)*/
			tail->next = new node; //node created and next points to it
			tail->next->prev = tail;//newnode.prev assigned to tail
			tail = tail->next;//point tail at new node
			tail->data = s;

		}
		numStudents++;
	}

	//find the student with the given id number and return it
	//What is the worst case run time of this? O(n)
	//What is the average case run time of this? O(n/2)
	student retrieveStudent(unsigned int idnumber)
	{
		for (node* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data.id == idnumber)
				return tmp->data;
		}
		//not found
		student notFound;
		notFound.id = 0;
		notFound.gpa = 0;
		notFound.name = "student not found!";
		return notFound;
	}
	node* retrieveStudentIDNode(unsigned int idnumber)
	{
		for (node* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data.id == idnumber)
				return tmp;
		}
		//not found

		return NULL;
	}
	node* retrieveStudentNameNode(std::string _name)
	{

		for (node* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data.name == _name)
				return tmp;
		}
		//not found
		return NULL;
	}
	node* retrieveStudentGPANode(double _GPA)
	{

		for (node* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data.gpa == _GPA)
				return tmp;
		}
		//not found
		return NULL;
	}

	//Change the gpa of the student with given id number to newGPA
	//What is the run time? O(n)
	void updateGPA(unsigned int idnumber, double newGPA)
	{
		node* update = retrieveStudentIDNode(idnumber);
		if (update != NULL)
			update->data.gpa = newGPA;
	}

	//Add all students from otherlist to this list.
	//otherlist should be empty after this operation.
	//Must run in O(1) time.
	void mergeList(studentList &otherlist)
	{/*uses pointers from other list to merge it ad the back of the list*/
		if (otherlist.empty())
		{
			//do nothing
		}
		else if(empty())
		{
			head = otherlist.head;
			tail = otherlist.tail;
			otherlist.head = NULL;
			otherlist.tail = NULL;
		}
		else
		{
			tail->next = otherlist.head;
			otherlist.head->prev = tail;
			tail = otherlist.tail;
			otherlist.tail = NULL;
			otherlist.head = NULL;
		}

	}

	//create a list of students whose gpa is at least minGPA.
	//Return this list.  The original list should
	//not be modified (do not remove the students from the original list).
	//Run time? O(n)
	studentList honorRoll(double minGPA)
	{
		studentList output;
		for (node* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			if (tmp->data.gpa >= minGPA)
				output.insert(tmp->data);
		}

		return output;
	}

	//sort the list by the given field ("name", "id", or "gpa").
	//Run time? O(n^2) selection sort
	void sort(std::string field)
	{
		if (!empty())
		{
			if (field == "name")
			{
				for (node* righttmp = tail; righttmp != NULL; righttmp = righttmp->prev)
					for (node* lefttmp = head; lefttmp != righttmp; lefttmp = lefttmp->next)
					{
						if (righttmp->data.name < lefttmp->data.name)
							swapNodeData(righttmp, lefttmp);
					}
			}
			else if (field == "id")
			{
				for (node* righttmp = tail; righttmp != NULL; righttmp = righttmp->prev)
					for (node* lefttmp = head; lefttmp != righttmp; lefttmp = lefttmp->next)
					{
						if (righttmp->data.id < lefttmp->data.id)
							swapNodeData(righttmp, lefttmp);
					}
			}
			else if (field == "GPA")
			{
				for (node* righttmp = tail; righttmp != NULL; righttmp = righttmp->prev)
					for (node* lefttmp = head; lefttmp != righttmp; lefttmp = lefttmp->next)
					{
						if (righttmp->data.gpa < lefttmp->data.gpa)
							swapNodeData(righttmp, lefttmp);
					}
			}
		}
	}
	//Print out each student in the list.  This is mainly for testing purposes.
	void printList()
	{
		if (!empty())
		{
			for (node* tmp = head; tmp != NULL; tmp = tmp->next)
			{
				std::cout << "id: " << tmp->data.id << ' ' << "name: " << tmp->data.name << ' ' << "GPA: " << tmp->data.gpa << "  " << std::endl;
			}
		}
		else
		{
			std::cout << "empty" << std::endl;
		}
	}
	//make list of studnts for testing
	void makeRandomList(unsigned int x)
	{
		for (int i = 0; i < x; i++)
		{
			student st;
			st.gpa = rand() % 100 + 1;
			st.id = i;
			char letter = rand() % 26 + 1 + 65;
			st.name = letter;
			insert(st);
		}
	}

	unsigned int getNumStudents()
	{
		return numStudents;
	}

	student popFrontStudent()
	{
		student holder = head->data;
		remove(head);
		return holder;
	}
};
class hashTable
{
private:

	//an array of linked lists (use your linked list class from homework 8)
	studentList* table;

	//size of table
	unsigned int tableSize;

	//number of students in data stucture
	unsigned int numStudents;

	unsigned int hashConstant; //random number used for hash maths

	unsigned int hashFunction(int studentID)
	{
		return hashConstant + studentID;
	}

	unsigned int hashIndex(int studentID)
	{
		return hashFunction(studentID) % tableSize;
	}
public:
	//create a table of some hard coded size of your choice
	hashTable()
	{
		tableSize = 100;
		table = new studentList[tableSize];
		srand(time(NULL));
		hashConstant = unsigned int(rand() % 10000 + 2);
		numStudents = 0;
	}
	~hashTable()
	{
		//delete table;
	}

	//create a table of a given size
	hashTable(unsigned int size)
	{
		tableSize = size;
		table = new studentList[tableSize];
		srand(time(NULL));
		hashConstant = unsigned int (rand() % 10000 + 2);
		numStudents = 0;
	}

	//insert s into hash table.  Store by hashing the student's id number.
	//Run time must be: O(1)
	void insert(student s)
	{
		table[hashIndex(s.id)].insert(s);
		numStudents++;
		optimalResize();
	}

	//remove student with given id from table
	//Run time:  Average case O(1 + numStudents/tableSize)
	void remove(unsigned int id)
	{
		int index = hashIndex(id);
		table[index].remove(table[index].retrieveStudentIDNode(id));
		numStudents--;
		optimalResize();
	}

	//Change the gpa of the student with given id number to newGPA
	//Run time:  Average case O(1 + numStudents/tableSize)
	void updateGPA(unsigned int idnumber, double newGPA)
	{
		table[hashIndex(idnumber)].updateGPA(idnumber, newGPA);
	}

	//lookup up and return copy of student with given id.
	//Run time: Average case O(1 + numStudents/tableSize)
	student getStudent(unsigned int id)
	{
		return table[hashIndex(id)].retrieveStudent(id);
	}
	
	//Change the size of your table!  newSize may be bigger or smaller that the current size.
	//Run time? O(n)
	void resize(unsigned int newSize)
	{
		unsigned int oldCapacity = tableSize;
		tableSize = newSize;
		studentList newList;
		for (int i = 0; i < oldCapacity; i++) {
			newList.mergeList(table[i]);
		}
		//delete table;
		table = new studentList[tableSize];
		insert(newList.popFrontStudent());
	}

	//Resize your table to an "optimal" choice based on the
	//current number of entries.  If you make it too large, you waste space.
	//If you make it too small, your searches are slow.  Pick a value
	//that is perfect.  Include in comments the reasoning for your
	//resizing choice.
	/*with the table always slightly larger than the number of students,
	and with a reasonable distribution of students, it will allow */
	void optimalResize()
	{
		if (numStudents == tableSize || tableSize > numStudents * 2) {
			resize(numStudents * 2);
		}
	}

	void print()
	{
		for (int i = 0; i < tableSize; i++){
			std::cout << table[i].getNumStudents() << std::endl;
		}
	}

	void printAllStudents()
	{
		for (int i = 0; i < tableSize; i++) {
			table[i].printList();
			std::cout << std::endl;
		}
	}
	void RANDOM(int listSize)
	{
		srand(time(NULL));
		for (int i = 0; i < listSize; i++) {
			student RStudent("Pedro", rand(), 4.0);
			insert(RStudent);
		}
	}
};