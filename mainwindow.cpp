#include "mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <fstream>
#include <unordered_map>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <iostream>
#include <QtCharts/QPercentBarSeries>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ustawienie głównego okna
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Układ pionowy dla głównego widżetu
    layout = new QVBoxLayout(centralWidget);

    // Etykieta informacyjna
    QLabel *infoLabel = new QLabel("Witaj w BioSeq Analyzer!", this);
    infoLabel->setAlignment(Qt::AlignCenter); // Wyśrodkowanie tekstu
    layout->addWidget(infoLabel);

    // Przycisk do wyboru pliku
    fileButton = new QPushButton("Wybierz plik", this);
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
    filePath = QFileDialog::getOpenFileName(this,
                                            "Wybierz plik",
                                            "",
                                            "Pliki tekstowe (*.txt)");
    // Tutaj możesz wykorzystać filePath do wczytania wybranego pliku
}

void MainWindow::startAnalysis()
{
    // Tutaj możesz umieścić kod rozpoczynający analizę
    // Na przykład możesz wywołać funkcje analizy sekwencji DNA

    // Przykładowy kod analizy sekwencji DNA
    std::ifstream file(filePath.toStdString()); // Otwieramy plik
    if (!file.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
        return;
    }

    std::unordered_map<char, int> charCounts; // Mapa do przechowywania liczebności znaków
    char c;
    while (file >> c) {
        if (c != '\n') // Pomijamy znaki nowej linii
            charCounts[c]++;
    }

    // Wyświetlanie wyników w interfejsie użytkownika
    QString resultText;
    for (const auto& pair : charCounts) {
        resultText += QString("%1: %2\n").arg(pair.first).arg(pair.second);
    }

    QBarSet *set0 = new QBarSet("A");
    QBarSet *set1 = new QBarSet("T");
    QBarSet *set2 = new QBarSet("G");
    QBarSet *set3 = new QBarSet("C");

    *set0 << charCounts['A'];
    *set1 << charCounts['T'];
    *set2 << charCounts['G'];
    *set3 << charCounts['C'];

    QPercentBarSeries *series = new QPercentBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("% of A,T,G,C");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "All of This";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Usuwamy istniejące elementy z układu, jeśli istnieją
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Dodajemy wykres i etykietę do układu
    layout->addWidget(chartView);
    QLabel* resultLabel = new QLabel(resultText, this);
    resultLabel->setWordWrap(true); // Właczamy zawijanie tekstu
    layout->addWidget(resultLabel);

    resize(900, 900);
}
