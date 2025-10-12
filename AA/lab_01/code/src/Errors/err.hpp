#ifndef EXCEPTIONS_HPP__
#define EXCEPTIONS_HPP__

#include <exception>
#include <string>

class BaseExceptions : public std::exception
{
public:
    BaseExceptions(const char* what_happened) noexcept
    {
        snprintf(err_msg, msg_len, "\n%s\n", what_happened);
    };

    const char *what() const noexcept override
    {
        return err_msg;
    };

protected:
    static const size_t msg_len = 512;
    char err_msg[msg_len] = "";
};

class Unmultipliable : public BaseExceptions
{
public:
    Unmultipliable() noexcept : BaseExceptions("Ошибка: неверный размер матриц для умножения") {};
};

class FileError : public BaseExceptions
{
public:
    FileError() noexcept : BaseExceptions("Ошибка: не удалось открыть файл") {};
};

class SizeError : public BaseExceptions
{
public:
    SizeError() noexcept : BaseExceptions("Ошибка: заданые некорректные размеры матриц") {};
};

class DataError : public BaseExceptions
{
public:
    DataError() noexcept : BaseExceptions("Ошибка чтения данных из файла") {};
};


#endif // EXCEPTIONS_HPP__
