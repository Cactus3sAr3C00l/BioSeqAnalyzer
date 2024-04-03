#include "mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ustawienie głównego okna
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Układ pionowy dla głównego widżetu
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Etykieta informacyjna
    QLabel *infoLabel = new QLabel("Witaj w BioSeq Analyzer!", this);
    infoLabel->setAlignment(Qt::AlignCenter); // Wyśrodkowanie tekstu
    layout->addWidget(infoLabel);

    // Przycisk do wyboru pliku
    fileButton = new QPushButton("Wybierz KURWA PLIK", this);
    layout->addWidget(fileButton);

    // Przycisk do uruchomienia analizy
    analyzeButton = new QPushButton("Wykonaj analizę", this);
    layout->addWidget(analyzeButton);

    // Ustawienie układu głównego w oknie
    centralWidget->setLayout(layout);

    // Połączenie przycisków z odpowiednimi funkcjami
    connect(fileButton, &QPushButton::clicked, this, &MainWindow::chooseFile);
    connect(analyzeButton, &QPushButton::clicked, this, &MainWindow::startAnalysis);

    // Ustawienie tytułu okna
    setWindowTitle("BioSeq Analyzer");
    // Ustawienie rozmiaru okna
    resize(400, 200);
}

MainWindow::~MainWindow() {}

void MainWindow::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Wybierz plik",
                                                    "",
                                                    "Pliki tekstowe (*.txt)");
    // Tutaj możesz wykorzystać filePath do wczytania wybranego pliku
}

void MainWindow::startAnalysis()
{
    // Tutaj możesz umieścić kod rozpoczynający analizę
    // Na przykład możesz wywołać funkcje analizy sekwencji DNA
}
