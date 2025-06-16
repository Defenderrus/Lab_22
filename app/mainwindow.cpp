#include "mainwindow.h"
#include "./ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setStyleSheet(
        "QMainWindow {"
        "   background: #f8fafc;"
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QGroupBox {"
        "   border: 1px solid #e2e8f0;"
        "   border-radius: 10px;"
        "   margin-top: 15px;"
        "   padding-top: 15px;"
        "   background: white;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 4px;"
        "   color: #3958af;"
        "   font-weight: 600;"
        "   font-size: 14px;"
        "}"
        "QPushButton {"
        "   background: white;"
        "   color: #3958af;"
        "   border: 1px solid #e2e8f0;"
        "   padding: 4px 8px;"
        "   border-radius: 6px;"
        "   font-weight: 500;"
        "   transition: all 0.2s ease;"
        "}"
        "QPushButton:hover {"
        "   background: #3958af;"
        "   color: white;"
        "   border-color: #3958af;"
        "}"
        "QLineEdit, QTextEdit, QComboBox, QSpinBox {"
        "   padding: 4px 6px;"
        "   border: 1px solid #e2e8f0;"
        "   border-radius: 6px;"
        "   background: white;"
        "   selection-background-color: #3958af;"
        "   selection-color: white;"
        "}"
        "QLineEdit:focus, QTextEdit:focus, QComboBox:focus {"
        "   border-color: #3958af;"
        "   outline: none;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "   width: 24px;"
        "}"
        "QScrollBar:vertical {"
        "   border: none;"
        "   background: #f1f5f9;"
        "   width: 10px;"
        "   margin: 0;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #cbd5e1;"
        "   min-height: 20px;"
        "   border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   border: none;"
        "   background: none;"
        "   height: 0;"
        "}"
        "QTabWidget::pane {"
        "   border: 1px solid #e2e8f0;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   margin-top: -1px;"
        "}"
        "QTabBar::tab {"
        "   padding: 8px 16px;"
        "   border: none;"
        "   color: #64748b;"
        "}"
        "QTabBar::tab:selected {"
        "   color: #3958af;"
        "   border-bottom: 2px solid #3958af;"
        "}"
        "QMessageBox, QInputDialog, QDialog {"
        "background: #f8fafc;"
        "font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QMessageBox QLabel {"
        "   color: #334155;"
        "}"
        );

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::createArraySequence);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::createListSequence);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::createImmutableArraySequence);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::createImmutableListSequence);

    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::getSize);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::getFirst);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::getLast);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::getAt);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::getSubsequence);

    connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::prepend);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::append);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::insertAt);
    connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::remove);
    connect(ui->pushButton_14, &QPushButton::clicked, this, &MainWindow::concatenate);

    connect(ui->pushButton_15, &QPushButton::clicked, this, &MainWindow::showResult);
    connect(ui->pushButton_16, &QPushButton::clicked, this, &MainWindow::runTests);
}

MainWindow::~MainWindow() {
    delete ui;
    delete arrSeq;
    delete listSeq;
    delete arrSeqIm;
    delete listSeqIm;
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
    string input = getInput("ArraySequence", "Введите элементы через пробел:");
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
    string input = getInput("ListSequence", "Введите элементы через пробел:");
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

void MainWindow::createImmutableArraySequence() {
    string input = getInput("ImmutableArraySequence", "Введите элементы через пробел:");
    if (!input.empty()) {
        vector<string> items = splitString(input);
        DynamicArray<string> array(items.size());
        mode = 3;
        for (int i = 0; i < items.size(); i++) {
            array.Set(i, items[i]);
        }
        arrSeqIm = new ImmutableArraySequence<string>(array);
        showMessage("Успех", "ImmutableArraySequence создан!");
    }
}

void MainWindow::createImmutableListSequence() {
    string input = getInput("ImmutableListSequence", "Введите элементы через пробел:");
    if (!input.empty()) {
        vector<string> items = splitString(input);
        LinkedList<string> list;
        mode = 4;
        for (const auto& item : items) {
            list.Append(item);
        }
        listSeqIm = new ImmutableListSequence<string>(list);
        showMessage("Успех", "ImmutableListSequence создан!");
    }
}

void MainWindow::getSize() {
    if (mode == 0) {
        showMessage("Ошибка", "Сначала создайте последовательность!");
    } else if (mode == 1) {
        showMessage("Размер", "Размер: " + to_string(arrSeq->GetLength()));
    } else if (mode == 2) {
        showMessage("Размер", "Размер: " + to_string(listSeq->GetLength()));
    } else if (mode == 3) {
        showMessage("Размер", "Размер: " + to_string(arrSeqIm->GetLength()));
    } else if (mode == 4) {
        showMessage("Размер", "Размер: " + to_string(listSeqIm->GetLength()));
    }
}

void MainWindow::getFirst() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        showMessage("Первый элемент", "Первый элемент: " + arrSeq->GetFirst());
    } else if (mode == 2) {
        showMessage("Первый элемент", "Первый элемент: " + listSeq->GetFirst());
    } else if (mode == 3) {
        showMessage("Первый элемент", "Первый элемент: " + arrSeqIm->GetFirst());
    } else if (mode == 4) {
        showMessage("Первый элемент", "Первый элемент: " + listSeqIm->GetFirst());
    }
}

void MainWindow::getLast() {
    if (mode == 0 || (mode == 1 && arrSeq->GetLength() == 0) || (mode == 2 && listSeq->GetLength() == 0)) {
        showMessage("Ошибка", "Последовательность пуста!");
    } else if (mode == 1) {
        showMessage("Последний элемент", "Последний элемент: " + arrSeq->GetLast());
    } else if (mode == 2) {
        showMessage("Последний элемент", "Последний элемент: " + listSeq->GetLast());
    } else if (mode == 3) {
        showMessage("Последний элемент", "Последний элемент: " + arrSeqIm->GetLast());
    } else if (mode == 4) {
        showMessage("Последний элемент", "Последний элемент: " + listSeqIm->GetLast());
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
    } else if (mode == 3) {
        int index = getIntInput("Получить элемент", "Введите индекс:", 0, arrSeqIm->GetLength()-1);
        if (index >= 0) {
            showMessage("Элемент", "Элемент с индексом " + to_string(index) + ": " + arrSeqIm->Get(index));
        }
    } else if (mode == 4) {
        int index = getIntInput("Получить элемент", "Введите индекс:", 0, listSeqIm->GetLength()-1);
        if (index >= 0) {
            showMessage("Элемент", "Элемент с индексом " + to_string(index) + ": " + listSeqIm->Get(index));
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
    } else if (mode == 3) {
        int start = getIntInput("Подпоследовательность", "Введите начальный индекс:", 0, arrSeqIm->GetLength()-1);
        if (start >= 0) {
            int end = getIntInput("Подпоследовательность", "Введите конечный индекс:", start, arrSeqIm->GetLength()-1);
            if (end >= 0) {
                auto* arrSeqSub = arrSeqIm->GetSubsequence(start, end);
                string result;
                for (int i = 0; i < arrSeqSub->GetLength(); i++) {
                    result += arrSeqSub->Get(i) + " ";
                }
                delete arrSeqSub;
                showMessage("Подпоследовательность", "Результат:\n" + result);
            }
        }
    } else if (mode == 4) {
        int start = getIntInput("Подпоследовательность", "Введите начальный индекс:", 0, listSeqIm->GetLength()-1);
        if (start >= 0) {
            int end = getIntInput("Подпоследовательность", "Введите конечный индекс:", start, listSeqIm->GetLength()-1);
            if (end >= 0) {
                auto* listSeqSub = listSeqIm->GetSubsequence(start, end);
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
            } else if (mode == 3) {
                arrSeqIm->Prepend(item);
            } else if (mode == 4) {
                listSeqIm->Prepend(item);
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
            } else if (mode == 3) {
                arrSeqIm->Append(item);
            } else if (mode == 4) {
                listSeqIm->Append(item);
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
    } else if (mode == 3) {
        int index = getIntInput("Вставить элемент", "Введите индекс:", 0, arrSeqIm->GetLength()-1);
        if (index >= 0) {
            string item = getInput("Вставить элемент", "Введите элемент:");
            if (!item.empty()) {
                arrSeqIm->InsertAt(item, index);
            }
        }
    } else if (mode == 4) {
        int index = getIntInput("Вставить элемент", "Введите индекс:", 0, listSeqIm->GetLength()-1);
        if (index >= 0) {
            string item = getInput("Вставить элемент", "Введите элемент:");
            if (!item.empty()) {
                listSeqIm->InsertAt(item, index);
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
    } else if (mode == 3) {
        int index = getIntInput("Удалить элемент", "Введите индекс:", 0, arrSeqIm->GetLength()-1);
        if (index >= 0) {
            arrSeqIm->Remove(index);
            showMessage("Успех", "Элемент удалён из последовательности!");
        }
    } else if (mode == 4) {
        int index = getIntInput("Удалить элемент", "Введите индекс:", 0, listSeqIm->GetLength()-1);
        if (index >= 0) {
            listSeqIm->Remove(index);
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
            } else if (mode == 3) {
                ArraySequence<string>* arrSeqIm2 = new ArraySequence<string>();
                for (const auto& item : items) {
                    arrSeqIm2->Append(item);
                }
                arrSeqIm->Concat(arrSeqIm2);
                delete arrSeqIm2;
                showMessage("Успех", "Последовательности объединены!");
            } else if (mode == 4) {
                ListSequence<string>* listSeqIm2 = new ListSequence<string>();
                for (const auto& item : items) {
                    listSeqIm2->Append(item);
                }
                listSeqIm->Concat(listSeqIm2);
                delete listSeqIm2;
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
        } else if (mode == 3) {
            for (int i = 0; i < arrSeqIm->GetLength(); i++) {
                result += arrSeqIm->Get(i) + " ";
            }
        } else if (mode == 4) {
            for (int i = 0; i < listSeqIm->GetLength(); i++) {
                result += listSeqIm->Get(i) + " ";
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
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PYTHONIOENCODING", "utf-8");
    env.insert("QT_LOGGING_TO_CONSOLE", "1");
    testProcess.setProcessEnvironment(env);
    testProcess.start(testProgram);
    if (!testProcess.waitForFinished(30000)) {
        if (testProcess.state() == QProcess::Running) {
            testProcess.kill();
        }
        QMessageBox::critical(this, "Ошибка", "Тесты не завершились за отведенное время");
        return;
    }

    QString output = QString::fromUtf8(testProcess.readAllStandardOutput());
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
    htmlOutput += "<style>pre {margin:0; font-family:'Courier New'; font-size:10pt;}</style>";
    htmlOutput += "<h3>" + QDateTime::currentDateTime().toString() + "</h3>";
    htmlOutput += "<pre>" + output.toHtmlEscaped().replace("\n", "<br>") + "</pre>";
    textEdit.setHtml(htmlOutput);
    layout.addWidget(&textEdit);

    resultsDialog.exec();
}
