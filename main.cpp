#include "config.h"
#include "decodehtml.h"
#include "installaddon.h"
#include "unistd.h"
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <filesystem>

namespace fs = std::filesystem;

void readAddon(const QString& htmlFileName) {
	QFile htmlFile(htmlFileName);
	if (!htmlFile.open(QFile::ReadOnly)) {
		qCritical() << "impossible to open " << htmlFileName;
		exit(1);
	}
	DecodeHTML decoder;
	auto       newAddons = decoder.fromHtml(htmlFile.readAll().toStdString());
	//	for (auto& [id, name] : newAddons) {
	//		qDebug() << id << name.data();
	//	}
	//find the new addon and add in the json and perform the install
	AddonMap addonToInstall;
	auto     oldAddons = extractAddonFromJson();
	for (auto& [id, name] : newAddons) {
		if (oldAddons.count(id)) {
			continue;
		}
		addonToInstall.insert({id, name});
	}
	installAddon(addonToInstall);
}

//void readAddon(const std::string& htmlFileName) {
//	readAddon(QString::fromStdString(htmlFileName));
//}

int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; ++i) {
		qDebug() << argv[i];
	}

	QCoreApplication application(argc, argv);

	QFile configFile("config.json");
	if (!configFile.open(QFile::ReadOnly)) {
		qCritical() << "impossible to open config.json";
		exit(1);
	}

	decodeJson(configFile.readAll().toStdString());

	if (argc == 1) {
		//if we just call the program we just update the addon
		// TODO
		return 0;
	}

	if (argc == 2) {
		readAddon(argv[1]);
		return 0;
	}
}

//
