class INotifier {
public:
    virtual void Notify(std::string msg) const = 0;
};

class SmsNotifier : public INotifier {
public:
    SmsNotifier(std::string sms) : Number(sms) {
        
    }
    virtual void Notify(std::string msg) const override {
        SendSms(Number, msg);
    }
private:
    std::string Number;
};

class EmailNotifier : public INotifier {
public:
    EmailNotifier(std::string email) : Email(email) {
        
    }
    void Notify(std::string msg) const override {
        SendEmail(Email, msg);
    }
private:
    std::string Email;
};

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}