#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <fstream>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <iostream>
#include <QtCharts/QPercentBarSeries>
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
public slots:
    void chooseFile();    // Deklaracja funkcji wyboru pliku
    void startAnalysis(); // Deklaracja funkcji rozpoczęcia analizy
private:
    QPushButton *fileButton; // Przycisk do wyboru pliku
    QPushButton *analyzeButton;
    QVBoxLayout *layout;
    QString filePath;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
