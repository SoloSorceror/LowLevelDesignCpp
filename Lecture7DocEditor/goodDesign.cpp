#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>



// ============================================================
// Document Elements
// ============================================================

class DocumentElement {
public:
    virtual std::string render() const = 0;

    virtual ~DocumentElement() = default;
};

class TextElement : public DocumentElement {
private:
    std::string text;

public:
    explicit TextElement(std::string text)
        : text(std::move(text)) {}

    std::string render() const override {
        return text;
    }
};

class ImageElement : public DocumentElement {
private:
    std::string imagePath;

public:
    explicit ImageElement(std::string imagePath)
        : imagePath(std::move(imagePath)) {}

    std::string render() const override {
        return "[Image: " + imagePath + "]";
    }
};

// ============================================================
// Document
// ============================================================

class Document {
private:
    std::vector<std::unique_ptr<DocumentElement>> elements;

public:
    void addElement(std::unique_ptr<DocumentElement> element) {
        elements.push_back(std::move(element));
    }

    const auto& getElements() const {
        return elements;
    }
};

// ============================================================
// Renderer
// ============================================================

class DocumentRenderer {
public:
    std::string render(const Document& document) const {
        std::string result;

        for (const auto& element : document.getElements()) {
            result += element->render();
            result += '\n';
        }

        return result;
    }
};

// ============================================================
// Persistence
// ============================================================

class Persistence {
public:
    virtual void save(const std::string& data) = 0;

    virtual ~Persistence() = default;
};

class FileStorage : public Persistence {
private:
    std::string filePath;

public:
    explicit FileStorage(std::string filePath)
        : filePath(std::move(filePath)) {}

    void save(const std::string& data) override {
        std::ofstream file(filePath);

        if (!file) {
            throw std::runtime_error(
                "Unable to open file for writing"
            );
        }

        file << data;
    }
};

class DBStorage : public Persistence {
public:
    void save(const std::string& data) override {
        std::cout << "Saving to database:\n";
        std::cout << data;
    }
};

// ============================================================
// Document Editor
// ============================================================

class DocumentEditor {
private:
    Document document;
    DocumentRenderer renderer;
    std::unique_ptr<Persistence> persistence;

public:
    explicit DocumentEditor(
        std::unique_ptr<Persistence> persistence
    )
        : persistence(std::move(persistence)) {}

    void addText(const std::string& text) {
        document.addElement(
            std::make_unique<TextElement>(text)
        );
    }

    void addImage(const std::string& imagePath) {
        document.addElement(
            std::make_unique<ImageElement>(imagePath)
        );
    }

    std::string renderDocument() const {
        return renderer.render(document);
    }

    void saveDocument() {
        persistence->save(renderDocument());
    }
};

// ============================================================
// Client
// ============================================================

int main() {

    auto storage =
        std::make_unique<FileStorage>("document.txt");

    DocumentEditor editor(std::move(storage));

    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor.");

    std::cout << editor.renderDocument();

    editor.saveDocument();

    return 0;
}