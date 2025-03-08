# 智能选课系统

# 项目说明

## **项目背景**

基于本专业的课程设置，实现智能课程规划。

## **项目主要功能**

本项目要实现的主要功能：

1. **课程维护：** 基于给定的部分数据维护某专业的培养方案的课程信息。建议的信息包括：

   * 课程编号
   * 课程名称
   * 课程学分
   * 上课时间（取值范围：周一~周日）
   * 上课节数
   * 课程类型
   * 前置课程编号

**提示：** 提供的数据来自于华东师范大学-公共数据库-全校开课查询，其中包含了 2022 年至 2023 年计算机科学与技术学院开设的一部分课程信息，还包含了一部分独立的测试数据。

我们提供的数据存储在四个.csv 文件中，分别为：**课程开课时间**，**课程信息**，**前置课程**，**后继课程**，详细的说明请看<u>数据说明</u>。你可以自行选择其中的信息完成项目的主要目标，**对给定数据进行部分删减、增添都是可以接受的，如果你希望采用其他来源的数据，请至少包含以上建议信息来完成主要目标。**

我们不对数据存储格式做限制，你可以自由选择文本文档，json 格式文件或者数据库来进行存储。

2. **根据毕业要求（总学分及各类课程的学分）需求，生成选课方案：** 给定总学分和不同类别课程的学分要求后，能够按照不同学期给出一个合理的选课方案，如第一学期：课程 A，课程 B，第二学期：课程 C，课程 D。

**提示：** 一门课每周可能有超过 1 次的上课时间，比如数据结构，每周有 3 个时间段上课。

相同的课程在同一学期可以有多位老师开设，上课的时间段可能各不相同，例如计算机学院开设的大学物理 B(二)课程三位老师，但三位老师的上课时间段并不完全重合；而另外一门开在同一学期的必修课程可能与这门课程的时间是存在冲突的，例如 2023 年计算机学院开设的线性代数课程有三位老师，而其中一位老师的一个课程时间与大学物理 B(二)的一个课程时间存在冲突，但合理的课程容量安排使得这两门课实际上可以在同一学期开设，这两门课程已经包括在提供的数据当中，你可以尝试把它作为自主拓展功能实现。

## **项目评分要点**

1. 生成 8 个学期的课程推荐，每个学期包括学科基础课和专业必修课，剩余学分将通过其他类型的课程来补齐。生成的课表需要满足前置课程的限制。（40 分）
   知识点：拓扑排序（将在课程“第 6 章 图”中学习）。

加分项：能在满足前置课程限制的条件下，满足后继课程要求（例如数学分析一和数学分析二尽量连续排在 2 个学期）。

2. 生成一套在最短时间内修完毕业所需学分的课程方案，每个学期修读的学分上限作为变量输入。（40 分）
   知识点：AOE 网络（将在课程“第 6 章 图”中学习）。
3. 自主扩展功能。根据选课场景，自主生成其他限制条件下的课程方案生成，要求功能扩展合理。（20 分）例如：
   “意愿值”场景：选修课选课要花费“意愿值”，每学期每个同学可以使用的意愿值总和为 100。为每门选修课程设置高低不等的选课最低意愿值；在此基础上，生成选课方案。
   “时间限制场景”：某学生在某个时间段不希望有课，基于这个限制条件生成选课方案。

## 数据说明

这是从公共数据库全校开课查询中截取的数据结构课程，这将会帮助你理解我们提供的数据。

​![](assets/wps1-20241217193444-2gptnd3.jpg)​

### **课程信息 courses**

* **course_basic_ID**

课程基础序号，例如 'COMS0031121009'

* **course_sp_ID**

课程班级序号，例如贺老师班是 '02'

* **course_name**

课程名称 例如'数据结构'

* **teacher**

教师姓名

* **department**

开课院系。 我们提供的数据中，'计算机科学与技术学院'是从公共数据库下载的数据，还有其他院系为'测试数据'的，是一些特殊情况的测试。

* **semester**

学期。分为秋季学期和春季学期。

* **category**

课程类别，例如 '专业必修课'

* **credit**

学分

* **beg_week**

开始周数

* **last_week**

持续的周数。

* **limits**

选课人数上限

### **开课时间 course_period**

我们存储的上课，每一段连续的上课时段为一条记录。

例如：数据结构在周二 3-4，周五 3-4，周五 6-7 节上课，就会存储三条记录。

* **course_basic_ID**

课程基础序号。和 courses 中保持一致。

* **course_sp_ID**

课程班级序号。和 courses 中保持一致。

* **day**

上课日期。从周一到周日以缩写记录。

* **beg**

开始节数，与数据库中保持一致。例如上午第三节是 3，下午第一节是 6。

* **last**

持续节数，比如 2 节就是 2。

### **前置课程 prereq**

记录某一门课程所需要的前置课程。使用 ID 来记录。

例如：学习数据结构（ID：COMS0031121009）需要先学习编程思维与实践（ID: COMS0031131043），则会有一条记录：（COMS0031121009，COMS0031131043）。 一门课程可能有多个前置课程，则会有多条记录。

* **course_basic_ID**

课程基础序号，与 courses 中保持一致。在上面的例子中为‘COMS0031121009’

* **prereq_ID**

前序课程的基础序号，与 courses 中保持一致。在上面的例子中为‘COMS0031131043’。

### **后继课程 succeed**

有时我们希望两节课尽量排在相连的两个学期，则会使用该信息。

例如：数学分析 I（ID：COMS0031121013）和数学分析 II（ID：COMS0031121014）尽量连在两个学期安排，则会有一条记录（COMS0031121013，COMS0031121014）。

* **course_basic_ID**

课程基础序号，与 courses 中保持一致。在上面的例子中为‘COMS0031121013’。

* **succeed_course_basic_ID**

后继课程的基础序号，与 courses 中保持一致。在上面的例子中为‘COMS0031121013’。

# 算法部分

## 数据结构

### 数据组织

以**有向图**结构组织课程，记为 `G = (E, V)`​

* 每个节点对应一个课程，节点信息同上
* 每条边对应课程的**先修**关系，`(a, b)` ​即 a 课程为 b 课程的先修课

  * 没有先修课程要求，则作为无入度的节点存在

### 创建

* 从 *course* 数据库和 *course_period* 中读取数据，创建节点
* 从 *prereq* 数据库和 *succeed* 数据库中读取数据，创建边

  * *prereq* 中的边不要求在相邻学期
  * *succeed* 中的边要求尽量在相邻学期

### 遍历

需要是拓扑遍历

* 只能将无入度的节点作为起点
* 同时需要获取节点占用时间段，解决时间冲突问题
* 当前节点被遍历后，删除该节点的所有边

## 根据学分生成选课方案

1. 满足学期限制

    1. 只关注春秋学期的区分，忽略年级（实际上也没有对应数据）
    2. 通过 flag 进行切换
2. 满足学分要求
3. 避免上课时间冲突

    1. 三维数组
    2. x-当日时间; y-星期; z-周数
4. 满足先修要求

    1. 拓扑排序
5. 同一门课可能会有多个上课时间
6. 满足后继要求

    1. 相关联的课程放在相邻学期

## 修读最短时间

* AOE 网络

1. 满足每学期学分限制
2. 尽可能快地修完课程
3. 不考虑春秋学期的划分，有课就上
4. 避免上课时间冲突
5. 满足先修要求
6. 满足后继要求

## 自主扩展功能

设置上课时间限制，该时间段不会分配上课，但是如果有前置课程只能分配在该时间段，则会返回错误信息

# 后端部分

* 使用 Java 语言，SpringBoot3、MyBatis-Plus 相关技术栈
* 数据库：MySQL
* 部分工具代码：Python

## 基本增删改查

### 查询所有课程信息

> CourseController

```Java
/**
 * 获取所有课程信息
 *
 * @return
 */
@GetMapping("getAllCourses")
public Result getAllCourse() {
    Result result = courseService.getAllCourses();
    System.out.println("result = " + result);
    return result;
}
```

> CourseService

```Java
/**
 * 获取所有的课程信息
 *
 * @return
 */
Result getAllCourses();
```

> CourseServiceImpl

```Java
@Override
public Result getAllCourses() {
    List<Course> courses = courseMapper.selectList(null);
    if (courses == null || courses.isEmpty()) {
        return Result.build(null, ResultCodeEnum.ERROR);
    }
    return Result.ok(courses);
}
```

## 一般选课方案生成

### 实现思路

1. 从数据库读取数据

   1. 存放，注意需要将 Course 和 CoursePeriod 进行对应
2. 初始化容器

   1. 建图，点数为 *n*

      1. 根据节点的编号进行存放，一门课一周会上多次课
   2. 容器 `List<int[][][]> result = new ArrayList<>();` ​存放 8 个学期的课程表
   3. 三维数组 `int[][][] occupied = new int[18][7][14];` ​每个学期的课程表

      1. 每天 14 个时间段
      2. 每周 7 天
      3. 每学期 18 周
      4. 使用 `CourseTableVo` ​进行封装
   4. 一维数组 `boolean[] visited = new boolean[n];` ​表示当前课是否被选读过
3. 拓扑排序

   1. 准备两个队列，一个队列对应春学期，一个对应秋学期，两个队列交替使用

      1. 初始先将入度为 0 的节点全部存放到队列中（注意学期对应）
   2. 根据 flag 取出对应队列中的节点，检查并标记 `visited`​ ​和 `occupied`​

      1. ​`occupied` ​标记如何实现？

         1. 会有多个老师可以满足，若满足则直接选择（最快修读可能会有要求）
         2. 如果加入失败怎么处理？

            1. 直接略过？

               1. 后序课程怎么办？
            2. 放回队列里？
            3. 如果只将后序课程存放在当前课程中，该何时加入？
   3. 删除指向其他节点的边

      1. 注意要删除入边和出边
      2. 对于入边，只关注数量; 对于出边，不考虑实际删除，可以节约这部分时间
   4. 更新队列

      1. 放入对应学期的队列中
      2. 如果为 succeed 中的关系，则放入队首，确保能尽量选上

          1. 在实现中，将succeed转换为从后指向前，以便遍历时进行添加
      3. 入度为 0 的节点放入队尾
   5. 直到满足学分要求或者无课可选

### 问题

> Q：如何解决同个课程不同老师？

* 图的初始化和求拓扑排序
* 是直接看成两个节点，还是当成同一个节点？

  * 看成两个节点，`visited` ​如何维护？
  * 看成一个节点，将不同老师及其时间另外存放容器，更好维护，但是不能根据 ID 取——需要 Map

A：采用当做一个节点的实现，Course 的 `equals()` ​只对 `courseBasicId` ​进行比较，使用 Map `basicIdToIndex` ​来存储 `courseBasicId` ​对应的 `graph` ​下标

> Q：邻接表的实现，是存储索引配合另外的容器，还是直接存放对象？

A：在对象中存放边，提高聚合度

### 数据结构实现

* `CourseDetailBo`​​
* `CourseGraph`​
* ​`CourseTableVo`​

### 返回结果

```JSON
{
    "code": 200,
    "message": "seccess",
    "data": {
        "Semester1": {
            "WEEK1": [
                [
                    courseName1, courseName2
				],
				[
					courseName1, courseName3
				]
			],
            "WEEK2": [
                [
                    courseName1, courseName2
				],
				[
					courseName1, courseName3
				]
			]
		},
		"Semester2": {
            "WEEK1": [
                [
                    courseName1, courseName2
				],
				[
					courseName1, courseName3
				]
			],
            "WEEK2": [
                [
                    courseName1, courseName2
				],
				[
					courseName1, courseName3
				]
			]
		}
	}
}
```

## 最快修读方案生成

### 要求

前端给定 8 个学期的学分上限，根据每个学期的学分上限进行限制

不限于春秋学期的限制，生成最快的方案

### 实现思路

1. 接收前端的`credits`​
2. 构建AOE网络

    1. 同上，根据前置关系构建图
3. 拓扑排序

    1. 不再按照春秋学期分两个队列
4. 计算关键路径

    1. 计算课程的最早开始时间和最晚开始时间
    2. 找到关键路径上的课程
5. 分配学期

    1. **优先分配关键路径上的课程**

        1. 非关键路径上的课程可以灵活安排，但不能影响关键路径的进度
    2. 按照拓扑排序分配课程

        1. 不考虑时间冲突
    3. 保证每学期学分不超上限

## 自主扩展功能

时间限制选课：

可以在前端选择时间段，规划课程时会避开该时间段，但是如果设置了该时间段后导致不能正常修完课程，则会告知用户无法规划课程

### 实现思路

根据传入的数据设置`CourseTableVo`​，使课程无法落在该处

# 数据库部分

## 建表语句

```SQL
CREATE TABLE course
(
    id              INT PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    course_basic_id VARCHAR(20) NOT NULL COMMENT '课程基础序号',
    course_sp_id    VARCHAR(5)  NOT NULL COMMENT '课程班级序号',
    course_name     VARCHAR(20) NOT NULL COMMENT '课程名称',
    teacher         VARCHAR(20) NOT NULL COMMENT '教师',
    department      VARCHAR(20) NOT NULL COMMENT '开设院系',
    semester        VARCHAR(8)  NOT NULL COMMENT '学期',
    category        VARCHAR(15) NOT NULL COMMENT '课程类别',
    credit          DOUBLE      NOT NULL COMMENT '学分',
    beg_week        INT         NOT NULL COMMENT '开始周数',
    last_week       INT         NOT NULL COMMENT '持续周数',
    limits          INT         NOT NULL COMMENT '选课人数上限'
)
    COMMENT '课程';

CREATE TABLE course_period
(
    id              INT PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    course_basic_id VARCHAR(20) NOT NULL COMMENT '课程基础序号',
    course_sp_id    VARCHAR(5)  NOT NULL COMMENT '课程班级序号',
    day             VARCHAR(5)  NOT NULL COMMENT '上课日期',
    beg             INT         NOT NULL COMMENT '开始节数',
    last            INT         NOT NULL COMMENT '持续节数'
)
    COMMENT '课程时间';

CREATE TABLE prereq
(
    id              INT PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    course_basic_id VARCHAR(20) NOT NULL COMMENT '课程基础序号',
    prereq_id       VARCHAR(20) NOT NULL COMMENT '前置课程基础序号'
)
    COMMENT '前置课程';

CREATE TABLE succeed
(
    id                      INT PRIMARY KEY AUTO_INCREMENT COMMENT '编号',
    course_basic_id         VARCHAR(20) NOT NULL COMMENT '课程基础序号',
    succeed_course_basic_id VARCHAR(20) NOT NULL COMMENT '后继课程基础序号'
)
    COMMENT '后继课程';
```

## 数据插入

使用 Python 将.csv 文件中的数据插入数据库中，之后不再使用.csv 文件中的内容

```Python
import csv
import sqlite3
import mysql.connector

# 数据库连接信息
db_config = {
    'host': '127.0.0.1',
    'port': 3306,
    'user': 'root',
    'password': '123456',
    'database': 'intelligent-course-system'
}

# 定义 CSV 文件路径
courses_csv_file_path = "courses.csv"
course_period_csv_file_path = "course_period.csv"
prereq_csv_file_path = "prereq.csv"
succeed_csv_file_path = "succeed.csv"


# 连接 SQLite 数据库
def create_connection(db_config):
    try:
        # 连接数据库
        conn = mysql.connector.connect(**db_config)
        return conn

    except mysql.connector.Error as e:
        print("Error connecting to MySQL database:", e)


# 读取 CSV 文件并插入数据到数据库
def read_courses(conn, csv_file):
    try:
        cursor = conn.cursor(prepared=True)
        # 打开 CSV 文件
        with open(csv_file, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            headers = next(reader)  # 读取表头，跳过表头行
            print("CSV Headers:", headers)
            # 插入数据
            for row in reader:
                insert_sql = "INSERT INTO course (course_basic_id, course_sp_id, course_name, teacher, department, semester, category, credit, beg_week, last_week, limits) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
                cursor.execute(insert_sql, (
                    row[0], row[1], row[2], row[3], row[4], row[5], row[6], float(row[7]), int(row[8]),
                    int(row[9]), int(row[10])))
        # 提交事务
        conn.commit()
        print("Data inserted successfully")
    except sqlite3.Error as e:
        print(e)
    except Exception as ex:
        print(f"Error reading CSV file: {ex}")


def read_course_period(conn, csv_file):
    try:
        cursor = conn.cursor(prepared=True)
        # 打开 CSV 文件
        with open(csv_file, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            headers = next(reader)  # 读取表头，跳过表头行
            print("CSV Headers:", headers)
            # 插入数据
            for row in reader:
                insert_sql = "INSERT INTO course_period (course_basic_id, course_sp_id, day, beg, last) VALUES(?, ?, ?, ?, ?) "
                cursor.execute(insert_sql, (
                    row[0], row[1], row[2], int(row[3]), int(row[4])))
        # 提交事务
        conn.commit()
        print("Data inserted successfully")
    except sqlite3.Error as e:
        print(e)
    except Exception as ex:
        print(f"Error reading CSV file: {ex}")


def read_prereq(conn, csv_file):
    try:
        cursor = conn.cursor(prepared=True)
        # 打开 CSV 文件
        with open(csv_file, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            headers = next(reader)  # 读取表头，跳过表头行
            print("CSV Headers:", headers)
            # 插入数据
            for row in reader:
                insert_sql = "INSERT INTO prereq (course_basic_id, prereq_id) VALUES(?, ?) "
                cursor.execute(insert_sql, (row[0], row[1]))
        # 提交事务
        conn.commit()
        print("Data inserted successfully")
    except sqlite3.Error as e:
        print(e)
    except Exception as ex:
        print(f"Error reading CSV file: {ex}")


def read_succeed(conn, csv_file):
    try:
        cursor = conn.cursor(prepared=True)
        # 打开 CSV 文件
        with open(csv_file, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            headers = next(reader)  # 读取表头，跳过表头行
            print("CSV Headers:", headers)
            # 插入数据
            for row in reader:
                insert_sql = "INSERT INTO succeed (course_basic_id, succeed_course_basic_id) VALUES(?, ?) "
                cursor.execute(insert_sql, (row[0], row[1]))
        # 提交事务
        conn.commit()
        print("Data inserted successfully")
    except sqlite3.Error as e:
        print(e)
    except Exception as ex:
        print(f"Error reading CSV file: {ex}")


# 主函数
def main():
    # 创建数据库连接
    conn = create_connection(db_config)
    if conn is not None:
        # 插入数据
        read_courses(conn, courses_csv_file_path)
        read_course_period(conn, course_period_csv_file_path)
        read_prereq(conn, prereq_csv_file_path)
        read_succeed(conn, succeed_csv_file_path)
        # 关闭数据库连接
        conn.close()
    else:
        print("Error! Cannot connect to the database.")


if __name__ == "__main__":
    main()

```

# 前端部分

* 使用 VUE3 实现

详见[github.com/Zephyrtoria/Intelligent-Course-Selection-UI](https://github.com/Zephyrtoria/Intelligent-Course-Selection-UI)

‍
