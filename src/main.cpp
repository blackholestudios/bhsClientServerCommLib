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
	const QJsonObject converJsonObj{converJsonDoc.object()};

	return {
		ConverData::string2status(converJsonObj["status"].toString("UNASSIGNED")),
		converJsonObj["assignee"].toString("UNASSIGNED"),
		QDateTime::fromString(converJsonObj["deadline"].toString(), Qt::ISODate),
		QDateTime::fromString(converJsonObj["commitDate"].toString(), Qt::ISODate)
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
	const QJsonArray responsibilitiesJson{json.object()["convers"].toArray()[0]};
	
	QStringList responsibilities;
	for(const QJsonValue& entry : responsibilitiesJson) {
		responsibilities << entry.toString();
	}
	return responsibilities;
}

QStringList
BhsProductionMeta::DB::
getAllContentVersions() {
	QStringList responsibilities;

	// Read from user files
	const QStringList users{getAllUsers()};
	for(const QString& user : users) {
		const QStringList userResponsibilities{getUserResponsibilities(user)};
		responsibilities << userResponsibilities;
	}

	// Read from unassigned.json
	const QDir jsonPath{basePath + "/meta/unassigned.json"}; 
	const QJsonDocument json{readJsonFile(jsonPath.path())};
	const QJsonArray unassigned{json.array()[0]};
	for(const QJsonValue& entry : unassigned) {
		responsibilities << entry.toString();
	}

	return responsibilities;
}

void
BhsProductionMeta::DB::
assignConverToUser(	const QString& converId,
					const QString& username) {
	// Add to user
	
	// Remove from unassigned
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

QJsonDocument 
BhsProductionMeta::
readJsonFile(const QString& path) {
	QFile converMetaFile{path};
	converMetaFile.open(QIODevice::ReadOnly | QIODevice::Text);
	return {QJsonDocument::fromJson(converMetaFile.readAll())};
}