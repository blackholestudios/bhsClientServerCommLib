#ifndef _BHS_PRODUCTION_META_HPP_
#define _BHS_PRODUCTION_META_HPP_

#include <QDebug>
#include <QString>
#include <QDir>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject> 
#include <QJsonValue>
#include <QFile>
#include <QStringList>
#include <QDateTime>

namespace BhsProductionMeta {

	/**
	 * Data related to a content version
	 */
	class ConverData {
	public:
		enum Status {
			APPROVED,
			ASSIGNED,
			COMMENTING,
			POLLING,
			REJECTED,
			UNASSIGNED,
			WIP
		};

		Status			status;
		QString			assignee;
		QDateTime		deadline;
		QDateTime		commitDate;

		/**
		 * Convert a string into corresponding Status
		 * 
		 * @param s The string to convert
		 * @returns The status with the given name.
		 * 			UNASSIGNED is returned if the given name doesn't correspond to any status.
		 */
		static Status string2status(const QString& s);
	};
	
	class DB {
	public:
		/**
		 * @param projectBaseFolderPath	Path to the project base folder.
		 * 								It is the folder which contains the "content" and "meta" folder.
		 */
		DB(const QString& projectBaseFolderPath);

		/**
		 * Get data relative to a content version, given its id.
		 * @param converId	Content version id in path form.
		 * 					Eg: "/shot/001/layout/v001" 
		 * @return BhsProductionMeta::ConverData filled with proper data
		 */
		ConverData getContentVersionData(const QString& converId);

		/**
		 * Get a list of all users reistered in the system
		 * 
		 * @return List of all usernames
		 */
		QStringList getAllUsers();

		/**
		 * Get a list of all content versions
		 * 
		 * @return List with the ids of all convers.
		 */
		QStringList getAllContentVersions();

	private:
		QString basePath;
	};

	/**
	 * Get key-value pairs of given keys from Json document.
	 * 
	 * @param json QJsonDocument to get data from.
	 * @param keys List of keys to get.
	 * @return Requested key-value pairs.
	 */
	QHash<QString, QJsonValue>
	extractFromJson(
		const QJsonDocument&	json,
		const QStringList&		keys);

	/**
	 * Read Json from file
	 * 
	 * @param path Path of the json file as a QString.
	 * @return JSON data contained in the passed file.
	 */
	QJsonDocument readJsonFile(const QString& path);
}

#endif