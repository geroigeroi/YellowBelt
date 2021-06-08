#pragma once
#include "date.h"
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    And,
    Or,
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate (const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison cmp, const Date& date) : date_(date), cmp_(cmp) {}
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    const Comparison cmp_;
    const Date date_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison cmp, const std::string& event) : event_(event), cmp_(cmp) {}
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    const Comparison cmp_;
    const std::string event_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& o, std::shared_ptr<const Node> lhs, std::shared_ptr<const Node> rhs) : o_(o), lhs_(lhs), rhs_(rhs) {}
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    const LogicalOperation o_;
    const std::shared_ptr<const Node> lhs_;
    const std::shared_ptr<const Node> rhs_;
};
