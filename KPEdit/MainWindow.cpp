#include "MainWindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>
#include <QFileInfo>

// 설정창용
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QTimer>
#include <QDialogButtonBox>
#include <QMessageBox> // 테스트 메시지용

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("KPEdit");
    resize(800, 600);

    textWidget = new TextWidgetUI(this);
    setCentralWidget(textWidget);

    controller = new Controller(textWidget);
    textWidget->setController(controller);

    autoSaveManager = new AutoSaveManager(this);

    //자동저장 모드 연동
    controller->setAutoSaveManager(autoSaveManager);
    connect(autoSaveManager, &AutoSaveManager::requestSave, this, &MainWindow::onRequestAutoSave);

    //문자열 저장, 변경 문자열 수 관리
    connect(textWidget, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);

    //불러온 파일인지 확인
    fileLoaded = false;
    
    //찾기쪽 함수 연동

    // 텍스트 변경 시 -> Dirty 설정 및 제목 갱신
    connect(textWidget, &QPlainTextEdit::textChanged, [=]() {
        controller->setdirty();
        updateWindowTitle();
        });

    createActions();
    createMenus();
    updateWindowTitle();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    // 파일
    newAction = new QAction("새 파일(&N)", this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onFileNew);

    openAction = new QAction("열기(&O)...", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onFileOpen);

    saveAction = new QAction("저장(&S)", this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onFileSave);

    saveAsAction = new QAction("다른 이름으로 저장(&A)...", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onFileSaveAs);

    exitAction = new QAction("종료(&X)", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // 편집 (Qt 기본 슬롯 연결)
    undoAction = new QAction("실행 취소(&U)", this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, textWidget, &QPlainTextEdit::undo);

    redoAction = new QAction("다시 실행(&R)", this);
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, textWidget, &QPlainTextEdit::redo);

    findAction = new QAction("찾기/바꾸기(&F)...", this);
    findAction->setShortcut(QKeySequence::Find);
    connect(findAction, &QAction::triggered, this, &MainWindow::onFind);

    settingsAction = new QAction("환경 설정(&P)...", this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettings);
}

void MainWindow::createMenus()
{
    QMenu* fileMenu = menuBar()->addMenu("파일(&F)");
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    QMenu* editMenu = menuBar()->addMenu("편집(&E)");
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(findAction);

    QMenu* settingsMenu = menuBar()->addMenu("설정(&S)");
    settingsMenu->addAction(settingsAction);
}

// title 갱신 헬퍼 함수
void MainWindow::updateWindowTitle()
{
    string path = controller->getFilePath();
    bool isDirty = controller->getIsDirty();

    QString title;
    if (path.empty()) title = "제목 없음";
    else title = QFileInfo(QString::fromStdString(path)).fileName();

    title += " - KPEdit";
    if (isDirty) title += " *";
    AutoSaveMode mode = controller->getAutoSaveMode();
    if (mode == AutoSaveMode::TimeBased) {
        title += "- 시간 기반 자동 저장 중";
    }
    else if (mode == AutoSaveMode::InputBased) {
        title += "- 문자열 기반 자동 저장 중";
    }

    setWindowTitle(title);
}

// 저장 확인 헬퍼 함수 [사용 위치 : 새 파일, 열기, 닫기]
bool MainWindow::checkSave()
{
    if (!controller->getIsDirty()) return true;

    QMessageBox msgBox;
    msgBox.setWindowTitle("KPEdit");
    msgBox.setText("변경 사항이 저장되지 않았습니다.\n저장하시겠습니까?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton* saveBtn = msgBox.addButton("저장", QMessageBox::AcceptRole);
    QPushButton* discardBtn = msgBox.addButton("저장 안 함", QMessageBox::DestructiveRole);
    msgBox.addButton("취소", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == saveBtn) {
        onFileSave();
        return true;
    }
    else if (msgBox.clickedButton() == discardBtn) {
        return true;
    }
    return false;
}

// "새 파일" 구현
void MainWindow::onFileNew() {
    if (checkSave()) {
        controller->onFileNew();
        fileLoaded = false;
        updateWindowTitle();
    }
}

// "열기" 구현
void MainWindow::onFileOpen() {
    if (checkSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            controller->onFileOpen(fileName.toStdString());
            fileLoaded = true;
            updateWindowTitle();
        }
    }
}

// "저장" 구현
void MainWindow::onFileSave() {
    if (controller->getIsNewFile()) 
        onFileSaveAs();
    else {
        controller->onFileSave();
        fileLoaded = true;
        updateWindowTitle();
    }
}

// "다른 이름으로 저장" 구현
void MainWindow::onFileSaveAs() {
    QString fileName = QFileDialog::getSaveFileName(this);
    if (!fileName.isEmpty()) {
        controller->onFileSaveAs(fileName.toStdString());
        fileLoaded = true;
        updateWindowTitle();
    }
}

void MainWindow::onSettings()
{
    // 1. 다이얼로그 창 생성
    QDialog dialog(this);
    dialog.setWindowTitle("환경 설정");
    dialog.resize(350, 180); // 적당한 크기 설정

    // 2. 전체 레이아웃 생성 (수직 정렬)
    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);

    // 3. 그룹박스 생성 (시각적으로 묶어주기 위함)
    QGroupBox* groupBox = new QGroupBox("자동 저장 옵션", &dialog);
    QVBoxLayout* radioLayout = new QVBoxLayout(groupBox);

    // 4. 라디오 버튼 2개 생성
    QRadioButton* timeRadio = new QRadioButton("일정 시간마다 저장 (1분)");
    QRadioButton* inputRadio = new QRadioButton("일정 입력 횟수마다 저장 (100자)");

    // 기본값 설정 (예: 시간 기반을 기본으로 체크)
    // (나중에는 현재 설정값을 읽어와서 체크해주는 로직이 필요합니다)
    timeRadio->setChecked(true);

    // 레이아웃에 라디오 버튼 추가
    radioLayout->addWidget(timeRadio);
    radioLayout->addWidget(inputRadio);
    radioLayout->addStretch(1); // 여백 추가 (디자인)

    // 메인 레이아웃에 그룹박스 추가
    mainLayout->addWidget(groupBox);

    // 5. 확인/취소 버튼 상자 생성
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    mainLayout->addWidget(buttonBox);

    // 버튼 동작 연결 (Ok -> accept(), Cancel -> reject())
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 6. 다이얼로그 실행 (Modal 모드 - 창이 닫힐 때까지 대기)
    if (dialog.exec() == QDialog::Accepted) {
        // 사용자가 [확인]을 눌렀을 때 실행되는 코드

        if (timeRadio->isChecked() && fileLoaded == true) {
            // TODO: Controller에게 "시간 기반 모드"로 설정 변경 요청
            controller->setAutoSaveMode(AutoSaveMode::TimeBased);
            QMessageBox::information(this, "설정 변경", "자동 저장 모드가 [시간 기반]으로 변경되었습니다.");
        }
        else if (inputRadio->isChecked() && fileLoaded == true) {
            // TODO: Controller에게 "입력 수 기반 모드"로 설정 변경 요청
            controller->setAutoSaveMode(AutoSaveMode::InputBased);
            QMessageBox::information(this, "설정 변경", "자동 저장 모드가 [입력 수 기반]으로 변경되었습니다.");
        }
        else {
            QMessageBox::information(this, "설정 변경", "먼저 파일을 저장해주세요.");
        }
    }
}

void MainWindow::onRequestAutoSave()
{
        controller->onFileSave();
        updateWindowTitle();
}

void MainWindow::onTextChanged() {
    QString latestText = textWidget->toPlainText();
    int curLen = latestText.length();
    int diff = curLen - prevTextLength;
    prevTextLength = curLen;
    controller->notifyInputEdited(diff);
}
    

// 창 닫기 이벤트 처리
void MainWindow::closeEvent(QCloseEvent* event) {
    if (checkSave())
		// 닫기 허용
        event->accept();
    else
		// 닫기 취소
        event->ignore();
}

// 찾기/바꾸기 
void MainWindow::onFind() {
    FindDialog dlg(this);

    // 찾기 신호 연결
    connect(&dlg, &FindDialog::findRequested, this, &MainWindow::onFindRequested);

    // 바꾸기 신호 연결
    connect(&dlg, &FindDialog::replaceRequested, this, &MainWindow::onReplaceRequested);

    // 전체 바꾸기 신호 연결
    connect(&dlg, &FindDialog::replaceAllRequested, this, &MainWindow::onReplaceAllRequested);

    dlg.exec();
}

// '찾기' 기능 (커서 이동 등)
void MainWindow::onFindRequested(const QString& findText) {
    QString text = textWidget->toPlainText();

    // 새 검색어거나, 위치 초과시 리셋
    if (lastFindText != findText || lastFindPos == -1 || lastFindPos >= text.length()) {
        lastFindText = findText;
        lastFindPos = -1;
    }

    // 다음 위치 찾기
    int pos = text.indexOf(findText, lastFindPos + 1);

    if (findText.isEmpty()) {
        // 검색어가 비어있을 때 아무것도 안 함
        return;
    }

    if (lastFindPos == -1 && pos == -1) {
        QMessageBox::information(this, "Find/Replace", "찾는 단어가 없습니다.");
        lastFindPos = -1;  // 검색 위치 초기화
    }
    else if (pos == -1) {
        QMessageBox::information(this, "Find/Replace", "마지막 단어까지 모두 찾았습니다. \n한번 더 누를 시, 위에서부터 다시 탐색을 시작합니다.");
        lastFindPos = -1;  //다시 맨 위부터 탐색
    }
    else {
        // 정상적으로 다음 단어 찾음
        lastFindPos = pos;
        QTextCursor cursor = textWidget->textCursor();
        cursor.setPosition(pos);
        cursor.setPosition(pos + findText.length(), QTextCursor::KeepAnchor);
        textWidget->setTextCursor(cursor);
    }
}

// '바꾸기' 기능 (한 번만 치환할 때)
void MainWindow::onReplaceRequested(const QString& findText, const QString& replaceText) {
    QTextCursor cursor = textWidget->textCursor();
    if (cursor.selectedText() == findText) {
        cursor.insertText(replaceText);
        lastFindPos += (replaceText.length() - findText.length());
    }
}

// '전체 바꾸기' 기능
void MainWindow::onReplaceAllRequested(const QString& findText, const QString& replaceText) {
    QString text = textWidget->toPlainText();
    QString result = controller->replaceAllText(text, findText, replaceText);
    textWidget->setPlainText(result);
    lastFindPos = -1;
}