#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->txtBasicK->setValidator(new QIntValidator(1, 10000, this));
    ui->txtBasicM->setValidator(new QIntValidator(1, 10000, this));
    ui->txtBFSK->setValidator(new QIntValidator(1, 10000, this));
    ui->txtBFSM->setValidator(new QIntValidator(1, 10000, this));
    ui->txtS->setValidator(new QIntValidator(0, INT_MAX, this));
    ui->txtT->setValidator(new QIntValidator(0, INT_MAX, this));

    // Подключение сигналов
    connect(ui->createGraphButton, &QPushButton::clicked,
            this, &MainWindow::onCreateGraphButtonClicked);

    connect(ui->btnCreateBasic, &QPushButton::clicked,
            this, &MainWindow::onCreateBasicClicked);

    connect(ui->btnCreateBFS, &QPushButton::clicked,
            this, &MainWindow::onCreateBFSClicked);

    connect(ui->btnExact, &QPushButton::clicked, this, &MainWindow::onExactCalculateClicked);
    connect(ui->btnApproxBFS, &QPushButton::clicked, this, &MainWindow::onApproxBFSClicked);
    connect(ui->btnApproxBasic, &QPushButton::clicked, this, &MainWindow::onApproxBasicClicked);
}


void MainWindow::onExactCalculateClicked() {
    if(!currentGraph) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте граф!");
        return;
    }

    bool ok;
    uint32 s = ui->txtS->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина s!");
        return;
    }

    uint32 t = ui->txtT->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина t!");
        return;
    }

    try {
        bool internal = ui->chkInternalRepr->isChecked();
        uint64 result = currentGraph->findShortestPath(s, t, internal);
        showResult("Точный алгоритм", result);
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка: %1").arg(e.what()));
    }
}


void MainWindow::onApproxBFSClicked() {
    if(!landmarksBFS) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте Landmarks BFS!");
        return;
    }

    bool ok;
    uint32 s = ui->txtS->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина s!");
        return;
    }

    uint32 t = ui->txtT->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина t!");
        return;
    }

    bool internal = ui->chkInternalRepr->isChecked();
    uint64 result = landmarksBFS->computeApproximateDistance(
        *currentGraph, s, t, internal
        );
    showResult("Landmarks BFS", result);
}


void MainWindow::onApproxBasicClicked() {
    if(!landmarksBasic) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте Landmarks Basic!");
        return;
    }

    bool ok;
    uint32 s = ui->txtS->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина s!");
        return;
    }

    uint32 t = ui->txtT->text().toUInt(&ok);
    if(!ok) {
        QMessageBox::warning(this, "Ошибка", "Некорректная вершина t!");
        return;
    }

    bool internal = ui->chkInternalRepr->isChecked();
    uint64 result = landmarksBasic->computeApproximateDistance(
        *currentGraph, s, t, internal
        );
    showResult("Landmarks Basic", result);
}


void MainWindow::showResult(const QString& method, uint64 result) {
    QString msg = QString("[%1] %2 -> %3 = %4\n")
    .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(ui->txtS->text())
        .arg(ui->txtT->text())
        .arg(result);

    ui->txtResults->append(QString("%1Результат: %2").arg(method).arg(msg));
}


void MainWindow::onCreateGraphButtonClicked() {
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Выберите файл графа",
                                                    "",
                                                    "Graph Files (*.txt *.graph)"
                                                    );

    if (!filePath.isEmpty()) {
        try {
            currentGraph = new UndirectedGraph(filePath.toStdString());
            QMessageBox::information(this, "Успех", "Граф создан!");
            // Дополнительные действия с графом...
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Ошибка",
                                  QString("Ошибка создания графа: %1").arg(e.what()));
        }
    }
}


void MainWindow::onCreateBasicClicked() {
    if (!currentGraph) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте граф!");
        return;
    }

    try {
        QString method = ui->cmbBasicMethod->currentText();
        uint32 k = ui->txtBasicK->text().toUInt();
        uint32 M = ui->txtBasicM->text().isEmpty() ? 0 : ui->txtBasicM->text().toUInt();

        landmarksBasic = new LandmarksBasic(*currentGraph,
                                            method.toStdString(),
                                            k,
                                            M);
        QMessageBox::information(this, "Успех", "LandmarksBasic создан!");
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка",
                              QString("Ошибка: %1").arg(e.what()));
    }
}

void MainWindow::onCreateBFSClicked() {
    if (!currentGraph) {
        QMessageBox::warning(this, "Ошибка", "Сначала создайте граф!");
        return;
    }

    try {
        QString method = ui->cmbBFSMethod->currentText();
        uint32 k = ui->txtBFSK->text().toUInt();
        uint32 M = ui->txtBFSM->text().isEmpty() ? 0 : ui->txtBFSM->text().toUInt();

        landmarksBFS = new LandmarksBFS(*currentGraph,
                                        method.toStdString(),
                                        k,
                                        M);
        QMessageBox::information(this, "Успех", "LandmarksBFS создан!");
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка",
                              QString("Ошибка: %1").arg(e.what()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
