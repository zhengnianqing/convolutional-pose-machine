#ifndef THREADFROM_H
#define THREADFROM_H
#include <QThread>
#include<QTimer>
class ThreadFunction : public QObject
{
	Q_OBJECT
signals :
	//void message(const QString& info);
	//void progress_1();
	void message();
public:
	ThreadFunction(){};
	ThreadFunction(QObject *parent);
	~ThreadFunction();
public slots:
	void send_message();

private:
	int m_runCount;

};

#endif // THREADFROM_H
