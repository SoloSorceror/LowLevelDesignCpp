#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class DocumentElement{
public:
    virtual std::string render() const = 0;
    virtual ~DocumentElement() = default;
};

class TextElement: public DocumentElement{
private:
    std::string text;
public:

    explicit TextElement(std::string text):text(std::move(text)){}

    std::string render() const override{
        return text;
    }
};

class ImageElement: public DocumentElement{
private:
    std::string imagePath;
public:
    explicit ImageElement(std::string imagePath): imagePath(std::move(imagePath)){}

    std::string render() const override{
        return "[Image :" + imagePath + "]";
    }
};

//Document

class Document{
private:
    std::vector<std::unique_ptr<DocumentElement>> elements;
public:
    void addElement(std::unique_ptr<DocumentElement> element){
        elements.push_back(std::move(element));
    }
    const auto &getElements() const{
        return elements;
    }
};

class DocumentRenderer{
public:
    std::string result;
};
