#include "threadfrom.h"

ThreadFunction::ThreadFunction(QObject *parent)
{
  
}

ThreadFunction::~ThreadFunction()
{
	
}
void ThreadFunction::send_message()
{
	emit message();
}
