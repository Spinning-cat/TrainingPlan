#include "mainwindow.h"

#include <QApplication>
#include <QFont>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建路径输入对话框
    QDialog dialog;
    dialog.setFixedSize(600, 300);  // 设置弹窗宽度为600，高度为300
    QFont dialogFont;
    dialogFont.setPointSize(18);  // 设置字号为16

    dialog.setWindowTitle("请输入文件路径");
    QVBoxLayout *layout = new QVBoxLayout;
    // 输入路径控件
    QLabel *labelInput = new QLabel("课程文件路径");
    QLineEdit *editInput = new QLineEdit;
    QLabel *labelOutput = new QLabel("输出文件路径");
    QLineEdit *editOutput = new QLineEdit;

    // 设置默认路径（可改）
    editInput->setText("/Users/cynthia/TrainingPlan/courses.txt");
    editOutput->setText("/Users/cynthia/TrainingPlan/semesterCourses.txt");

    // 确认按钮
    QPushButton *btnOk = new QPushButton("确定");
    QObject::connect(btnOk, &QPushButton::clicked, [&dialog]() {
        dialog.accept();
    });

    // 添加控件
    layout->addWidget(labelInput);
    layout->addWidget(editInput);
    layout->addWidget(labelOutput);
    layout->addWidget(editOutput);
    layout->addWidget(btnOk);

    dialog.setLayout(layout);

    // 美观
    editInput->setFont(dialogFont);
    editOutput->setFont(dialogFont);
    labelInput->setFont(dialogFont);
    labelOutput->setFont(dialogFont);
    btnOk->setFont(dialogFont);

    // 设置行编辑框高度（大一些）
    editInput->setFixedHeight(40);   // 输入框高度设为40
    editOutput->setFixedHeight(40);

    // 用户点击“确定”才进入主窗口
    if (dialog.exec() != QDialog::Accepted) {
        return 0;
    }

    // 获取路径
    QString inputPath = editInput->text();
    QString outputPath = editOutput->text();

    MainWindow w;

    // 给两个路径属性赋值
    w.setInputPath(inputPath);
    w.setOutputPath(outputPath);

    // 设置全局字体大小
    QFont font;
    font.setPointSize(16);  // 统一设置字体大小
    a.setFont(font);

    // 设置全局字体颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);  // 设置字体颜色为黑色
    a.setPalette(palette);

    // 背景色设置
    w.setStyleSheet(
        "QWidget { background-color: rgba(173, 216, 230, 150); font-size: 15pt; color: black;}"  // 窗口背景色--浅蓝
        "QTableWidget,QDoubleSpinBox ,QLineEdit {background-color: white; gridline-color: white; color: black;}"
        "QPushButton { background-color: #E3E7C0; border: 0.3pt solid red; padding: 0.5pt; color: black;}" // 按钮背景色
        );

    // 标题
    w.setWindowTitle("培养计划编制");

    // icon
    w.setWindowIcon(QIcon("../icon.icns"));
    w.show();
    return a.exec();
}
