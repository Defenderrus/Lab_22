#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include <sstream>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QTextEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include "../tests/test.hpp"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createArraySequence();
    void createListSequence();
    void createImmutableArraySequence();
    void createImmutableListSequence();

    void getSize();
    void getFirst();
    void getLast();
    void getAt();
    void getSubsequence();

    void prepend();
    void append();
    void insertAt();
    void remove();
    void concatenate();

    void showResult();
    void runTests();

private:
    Ui::MainWindow *ui;
    ArraySequence<string>* arrSeq = nullptr;
    ListSequence<string>* listSeq = nullptr;
    ImmutableArraySequence<string>* arrSeqIm = nullptr;
    ImmutableListSequence<string>* listSeqIm = nullptr;
    int mode = 0;

    vector<string> splitString(const string& str);
    void showMessage(const string& title, const string& message);
    string getInput(const string& title, const string& label);
    int getIntInput(const string& title, const string& label, int min, int max);
};
#endif // MAINWINDOW_H
