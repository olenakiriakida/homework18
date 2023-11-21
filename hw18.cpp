
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;


class DateTime
{
private:
    int day;
    int month;
    int year;
    static time_t t;
    static struct tm* now;

public:

    void SetDay(int day)
    {
        if (day > 0 && day <= 31)
        {
            this->day = day;
        }
        else
        {
            cout << "Invalid value!\n";
            throw "ERROR!\n";
        }
    }

    int GetDay() const
    {
        return day;
    }

    void SetMonth(int month)
    {
        if (month >= 1 && month <= 12)
        {
            this->month = month;
        }
        else
        {
            cout << "Invalid value!\n";
            throw "ERROR!\n";
        }
    }

    int GetMonth() const
    {
        return month;
    }

    void SetYear(int year)
    {
        this->year = year;
    }

    int GetYear() const
    {
        return year;
    }

    int PrintSystemHours() {
        return now->tm_hour;
    }

    int PrintSystemMinutes() {
        return now->tm_min;
    }

    int PrintSystemSeconds()
    {
        return now->tm_sec;
    }

    DateTime() : DateTime(9, 4, 2005) {}

    DateTime(int day) : DateTime(day, 4, 2005) {}

    DateTime(int day, int month, int year)
    {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }

    void Print() const
    {
        cout << "Date: " << day << "." << month << "." << year << "\n";
    }


    string date_to_string() const
    {
        return to_string(day) + "." + to_string(month) + "." + to_string(year);
    }

};


istream& operator>>(istream& cin, DateTime& obj)
{
    int day, month, year;
    cout << "Type a year:\n";
    cin >> year;
    obj.SetYear(year);
    cout << "Type a month:\n";
    cin >> month;
    obj.SetMonth(month);
    cout << "Type a day:\n";
    cin >> day;
    obj.SetDay(day);
    return cin;
}

ostream& operator<<(ostream& cout, DateTime& obj)
{
    obj.Print();
    return cout;
}

class Logger
{
    static Logger* instance;
    DateTime* date_time;
    int log_сount = 0;
    string path = "D:/log.txt";

    Logger()
    {
    }

public:
    static Logger* GetInstance()
    {
        return instance == nullptr ? instance = new Logger() : instance;
    }

    void Write(string message)
    {
        log_сount++;
        int hours = date_time->PrintSystemHours(), minutes = date_time->PrintSystemMinutes(), seconds = date_time->PrintSystemSeconds();
        string time = to_string(hours);
        time += ':';
        time += to_string(minutes);
        time += ':';
        time += to_string(seconds);
        ofstream output_file(path, ios::app);
        if (output_file.is_open())
        {
            output_file << message << " in " << time << "\n";
            cout << message << " in " << time << '\n';
            output_file.close();
        }
        else
        {
            cerr << "Can't open file.\n";
        }
    }

    void Write(int value)
    {
        Write(to_string(value));
    }
};

class Student
{
private:
    string name;
    string surname;
    string father_name;
    DateTime birthday;
    string address;
    string phone_number;
    DateTime study_start;
    static int totalCountOfStudents;
    static const int maxAllowedStudents = 15;

    int* practice_rates = nullptr;
    int practice_rates_count = 0;

    int* exam_rates = nullptr;
    int exam_rates_count = 0;

    int* hometask_rates = nullptr;
    int hometask_rates_count = 0;

public:
    Student() : Student("prismo", "the wishmaster", "almighty", { 9, 10, 2000 }, "cube", "077777777", { 12, 02, 2009 }) {
        cout << "Student has been created!" << endl;
    }

    Student(string name, string surname, string father_name, string address, string phone_number)
        : Student(name, surname, father_name, { 9, 10, 2000 }, address, phone_number, { 12, 02, 2009 }) {}

    Student(string name, string surname, string father_name, DateTime birthday, string address, string phone_number, DateTime study_start)
    {
        SetName(name);
        SetSurname(surname);
        SetFatherName(father_name);
        SetBirthday(birthday);
        SetAddress(address);
        SetPhoneNumber(phone_number);
        SetStudyStart(study_start);
    }

    ~Student()
    {
        if (practice_rates != nullptr)
        {
            delete[] practice_rates;
            practice_rates = nullptr;
        }
        if (hometask_rates != nullptr)
        {
            delete[] hometask_rates;
            hometask_rates = nullptr;
        }
        if (exam_rates != nullptr)
        {
            delete[] exam_rates;
            exam_rates = nullptr;
        }

        cout << "Student #" << totalCountOfStudents << " has been destroyed\n";
        totalCountOfStudents--;
    }

    Student(const Student& other) {
        name = other.name;
        surname = other.surname;
        father_name = other.father_name;
        birthday = other.birthday;
        address = other.address;
        phone_number = other.phone_number;
        study_start = other.study_start;

        practice_rates_count = other.practice_rates_count;
        practice_rates = new int[practice_rates_count];
        for (int i = 0; i < practice_rates_count; ++i) {
            practice_rates[i] = other.practice_rates[i];
        }

        exam_rates_count = other.exam_rates_count;
        exam_rates = new int[exam_rates_count];
        for (int i = 0; i < exam_rates_count; ++i) {
            exam_rates[i] = other.exam_rates[i];
        }

        hometask_rates_count = other.hometask_rates_count;
        hometask_rates = new int[hometask_rates_count];
        for (int i = 0; i < hometask_rates_count; ++i) {
            hometask_rates[i] = other.hometask_rates[i];
        }

        if (totalCountOfStudents >= maxAllowedStudents)
        {
            throw runtime_error("Max number of students exceeded. Cannot create more students.");
        }
        totalCountOfStudents++;
        cout << "Student #" << totalCountOfStudents << " has been created\n";
    }

    void SetName(string name)
    {
        this->name = name;
    }

    string GetName() const
    {
        return name;
    }

    void SetSurname(string surname)
    {
        this->surname = surname;
    }

    string GetSurname() const
    {
        return surname;
    }

    void SetFatherName(string father_name) {
        this->father_name = father_name;
    }

    string GetFatherName() const {
        return father_name;
    }

private:
    void SetBirthday(const DateTime& birthday)
    {
        this->birthday = birthday;
    }

public:

    DateTime GetBirthday() const
    {
        return birthday;
    }

    void SetAddress(string address) {
        this->address = address;
    }

    string GetAddress() const {
        return address;
    }

    void SetPhoneNumber(string phone_number) {
        this->phone_number = phone_number;
    }

    string GetPhoneNumber() const {
        return phone_number;
    }

    void SetStudyStart(const DateTime& study_start)
    {
        this->study_start = study_start;
    }

    DateTime GetStudyStart() const
    {
        return study_start;
    }

    void AddPracticeRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter grade. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (practice_rates_count == 0)
        {
            practice_rates = new int[1];
            practice_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another grade\n";

            int* temp = new int[practice_rates_count + 1];

            for (int i = 0; i < practice_rates_count; i++)
            {
                temp[i] = practice_rates[i];
            }
            temp[practice_rates_count] = rate;

            delete[] practice_rates;

            practice_rates = temp;
        }

        practice_rates_count++;
    }

    void PrintPracticeRates() const
    {
        cout << "Practice rates: ";
        for (int i = 0; i < practice_rates_count; i++)
        {
            cout << practice_rates[i] << ", ";
        }
        cout << "\n";
    }

    int GetPracticeRateByIndex(unsigned int index) const
    {
        if (index >= practice_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return practice_rates[index];
    }

    int GetPracticeRatesCount() const
    {
        return practice_rates_count;
    }

    void AddHometaskRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter rate. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (hometask_rates_count == 0)
        {
            hometask_rates = new int[1];
            hometask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[hometask_rates_count + 1];
            for (int i = 0; i < hometask_rates_count; i++)
                temp[i] = hometask_rates[i];
            temp[hometask_rates_count] = rate;
            delete[] hometask_rates;
            hometask_rates = temp;
        }
        hometask_rates_count++;
    }

    void PrintHometaskRates() const
    {
        cout << "Hometasks rates: ";
        for (int i = 0; i < hometask_rates_count; i++)
        {
            cout << hometask_rates[i] << ", ";
        }
        cout << "\n";
    }

    int GetHometaskRateByIndex(unsigned int index) const //to get the grade by index, but without returning a pointer to the original data array, we need to add the "const" keyword to this method
    {
        if (index >= hometask_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return hometask_rates[index];
    }

    int GetHometasksRatesCount() const
    {
        return hometask_rates_count;
    }

    void AddExamRate(unsigned int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "Incorrect value for parameter grade. Value must be from 1 to 12\n";
            throw "ERROR!";
        }

        if (exam_rates_count == 0)
        {
            exam_rates = new int[1];
            exam_rates[0] = rate;
        }
        else
        {
            cout << "Add yet another grade\n";

            int* temp = new int[exam_rates_count + 1];

            for (int i = 0; i < exam_rates_count; i++)
            {
                temp[i] = exam_rates[i];
            }
            temp[exam_rates_count] = rate;

            delete[] exam_rates;

            exam_rates = temp;
        }

        exam_rates_count++;
    }

    void PrintExamRates() const
    {
        cout << "Exam rates: ";
        for (int i = 0; i < exam_rates_count; i++)
        {
            cout << exam_rates[i] << ", ";
        }
        cout << "\n";
    }

    int GetExamRateByIndex(unsigned int index) const
    {
        if (index >= exam_rates_count)
        {
            cout << "Incorrect index when accessing the evaluation array\n";
            throw "ERROR!";
        }
        return exam_rates[index];
    }

    int GetExamRatesCount() const
    {
        return exam_rates_count;
    }

    double GetHometaskAverageRate() const
    {
        if (hometask_rates_count == 0) return 0;

        double sum = 0;
        for (int i = 0; i < hometask_rates_count; i++)
        {
            sum += hometask_rates[i];
        }
        double average = sum / hometask_rates_count;
        return average;
    }

    void ShowStudent() const {
        cout << "Name: " << name << "\n";
        cout << "Surname: " << surname << "\n";
        cout << "Father Name: " << father_name << "\n";
        cout << "Address: " << address << "\n";
        cout << "Phone Number: " << phone_number << "\n";
    }

    static int GetTotalCountOfStudents()
    {
        return totalCountOfStudents;
    }

};


bool operator==(const Student& left, const Student& right)
{
    return left.GetHometaskAverageRate() == right.GetHometaskAverageRate();
}

bool operator!=(const Student& left, const Student& right)
{
    return left.GetHometaskAverageRate() != right.GetHometaskAverageRate();
}

bool operator>(const Student& left, const Student& right)
{
    return left.GetHometaskAverageRate() > right.GetHometaskAverageRate();
}

bool operator<(const Student& left, const Student& right)
{
    return left.GetHometaskAverageRate() < right.GetHometaskAverageRate();
}

class Group
{
private:
    Student** students = nullptr;
    string name;
    int students_amount = 0;
    int course_number;
    string specialization;
    static int totalCountOfGroups;
    int groupsize = 12;

public:

    Group()
    {
        SetName("cosmic gate");
        SetCourseNumber(2023);
        SetSpecialization("piloting of spacecraft");
    }

    Group(const Group& group)
    {
        this->name = group.name;
        this->students_amount = group.students_amount;
        this->specialization = group.specialization;
        this->course_number = group.course_number;
        this->specialization = group.specialization;

        this->students = new Student * [this->students_amount];

        for (int i = 0; i < this->students_amount; i++)
        {
            this->students[i] = group.students[i];
        }

        totalCountOfGroups++;
        cout << "Group " << totalCountOfGroups << " has been created\n";
    }

    ~Group()
    {
        if (students != nullptr)
        {
            for (int i = 0; i < students_amount; i++)
            {
                delete students[i];
            }
            delete[] students;
        }

        cout << "Group #" << totalCountOfGroups << " has been destroyed\n";
        totalCountOfGroups--;
    }

    void SetName(string name)
    {
        if (name != "")
        {
            this->name = name;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    string GetName() const
    {
        return name;
    }

    void SetCourseNumber(int course_number)
    {
        if (course_number > 0)
        {
            this->course_number = course_number;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    int GetCourseNumber() const
    {
        return course_number;
    }

    void SetSpecialization(string specialization)
    {
        if (specialization != "")
        {
            this->specialization = specialization;
        }
        else
        {
            cout << "Invalid value!" << endl;
            throw "ERROR!\n";
        }
    }

    string GetSpecializationGroup() const
    {
        return specialization;
    }

    int GetStudentsAmount() const
    {
        return students_amount;
    }

public:

    void ShowStudents()
    {
        cout << "Name of the group: " << name << "\n";
        cout << "Course: " << course_number << "\n";
        cout << "Specialization: " << specialization << "\n";

        if (students_amount == 0)
        {
            cout << "You don't have students in this group\n";
            return;
        }

        cout << "Students: \n";

        for (int i = 0; i < students_amount - 1; i++)
        {
            for (int j = i + 1; j < students_amount; j++)
            {
                if (students[j]->GetSurname() < students[i]->GetSurname())
                {
                    Student* temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }

        for (int i = 0; i < students_amount; i++)
        {
            cout << i + 1 << ", ";
            students[i]->ShowStudent();
        }

    }

    void NewStudent(const Student& new_student)
    {
        Student** temp = new Student * [students_amount + 1];

        for (int i = 0; i < students_amount; i++)
        {
            temp[i] = new Student(*students[i]);
        }

        temp[students_amount] = new Student(new_student);

        delete[] students;
        students = temp;
        students_amount++;
    }

    void ChangeGroups(Group& group2)
    {
        for (int i = 0; i < group2.GetStudentsAmount(); i++)
        {
            this->NewStudent(group2.GetStudentByIndex(i));
        }

        int k = group2.GetStudentsAmount();
        for (int i = 0; i < k; i++)
        {
            group2.DeleteFailedHomeworkStudent();
        }
    }

    void TransferStudent(Group& group, int index)
    {
        if (index >= 0 && index < students_amount)
        {
            group.NewStudent(*students[index]);

            for (int i = index; i < students_amount - 1; i++)
            {
                students[i] = students[i + 1];
            }

            students_amount--;
        }
    }

    void DeleteFailedExamStudent()
    {
        for (int i = 0; i < students_amount; i++)
        {
            if (students[i]->GetExamRatesCount() > 0)
            {
                int minExamRate = students[i]->GetExamRateByIndex(0);

                for (int j = 1; j < students[i]->GetExamRatesCount(); j++)
                {
                    if (students[i]->GetExamRateByIndex(j) < minExamRate)
                    {
                        minExamRate = students[i]->GetExamRateByIndex(j);
                    }
                }

                if (minExamRate < 3)
                {
                    cout << "Removing student " << students[i]->GetName() << " " << students[i]->GetSurname() << " due to failed exams." << endl;

                    for (int k = i; k < students_amount - 1; k++)
                    {
                        students[k] = students[k + 1];
                    }
                    students_amount--;
                    i--;
                }
            }
        }
    }

    void DeleteFailedHomeworkStudent()
    {
        if (students_amount == 0)
        {
            cout << "You don't have students in this group\n.";
            return;
        }

        int lowestIndex = 0;
        double lowestAverageGrade = students[0]->GetHometaskAverageRate();

        for (int i = 1; i < students_amount; i++)
        {
            double currentAverageGrade = students[i]->GetHometaskAverageRate();
            if (currentAverageGrade < lowestAverageGrade)
            {
                lowestAverageGrade = currentAverageGrade;
                lowestIndex = i;
            }
        }

        for (int i = lowestIndex; i < students_amount - 1; i++)
        {
            students[i] = students[i + 1];
        }
        students_amount--;


    }

    Student GetStudentByIndex(unsigned int index) const
    {
        if (index < students_amount)
        {
            return *students[index];
        }
        else
        {
            cout << "Incorrect index " << endl;
            throw "ERROR!";
        }
    }

    static int GetTotalCountOfGroups()
    {
        return totalCountOfGroups;
    }

    operator string() {
        string info;
        info += "Group\nName: ";
        info += name;
        info += "\n";
        info += "Specialization: ";
        info += specialization;
        info += "\n\n";
        for (int i = 0; i < students_amount; i++) {
            info += "Student # ";
            info += to_string(i + 1);
            info += '\n';
            info += "Name: ";
            info += students[i]->GetName();  
            info += '\n';
            info += "Surname: ";
            info += students[i]->GetSurname();  
            info += "\nStudy start: ";
            info += students[i]->GetStudyStart().date_to_string();
            info += '\n';
        }
        info += "\n\n\n";
        return info;
    }

    friend istream& operator>>(istream& cin, Group& group);
    friend ostream& operator<<(ostream& cout, const Group& group);
};

istream& operator>>(istream& cin, Group& group)
{
    cout << "Enter group name: ";
    cin >> group.name;

    cout << "Enter course number: ";
    cin >> group.course_number;

    return cin;
}

ostream& operator<<(ostream& cout, const Group& group)
{
    cout << "Group Name: " << group.name << "\n";
    cout << "Course Number: " << group.course_number;
    return cout;
}

int Student::totalCountOfStudents;
int Group::totalCountOfGroups;

class Fraction
{
    int numerator;
    int denominator;

public:
    Fraction();
    Fraction(int numerator, int denominator);

    Fraction(int value)
    {
        numerator = value;
        denominator = 1;
    }

    double GetDecimal() const;
    void Print() const;
    void PrintDecimal() const;

    static Fraction Sum(const Fraction& left, const Fraction& right);
    bool GreaterThan(const Fraction& another) const;
    bool IsEquals(const Fraction& another) const;
    bool LessThan(const Fraction& another) const;

    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int numerator);
    void SetDenominator(int denominator);
};

Fraction operator + (const Fraction& f1, const Fraction& f2);
void F1(Fraction a);
Fraction F2();

Fraction::Fraction() : Fraction(0, 1)
{

}

Fraction::Fraction(int numerator, int denominator)
{
    SetNumerator(numerator);
    SetDenominator(denominator);
}

double Fraction::GetDecimal() const
{
    return (double)numerator / denominator;
}

void Fraction::Print() const
{
    cout << numerator << "/" << denominator << "\n";
}

void Fraction::PrintDecimal() const
{
    cout << GetDecimal() << "\n";
}

int Fraction::GetNumerator() const
{
    return numerator;
}

int Fraction::GetDenominator() const
{
    return denominator;
}

void Fraction::SetNumerator(int numerator)
{
    this->numerator = numerator;
}

void Fraction::SetDenominator(int denominator)
{
    if (denominator != 0)
    {
        this->denominator = denominator;
    }
    else
    {
        throw "ERROR!";
    }
}

bool Fraction::LessThan(const Fraction& right) const
{
    return this->GetDecimal() < right.GetDecimal();
}

bool Fraction::GreaterThan(const Fraction& right) const
{
    return this->GetDecimal() > right.GetDecimal();
}

bool Fraction::IsEquals(const Fraction& right) const
{
    return this->GetDecimal() == right.GetDecimal();
}

void F1(Fraction a)
{
    cout << "explicit c-tor test global function F1\n";
}

Fraction F2()
{
    cout << "explicit c-tor test global function F2\n";
    return 5;
}

Fraction Fraction::Sum(const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.numerator * right.denominator + right.numerator * left.denominator);
    result.SetDenominator(left.denominator * right.denominator);
    return result;
}

Fraction operator + (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator() + right.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator + (const Fraction& left, int right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() + (right * left.GetDenominator()));
    result.SetDenominator(left.GetDenominator());
    return result;
}

Fraction operator + (int left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator((left * right.GetDenominator()) + right.GetDenominator());
    result.SetDenominator(right.GetDenominator());
    return result;
}

Fraction operator + (const Fraction& left, double right)
{
    Fraction result, tmp;
    tmp.SetNumerator((int)right);
    if (right - (int)right > 0)
        tmp.SetDenominator((right - (int)right) * 10);
    else
        tmp.SetDenominator(1);
    result.SetNumerator(left.GetNumerator() * tmp.GetDenominator() + tmp.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * tmp.GetDenominator());
    return result;
}

Fraction operator + (double left, const Fraction& right)
{
    Fraction result, tmp;
    tmp.SetNumerator((int)left);
    if (left - (int)left > 0)
        tmp.SetDenominator((left - (int)left) * 10);
    else
        tmp.SetDenominator(1);
    result.SetNumerator(right.GetNumerator() * tmp.GetDenominator() + tmp.GetNumerator() * right.GetDenominator());
    result.SetDenominator(right.GetDenominator() * tmp.GetDenominator());
    return result;
}

Fraction operator - (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator() - right.GetNumerator() * left.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator * (const Fraction& left, const Fraction& right)
{
    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetNumerator());
    result.SetDenominator(left.GetDenominator() * right.GetDenominator());
    return result;
}

Fraction operator / (const Fraction& left, const Fraction& right)
{
    if (right.GetNumerator() == 0) {
        throw "ERROR: Division by zero.";
    }

    Fraction result;
    result.SetNumerator(left.GetNumerator() * right.GetDenominator());
    result.SetDenominator(left.GetDenominator() * right.GetNumerator());
    return result;
}


int main()
{
    Logger::GetInstance()->Write("prismo logged in in");
    Group group;
    Student a;
    Student b;
    Student c;
    Logger::GetInstance()->Write("prismo exited ");
}
