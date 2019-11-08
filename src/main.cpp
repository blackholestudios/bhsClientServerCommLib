#include <bhsProductionMeta.hpp>

BhsProductionMeta::DB::
DB(const QString& projectBaseFolderPath) :
	basePath{projectBaseFolderPath} {
	
}

BhsProductionMeta::ConverData
BhsProductionMeta::DB::
getContentVersionData(const QString& converId) {
	QString metaPath{basePath + "/content/" + converId + "/meta.json"};
	QJsonDocument converJsonDoc{readJsonFile(metaPath)};

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