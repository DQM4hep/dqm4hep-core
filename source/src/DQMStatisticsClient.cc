/*
 *
 * DQMStatisticsClient.cc source template automatically generated by a class generator
 * Creation date : lun. d�c. 14 2015
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

// -- dqm4hep headers
#include "dqm4hep/DQMStatisticsClient.h"

namespace dqm4hep
{

DQMStatisticsClient::DQMStatisticsClient(const std::string &baseServiceName) :
		m_lastStatsTimestamp(0),
		m_rate(0.f),
		m_meanStats(0.f),
		m_lastStatistics(0)
{
	m_pLastUpdateTimeInfo = new DimUpdatedInfo((baseServiceName + "/LAST_UPDATE_TIME").c_str(), static_cast<int>(0), this);
	m_pRateInfo = new DimUpdatedInfo((baseServiceName + "/RATE").c_str(), static_cast<float>(0.f), this);
	m_pMeanStatsInfo = new DimUpdatedInfo((baseServiceName + "/MEAN_STATS").c_str(), static_cast<float>(0.f), this);
	m_pLastUpdateStatisticsInfo = new DimUpdatedInfo((baseServiceName + "/LAST_UPDATE_STATS").c_str(), static_cast<int>(0), this);

	pthread_mutex_init(&m_mutex, NULL);
}

//-------------------------------------------------------------------------------------------------

DQMStatisticsClient::~DQMStatisticsClient() 
{
	delete m_pLastUpdateTimeInfo;
	delete m_pRateInfo;
	delete m_pMeanStatsInfo;
	delete m_pLastUpdateStatisticsInfo;

	pthread_mutex_destroy(&m_mutex);
}

//-------------------------------------------------------------------------------------------------

int DQMStatisticsClient::getLastUpdateTime() const
{
	pthread_mutex_lock(&m_mutex);
	int lastStatsTimestamp = m_lastStatsTimestamp;
	pthread_mutex_unlock(&m_mutex);

	return lastStatsTimestamp;
}

//-------------------------------------------------------------------------------------------------

float DQMStatisticsClient::getRate() const
{
	pthread_mutex_lock(&m_mutex);
	int rate = m_rate;
	pthread_mutex_unlock(&m_mutex);

	return rate;
}

//-------------------------------------------------------------------------------------------------

float DQMStatisticsClient::getMeanStats() const
{
	pthread_mutex_lock(&m_mutex);
	int meanStats = m_meanStats;
	pthread_mutex_unlock(&m_mutex);

	return meanStats;
}

//-------------------------------------------------------------------------------------------------

float DQMStatisticsClient::getLastStats() const
{
	pthread_mutex_lock(&m_mutex);
	int lastStatistics = m_lastStatistics;
	pthread_mutex_unlock(&m_mutex);

	return lastStatistics;
}

//-------------------------------------------------------------------------------------------------

void DQMStatisticsClient::updated()
{
	/* nop */
}

//-------------------------------------------------------------------------------------------------

void DQMStatisticsClient::infoHandler()
{
	DimInfo *pCurrentInfo = getInfo();

	pthread_mutex_lock(&m_mutex);

	if(pCurrentInfo == m_pLastUpdateTimeInfo)
	{
		m_lastStatsTimestamp = pCurrentInfo->getInt();
	}
	else if(pCurrentInfo == m_pRateInfo)
	{
		m_rate = pCurrentInfo->getFloat();
	}
	else if(pCurrentInfo == m_pMeanStatsInfo)
	{
		m_meanStats = pCurrentInfo->getFloat();
	}
	else if(pCurrentInfo == m_pLastUpdateStatisticsInfo)
	{
		m_lastStatistics = pCurrentInfo->getInt();
	}

	pthread_mutex_unlock(&m_mutex);

	this->updated();
}


} 

