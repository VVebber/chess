#include "ChessJsonList.h"
#include "../../../../../core/ChessInfoJson.h"

#include <QDir>
#include <QLabel>
#include <QLayout>
#include <QScrollArea>
#include <QPushButton>

ChessJsonList::ChessJsonList()
{
  m_jsonListLayout = new QVBoxLayout;

  setup();
  initFiles();
  setupStyleSheet();
}

void ChessJsonList::setup()
{
  QWidget* mainWidget = new QWidget;
  mainWidget->setStyleSheet("background: transparent;"); // <- проверь это!

  QScrollArea* scrol = new QScrollArea;
  scrol->setWidgetResizable(true);


  QLabel* features = new QLabel("Список видов:");
  features->setObjectName("title");

  QGridLayout* mainLayout = new QGridLayout;
  mainLayout->addWidget(features, 0, 0, 1, 1, Qt::AlignVCenter);
  mainLayout->addLayout(m_jsonListLayout, 1, 0, 1, 1);

  QVBoxLayout* layout = new QVBoxLayout(mainWidget);
  layout->addLayout(mainLayout);
  layout->addStretch();

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  mainWidget->setFixedWidth(mainWidget->size().width() * 1.5);

  scrol->setFixedWidth(mainWidget->width());
  scrol->setWidget(mainWidget);

  QVBoxLayout* thisLayout = new QVBoxLayout(this);
  thisLayout->setSpacing(0);
  layout->setContentsMargins(10, 10, 20, 0);

  thisLayout->addWidget(scrol);
  this->setLayout(thisLayout);
  this->setFixedWidth(scrol->size().width());
}

void ChessJsonList::initFiles()
{
  QStringList files;
  QDir dir("/home/daniel/Документы/JSON/");
  if (!dir.exists()) {
    qWarning() << "Папка не существует:";
    if (!dir.mkpath(".")) {
      qWarning() << "Не удалось создать папку:" << dir.path();
      return;
    } else {
      qDebug() << "Папка успешно создана:" << dir.path();
    }
  } else {
    QStringList filters;
    filters << "*.json";
    files = dir.entryList(filters, QDir::Files);

    if (files.isEmpty()) {
        QLabel* noFilesLabel = new QLabel("Нет файлов JSON в папке");
        m_jsonListLayout->addWidget(noFilesLabel);
        return;
    }

    for(auto& fileName : files)
    {
      QString name = QFileInfo(fileName).completeBaseName();
      QString fullPath = dir.filePath(fileName);
      QPushButton* btn = new QPushButton(name);
      m_jsonListLayout->addWidget(btn);
      connect(btn, &QPushButton::clicked, [this, fullPath]() {
        ChessInfoJson::instance().loadFromFile(fullPath);

        emit updateFormInfo();
      });
    }
  }
}

void ChessJsonList::setupStyleSheet()
{
  this->setStyleSheet(R"(
    QPushButton {
      background-color: rgba(255, 255, 255, 0.05); /* почти прозрачный */
      color: white;
      border: 3px solid #a67c52;
      border-radius: 6px;
      padding: 6px 10px;
      margin: 4px 0;
      text-align: left;
      font-size: 14px;
    }

    QPushButton:hover {
      background-color: rgba(255, 255, 255, 0.1);
      border-color: #d4a373;
    }

    QPushButton:pressed {
      background-color: rgba(255, 255, 255, 0.2);
      border-color: #8b5e3c;
    }

    QLabel {
      font-size: 16px;
      font-weight: bold;
      color: white;
    }

    QScrollArea {
      background: transparent;
      border: none;
    }

    QWidget {
      background: transparent;
    }

    #title {
      font-weight: bold;
      font-size: 20px;
      border-bottom: 2px dashed #a67c52;
      padding-bottom: 2px;
    }
  )");
}


