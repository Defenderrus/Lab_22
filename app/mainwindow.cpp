#include "mainwindow.h"
#include "./ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::createArraySequence);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::createListSequence);

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::getSize);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::getFirst);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::getLast);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::getAt);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::getSubsequence);

    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::prepend);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::append);
    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::insertAt);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::remove);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::concatenate);

    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::showResult);
    connect(ui->pushButton_14, &QPushButton::clicked, this, &MainWindow::runTests);
}

MainWindow::~MainWindow() {
    delete ui;
    delete arrSeq;
    delete listSeq;
}

vector<string> MainWindow::splitString(const string& str) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, ' ')) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

void MainWindow::showMessage(const string& title, const string& message) {
    QMessageBox::information(this, QString::fromStdString(title), QString::fromStdString(message));
}

string MainWindow::getInput(const string& title, const string& label) {
    bool ok;
    QString text = QInputDialog::getText(this, QString::fromStdString(title), QString::fromStdString(label), QLineEdit::Normal, "", &ok);
    return ok ? text.toStdString() : "";
}

int MainWindow::getIntInput(const string& title, const string& label, int min, int max) {
    bool ok;
    int value = QInputDialog::getInt(this, QString::fromStdString(title), QString::fromStdString(label), 0, min, max, 1, &ok);
    return ok ? value : -1;
}

void MainWindow::createArraySequence() {
    string input = getInput("Создание ArraySequence", "Введите элементы через пробел:");
    if (!input.empty()) {
        vector<string> items = splitString(input);
        arrSeq = new ArraySequence<string>();
        mode = 1;
        for (const auto& item : items) {
            arrSeq->Append(item);
        }
        showMessage("Успех", "ArraySequence создан!");
    }
}

void MainWindow::createListSequence() {
    string input = getInput("Создание ListSequence", "Введите элементы через пробел:");
    if (!input.empty()) {
        vector<string> items = splitString(input);
        listSeq = new ListSequence<string>();
        mode = 2;
        for (const auto& item : items) {
            listSeq->Append(item);
        }
        showMessage("Успех", "ListSequence создан!");
    }
}

void MainWindow::getSize() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else if (mode == 1) {
        showMessage("Размер", "Размер: " + to_string(arrSeq->GetLength()));
    } else if (mode == 2) {
        showMessage("Размер", "Размер: " + to_string(listSeq->GetLength()));
    }
}

void MainWindow::getFirst() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        showMessage("Первый элемент", "Первый элемент: " + arrSeq->GetFirst());
    } else if (mode == 2) {
        showMessage("Первый элемент", "Первый элемент: " + listSeq->GetFirst());
    }
}

void MainWindow::getLast() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        showMessage("Последний элемент", "Последний элемент: " + arrSeq->GetLast());
    } else if (mode == 2) {
        showMessage("Последний элемент", "Последний элемент: " + listSeq->GetLast());
    }
}

void MainWindow::getAt() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        int index = getIntInput("Получить элемент", "Введите индекс:", 0, arrSeq->GetLength()-1);
        if (index >= 0) {
            showMessage("Элемент", "Элемент с индексом " + to_string(index) + ": " + arrSeq->Get(index));
        }
    } else if (mode == 2) {
        int index = getIntInput("Получить элемент", "Введите индекс:", 0, listSeq->GetLength()-1);
        if (index >= 0) {
            showMessage("Элемент", "Элемент с индексом " + to_string(index) + ": " + listSeq->Get(index));
        }
    }
}

void MainWindow::getSubsequence() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        int start = getIntInput("Подпоследовательность", "Введите начальный индекс:", 0, arrSeq->GetLength()-1);
        if (start >= 0) {
            int end = getIntInput("Подпоследовательность", "Введите конечный индекс:", start, arrSeq->GetLength()-1);
            if (end >= 0) {
                auto* arrSeqSub = arrSeq->GetSubsequence(start, end);
                string result;
                for (int i = 0; i < arrSeqSub->GetLength(); i++) {
                    result += arrSeqSub->Get(i) + " ";
                }
                delete arrSeqSub;
                showMessage("Подпоследовательность", "Результат:\n" + result);
            }
        }
    } else if (mode == 2) {
        int start = getIntInput("Подпоследовательность", "Введите начальный индекс:", 0, listSeq->GetLength()-1);
        if (start >= 0) {
            int end = getIntInput("Подпоследовательность", "Введите конечный индекс:", start, listSeq->GetLength()-1);
            if (end >= 0) {
                auto* listSeqSub = listSeq->GetSubsequence(start, end);
                string result;
                for (int i = 0; i < listSeqSub->GetLength(); i++) {
                    result += listSeqSub->Get(i) + " ";
                }
                delete listSeqSub;
                showMessage("Подпоследовательность", "Результат:\n" + result);
            }
        }
    }
}

void MainWindow::prepend() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else {
        string item = getInput("Добавить в начало", "Введите элемент:");
        if (!item.empty()) {
            if (mode == 1) {
                arrSeq->Prepend(item);
            } else if (mode == 2) {
                listSeq->Prepend(item);
            }
            showMessage("Успех", "Элемент добавлен в начало!");
        }
    }
}

void MainWindow::append() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else {
        string item = getInput("Добавить в конец", "Введите элемент:");
        if (!item.empty()) {
            if (mode == 1) {
                arrSeq->Append(item);
            } else if (mode == 2) {
                listSeq->Append(item);
            }
            showMessage("Успех", "Элемент добавлен в конец!");
        }
    }
}

void MainWindow::insertAt() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else if (mode == 1) {
        int index = getIntInput("Вставить элемент", "Введите индекс:", 0, arrSeq->GetLength()-1);
        if (index >= 0) {
            string item = getInput("Вставить элемент", "Введите элемент:");
            if (!item.empty()) {
                arrSeq->InsertAt(item, index);
            }
        }
    } else if (mode == 2) {
        int index = getIntInput("Вставить элемент", "Введите индекс:", 0, listSeq->GetLength()-1);
        if (index >= 0) {
            string item = getInput("Вставить элемент", "Введите элемент:");
            if (!item.empty()) {
                listSeq->InsertAt(item, index);
            }
        }
    }
}

void MainWindow::remove() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else if (mode == 1) {
        int index = getIntInput("Удалить элемент", "Введите индекс:", 0, arrSeq->GetLength()-1);
        if (index >= 0) {
            arrSeq->Remove(index);
            showMessage("Успех", "Элемент удалён из последовательности!");
        }
    } else if (mode == 2) {
        int index = getIntInput("Удалить элемент", "Введите индекс:", 0, listSeq->GetLength()-1);
        if (index >= 0) {
            listSeq->Remove(index);
            showMessage("Успех", "Элемент удалён из последовательности!");
        }
    }
}

void MainWindow::concatenate() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else {
        string input = getInput("Конкатенация", "Введите элементы второй последовательности через пробел:");
        if (!input.empty()) {
            vector<string> items = splitString(input);
            if (mode == 1) {
                ArraySequence<string>* arrSeq2 = new ArraySequence<string>();
                for (const auto& item : items) {
                    arrSeq2->Append(item);
                }
                arrSeq->Concat(arrSeq2);
                delete arrSeq2;
                showMessage("Успех", "Последовательности объединены!");
            } else if (mode == 2) {
                ListSequence<string>* listSeq2 = new ListSequence<string>();
                for (const auto& item : items) {
                    listSeq2->Append(item);
                }
                listSeq->Concat(listSeq2);
                delete listSeq2;
                showMessage("Успех", "Последовательности объединены!");
            }
        }
    }
}

void MainWindow::showResult() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else {
        string result;
        if (mode == 1) {
            for (int i = 0; i < arrSeq->GetLength(); i++) {
                result += arrSeq->Get(i) + " ";
            }
        } else if (mode == 2) {
            for (int i = 0; i < listSeq->GetLength(); i++) {
                result += listSeq->Get(i) + " ";
            }
        }
        showMessage("Результат", "Текущая последовательность:\n" + result);
    }
}

void MainWindow::runTests() {
    QString testProgram = "../../../main.exe";
    if (!QFile::exists(testProgram)) {
        QMessageBox::critical(this, "Ошибка", "Тестовая программа не найдена по пути:\n" +
                                  QDir::toNativeSeparators(QFileInfo(testProgram).absoluteFilePath()));
        return;
    }

    QProcess testProcess;
    testProcess.setProcessChannelMode(QProcess::MergedChannels);
    testProcess.start(testProgram);
    if (!testProcess.waitForFinished(30000)) {
        if (testProcess.state() == QProcess::Running) {
            testProcess.kill();
        }
        QMessageBox::critical(this, "Ошибка", "Тесты не завершились за отведенное время");
        return;
    }

    int exitCode = testProcess.exitCode();
    QString output = QString::fromLocal8Bit(testProcess.readAllStandardOutput());
    QDialog resultsDialog(this);
    resultsDialog.setWindowTitle("Результаты тестирования");
    resultsDialog.resize(800, 600);
    QVBoxLayout layout(&resultsDialog);
    QTextEdit textEdit;
    textEdit.setReadOnly(true);
    textEdit.setLineWrapMode(QTextEdit::NoWrap);
    textEdit.setFontFamily("Courier New");
    textEdit.setFontPointSize(10);

    QString htmlOutput;
    htmlOutput += "<style>pre {margin:0;}</style>";
    htmlOutput += "<h3>" + QDateTime::currentDateTime().toString() + "</h3>";
    htmlOutput += exitCode == 0 ? "<p style='color:green;'>✓ Тесты пройдены успешно</p>"
                                : "<p style='color:red;'>✗ Обнаружены ошибки (код: " + QString::number(exitCode) + ")</p>";
    htmlOutput += "<pre>" + output.toHtmlEscaped() + "</pre>";
    textEdit.setHtml(htmlOutput);
    layout.addWidget(&textEdit);

    QDialogButtonBox buttons(QDialogButtonBox::Close | QDialogButtonBox::Save);
    layout.addWidget(&buttons);
    connect(&buttons, &QDialogButtonBox::rejected, &resultsDialog, &QDialog::reject);
    connect(buttons.button(QDialogButtonBox::Save), &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getSaveFileName(&resultsDialog, "Сохранить результаты", "", "Текстовые файлы (*.txt)");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << "=== Результаты тестирования ===\n" << QDateTime::currentDateTime().toString() << "\n\n" << output;
                file.close();
                QMessageBox::information(&resultsDialog, "Сохранено", "Результаты сохранены в файл");
            } else {
                QMessageBox::warning(&resultsDialog, "Ошибка", "Не удалось сохранить файл");
            }
        }
    });

    resultsDialog.exec();
}
