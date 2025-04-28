#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "avgassign.h"
#include "Course.h"
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    preassignedIDs = {"C09", "C10", "C11", "C12", "C24", "C25", "C26", "C27", "C28", "C94", "C95"};

    ui->gridLayout_5->setColumnStretch(0, 2);
    ui->gridLayout_5->setColumnStretch(1, 1);

    // confirmButton在点击editCourse之前不可点击
    ui->confirmButton->setEnabled(false);

    // 设置结果表格不可编辑
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 向coursesTable中添加表头
    ui->coursesTable->setColumnCount(6);
    ui->coursesTable->setHorizontalHeaderLabels(QStringList() << "课程id" << "课程名称" << "学分" << "总学时" << "课程类别" << "前置课程");

    // 使表头拉伸
    ui->coursesTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    // 设置学分修读默认值
    ui->needCredit1->setValue(70);
    ui->needCredit2->setValue(45);
    ui->needCredit3->setValue(23);
    ui->needCredit4->setValue(28);
    ui->needCredit5->setValue(4);

    // 显示学分设为只读
    ui->credit1->setReadOnly(true);
    ui->credit2->setReadOnly(true);
    ui->credit3->setReadOnly(true);
    ui->credit4->setReadOnly(true);
    ui->credit5->setReadOnly(true);

    // 表格大小自适应内容
    ui->coursesTable->resizeColumnsToContents();
    ui->coursesTable->resizeRowsToContents();
    ui->coursesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->coursesTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->resultTable->resizeColumnsToContents();
    ui->resultTable->resizeRowsToContents();
    ui->resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->resultTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // 设置表格颜色交替显示
    ui->coursesTable->setAlternatingRowColors(true);
    ui->resultTable->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 在coursesTable末尾添加行
void MainWindow::appendOneRow(QString CID, QString Cname, double credit, int hours, int category, QString prereq)
{
    int count = ui->coursesTable->rowCount();
    ui->coursesTable->setRowCount(count + 1);
    QString category_str = "";
    switch (category) {
    case 1: category_str = "公共基础课"; break;
    case 2: category_str = "专业基础课"; break;
    case 3: category_str = "专业选修课"; break;
    case 4: category_str = "实践必修课"; break;
    case 5: category_str = "实践选修课"; break;
    default:
        break;
    }

    QTableWidgetItem *idItem = new QTableWidgetItem(CID);
    QTableWidgetItem *nameItem = new QTableWidgetItem(Cname);
    QTableWidgetItem *creditItem = new QTableWidgetItem(QString::number(credit, 'f', 1));
    QTableWidgetItem *hoursItem = new QTableWidgetItem(QString::number(hours));
    QTableWidgetItem *categoryItem = new QTableWidgetItem(category_str);
    QTableWidgetItem *prereqItem = new QTableWidgetItem(prereq);

    ui->coursesTable->setItem(count, 0, idItem);
    ui->coursesTable->setItem(count, 1, nameItem);
    ui->coursesTable->setItem(count, 2, creditItem);
    ui->coursesTable->setItem(count, 3, hoursItem);
    ui->coursesTable->setItem(count, 4, categoryItem);
    ui->coursesTable->setItem(count, 5, prereqItem);

    //  单元格文字居中
    for(int i = 0; i < 5; i++){
        if(i == 1) continue;
        QTableWidgetItem* item = ui->coursesTable->item(count, i);
        item->setTextAlignment(Qt::AlignCenter);
    }
}

// 读取txt文件并显示在表格上
void MainWindow::loadtxtIntoTable(const QString& filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "课程文件路径：" << filename;
        QMessageBox::warning(nullptr, "错误", "无法打开课程文件");
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QTextStream ss(&line);

        QString CID, Cname, prereq, prereqList;
        double credit;
        int hours, category;

        ss >> CID >> Cname >> credit >> hours >> category;
        if(!(CID.startsWith('C'))) continue;

        // 可能有前置课程
        while(!ss.atEnd())
        {
            ss >> prereq;
            prereqList += prereq + "  ";
        }
        courseIDs.insert(CID);

        appendOneRow(CID, Cname, credit, hours, category, prereqList);

        // 设置只读（如果是预分配课程）
        if (preassignedIDs.contains(CID)) {
            for (int col = 0; col < ui->coursesTable->columnCount(); ++col) {
                QTableWidgetItem* item = ui->coursesTable->item(ui->coursesTable->rowCount() - 1, col);
                if (item)
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
}

// 将结果txt输出在表格上
void MainWindow::loadResultTxtIntoTable(const QString& filename)
{
    ui->resultTable->clearContents(); // 清空表格内容，刷新表格

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "错误", "无法打开输出文件");
        return;
    }

    QTextStream in(&file);

    // 读取前5行：5类课程总学分
    QStringList totalCredits;
    for (int i = 0; i < 5; i++) {
        if (!in.atEnd()) {
            totalCredits.append(in.readLine().trimmed());
        }
    }

    // 变量初始化
    int numSemesters = 8; // 8 个学期
    QVector<QString> semesterNames;
    QVector<QString> semesterCredits;
    QVector<QString> semesterHours;
    QVector<QStringList> typeCredits;
    QVector<QVector<QString>> courses(numSemesters); // 每个学期一个 课程list

    int semesterIndex = -1;
    semesterNames.append("");  // 第一列表头

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // 检测到新学期
        if (line.startsWith("Semester")) {
            semesterIndex++;
            semesterNames.append(line.split(":").first().trimmed()); // 添加学期名
            semesterCredits.append("");
            semesterHours.append("");
            typeCredits.append(QStringList());
            continue;
        }

        // 解析学分、学时
        if (semesterIndex >= 0 && semesterCredits[semesterIndex].isEmpty()) {
            semesterCredits[semesterIndex] = line;
            continue;
        }
        if (semesterIndex >= 0 && semesterHours[semesterIndex].isEmpty()) {
            semesterHours[semesterIndex] = line;
            continue;
        }

        // 解析 5 类课程学分
        if (semesterIndex >= 0 && typeCredits[semesterIndex].size() < 5) {
            typeCredits[semesterIndex].append(line);
            continue;
        }

        // 解析课程
        if (semesterIndex >= 0) {
            courses[semesterIndex].append(line);
        }
    }

    file.close();

    // 计算最大课程数量，确定表格行数，动态设置
    int baseRows = 7; // 学分、学时和5类课程修读学分信息共占 7 行
    int maxCourses = 0;
    for (const auto& courseList : courses) {
        maxCourses = qMax(maxCourses, courseList.size());
    }
    int totalRows = baseRows + maxCourses;

    // 确保列数 = 学期数 + 1
    int columnCount = semesterNames.size();
    ui->resultTable->setRowCount(totalRows);
    ui->resultTable->setColumnCount(columnCount);
    ui->resultTable->setHorizontalHeaderLabels(semesterNames);

    for (int i = 0; i < maxCourses; i++) {
        ui->resultTable->setItem(baseRows + i , 0, new QTableWidgetItem("课程" + QString::number(i)));
    }

    // 设置垂直表头
    ui->resultTable->verticalHeader()->setVisible(false);
    QStringList headers = { "修读学分", "修读学时", "公共基础课学分", "专业基础课学分", "专业选修课学分", "实践必修课学分", "实践选修课学分" };

    // 填充左侧表头
    for (int i = 0; i < headers.size(); i++) {
        QTableWidgetItem* item = new QTableWidgetItem(headers[i]);
        ui->resultTable->setItem(i, 0, item);
    }

    // 填充学分、学时、5类课程学分
    for (int i = 0; i < semesterCredits.size(); i++) {
        ui->resultTable->setItem(0, i + 1, new QTableWidgetItem(semesterCredits[i]));
        ui->resultTable->setItem(1, i + 1, new QTableWidgetItem(semesterHours[i]));
        ui->resultTable->item(0, i + 1)->setTextAlignment(Qt::AlignCenter);
        ui->resultTable->item(1, i + 1)->setTextAlignment(Qt::AlignCenter);

        for (int j = 0; j < 5; j++) {
            if (j < typeCredits[i].size()) {
                ui->resultTable->setItem(j + 2, i + 1, new QTableWidgetItem(typeCredits[i][j]));
                ui->resultTable->item(j + 2, i + 1)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

    // 填充课程
    for (int i = 0; i < courses.size(); i++) {
        for (int j = 0; j < courses[i].size(); j++) {
            QString rawCourse = courses[i][j];
            QRegularExpression regex(R"(\(([^)]+)\)(\d)(.*))");  // 提取 (ID)type name 格式
            QRegularExpressionMatch match = regex.match(rawCourse);

            QString displayText = rawCourse;
            int type = 0;

            if (match.hasMatch()) {
                QString id = match.captured(1);       // 课程ID
                type = match.captured(2).toInt();     // 课程类型
                QString name = match.captured(3);     // 课程名称
                displayText = "(" + id + ")" + name;  // 去掉类型数字
            }

            QTableWidgetItem* item = new QTableWidgetItem(displayText);

            // 设置背景色根据类型
            switch (type) {
            case 1: item->setBackground(QBrush(QColor(250, 128, 114))); break;
            case 2: item->setBackground(QBrush(QColor(255, 246, 143))); break;
            case 3: item->setBackground(QBrush(QColor(151, 255, 255))); break;
            case 4: item->setBackground(QBrush(QColor(154, 255, 154))); break;
            case 5: item->setBackground(QBrush(QColor(255, 255, 255))); break;
            default: break;
            }

            item->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->setItem(baseRows + j, i + 1, item);
        }
    }

    // 更新 UI（插入总学分..）
    if (totalCredits.size() >= 5) {
        ui->credit1->setText(totalCredits[0]);
        ui->credit2->setText(totalCredits[1]);
        ui->credit3->setText(totalCredits[2]);
        ui->credit4->setText(totalCredits[3]);
        ui->credit5->setText(totalCredits[4]);
    }
}

void MainWindow::getTrainingPlan()
{
    loadCourses(getFilename(), static_cast<QWidget*>(this));
    vector<string> top_courses = TopologicalSort(static_cast<QWidget*>(this));

    // 获取5类课程需求学分
    vector<double>creditDemand(5, 0);
    creditDemand[0] = stod(ui->needCredit1->text().toStdString());
    creditDemand[1] = stod(ui->needCredit2->text().toStdString());
    creditDemand[2] = stod(ui->needCredit3->text().toStdString());
    creditDemand[3] = stod(ui->needCredit4->text().toStdString());
    creditDemand[4] = stod(ui->needCredit5->text().toStdString());
    assignCourses(top_courses, creditDemand, this->filepath);
    loadResultTxtIntoTable(getFilepath());
}

string join(const vector<string>& vec, const string& delimiter) // 将vector<string>转为用delimiter分隔的string
{
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) result += delimiter;
        result += vec[i];
    }
    return result;
}

// 在course.txt中更新课程记录
void MainWindow::updateCourseInFile(const vector<Course>& updatedCourses)
{
    // 打开courses.txt并更新课程记录
    QFile file(getFilename());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "错误", "无法打开文件");
        return;
    }

    QTextStream in(&file);
    QVector<QString> fileLines;
    while(!in.atEnd()) // 读取文件所有行，并存储到fileLines中
    {
        fileLines.append(in.readLine());
    }
    file.close();
    QMap<QString, QString> courseMap;
    for (auto& course : updatedCourses) {
        if(course.id.empty()) continue;
        courseMap[QString::fromStdString(course.id)] = QString("%1    %2    %3    %4    %5    %6")
        .arg(QString::fromStdString(course.id))
            .arg(QString::fromStdString(course.name))
            .arg(course.credit)
            .arg(course.hours)
            .arg(course.type)
            .arg(QString::fromStdString(join(course.prerequisites, " ")));
    }

    // update fileLines
    for (int i = 0; i < fileLines.size(); i++) {
        // 按照多个空格或者tab分隔
        QStringList fields = fileLines[i].split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (fields.size() > 0 && courseMap.contains(fields[0])) {
            fileLines[i] = courseMap[fields[0]];
        }
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "错误", "无法打开 courses.txt 进行写入！");
        return;
    }

    QTextStream out(&file);
    for (const QString &line : fileLines) {
        out << line << "\n";
    }

    file.close();
    QMessageBox::information(this, "成功", "课程信息已更新！");
    ui->confirmButton->setEnabled(false);
}

QString MainWindow::getFilename()
{
    return filename;
}

QString MainWindow::getFilepath()
{
    return filepath;
}

void MainWindow::setFilename(const QString& filename) {this->filename = filename;}
void MainWindow::setFilepath(const QString& filepath) {this->filepath = filepath;}


// 判断cid是否出现过
bool MainWindow::isCIDexists(QString cid)
{
    return courseIDs.contains(cid);
}

void MainWindow::on_getTrainingPlan_clicked()
{
    getTrainingPlan();
}

// 查找按钮，对被查找到的课程高亮并传送到具体位置
void MainWindow::on_searchCourse_clicked()
{
    QString keyword = ui->keyword->text();
    if(keyword.isEmpty())
    {
        QMessageBox::information(nullptr, "提示", "请输入关键词");
        return;
    }

    ui->coursesTable->clearSelection(); // 清除之前的选中状态

    bool found = false;
    int row = ui->coursesTable->rowCount();
    int col = ui->coursesTable->columnCount();

    // 清除原先选中的单元格背景色
    for(int i=0;i<row;i++)
    {
        for(int j = 0;j<col;j++)
        {
            QTableWidgetItem* item = ui->coursesTable->item(i, j);
            if(item)
                item->setBackground(Qt::NoBrush);
        }
    }

    // 有keyword后，遍历coursesTable匹配字符串
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            QTableWidgetItem* item = ui->coursesTable->item(i, j);
            // 当item非空 并且其中文字包含关键词
            if(item && item->text().contains(keyword))
            {
                for(int k = 0; k < col; ++k)
                {
                    ui->coursesTable->item(i, k)->setBackground(Qt::yellow);
                }
                item->setSelected(true);
                ui->coursesTable->scrollToItem(item, QAbstractItemView::PositionAtCenter);
                found = true;
            }
        }
    }
    if (!found) {
        QMessageBox::information(this, "提示", "未找到匹配的课程");
    }
}

// 添加课程，只能在后面添加
void MainWindow::on_addCourse_clicked()
{
    QString CID = QInputDialog::getText(this, "添加课程", "课程id（格式\"Cxxx\"）");
    if(isCIDexists(CID))
    {
        QMessageBox::warning(this, "错误", "课程id不能重复！");
        return;
    }
    if(!CID.startsWith('C'))
    {
        QMessageBox::warning(this, "错误", "课程id格式错误！");
        return;
    }
    QString Cname = QInputDialog::getText(this, "添加课程", "课程名称");
    double credit = QInputDialog::getDouble(this, "添加课程", "学分");
    int hours = QInputDialog::getInt(this, "添加课程", "总学时");
    int category = QInputDialog::getInt(this, "添加课程", "课程类型（1:公共基础课 2:专业基础课 3:专业选修课 4: 实践必修课 5: 实践选修课");
    QString prereq = QInputDialog::getText(this, "添加课程", "前置课程（空格分隔）");

    appendOneRow(CID, Cname, credit, hours, category, prereq);

    QFile file(getFilename());
    if(file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream os(&file);
        os << CID << " " << Cname << " " << credit << " " << hours << " " << category << " " << prereq << '\n';
        file.close();
    }
    QMessageBox::information(this, "成功", "课程已添加！");
}

// 修改课程属性，允许一次性修改多行记录
void MainWindow::on_editCourse_clicked()
{
    // 点击了编辑按钮后方可编辑
    ui->coursesTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    // 同时confirmButton启用
    ui->confirmButton->setEnabled(true);
    // 让 "课程 ID" 列不可编辑
    for (int row = 0; row < ui->coursesTable->rowCount(); row++)
    {
        QTableWidgetItem* item = ui->coursesTable->item(row, 0); // 获取第 0 列（课程 ID）
        if (item) item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }
}

// 确认修改后调用updateCourseInFile对txt进行更新
void MainWindow::on_confirmButton_clicked()
{
    vector<Course> updatedCourses;
    QMap<QString, int> courseTypeMap;
    courseTypeMap["公共基础课"] = 1;
    courseTypeMap["专业基础课"] = 2;
    courseTypeMap["专业选修课"] = 3;
    courseTypeMap["实践必修课"] = 4;
    courseTypeMap["实践选修课"] = 5;

    for(int row = 0; row < ui->coursesTable->rowCount(); row++)
    {
        QString CID = ui->coursesTable->item(row, 0)->text();
        // 获取修改后的值
        QString Cname = ui->coursesTable->item(row, 1)->text();

        double credit = ui->coursesTable->item(row, 2)->text().toDouble();
        int hours = ui->coursesTable->item(row, 3)->text().toInt();
        QString category = ui->coursesTable->item(row, 4)->text();
        int type = 0;
        if(courseTypeMap.contains(category))
        {
            type = courseTypeMap[category];
        } else {
            QMessageBox::warning(this, "错误", "输入课程类型错误，修改失败！");
            return;
        }

        QStringList prereqlist = ui->coursesTable->item(row, 5)->text().split(' ');

        Course course;
        course.id = CID.toStdString();
        course.name = Cname.toStdString();
        course.credit = credit;
        course.hours = hours;
        course.type = type;
        for(const auto&pre : prereqlist)
        {
            course.prerequisites.push_back(pre.toStdString());
        }
        updatedCourses.push_back(course);
    }

    updateCourseInFile(updatedCourses);
    ui->coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// 删除课程
void MainWindow::on_deleteCourse_clicked()
{
    int row = ui->coursesTable->currentRow();
    if (row == -1)
    {
        QMessageBox::warning(this, "错误", "请先选择一行");
        return;
    }

    // 获取课程ID
    QString courseId = ui->coursesTable->item(row, 0)->text();
    courseIDs.remove(courseId);

    // 判断要删除的课程是否为预分配课程
    if (preassignedIDs.contains(courseId)) {
        QMessageBox::information(this, "提示", "该课程为固定课程，无法删除。");
        return;
    }

    // 确认是否删除
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确定要删除该课程吗？",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No)
        return;

    // 从表格中删除该行
    ui->coursesTable->removeRow(row);

    // 更新 txt 文件
    updateCourseFile(courseId);
}

// 删除后对txt更新
void MainWindow::updateCourseFile(const QString &courseId)
{
    QFile file(getFilename());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "错误", "无法打开文件进行读取");
        return;
    }

    // 读取所有行
    QList<QString> lines;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (!line.startsWith(courseId)) // 确保匹配完整 ID
        {
            lines.append(line);  // 仅保留未删除的行
        }
    }
    file.close();

    // 重新写入文件
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QMessageBox::critical(this, "错误", "无法打开文件进行写入");
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < lines.size(); ++i)
    {
        out << lines[i] << '\n';
    }
    file.close();
    QMessageBox::information(this, "成功", "删除课程成功");
}


void MainWindow::on_showCourses_clicked()
{
    loadtxtIntoTable(getFilename());
}

