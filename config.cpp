#include "config.h"
#include <boost/json.hpp>
#include <QDebug>
#include "boostJson.h"
#include <QFile>

namespace bj = boost::json;

bj::object config;

void decodeJson(const std::string& raw) {
    bj::error_code    ec;
    bj::stream_parser p;
    int               pos = p.write(raw, ec);
    if (ec) {
        qCritical() << "Error decoding config.json at position " << pos;
        exit(1);
    }
    try{
        config = p.release().as_object();
    }catch(std::exception& e){
        qDebug() << e.what();
    }


}
void updateJson(unsigned int id, const std::string &name)
{
    auto newLine = bj::object({{"id",id}, {"name",name}});
    config["addon"].as_array().emplace_back(newLine);
    auto neu = pretty_print(config);

    QFile configFile("config.json");
    if (!configFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qCritical() << "impossible to open config.json";
        exit(1);
    }

    configFile.write(neu.data(),neu.size());
}

AddonMap extractAddonFromJson() {
    if (!config.contains("addon")) {
        config.insert_or_assign("addon", bj::array());
        return {};
    }
    AddonMap res;
    for (auto& row_ : config["addon"].as_array()) {
        auto r = pretty_print(row_);
        auto row  = row_.as_object();
        auto name = row["name"].as_string();
        auto id   = row["id"].as_int64();
        res.insert({id, name.data()});
    }
    return res;
}
