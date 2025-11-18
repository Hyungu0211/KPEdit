#include "MainWindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>

// 설정 창 구현을 위한 헤더들 추가
#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGroupBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // 1. 창 기본 설정
    setWindowTitle("KPEdit - C++ Source Editor");
    resize(800, 600);

    // 2. 중앙 위젯 배치
    m_textWidget = new TextWidgetUI(this);
    setCentralWidget(m_textWidget);

    // 3. 메뉴 생성
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    // [파일]
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

    // [편집]
    undoAction = new QAction("실행 취소(&U)", this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::onUndo);

    redoAction = new QAction("다시 실행(&R)", this);
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::onRedo);

    findAction = new QAction("찾기/바꾸기(&F)...", this);
    findAction->setShortcut(QKeySequence::Find);
    connect(findAction, &QAction::triggered, this, &MainWindow::onFind);

    // [설정]
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

    // 설정 메뉴 추가
    QMenu* settingsMenu = menuBar()->addMenu("설정(&S)");
    settingsMenu->addAction(settingsAction);
}

// ---------------- 기능 구현부 ----------------

void MainWindow::onSettings()
{
    // 1. 다이얼로그 창 생성
    QDialog dialog(this);
    dialog.setWindowTitle("환경 설정");
    dialog.resize(300, 150); // 크기 조절

    // 2. 레이아웃 생성 (수직 정렬)
    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    // 3. 그룹박스 (테두리와 제목)
    QGroupBox* groupBox = new QGroupBox("자동 저장 옵션", &dialog);
    QVBoxLayout* radioLayout = new QVBoxLayout(groupBox);

    // 4. 라디오 버튼 2개 생성
    QRadioButton* timeRadio = new QRadioButton("일정 시간마다 저장 (Time-based)");
    QRadioButton* inputRadio = new QRadioButton("일정 입력 수마다 저장 (Input-based)");

    // 기본값 설정 (예: 시간 기반을 기본으로)
    timeRadio->setChecked(true);

    radioLayout->addWidget(timeRadio);
    radioLayout->addWidget(inputRadio);
    layout->addWidget(groupBox);

    // 5. 확인/취소 버튼 생성
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);

    // 버튼 연결 (OK -> 승인, Cancel -> 거절)
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    // 6. 다이얼로그 실행 (Modal 모드)
    if (dialog.exec() == QDialog::Accepted) {
        // 사용자가 '확인'을 눌렀을 때 처리 로직
        if (timeRadio->isChecked()) {
            // TODO: AutoSaveManager에게 "시간 기반 모드"로 설정하라고 명령
            // QMessageBox::information(this, "설정", "시간 기반 저장이 선택되었습니다.");
        }
        else {
            // TODO: AutoSaveManager에게 "입력 수 기반 모드"로 설정하라고 명령
            // QMessageBox::information(this, "설정", "입력 수 기반 저장이 선택되었습니다.");
        }
    }
}

void MainWindow::onFileNew() { /* Controller 연결 예정 */ }
void MainWindow::onFileOpen() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) { /* Controller 연결 예정 */ }
}
void MainWindow::onFileSave() { /* Controller 연결 예정 */ }
void MainWindow::onFileSaveAs() { /* Controller 연결 예정 */ }
void MainWindow::onUndo() { /* Controller 연결 예정 */ }
void MainWindow::onRedo() { /* Controller 연결 예정 */ }
void MainWindow::onFind() { /* Controller 연결 예정 */ }

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
}