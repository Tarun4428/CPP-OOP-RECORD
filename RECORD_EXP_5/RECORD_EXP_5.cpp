#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    vector<Student> students = {
        {"Tarun", 88, ' '},
        {"Renisha", 79, ' '},
        {"Sananth", 94, ' '},
        {"Vikas", 58, ' '}
    };

    sort(students.begin(), students.end(),
         [](Student a, Student b)
         {
             return a.mark > b.mark;
         });

    transform(students.begin(), students.end(),
              students.begin(),
              [](Student s)
              {
                  if (s.mark >= 90)
                      s.grade = 'A';
                  else if (s.mark >= 75)
                      s.grade = 'B';
                  else if (s.mark >= 50)
                      s.grade = 'C';
                  else
                      s.grade = 'F';

                  return s;
              });

    auto it = find_if(students.begin(), students.end(),
                      [](Student s)
                      {
                          return s.mark > 80;
                      });

    int total = accumulate(students.begin(), students.end(), 0,
                           [](int sum, Student s)
                           {
                               return sum + s.mark;
                           });

    float average = (float)total / students.size();

    cout << "Grade Analyzer\n";
    cout << "--------------\n";
    cout << "Name\tMark\tGrade\n";

    for (Student s : students)
    {
        cout << s.name << "\t"
             << s.mark << "\t"
             << s.grade << endl;
    }

    if (it != students.end())
    {
        cout << "\nScored above 80: "
             << it->name << endl;
    }

    cout << "Total: " << total << endl;
    cout << "Average: " << average << endl;

    return 0;
}
