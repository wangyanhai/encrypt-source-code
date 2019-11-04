///////////////////////////////////////////////////////////
//  translate.h
//  Implementation of the Class CTranslateController
//  Created on:      30-10ÔÂ-2019 17:59:02
///////////////////////////////////////////////////////////

#if !defined(EA_E4D8A91C_41F7_4200_9050_27B64A32353A__INCLUDED_)
#define EA_E4D8A91C_41F7_4200_9050_27B64A32353A__INCLUDED_
#include <QString>
#include <QThread>
#include <QList>
#include "util.h"

class CTranslateObject;
class CTranslateController : public QObject
{
	Q_OBJECT
public:
	CTranslateController();
	virtual ~CTranslateController();

	bool waitForFinished(int msecs);
	bool isRunning();
	void translate(QString filename);

signals:
	void translateEntrance(QString filename);

private:
	QThread m_thread;
	CTranslateObject* m_translateObject;
};

class CTranslateManager : public QObject
{
	Q_OBJECT
public:
	CTranslateManager();
	virtual ~CTranslateManager();

	bool waitForFinished(int msecs);
	void translateFile(QString filename);
	bool isRunning();

private:
	QList<CTranslateController*> m_translate_list;

};

class CTranslateObject : public QObject
{
	Q_OBJECT
public:
	CTranslateObject();
	virtual ~CTranslateObject();

	bool isRunning();
	void setRunning(bool state);

private slots:
	void translate(QString filename);
signals:
	void finished();
private:
	bool m_bRunning;
	QMutex m_mutex_state;
	friend class CTranslateController;
};
#endif // !defined(EA_E4D8A91C_41F7_4200_9050_27B64A32353A__INCLUDED_)
