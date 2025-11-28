#include "QSaveState.hpp"
#include <qdir.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

QSaveState::QSaveState() {}

void QSaveState::saveToFile(std::string& path, UAR* uar, bool* simmulation_running, State::TypGeneratora* typ, GeneratorProstokatny* gen_pros, GeneratorSinusoida* gen_sin)
{
    QJsonObject jsonObject;

    QJsonObject jsonAXR;
    QJsonObject jsonPID;
    QJsonObject jsonGenSin;
    QJsonObject jsonGenPros;

    jsonObject["simmulation_running"] = *simmulation_running;
    jsonObject["wybrany_typ_generatora"] = (int)*typ;
    jsonAXR["k"] = uar->getARX().getK();
    jsonAXR["standard_deviation"] = uar->getARX().getStandardDeviation();
    jsonAXR["input_limit_low"] = uar->getARX().getInputLimits().first;
    jsonAXR["input_limit_high"] = uar->getARX().getInputLimits().second;
    jsonAXR["output_limit_low"] = uar->getARX().getOutputLimits().first;
    jsonAXR["output_limit_high"] = uar->getARX().getOutputLimits().second;
    jsonObject["arx"] = jsonAXR;

    jsonObject["pid"] = jsonPID;
    jsonObject["generator_sinusoidalny"] = jsonGenSin;
    jsonObject["generator_prostokatny"] = jsonGenPros;

    QJsonDocument jsonDoc(jsonObject);

    QFile file(path.c_str());
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Could not open file for writing";
        return;
    }

    file.write(jsonDoc.toJson());
    file.close();
}
void QSaveState::readFromFile(std::string& path, UAR* uar, bool* simmulation_running, State::TypGeneratora* typ, GeneratorProstokatny* gen_pros, GeneratorSinusoida* gen_sin)
{

}
