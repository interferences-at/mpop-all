#ifndef MISSINGPARAMETERERROR_H
#define MISSINGPARAMETERERROR_H

#include <QException>
#include <QString>

/**
 * @brief Generic error about a missing parameter that is missing from a request.
 */
class MissingParameterError : public QException
{
public:
    MissingParameterError(const QString& methodName) {
        this->methodName = methodName;
    }
    void raise() const override {
        throw *this;
    }
    MissingParameterError* clone() const override {
        return new MissingParameterError(*this);
    }

    virtual const char* what() const noexcept override {
        QString message("A parameter is missing from request %1.");
        message = message.arg(this->methodName);
        return message.toStdString().c_str();
    }
protected:
    QString methodName;
};

/**
 * @brief A named parameter is missing from the request.
 */
class MissingParamemeterByName : public MissingParameterError
{
public:
    MissingParamemeterByName(const QString& methodName, const QString& parameterName) : MissingParameterError(methodName) {
        this->parameterName = parameterName;
    }
    void raise() const override {
        throw *this;
    }
    MissingParamemeterByName* clone() const override {
        return new MissingParamemeterByName(*this);
    }
    virtual const char* what() const noexcept override {
        QString message("Parameter %1 is missing from request %2.");
        message = message.arg(this->parameterName).arg(this->methodName);
        return message.toStdString().c_str();
    }
private:
    QString parameterName;
};

/**
 * @brief A positional parameter is missing from the request.
 */
class MissingParamemeterByPosition : public MissingParameterError
{
public:
    MissingParamemeterByPosition(const QString& methodName, int parameterPosition) : MissingParameterError(methodName) {
        this->parameterPosition = parameterPosition;
    }
    void raise() const override {
        throw *this;
    }
    MissingParamemeterByPosition* clone() const override {
        return new MissingParamemeterByPosition(*this);
    }

    virtual const char* what() const noexcept override {
        QString message("Parameter %1 is missing from request %2.");
        message = message.arg(this->parameterPosition).arg(this->methodName);
        return message.toStdString().c_str();
    }
private:
    int parameterPosition;
};

#endif // MISSINGPARAMETERERROR_H
