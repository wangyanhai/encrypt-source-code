///////////////////////////////////////////////////////////
//  translate.cpp
//  Implementation of the Class CTranslateController
//  Created on:      30-10ÔÂ-2019 17:59:02
///////////////////////////////////////////////////////////

#include "translate.h"
#include <iostream>

CTranslateController::CTranslateController(){
	m_translateObject = new CTranslateObject;
	m_translateObject->moveToThread(&m_thread);
	connect(m_translateObject, SIGNAL(finished()), &m_thread, SLOT(quit()));  
	connect(&m_thread, SIGNAL(finished()), m_translateObject, SLOT(deleteLater()));  
	connect(this, SIGNAL(translateEntrance(QString)), m_translateObject,
		SLOT(translate(QString)));  
	m_thread.start();
}



CTranslateController::~CTranslateController(){
	if (m_translateObject){
		delete m_translateObject;
	}
}


bool CTranslateController::waitForFinished(int msecs){
	QTime t;
	t.start();
	while (true){
		int elapsed = t.elapsed();
		if (msecs!=-1 && elapsed>msecs)
		{
			if (isRunning())
				return false;
			else 
				return true;
		}
	}

	return false;
}


bool CTranslateController::isRunning(){

	return m_translateObject->isRunning();
}


void CTranslateController::translate(QString filename){
	cout << "begin to translate " << qPrintable(filename) << endl;
	emit translateEntrance(filename);
}


CTranslateManager::CTranslateManager(){

}



CTranslateManager::~CTranslateManager(){

}


bool CTranslateManager::waitForFinished(int msecs){
	QTime t;
	t.start();
	while (true){
		int elapsed = t.elapsed();
		bool beingRunning = isRunning();
		if (!beingRunning)
			return true;

		if (msecs!=-1 && elapsed>msecs)
		{
			if (beingRunning)
				return false;
			else 
				return true;
		}
	}

	return false;
}


void CTranslateManager::translateFile(QString filename){
	CTranslateController* controller = new CTranslateController;
	m_translate_list.append(controller);
	controller->translate(filename);
}


bool CTranslateManager::isRunning(){
	bool bret = false;
	auto it = m_translate_list.begin();
	while (it != m_translate_list.end()){
		bret |= (*it)->isRunning();
		++it;
	}
	return bret;
}


CTranslateObject::CTranslateObject(){

}



CTranslateObject::~CTranslateObject(){

}


void CTranslateObject::translate(QString filename){
	setRunning(true);
	translateFile(filename);
	setRunning(false);
}


bool CTranslateObject::isRunning(){
	QMutexLocker locker(&m_mutex_state);
	return m_bRunning;
}


void CTranslateObject::setRunning(bool state){
	QMutexLocker locker(&m_mutex_state);
	m_bRunning = state;
}