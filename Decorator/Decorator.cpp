#include <string>
#include <iostream>
#include <algorithm> // Для std::reverse
#include <memory>    // Для std::shared_ptr

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }

    virtual ~Text() = default; // Виртуальный деструктор для корректного удаления
};

class Paragraph : public Text {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : text_(text) {}
    void render(const std::string& data) const override {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
private:
    std::shared_ptr<Text> text_;
};

class Reversed : public Text {
public:
    explicit Reversed(std::shared_ptr<Text> text) : text_(text) {}
    void render(const std::string& data) const override {
        std::string reversed_data = data;
        std::reverse(reversed_data.begin(), reversed_data.end());
        text_->render(reversed_data);
    }
private:
    std::shared_ptr<Text> text_;
};

class Link : public Text {
public:
    explicit Link(std::shared_ptr<Text> text) : text_(text) {}
    void render(const std::string& url, const std::string& data) const {
        std::cout << "<a href=" << url << ">";
        text_->render(data);
        std::cout << "</a>";
    }
private:
    std::shared_ptr<Text> text_;
};

class DecoratedText : public Text {
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
protected:
    std::shared_ptr<Text> text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const override {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

int main() {
    auto text_block1 = std::make_shared<ItalicText>(std::make_shared<BoldText>(std::make_shared<Text>()));
    text_block1->render("Hello world");
    std::cout << std::endl;

    auto text_block2 = std::make_shared<Paragraph>(std::make_shared<Text>());
    text_block2->render("Hello world");
    std::cout << std::endl;

    auto text_block3 = std::make_shared<Reversed>(std::make_shared<Text>());
    text_block3->render("Hello world");
    std::cout << std::endl;

    auto text_block4 = std::make_shared<Link>(std::make_shared<Text>());
    text_block4->render("netology.ru", "Hello world");
    std::cout << std::endl;

}