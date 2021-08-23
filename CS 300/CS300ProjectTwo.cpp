//=============================================================================================================
// Project Two
// CS300
// 8/13/2021
// Charles French
//
// This program will load course data from inputted CSV files, organize it into a binary tree, then allow the user to 
// list or search for items in the tree, outputting the course and any required prerequisites
//=============================================================================================================

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Course {
	string courseNumber;
	string courseName;
	string prerequisites;

	Course() {
		courseNumber = "";
		courseName = "";
		prerequisites = "";
	}

	//constructor given all info
	Course(string number, string name, string prerequisite) {
		courseNumber = number;
		courseName = name;
		prerequisites = prerequisite;
	}
};

struct Node {
	Course course;
	Node* left;
	Node* right;
	
	//default constructor
	Node(){
		left = nullptr;
		right = nullptr;
	}

	Node(Course course){
		this->course = course;
		left = nullptr;
		right = nullptr;
	}

	Node(Course course, Node* left, Node* right){
		this->course = course;
		this->left = left;
		this->right = right;
	}
};


class Tree {
private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);

public:
	Tree();
	virtual ~Tree();
	void InOrder();
	void Insert(Course course);
	Course Search(string courseId);
};

Tree::Tree() {
	//initialize root pointer
	root = nullptr;
}

Tree::~Tree() {
}

void Tree::InOrder() {
	//pass root to inOrder
	this->inOrder(root);
}

void Tree::Insert(Course course) {
	//if root is null ptr
	if (root == nullptr) {
		//root is new course node
		root = new Node(course);
	}
	else {
		//else add new node to tree
		this->addNode(root, course);
	}
}

Course Tree::Search(string courseId) {
	//set current node equal to root
	Node* current = root;
	//loop downwards until at bottom or matching course number found
	while (current != nullptr) {
		//if matching, return current course
		if (current->course.courseNumber.compare(courseId) == 0) {
			return current->course;
		}
		//if number is smaller, traverse left
		if (courseId.compare(current->course.courseNumber) < 0) {
			current = current->left;
		}
		else {
			//else larger so go right
			current = current->right;
		}
	}
	Course course;
	return course;
}

void Tree::addNode(Node* node, Course course) {
	//if node is larger, add to left
	if (node->course.courseNumber.compare(course.courseNumber) > 0) {
		if (node->left == nullptr) {
			//if no left node, this becomes left
			node->left = new Node(course);
		}
		else {
			//else recursive call down the left node
			this->addNode(node->left, course);
		}
	}
	else {
		//if no right node
		if (node->right == nullptr) {
			//this node becomes right
			node->right = new Node(course);
		}
		else {
			//else recursive call down the right node
			this->addNode(node->right, course);
		}
	}
}

void Tree::inOrder(Node* node) {
	//recursive call to travel tree and print in sorted order
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->course.courseNumber << ", " << node->course.courseName << endl;
		inOrder(node->right);
	}
}

void displayCourse(Course course) {
	//output course number and name
	cout << course.courseNumber << ", " << course.courseName << endl;
	return;
}

Tree* LoadCourses(string fileName, Tree* tree) {
	ifstream data;

	string number;
	string name;
	string prerequisites;
	
	vector<Course> courses;

	// open file
	data.open(fileName);

	// make sure file opened sucessfully
	if (data.is_open()) {
		string line;
		while (data.good()) {
			//get next line
			getline(data, line);
			stringstream item(line);
			while (item.good()) {
				//parse line into different course items
				getline(item, number, ',');
				getline(item, name, ',');
				getline(item, prerequisites);

				//build course object
				Course course = Course(number, name, prerequisites);

				//put course in temp vector
				courses.push_back(course);
			}
		}// close file
		
		data.close();
		
		// import courses into tree structure
		for (int i = 0; i < courses.size(); i++) {
			tree->Insert(courses.at(i));
		}

		return tree;
	}
	else {
		//display error message
		cout << "Error, could not open file." << endl;
		return tree;
	}
}


int main()
{
	//initialize variables
	Tree* tree = new Tree();
	Course course;
	int choice = 0;

	//print menu
		cout << "Welcome to the course planner." << endl;
		while (choice != 9) {
			cout << endl;
			cout << "   1. Load Data Structure." << endl;
			cout << "   2. Print Course List." << endl;
			cout << "   3. Print Course." << endl;
			cout << "   9. Exit" << endl;
			cout << endl;
			cout << "What would you like to do? ";

			cin >> choice;
			switch (choice)
			{
			case 1:
			{//load data structure
				cout << "What file would you like to load? ";
				string name;
				cin >> name;
				//LoadFile(name);
				LoadCourses(name, tree);
				cout << "File loaded!" << endl;
				break; }
			case 2:
				{//print course list
				cout << "Here is a sample course list: " << endl;
				tree->InOrder();
				break; }
			case 3:
				{//print course
				string courseNumber;
				cout << "What course would you like to know about? ";
				cin >> courseNumber;
				cout << endl;
				for (int i = 0; i < courseNumber.size(); i++) {
					// convert input
					if (isalpha(courseNumber[i])) {
						courseNumber[i] = toupper(courseNumber[i]);
					}
				}
				//search for course
				course = tree->Search(courseNumber);

				//check if course object is empty (not in tree -- doesnt exist)
				if (!course.courseNumber.empty()) {
					//output course
					cout << course.courseNumber << ", " << course.courseName << endl;
					//output prerequisites
					cout << "Prerequisites: ";

					if (course.prerequisites.empty()) {
						cout << "None" << endl;
					}
					else {
						//separate prerequisite courses into individual strings
						string prereq1;
						string prereq2;
						stringstream prereqs(course.prerequisites);

						while (prereqs.good()) {
							getline(prereqs, prereq1, ',');
							getline(prereqs, prereq2);
						}
						//check if 1 or 2 prerequisite courses
						if (prereq2.empty()) {
							cout << prereq1 << endl;
						}
						else {
							cout << prereq1 << ", " << prereq2 << endl;
						}
					}
				}
				else {
					//if course not found
					cout << "Course number " << courseNumber << " not found." << endl;
				}
				break; }
			case 9:
				//exit
				cout << "Thank you for using the course planner!" << endl;
				return 0;
			default:
				//invalid input
				cout << choice << " is not a valid option" << endl;
				break;
			}
		}
}

