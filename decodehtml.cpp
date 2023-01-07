#include "decodehtml.h"
#include "xPath/xml.h"
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <string>

AddonMap DecodeHTML::fromHtml(const std::string& html) {
	AddonMap res;

	XPath x;
	x.read(html.data(), html.size());
	/*
<body>
    <h1>Arma 3 Mods</h1>
    <p class="before-list">
      <em>To import this preset, drag this file onto the Launcher window. Or click the MODS tab, then PRESET in the top right, then IMPORT at the bottom, and finally select this file.</em>
    </p>
    <div class="mod-list">
      <table>
	<tr data-type="ModContainer">
	  <td data-type="DisplayName">@taroccoV2</td>
	  <td>
	    <span class="from-steam">Steam</span>
	  </td>
	  <td>
	    <a href="https://steamcommunity.com/sharedfiles/filedetails/?id=2873724117" data-type="Link">https://steamcommunity.com/sharedfiles/filedetails/?id=2873724117</a>
	  </td>
	</tr>
*/
	auto nodes = x.getNodes("//tr[contains(@data-type, 'ModContainer')]");
	for (auto& node : nodes) {
		auto tds = node.searchNodes("td");
		if (tds.size() != 3) {
			qCritical() << "invalid format in html file at row!" << node.getContent();
			continue;
		}

		std::string addonName = tds[0].getContent().toStdString();

		QString   urlRaw = tds[2].getContent().trimmed();
		QUrl      url(urlRaw);
		QUrlQuery query(url);

		if (!query.hasQueryItem("id")) {
			qCritical() << "invalid format in html file at row" << urlRaw;
			continue;
		}
		auto addonId = query.queryItemValue("id").toULong();

		res.insert({addonId, addonName});
	}
	return res;
}
