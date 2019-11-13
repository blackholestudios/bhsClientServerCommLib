#ifndef _BHS_PRODUCTION_META_HPP_
#define _BHS_PRODUCTION_META_HPP_

#include <QDebug>
#include <QString>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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
		 * @param converId	Content version id. 
		 * @return BhsProductionMeta::ConverData filled with proper data.
		 */
		ConverData getContentVersionData(const QString& converId);

		/**
		 * Get a list of all users registered in the system
		 * 
		 * @return QStringList of all usernames.
		 */
		QStringList getAllUsers();

		/**
		 * List all responsibilities of given user.
		 * 
		 * @param username The username the responsibilities must listed of.
		 * @return QStringList of all resposibilities of given user.
		 */
		QStringList getUserResponsibilities(const QString& username);

		/**
		 * Get a list of all content versions.
		 * 
		 * @return List with the ids of all convers.
		 */
		QStringList getAllContentVersions();

		/**
		 * Assign content version to user.
		 * 
		 * @param converId	Content version id in path form.
		 * @param username	User to assign the conver to.
		 */
		void assignConverToUser(const QString& converId,
								const QString& username);

	private:
		QString basePath;
	};

	/**
	 * Read Json from file
	 * 
	 * @param path Path of the json file as a QString.
	 * @return JSON data contained in the passed file.
	 */
	QJsonDocument readJsonFile(const QString& path);
}

#endif