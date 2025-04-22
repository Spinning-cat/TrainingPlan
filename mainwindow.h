#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QStyledItemDelegate>
#include <QTextStream>
#include <QInputDialog>
#include <QVBoxLayout>
#include "Course.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createTable();
    QString filename;
    QString filepath;
    QSet<QString> courseIDs;
    QSet<QString> preassignedIDs;  // 预设课程 ID

public:
    void appendOneRow(QString CID, QString Cname, double credit, int hours, int category, QString prereq);
    void loadtxtIntoTable(const QString& filename);
    void loadResultTxtIntoTable(const QString&filename);
    void getTrainingPlan();
    void updateCourseInFile(const vector<Course>& updatedCourses);
    void updateCourseFile(const QString &courseId);
    QString getFilename();
    QString getFilepath();
    void setFilename(const QString& filename);
    void setFilepath(const QString& filepath);
    bool isCIDexists(QString cid);
private slots:
    void on_getTrainingPlan_clicked();
    void on_searchCourse_clicked();
    void on_addCourse_clicked();
    void on_editCourse_clicked();
    void on_confirmButton_clicked();
    void on_deleteCourse_clicked();
    void on_showCourses_clicked();
};
#endif // MAINWINDOW_H
