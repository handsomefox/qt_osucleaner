#include "osucleaner.h"
#include "ui_osucleaner.h"
#include "directory_parser.h"

#include <QFileDialog>
#include <QList>
#include <QString>
#include <QStringListModel>
#include <QVector>

osucleaner::osucleaner(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::osucleaner)
{
	ui->setupUi(this);

	connect(ui->browseButton, SIGNAL(released()), this,
	        SLOT(browse_pressed()));

	connect(ui->deleteButton, SIGNAL(released()), this,
            SLOT(delete_pressed()));

	connect(ui->scanButton, SIGNAL(released()), this,
            SLOT(scan_pressed()));

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
}

osucleaner::~osucleaner()
{
	delete ui;
}

void osucleaner::browse_pressed()
{
	songs_path = QFileDialog::getExistingDirectory(this, tr("Open osu! songs folder"), "C:/",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	ui->pathLineEdit->setText(songs_path);
}

void osucleaner::delete_pressed()
{
    directory_parser::delete_scanned_files(results);

    QVector<QString> list;
    list.reserve(results.size());

    for(const auto& res : results){
        list.push_back(QString::fromStdWString(res.wstring()));
    }


    ui->foundFilesLabel->setText("Found files: " + QString::number(0));
    ui->foundFilesSizeLabel->setText("Found files size: " + QString::number(0) + "MB");
    ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(list)));
}

void osucleaner::scan_pressed()
{
    ui->progressBar->setValue(0);
    auto path = songs_path.toStdString();


   directory_parser dir_parser(path);

   if(ui->videoCheckbox->isChecked()) dir_parser.add_filters(video_filters);
   if(ui->hitsoundCheckbox->isChecked()) dir_parser.add_filters(hitsound_filter);
   if(ui->optionalCheckbox->isChecked()) dir_parser.add_filters(optional_filter);
   if(ui->backgroundCheckbox->isChecked()) dir_parser.add_filters(background_filter);
   if(ui->storyboardCheckbox->isChecked()) dir_parser.add_filters(storyboard_filter);

   dir_parser.scan_folder();


   results = dir_parser.scan_results();

   QVector<QString> list;
   list.reserve(results.size());

   for(const auto& res : results){
       list.push_back(QString::fromStdWString(res.wstring()));
   }


   ui->foundFilesLabel->setText("Found files: " + QString::number(results.size()));
   ui->foundFilesSizeLabel->setText("Found files size: " + QString::number(dir_parser.get_files_size()) + "MB");

   ui->listView->setModel(new QStringListModel(QList<QString>::fromVector(list)));
   ui->progressBar->setValue(100);

}


void osucleaner::on_actionExit_triggered()
{
    qApp->exit();
}

