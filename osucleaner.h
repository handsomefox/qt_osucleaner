#pragma once

#include <QMainWindow>
#include <QStyleFactory>
#include <QApplication>
#include <filesystem>

QT_BEGIN_NAMESPACE
namespace Ui { class osucleaner; }
QT_END_NAMESPACE

class osucleaner final : public QMainWindow
{
    Q_OBJECT

public:
    osucleaner(QWidget* parent = nullptr);
    ~osucleaner() override;

    static void apply_dark_theme()
    {
        qApp->setStyle(QStyleFactory::create("Fusion"));

        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);

        qApp->setPalette(darkPalette);
        qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    }

private:
    Ui::osucleaner* ui;

    std::vector<std::filesystem::path> results{};

    const std::vector<std::string> video_filters
    {
        ".avi", ".flv", ".wmv", ".mp4", ".mpg",
        ".mov", ".mkv", ".m4v", ".3gp", ".webm", ".mpeg"
    };

    const std::vector<std::string> hitsound_filter
    {
        ".wav", ".ogg"
    };

    const std::vector<std::string> optional_filter
    {
        ".txt"
    };

    const std::vector<std::string> background_filter
    {
      ".png", ".jpg"
    };

    const std::vector<std::string> storyboard_filter
    {
      ".osb"
    };

    QString songs_path{};

private slots:
    void browse_pressed();
    void delete_pressed();
    void scan_pressed();
    void on_actionExit_triggered();
};
