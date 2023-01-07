#include "installaddon.h"
#include <QDebug>
#include <QProcess>

void installAddon(uint id, std::string name) {
	QProcess    process;
	QStringList params;

	params << "+force_install_dir";
	params << R"(C:\GAME_SERVER\steamcmd\steamapps\workshop\content\107410)";
	params << "+login";
	params << "chameleonAD1";
	params << "ytTI1dztGKIN";
	params << "+workshop_download_item";
	params << "107410";
	params << QString::number(id);
	params << "+quit";

	process.start(R"(C:\GAME_SERVER\steamcmd\steamcmd.exe)", params);
	process.waitForFinished(9999999);
	QByteArray errorMsg = process.readAllStandardError();
	QByteArray msg      = process.readAllStandardOutput();

	if (process.error() != QProcess::ProcessError::UnknownError || !errorMsg.isEmpty()) {
		qCritical().noquote() << "error invoking steamcmd: " + errorMsg + msg + process.errorString();
		return;
	}
}

void installAddon(const AddonMap& addonToInstall) {
	for (auto& [id, name] : addonToInstall) {
		installAddon(id, name);
	}
}
