class Date {
public:
    Date();
    explicit Date(const std::string& input_date);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    Date& operator=(const Date& rhs);

    std::string GetDate(char separator = '-') const;

    time_t AsTimestamp() const;

    static int ComputeDaysDiff(const Date& date_to, const Date& date_from);

private:
    int year_;
    int month_;
    int day_;

    // Проверка формата
    void CheckFormat(const std::string& input);
    bool CheckNumber(std::stringstream& ss, int& number);
    // Проверка корректности даты
    void CheckData();
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);