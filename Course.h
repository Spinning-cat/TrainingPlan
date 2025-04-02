#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>

using namespace std;

struct Course {
    string id;                // 课程ID
    string name;              // 课程名称
    double credit;            // 学分
    int hours;                // 课时
    int priority;             // 课程优先级（1:公共基础/实践必修；2:专业基础；3:专业选修；4:实践选修）
    vector<string> prerequisites; // 先修课程列表
};
#endif // COURSE_H
