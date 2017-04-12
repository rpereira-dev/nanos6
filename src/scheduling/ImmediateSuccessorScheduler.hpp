#ifndef IMMEDIATE_SUCCESSOR_SCHEDULER_HPP
#define IMMEDIATE_SUCCESSOR_SCHEDULER_HPP


#include <deque>
#include <vector>

#include "SchedulerInterface.hpp"
#include "lowlevel/SpinLock.hpp"
#include "executors/threads/CPU.hpp"


class Task;


class ImmediateSuccessorScheduler: public SchedulerInterface {
	SpinLock _globalLock;
	
	std::deque<Task *> _readyTasks;
	std::deque<Task *> _unblockedTasks;
	
	std::deque<CPU *> _idleCPUs;
	
	inline CPU *getIdleCPU();
	inline Task *getReplacementTask(CPU *computePlace);
	inline void cpuBecomesIdle(CPU *cpu);
	
public:
	ImmediateSuccessorScheduler();
	~ImmediateSuccessorScheduler();
	
	ComputePlace *addReadyTask(Task *task, ComputePlace *computePlace, ReadyTaskHint hint);
	
	void taskGetsUnblocked(Task *unblockedTask, ComputePlace *computePlace);
	
	Task *getReadyTask(ComputePlace *computePlace, Task *currentTask = nullptr);
	
	ComputePlace *getIdleComputePlace(bool force=false);
	
	void disableComputePlace(ComputePlace *computePlace);
};


#endif // IMMEDIATE_SUCCESSOR_SCHEDULER_HPP

