#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QVector>
#include <QtCore/QtMath>

#ifdef Q_OS_ANDROID
const QString filename = "/data/user/qt/out.txt";
#else
const QString filename = "out.txt";
#endif

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("evensimplerapp");
    QCoreApplication::setApplicationVersion("0.9.453.276-alpha");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption maxNumOption(QStringList() << "l" << "limit",
            QCoreApplication::translate("main", "Stop counting primes at <number>. Number must be greater than zero."),
            QCoreApplication::translate("main", "number"));
    parser.addOption(maxNumOption);

    // Process the actual command line arguments given by the user
    parser.process(app);

    QString primeLimitString = parser.value(maxNumOption);
    quint32 primeLimit = 1000; // default
    if( primeLimitString.length() )
        primeLimit = primeLimitString.toInt();
    if (0 < primeLimit) {
        QFile file(filename);
        QTextStream* out;
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
            out = new QTextStream(&file);
        else
            out = new QTextStream(stdout, QIODevice::WriteOnly);
        *out << "Primes up to " << QString().number(primeLimit) << ":\n";
        *out << "1";
        if (primeLimit > 1)
            *out << " 2";
        QVector<quint32> primesSoFar;
        primesSoFar.append(3);
        if (primeLimit > 4) {
            quint32 currentNum = 5;
            while (currentNum <= primeLimit)
            {
                QVector<quint32>::const_iterator divider;
                bool isPrime = true;
                const quint32 maxValue = (quint32)qSqrt(currentNum);
                for (divider = primesSoFar.begin();
                     (*divider <= maxValue) && (divider != primesSoFar.end());
                     ++divider) {
                    if (0 == (currentNum % *divider)) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                    primesSoFar.append(currentNum);
                currentNum+=2;
            }
        }
        QVector<quint32>::const_iterator i;
        for (i = primesSoFar.begin(); i != primesSoFar.end(); ++i) {
            *out << " " << QString().number(*i);
        }
        *out << "\n";
        out->flush(); //flush before exit
        delete out;
    } else {
        parser.showHelp();
    }
    return 0;
}
