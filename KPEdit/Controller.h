#pragma once
#include <string>
#include <QString>

using namespace std;

class Document;
class FileManager;
class TextWidgetUI;
class AutoSaveManager;
enum class AutoSaveMode;

class Controller 
{
public:
    Controller(TextWidgetUI* ui);
    ~Controller();


    // 파일 작업
    void onFileNew();
    void onFileOpen(const string& filePath);
    void onFileSave();
    void onFileSaveAs(const string& filePath);

    // 상태 확인
    bool getIsDirty() const;
    string getFilePath() const;
    bool getIsNewFile() const;

    // 자동저장 연동
    void setAutoSaveManager(class AutoSaveManager* mgr);
    void setAutoSaveMode(AutoSaveMode mode);
    void notifyInputEdited(int charCountAdd);
    AutoSaveMode getAutoSaveMode() const;

    // 찾기 연동
    int findText(const QString& text, const QString& keyword);
    QString replaceText(const QString& text, const QString& oldWord, const QString& newWord);
    QString replaceAllText(const QString& text, const QString& oldWord, const QString& newWord);

    // Dirty 설정
    void setdirty();

private:
    Document* document;
    FileManager* fileManager;
    TextWidgetUI* textWidget;
    AutoSaveManager* autoSaveManager = nullptr;
};