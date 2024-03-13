#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Get a list of all screens
    QList<QScreen*> screens = QGuiApplication::screens();

    // Check the number of screens
    if (screens.size() < 2) {
        qDebug() << "Requires at least two display devices";
        return -1;
    }

    // Get screen devices A and B
    QScreen *screenA = screens[1]; // Screen A, indexed from 0
    QScreen *screenB = screens[0]; // Screen B, indexed from 0

    // Create a window and set it to display on screen device A
    QWidget windowA;
    // Setting the position and size of the window on Screen A
    windowA.setGeometry(screenA->geometry()); 

    // Add a vertical layout
    QVBoxLayout *layout = new QVBoxLayout(&windowA);

    // Create a spin button
    QPushButton *rotateButton = new QPushButton("Rotating pictures");
    layout->addWidget(rotateButton);

    // Determine which screen the window appears on and process it
    if (windowA.geometry().intersects(screenA->geometry())) {
        windowA.showFullScreen(); // Set the window to full screen
        windowA.setAttribute(Qt::WA_AcceptTouchEvents); // Capture touch operations
    } else {
        qDebug() << "Window on screen device B";
    }

    // Load the image onto screen device B
    QPixmap image("/home/radxa/Pictures/pic2.jpg"); // Load picture
    QLabel label;
    label.setPixmap(image);
    label.setGeometry(screenB->geometry());
    label.show();

    // Connect the rotate button to the rotate image action
    QObject::connect(rotateButton, &QPushButton::clicked, [&label](){
        // Rotate the image
        QPixmap rotatedImage = label.pixmap()->transformed(QTransform().rotate(90));
        label.setPixmap(rotatedImage);
    });

    // Display window
    windowA.showFullScreen(); // Set the window to full screen

    return app.exec();
}
