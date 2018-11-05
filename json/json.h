//
// Created by 艾峥鹏 on 2018/11/3.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <map>
#include <string>
#include <vector>

namespace json {
    void get_ws(std::istream &is);

    class type {
    private:
        friend std::istream &operator>>(std::istream &is, type &t);
        friend std::ostream &operator<<(std::ostream &os, const type &t);

    public:
        type();
        virtual ~type();
        virtual type &operator[](int index);
        virtual type &operator[](const std::string &name);
        virtual bool to_boolean() const;
        virtual long double to_decimal() const;
        virtual long long to_integer() const;
        virtual std::string to_string() const;
        virtual std::string to_json_text() const;
        virtual size_t size() const;
    };

    class array : public type {
    private:
        std::vector<type *> value;
        friend std::istream &operator>>(std::istream &is, array &arr);
        friend std::ostream &operator<<(std::ostream &os, const array &arr);

    public:
        array();
        array(const array &original);
        ~array() override;
        array &operator=(const array &another);
        type &operator[](int index) override;
        std::string to_json_text() const override;
        size_t size() const override;
    };

    class boolean : public type {
    private:
        bool value;
        friend std::istream &operator>>(std::istream &is, boolean &b);
        friend std::ostream &operator<<(std::ostream &os, const boolean &b);

    public:
        boolean();
        boolean(const boolean &original);
        explicit boolean(bool value);
        ~boolean() override;
        boolean &operator=(const boolean &another);
        bool to_boolean() const override;
        std::string to_json_text() const override;
    };

    class number : public type {
    private:
        std::string value;
        friend std::istream &operator>>(std::istream &is, number &num);
        friend std::ostream &operator<<(std::ostream &os, const number &num);

    public:
        number();
        number(const number &original);
        explicit number(long double value);
        explicit number(long long value);
        ~number() override;
        number &operator=(const number &another);
        long double to_decimal() const override;
        long long to_integer() const override;
        std::string to_json_text() const override;
    };

    class object : public type {
    private:
        std::map<std::string, type *> value;
        friend std::istream &operator>>(std::istream &is, object &obj);
        friend std::ostream &operator<<(std::ostream &os, const object &obj);

    public:
        object();
        object(const object &original);
        ~object() override;
        object &operator=(const object &another);
        type &operator[](const std::string &name) override;
        std::string to_json_text() const override;
        size_t size() const override;
        virtual std::string dump() const;
    };

    class string : public type {
    private:
        std::string value;
        friend std::istream &operator>>(std::istream &is, string &str);
        friend std::ostream &operator<<(std::ostream &os, const string &str);

    public:
        string();
        string(const string &original);
        explicit string(const std::string &value);
        ~string() override;
        string &operator=(const string &another);
        std::string to_string() const override;
        std::string to_json_text() const override;
    };

    object parse(const std::string &text);
}

#endif //JSON_JSON_H
