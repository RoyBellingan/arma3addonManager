#include "decodehtml.h"
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <boost/json.hpp>
#include <fmt/format.h>

namespace bj = boost::json;

QCommandLineParser cliParam;

bj::object decodeJson(const std::string& raw) {
	bj::error_code    ec;
	bj::stream_parser p;
	int               pos = p.write(raw, ec);
	if (ec) {
		fmt::print(stderr, "Error decoding config.json at position {} \n", pos);
		exit(1);
	}
	return p.release().as_object();
}

void cliParamManager(QCoreApplication& application) {
	cliParam.addHelpOption();
	cliParam.addVersionOption();

	QCommandLineOption fParm({{"F", "from"}, "Add the addon from this HTML file", "string"});
	cliParam.addOption(fParm);

	QCommandLineOption remoteParam({{"U", "update"}, "Update all the addon in the json file"});
	cliParam.addOption(remoteParam);

	QCoreApplication::setApplicationVersion("0.01");

	cliParam.process(application);
}

AddonMap extractAddonFromJson(bj::object& json) {
	if (!json.contains("addon")) {
		return {};
	}
	AddonMap res;
	for (auto& row_ : json["addon"].as_object()) {
		auto row  = row_.value().as_object();
		auto id   = row["id"].as_uint64();
		auto name = row["name"].as_string();
		res.insert({id, name.data()});
	}
	return res;
}



int main(int argc, char* argv[]) {
	//	for (int i = 0; i < argc; ++i) {
	//		fmt::print("{}\n", argv[i]);
	//	}

	QCoreApplication application(argc, argv);
	cliParamManager(application);

	QFile configFile("config.json");
	if (!configFile.open(QFile::ReadWrite)) {
		qCritical() << "impossible to open config.json";
		exit(1);
	}

	auto config = decodeJson(configFile.readAll().toStdString());

	if (cliParam.isSet("from")) {
		auto  htmlFileName = cliParam.value("from");
		QFile htmlFile(htmlFileName);
		if (!htmlFile.open(QFile::ReadOnly)) {
			qCritical() << "impossible to open " << htmlFileName;
			exit(1);
		}
		DecodeHTML h;
		auto       newAddons = h.fromHtml(htmlFile.readAll().toStdString());
		//		for (auto& [id, name] : addons) {
		//			fmt::print("{} - {}\n", id, name);
		//		}
		//find the new addon and add in the json and perform the install
		AddonMap addonToInstall;
		auto     oldAddons = extractAddonFromJson(config);
		for (auto& [id, name] : newAddons) {
			if (oldAddons.count(id)) {
				continue;
			}
			addonToInstall.insert({id, name});
		}
	}
}

//
