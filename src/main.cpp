#include <bhsProductionMeta.hpp>

BhsProductionMeta::DB::
DB(const QString& projectBaseFolderPath) :
	basePath{projectBaseFolderPath} {
	
}

BhsProductionMeta::ConverData
BhsProductionMeta::DB::
getContentVersionData(const QString& converId) {
	QDir metaPath{basePath + "/content/" + converId + "/meta.json"};
	QJsonDocument converJsonDoc{readJsonFile(metaPath.path())};

	const QHash<QString, QJsonValue>
	converJsonData{extractFromJson(converJsonDoc, {
		"status",
		"assignee",
		"deadline",
		"commitDate"
	})};

	return {
		ConverData::string2status(converJsonData["status"].toString("UNASSIGNED")),
		converJsonData["assignee"].toString("UNASSIGNED"),
		QDateTime::fromString(converJsonData["deadline"].toString(), Qt::ISODate),
		QDateTime::fromString(converJsonData["commitDate"].toString(), Qt::ISODate)
	};
}

QStringList
BhsProductionMeta::DB::
getAllUsers() {
	const QDir usersFolder{basePath + "/meta/"};
	QStringList usersFolderEntries{usersFolder.entryList({"*.json"})};

	QStringList userList;
	for(QString& entry : usersFolderEntries) {
		if(entry != "unassigned.json") {
			userList << entry.remove(".json");
		}
	}
	return userList;
}

QStringList
BhsProductionMeta::DB::
getUserResponsibilities(const QString& username) {
	const QDir userJsonPath{basePath + "/meta/" + username + ".json"};
	const QJsonDocument json{readJsonFile(userJsonPath.path())};
	const QJsonValue responsibilitiesJson{json.object()["convers"]};
	
	QStringList responsibilities;
	for(const QJsonValue& entry : responsibilitiesJson.toArray()) {
		responsibilities << entry.toString();
	}
	return responsibilities;
}

QStringList
BhsProductionMeta::DB::
getAllContentVersions() {
	const QDir metaFolder{basePath + "/meta/"};
	const QStringList metaFolderEntries{metaFolder.entryList({"*.json"})};

	for(const QString& entry : metaFolderEntries) {
		qInfo() << entry;
	}

	return {};
}

BhsProductionMeta::ConverData::Status
BhsProductionMeta::ConverData::
string2status(const QString& s) {
	const QString sUp{s.toUpper()};
	if(sUp == "APPROVED")	return APPROVED;
	if(sUp == "ASSIGNED")	return ASSIGNED;
	if(sUp == "COMMENTING")	return COMMENTING;
	if(sUp == "POLLING")	return POLLING;
	if(sUp == "REJECTED")	return REJECTED;
	if(sUp == "UNASSIGNED")	return UNASSIGNED;
	if(sUp == "WIP")		return WIP;
	return UNASSIGNED;
}

QHash<QString, QJsonValue>
BhsProductionMeta::
extractFromJson(
	const QJsonDocument&	json,
	const QStringList&		keys) {
	
	const QJsonObject jobj{json.object()};
	QHash<QString, QJsonValue> returnData;
	for(const QString& k : keys) {
		if(jobj.contains(k))
			returnData[k] = jobj[k];
	}
	return returnData;
}

QJsonDocument 
BhsProductionMeta::
readJsonFile(const QString& path) {
	QFile converMetaFile{path};
	converMetaFile.open(QIODevice::ReadOnly | QIODevice::Text);
	return {QJsonDocument::fromJson(converMetaFile.readAll())};
}