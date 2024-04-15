/*
	This file is part of Nanos6 and is licensed under the terms contained in the COPYING file.

	Copyright (C) 2020-2023 Barcelona Supercomputing Center (BSC)
*/

#ifndef INSTRUMENT_NULL_WORKERTHREAD_HPP
#define INSTRUMENT_NULL_WORKERTHREAD_HPP


#include "instrument/api/InstrumentWorkerThread.hpp"

namespace Instrument {

	void workerThreadSpins();
	void workerThreadObtainedTask();
	void workerProgressing();
	void workerResting();
	void workerAbsorbing();
	void workerThreadBusyWaits();
	void workerThreadBegin();
	void workerThreadEnd();
	void enterHandleTask();
	void exitHandleTask();
	void enterSwitchTo();
	void exitSwitchTo();
	void enterSuspend();
	void exitSuspend();
	void enterResume();
	void exitResume();
	void enterSpongeMode();
	void exitSpongeMode();
}

#endif // INSTRUMENT_NULL_WORKERTHREAD_HPP

