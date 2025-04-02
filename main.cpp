#include "mainwindow.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // 设置全局字体大小
    QFont font;
    font.setPointSize(16);  // 统一设置字体大小
    a.setFont(font);

    // 背景色设置
    w.setStyleSheet(
        "QWidget { background-color: rgba(173, 216, 230, 150); font-size: 15pt}"  // 窗口背景色--浅蓝
        "QTableWidget,QDoubleSpinBox ,QLineEdit {background-color: white; }"
        "QPushButton { background-color: #E3E7C0; border: 0.3pt solid red; padding: 0.5pt;}" // 按钮背景色
        );

    // 标题
    w.setWindowTitle("培养计划编制");

    // icon
    w.setWindowIcon(QIcon("../icon.icns"));
    w.show();
    return a.exec();
}
