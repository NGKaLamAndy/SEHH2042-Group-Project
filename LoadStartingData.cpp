#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_SUBJECTS = 50;
int studentCount = 0;

class subject
{
public:
	subject() {
		strcpy(code, "");
		strcpy(subName, "");
		credit = 0;
		strcpy(grade, "N/A");
	}

	void setSubject(const char* scode, const char* ssubName, int scredit, const char* sgrade) {
		strcpy(code, scode);
		strcpy(subName, ssubName);
		credit = scredit;
		strcpy(grade, sgrade);
	}

	void display() const {
		cout << left << setw(10) << code << setw(40) << subName << setw(6) << credit << grade << endl;
	}

	double getPoint() {
		const char* grades[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F"};
		const double points[] = { 4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1.3, 1.0, 0.0 };
		
		for (int i = 0; i < 12; i++) {
			if (strcmp(grade, grades[i]) == 0) {
				return points[i];
			}
		}
		return -1.0;
	}

	int getCredit() {
		return credit;
	}

private:
	char code[10], subName[41], grade[4];
	int credit;
};

class student
{
public:
	student() {
		strcpy(name, "");
		strcpy(id, "");
		strcpy(major, "");
		year = 0;
		gpa = 0.0;
	}

	void setInfo(const char* sname, const char* sid, const char* smajor, int syear, double sgpa) {
		strcpy(name, sname);
		strcpy(id, sid);
		strcpy(major, smajor);
		year = syear;
		gpa = sgpa;
	}

	void setName(const char* newname) {
		strcpy(name, newname);
	}

	const char* getName() {
		return name;
	}

	void setMajor(const char* newmajor) {
		strcpy(major, newmajor);
	}

	const char* getMajor() {
		return major;
	}

	void addSubject(const char* code, const char* subName, int credit, const char* grade) {
		subjects[subjectCount].setSubject(code, subName, credit, grade);
		subjectCount++;
		calculateGPA();
	}

	void calculateGPA() {
		double total = 0.0;
		int credits = 0;
		
		for (int i = 0; i < subjectCount; i++) {
			double p = subjects[i].getPoint();
			if (p >= 0) {
				total += p * subjects[i].getCredit();
				credits += subjects[i].getCredit();
			}
		}

		if (credits == 0)
			gpa = -1.0;
		else {
			double result = total / credits;
			gpa = result;
		}
	}


	void display() const {
		cout << "\nName: " << name << "\nID: " << id << "\nMajor: " << major << "\nYear: " << year << "\nGPA: " << gpa << endl;
		cout << left << setw(10) << "Code" << setw(40) << "Subject Name" << setw(6) << "Credit" << "Grade" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < subjectCount; ++i) {
			subjects[i].display();
		}
	}




private:
	char name[20], id[12], major[25];
	int year;
	double gpa;
	subject subjects[MAX_SUBJECTS];
	int subjectCount = 0;
};

student students[MAX_STUDENTS];
bool dataLoaded = false;

void loadStartingData() {
	studentCount = 0;

	students[studentCount].setInfo("CHAN Tai Man", "S243560", "Information Engineering", 1 , 4.00);
	students[studentCount].addSubject("ENG2042", "Introduction to C++", 3, "A");
	students[studentCount].addSubject("ENG2219", "Signal Processing", 3, "A");
	students[studentCount].addSubject("LCH1302", "Professional English Writing", 2, "A");
	students[studentCount].addSubject("LCH1019", "Japanese I", 2, "--");
	studentCount++;

	students[studentCount].setInfo("CHEUNG Jacky", "S232210", "Civil Engineering", 2 , 2.48);
	students[studentCount].addSubject("ENG1113", "Structural Fundamental", 3, "B");
	students[studentCount].addSubject("ENG2250", "Engineering Mathematics", 3, "B+");
	students[studentCount].addSubject("ENG2041", "Applied Computing", 3, "F");
	students[studentCount].addSubject("LCH1302", "Professional English Writing", 2, "A-");
	students[studentCount].addSubject("LCH1019", "Japanese I", 2, "B");
	students[studentCount].addSubject("BUS1021", "Personal Financial Planning", 3, "--");
	students[studentCount].addSubject("ENG2042", "Introduction to C++", 3, "--");
	studentCount++;

	students[studentCount].setInfo("PAN Peter", "S222343", "Global Business", 3, 3.42);
	students[studentCount].addSubject("BUS1021", "Personal Financial Planning", 3, "A");
	students[studentCount].addSubject("BUS2002", "Introduction to Economics", 3, "A+");
	students[studentCount].addSubject("BUS3006", "Understanding Globalization", 3, "B-");
	students[studentCount].addSubject("BUS4510", "Business Project Management", 4, "A-");
	students[studentCount].addSubject("BUS5523", "Final Year Project", 5, "B+");
	students[studentCount].addSubject("LCH1019", "Japanese I", 2, "C");
	studentCount++;

	students[studentCount].setInfo("WONG Kam", "S244617", "Educational Psychology", 1, 2.86);
	students[studentCount].addSubject("PSY1234", "Introduction to Psychology", 2, "C");
	students[studentCount].addSubject("PSY2233", "Sociology", 3, "B");
	students[studentCount].addSubject("PSY2190", "Human Behavior", 3, "B+");
	studentCount++;

	dataLoaded = true;
	cout << "All student records loaded successfully.\n";
}

void showAllStudents() {
	if (!dataLoaded) {
		cout << "Please load data first.\n";
		return;
	}

	for (int i = 0; i < studentCount; i++) {
		students[i].display();
	}
}

int main() {
	cout << "loading...\n";
	loadStartingData();
	showAllStudents();

	return 0;
}