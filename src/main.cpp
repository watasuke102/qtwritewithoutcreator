#include <QtWidgets>
#include <GL/glu.h>
#include <GL/gl.h>

class OGLWidget : public QOpenGLWidget
{
public:
    OGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent)
    {
    }

protected:
    void initializeGL()
    {
        glClearColor(0,0,0,1);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glColor4f(0, 128, 0, 0);
        glBegin(GL_POLYGON);
            glVertex3d(-2.0, -2.0, 0.0);
            glVertex3d( 2.0, -2.0, 0.0);
            glVertex3d( 2.0,  2.0, 0.0);
        glEnd();
    }

    void resizeGL(int w, int h)
    {
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, (float)w/h, 0.01, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,5,0,0,0,0,1,0);
    }
};


class widget_main : public QWidget
{
    public:
        widget_main(QWidget *parent = nullptr) : QWidget(parent)
        {
            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(new OGLWidget);
            layout->addWidget(new QScrollBar(Qt::Horizontal));
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
            widgetA->setWindowTitle(tr("Widget A"));
            addDockWidget(Qt::LeftDockWidgetArea, widgetA);

            QDockWidget *widgetB = new QDockWidget(tr("dock"));
            widgetB->setWidget(new widget_B);
            widgetB->setWindowTitle(tr("Widget B"));
            addDockWidget(Qt::BottomDockWidgetArea, widgetB);
            resizeDocks({widgetB}, {250}, Qt::Vertical);

            setCentralWidget(new widget_main);
            resize(1200, 675);
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