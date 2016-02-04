  /// \file DQMRunControl.h
/*
 *
 * DQMRunControl.h header template automatically generated by a class generator
 * Creation date : mar. oct. 7 2014
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMRUNCONTROL_H
#define DQMRUNCONTROL_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"

namespace dqm4hep
{

class DQMRun;

/** DQMRunListener class
 */
class DQMRunListener
{
public:
	/** Destructor
	 */
	virtual ~DQMRunListener() {}

	/** Called back when a run is started
	 */
	virtual void onStartOfRun(DQMRun *const pRun) = 0;

	/** Called back when a run ends
	 */
	virtual void onEndOfRun(const DQMRun *const pRun) = 0;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/** DQMRunControl class
 */ 
class DQMRunControl
{
public:
	/** Constructor
	 */
	DQMRunControl();

	/** Constructor with name
	 */
	DQMRunControl(const std::string &runControlName);

	/** Destructor
	 */
	virtual ~DQMRunControl();

	/** Set the run control name. This stops the current before
	 */
	void setRunControlName(const std::string &runControlName);

	/** Get the run control name
	 */
	const std::string &getRunControlName() const;

	/** Create a new run from a DQMRun
	 *  The run control is the owner the run
	 */
	StatusCode startNewRun(DQMRun *pRun);

	/** Create a new run.
	 *  End the current run if running
	 */
	StatusCode startNewRun(int runNumber, const std::string &description = "", const std::string &detectorName = "");

	/** End the current run
	 */
	StatusCode endCurrentRun();

	/** Get the current run number
	 */
	int getCurrentRunNumber() const;

	/** Get the current run header
	 */
	DQMRun *getCurrentRun() const;

	/** Get the run state (running or not)
	 */
	DQMState getRunState() const;

	/** Whether a run has been started.
	 */
	bool isRunning() const;

	/** Add a listener to the run control
	 */
	void addListener(DQMRunListener *pListener);

	/** Remove a listener from the run control
	 */
	void removeListener(DQMRunListener *pListener);

protected:
	DQMState                         m_runState;
	DQMRun                          *m_pCurrentRun;
	std::string                      m_runControlName;
	std::vector<DQMRunListener *>    m_listeners;
}; 

} 

#endif  //  DQMRUNCONTROL_H
