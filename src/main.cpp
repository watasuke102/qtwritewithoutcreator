#include <QApplication>
#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QWidget//QMainWindow
{
    private:
        int push_count = 0;
        QLabel      *label1;
        QPushButton *button;
    public slots:
        void onButtonClicked()
        {
            push_count++;
            label1->setText(tr("this is text (button has pushed!)\ncount: ") + QString::number(push_count) );
        }

    public:
        MainWindow(QWidget *parent = nullptr) : QWidget(parent)
        {
            label1 = new QLabel(tr("this is text (button has not pushed)"));
            button = new QPushButton(tr("Let's push"));
            QObject::connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

            QGridLayout *grid = new QGridLayout;
            grid->addWidget(label1, 0, 0);
            grid->addWidget(button, 0, 1);
            setLayout(grid);

            resize(400, 300);
            setWindowTitle(tr("Qt system window"));
        }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}