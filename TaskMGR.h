#pragma once
#include "PreCompile.h"

#include "Object.h"

class TaskMGR
{
	SINGLE(TaskMGR);

private:
	vector<Task>	m_TASK;

	vector<Object*>	m_GARBAGE;

public:
	void AddTask(const Task& _task)
	{
		m_TASK.push_back(_task);
	}

public:
	void Tick();
};