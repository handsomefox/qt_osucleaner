#include "osucleaner.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList ui_languages = QLocale::system().uiLanguages();
    for (const QString& locale : ui_languages) {
        if (const QString base_name = "qt_osu_cleaner_" + QLocale(locale).name(); translator.load(":/i18n/" + base_name)) {
            a.installTranslator(&translator);
            break;
        }
    }
    osucleaner w;
    w.show();
    w.apply_dark_theme();
    return a.exec();
}
