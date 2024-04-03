#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
