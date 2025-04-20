#include "avgassign.h"
#include "Course.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
unordered_map<string, vector<string>> graph;    // 课程依赖图
unordered_map<string, int> indegree;           // 入度表
unordered_map<string, Course> courses;         // 课程信息
void loadCourses(const string& filename) {
    graph.clear();
    indegree.clear();
    courses.clear();
    ifstream file(filename);
    if (!file) {
        cout << "文件无法打开！" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Course course;
        string prereq;

        ss >> course.id >> course.name >> course.credit >> course.hours >> course.priority;
        while (ss >> prereq) {
            course.prerequisites.push_back(prereq);
            graph[prereq].push_back(course.id);
            indegree[course.id]++;
        }

        courses[course.id] = course;
        if (indegree.find(course.id) == indegree.end()) {
            indegree[course.id] = 0;
        }
    }
    file.close();
}

vector<string> TopologicalSort() {
    queue<string> q;
    vector<string> sortedCourses;
    unordered_map<string, int> indegreeCopy = indegree;

    for (const auto& [course, deg] : indegree) {
        if (deg == 0) {
            q.push(course);
        }
    }

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        sortedCourses.emplace_back(cur);

        for (const string& neighbor : graph[cur]) {
            if (--indegreeCopy[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (sortedCourses.size() != courses.size()) {
        cout << "存在循环依赖，无法拓扑排序! \n";
        exit(EXIT_FAILURE);
    }

    return sortedCourses;
}

// 课程分配到 8 个学期，保证专业选修课均匀分布
void assignCourses(const vector<string>& sortedCourses, vector<double>creditDemand) {

    vector<double> semesterCredit(8, 0);
    vector<int> semesterHours(8, 0);
    vector<vector<double>> diffTypeCoursesCredit(4, vector<double>(8, 0)); // 4类课程在某个学期中的分布
    /**
            0   公共基础课和实践必修课总学分
            1   专业基础课
            2   专业选修课
            3   实践选修课
     */

    vector<vector<string>> diffTypeCourses(4, vector<string>());     // 4种不同课程类型中分别包含哪些课
    vector<vector<string>> semesters(8);    // 记录某学期修的课程


    unordered_map<string, int> assignedSemester;  // 存储已分配的课程
    vector<double> diffTypeCoursesCreditTotal(4, 0);     // 4种不同类型课程已修总学分

    // 预分配课程（体育4、通选10、毕业实习8 & 设计10）
    vector<pair<int, string>> peCourses = { {0, "C09"}, {0, "C24"},
                                           {1, "C10"}, {1, "C25"} ,
                                           {2, "C11"}, {2, "C26"} ,
                                           {3, "C12"}, {3, "C27"} ,
                                           {4, "C28"} ,
                                           {6, "C94"},
                                           {7, "C95"}};

    for (const auto& [sem, id] : peCourses) {  // 将已分配课程的学分加上
        semesters[sem].push_back(id);
        semesterCredit[sem] += courses[id].credit;
        semesterHours[sem] += courses[id].hours;
        diffTypeCoursesCredit[0][sem] += courses[id].credit;    // 都归属第一类
        assignedSemester[id] = sem;
    }

    for (const string& id : sortedCourses) {  // 将课程按类型分类，除去预分配课程，将课程按类划分进入diffTypeCourses
        if (assignedSemester.count(id) || id == "C06") continue; // 跳过已固定分配的课程
        if (courses[id].priority == 1 ) {    // 特判形势与政策
            diffTypeCourses[0].push_back(id);
        }
        else if (courses[id].priority == 2) {
            diffTypeCourses[1].push_back(id);
        }
        else if(courses[id].priority == 3) {
            diffTypeCourses[2].push_back(id);
        }
        else{
            diffTypeCourses[3].push_back(id);
        }
    }

    for (int i = 0; i < 8; i++){  // 给每个学期排课

        for (int j = 0; j < 4; j++) {   // 按课程类型给每个学期排课
            int seq = 0;  // 每学期从课程组中的第一个课程开始分配
            diffTypeCoursesCreditTotal[j] += diffTypeCoursesCredit[j][i];  // 将预分配课程某学期的学分加到diffTypeCoursesCreditTotal（8学期）中

            while(seq < diffTypeCourses[j].size()) {    // 用seq遍历某课程类型的所有课程
                string id = diffTypeCourses[j][seq];
                Course course = courses[id];

                // 设置学期平均学分和学期最大学分
                double avgCredit, maxCredit;
                // 初始化
                avgCredit = creditDemand[j] / 8;
                maxCredit = creditDemand[j];

                if(j == 0){
                    avgCredit = maxCredit = (creditDemand[j] - 32) / 4;
                } else if (j == 2){
                    if(i < 4){
                        maxCredit = avgCredit;
                    }else{
                        avgCredit = creditDemand[j] / 4;
                    }
                }
                /**
                                    *特殊设置原因
                 *      j == 0 （公共基础+实践必修） 一般集中在前4个学期，-32减去了预分配的
                 *      j ==  2（专业选修课） 一般集中在从第4个学期开始的4个学期（4-7）
                 */

                double forCredit = diffTypeCoursesCredit[j][i] + course.credit;

                if (forCredit < avgCredit * (i + 1) + 1) {  // 该课程类型的学分未达学期期望的学分时，满足尽量平均分配要求
                    if(forCredit > maxCredit){  // 加上当前课程时，已超最大学分要求，将课程排到后面的学期
                        seq++;
                        continue;
                    }

                    //判断该课程的preq是否已分配
                    bool allPrereqsMet = true;
                    for (const string& prereq : course.prerequisites) {
                        // prereq未分配 or prereq被分配在的学期 >= 第i学期（当前课程想要被分配到的学期，即若成功，prereq会出现在course后）
                        if (assignedSemester.find(prereq) == assignedSemester.end() || assignedSemester[prereq] >= i) {
                            allPrereqsMet = false;
                            break;
                        }
                    }

                    if(allPrereqsMet){  //若先修课程已分配，则分配该课程
                        semesters[i].push_back(id);
                        semesterCredit[i] += course.credit;
                        semesterHours[i] += course.hours;
                        diffTypeCoursesCreditTotal[j] += course.credit;
                        diffTypeCoursesCredit[j][i] += course.credit;  //i代表学期，j代表课程类型
                        assignedSemester.emplace(id, i);

                        diffTypeCourses[j].erase(diffTypeCourses[j].begin() + seq);  //该课程被安排后，删除它
                    }

                    else{
                        seq++;
                    }

                }
                else {  //该课程类型学分已达到要求
                    break;
                }
            }
        }
    }

    // 形势与政策每学期都上，但只把这2个学分加在最后一学期
    diffTypeCoursesCreditTotal[0] += 2;
    diffTypeCoursesCredit[0][7] += 2;

    string ofpath = "/Users/cynthia/projects/QtProject/TrainingPlan/semesterCourses.txt";
    ofstream of(ofpath);

    if (!of) {
        cout << "创建输出文件失败！ \n";
        return;
    }

    of << diffTypeCoursesCreditTotal[0] << endl
       << diffTypeCoursesCreditTotal[1] << endl
       << diffTypeCoursesCreditTotal[2] << endl
       << diffTypeCoursesCreditTotal[3] << endl;

    for (int i = 0; i < 8; i++) {
        of << "Semester" << (i + 1) << ": \n";

        // of << "\n 该学期共修读学分：";
        if (i < 7) {
            of << semesterCredit[i] << endl;
        }
        else {
            of << semesterCredit[i] + 2 << endl;
        }
        of << semesterHours[i] << endl;

        of << diffTypeCoursesCredit[0][i] << endl
           << diffTypeCoursesCredit[1][i] << endl
           << diffTypeCoursesCredit[2][i] << endl
           << diffTypeCoursesCredit[3][i] << endl;

        of << "(C06)" << courses["C06"].name << "\n";
        for (string s : semesters[i]) {
            if(s.empty()) continue;
            of << "("<< s  <<")"<< courses[s].name <<" \n";
        }
    }


    of.close();
}
