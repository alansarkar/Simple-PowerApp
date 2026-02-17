#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QProcess>
#include <iostream>
#include <stdlib.h>

class PowerWindow : public QWidget
{
public:
    PowerWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Power Options");
        resize(300, 200);

        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *rebootButton = new QPushButton("Reboot");
        QPushButton *shutdownButton = new QPushButton("Shutdown");
        QPushButton *logoutButton = new QPushButton("Logout");

        layout->addWidget(rebootButton);
        layout->addWidget(shutdownButton);
        layout->addWidget(logoutButton);

        connect(rebootButton, &QPushButton::clicked, this, [](){
            if (QMessageBox::question(nullptr, "Confirm Reboot",
                "Are you sure you want to reboot?") == QMessageBox::Yes)
            {
//                QProcess::startDetached("systemctl reboot");
                  system("systemctl reboot");

            }
        });

        connect(shutdownButton, &QPushButton::clicked, this, [](){
            if (QMessageBox::question(nullptr, "Confirm Shutdown",
                "Are you sure you want to shutdown?") == QMessageBox::Yes)
            {
//                QProcess::startDetached("systemctl poweroff");
                  system("systemctl poweroff");
            }
        });

        connect(logoutButton, &QPushButton::clicked, this, [](){
            if (QMessageBox::question(nullptr, "Confirm Logout",
                "Are you sure you want to logout?") == QMessageBox::Yes)
            {
//                QProcess::startDetached("pkill -KILL -u $USER");
                  system("pkill -KILL -u $USER");
            }
        });
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PowerWindow window;
  QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
 

    // Calculate center position
    int x = (screenGeometry.width() - window.width()) / 2;
    int y = (screenGeometry.height() - window.height()) / 2;

    window.move(x, y);
    window.show();

    return app.exec();
}

