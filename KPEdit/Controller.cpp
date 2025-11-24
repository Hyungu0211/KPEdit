#include "Controller.h"
#include "Document.h"
#include "FileManager.h"
#include "TextWidgetUI.h"
#include <QString>

using namespace std;

Controller::Controller(TextWidgetUI* ui) : textWidget(ui)
{
    document = new Document();
    fileManager = new FileManager();
}

Controller::~Controller()
{
    delete document;
    delete fileManager;
}


// 새 파일 만들기
void Controller::onFileNew()
{   
    // 화면 초기화
    textWidget->clear();

	// 상태 초기화
    document->setFilePath("");
    document->setDirty(false);
}


// 파일 열기
void Controller::onFileOpen(const string& filePath)
{
    // 1. 파일 읽기
    QString qPath = QString::fromStdString(filePath);
    QString content = fileManager->ReadFile(qPath);

    // 2. 화면에 뿌리기
    textWidget->setPlainText(content);

    // 3. 상태 설정
    document->setFilePath(filePath);
    document->setDirty(false);
}


// 파일 저장
void Controller::onFileSave()
{
    string path = document->getFilePath();
    if (path.empty()) return;

    // 화면 내용 가져오기
    QString content = textWidget->toPlainText();
    QString qPath = QString::fromStdString(path);

    fileManager->WriteFile(qPath, content);
    document->setDirty(false);
}

void Controller::onFileSaveAs(const string& filePath)
{
    document->setFilePath(filePath);
    onFileSave();
}

// 수정 여부 확인
bool Controller::getIsDirty() const { return document->getIsDirty(); }
// 파일 경로 가져오기
string Controller::getFilePath() const { return document->getFilePath(); }
// Dirty 설정
void Controller::setdirty() { document->setDirty(true); }

// 새 파일인지 확인
bool Controller::getIsNewFile() const { return document->getFilePath().empty();}