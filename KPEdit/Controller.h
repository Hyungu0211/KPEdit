#pragma once
#include <string>

using namespace std;

class Document;
class FileManager;
class TextWidgetUI;

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

    // Dirty 설정
    void setdirty();

private:
    Document* document;
    FileManager* fileManager;
    TextWidgetUI* textWidget;
};