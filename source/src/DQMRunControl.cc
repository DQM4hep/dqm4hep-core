  /// \file DQMRunControl.cc
/*
 *
 * DQMRunControl.cc source template automatically generated by a class generator
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

#include "dqm4hep/DQMRunControl.h"
#include "dqm4hep/DQMRun.h"

namespace dqm4hep
{

//-------------------------------------------------------------------------------------------------

DQMRunControl::DQMRunControl() :
		m_runState(STOPPED_STATE),
		m_pCurrentRun(NULL)
{
 /* nop */
}

//-------------------------------------------------------------------------------------------------

DQMRunControl::~DQMRunControl() 
{
	if(isRunning())
		endCurrentRun();
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMRunControl::startNewRun(DQMRun *pRun)
{
	if(NULL == pRun)
		return STATUS_CODE_INVALID_PTR;

	if(isRunning())
		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, endCurrentRun());

	m_pCurrentRun = pRun;
	m_runState = RUNNING_STATE;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMRunControl::startNewRun(int runNumber, const std::string &description, const std::string &detectorName)
{
	if(isRunning())
		RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, endCurrentRun());

	m_pCurrentRun = new DQMRun(runNumber, description, detectorName);
	m_runState = RUNNING_STATE;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMRunControl::endCurrentRun()
{
	if(!isRunning())
		return STATUS_CODE_SUCCESS;

	m_runState = STOPPED_STATE;

	if(NULL != m_pCurrentRun)
		delete m_pCurrentRun;

	m_pCurrentRun = NULL;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

int DQMRunControl::getCurrentRunNumber() const
{
	if(NULL != m_pCurrentRun)
		return m_pCurrentRun->getRunNumber();
	else
		return 0;
}

//-------------------------------------------------------------------------------------------------

DQMRun *DQMRunControl::getCurrentRun() const
{
	return m_pCurrentRun;
}

//-------------------------------------------------------------------------------------------------

DQMState DQMRunControl::getRunState() const
{
	return m_runState;
}

//-------------------------------------------------------------------------------------------------

bool DQMRunControl::isRunning() const
{
	return m_runState == RUNNING_STATE;
}

//-------------------------------------------------------------------------------------------------

} 

