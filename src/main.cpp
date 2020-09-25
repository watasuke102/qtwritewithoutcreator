#include <QtWidgets>

class widget_main : public QWidget
{
    public:
        widget_main(QWidget *parent = nullptr) : QWidget(parent)
        {
            QHBoxLayout *layout = new QHBoxLayout;
            layout->addWidget(new QLabel(tr("THIS IS CENTRAL WIDGET\nHELLO!!")));
            setLayout(layout);
        }
};

class widget_A : public QWidget
{
    private:
        int push_count = 0;
        QLabel      *label1;
        QPushButton *button;
    public slots:
        void onButtonClicked()
        {
            push_count++;
            label1->setText(tr("Widget A (button has pushed!)\ncount: ") + QString::number(push_count) );
        }

    public:
        widget_A(QWidget *parent = nullptr) : QWidget(parent)
{
            label1 = new QLabel(tr("Widget A (button has not pushed)"));
            button = new QPushButton(tr("Let's push"));
            QObject::connect(button, &QPushButton::clicked, this, &widget_A::onButtonClicked);

            QGridLayout *grid = new QGridLayout;
            grid->addWidget(label1, 0, 0);
            grid->addWidget(button, 1, 0);
            setLayout(grid);

            resize(300, 200);
            setWindowTitle(tr("Qt widget A"));
        }
};

class widget_B : public QWidget
{
    private:
        int push_count = 0;
        QLabel      *label1;
        QPushButton *button;
    public slots:
        void onButtonClicked()
        {
            push_count++;
            label1->setText(tr("Widget B (button has pushed!)\ncount: ") + QString::number(push_count) );
        }

    public:
        widget_B(QWidget *parent = nullptr) : QWidget(parent)
        {
            label1 = new QLabel(tr("Widget B (button has not pushed)"));
            button = new QPushButton(tr("Let's push"));
            QObject::connect(button, &QPushButton::clicked, this, &widget_B::onButtonClicked);

            QGridLayout *grid = new QGridLayout;
            grid->addWidget(label1, 0, 0);
            grid->addWidget(button, 1, 0);
            setLayout(grid);

            resize(300, 200);
            setWindowTitle(tr("Qt widget A"));
        }
};

class MainWindow : public QMainWindow
{

    public:
        MainWindow(QWidget *parent = nullptr)
        {
            QDockWidget *widgetA = new QDockWidget(tr("dock"));
            widgetA->setWidget(new widget_A);
            widgetA->resize(500, 200);
            widgetA->setWindowTitle(tr("Widget A"));
            addDockWidget(Qt::LeftDockWidgetArea,  widgetA);

            QDockWidget *widgetB = new QDockWidget(tr("dock"));
            widgetB->setWidget(new widget_B);
            widgetB->resize(300, 200);
            widgetB->setWindowTitle(tr("Widget B"));
            addDockWidget(Qt::RightDockWidgetArea, widgetB);

            setCentralWidget(new widget_main);

            resize(800, 200);
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